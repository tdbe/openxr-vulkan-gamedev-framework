#pragma once
#include <taskflow.hpp>
#include <vector>
#include "SystemBase.h"
#include "../GameData/GameData.h"
#include "../GameData/Components/CTransform.h"
#include "../GameData/Components/CParent.h"
#include "../GameData/Components/CChildren.h"
#include "../GameData/Entities/GameEntityObject.h"

namespace Game
{
    /// [tdbe] ECS transform hierarchy propagation system, ie the thing that allows the <see cref="Transform"/> of child entities to move / scale / rotate with the transform of the parent.
    /// The full traversal happens every frame but it skips disabled entities.
    /// I do a cache-coherent & multithreaded BFS traversal from root entities all the way to the leaves. Each chunk on each level of the (sub)tree is processed by a job (task). Each subtask knows what parent to look for in that chunk.
    /// Uses taskflow with dynamic subflows and a shared executor. Translation: we can spawn tasks from other tasks recursively and they are all monitored by an executor that assigns work to the appropriate amount of jobs for the CPU threads our system has.
    ///
    /// [tdbe] TODO: The downside to the current approach is it creates a taskflow subflow representation of essentially your entire scene graph. So, overhead, every update.
    /// I'm yolo-creating subtasks from subtasks because I wanted to avoid collecting and creating level-order arrays entities and components.
    /// It's a tree traversal so it needs recursion, but maybe we can build a more permanent and still cache friendly (and updateable) spatial partitioning scheme for transform propagation.
    struct SystemTransformPropagation : SystemBase
    {
        #ifdef DEBUG_THREADS
            size_t framesToDebug = 1;
        #endif
        
        virtual void OnCreate()
        {
            
        };
        
        /// [tdbe] Update all transforms in the world by traversing the hierarchy from roots down
        virtual void OnUpdate()
        {
            // (the main entry point for the transform propagation system).
            RecursiveEntityTraversalTasksFromRootEntities();
        };

        virtual void OnDestroy()
        {
            
        };

      private:
        tf::Executor m_executor;
        tf::Taskflow m_taskflow;
        
        /// [tdbe] We did a BFS search to get a root or parent entity.
        /// Now we also need a job to find all entities that have this entity as a parent, and for each one
        /// update its <see cref="Transform"/> component to propagate the parent values into the local.
        void DoEntityWork(tf::Subflow& subflow, const auto& entitySubpool, const GameEntityObject* entity, GameEntity* parentEntity)
        {
            if(parentEntity != nullptr)// we're not in the special initial case when we're a root
            {
                CTransform* transform = entity->GetComponentByTypeIndex<CTransform>();
                CTransform* parentTransform = parentEntity->GetComponentByTypeIndex<CTransform>();
                util::Posef parentWorldPose = parentTransform->GetWorldPose();

                transform->OnParentWorldPoseUpdated(parentWorldPose);
            }
            
            #ifdef DEBUG_THREADS
            // (only use a couple chunks and not too many entities if you want to print from here :))
            /*
            if(framesToDebug > 0)
            {
                util::DebugLog("[Game][SystemTransformPropagation][OnUpdate][DoEntityWork][Taskflow Graph Structure]\tframe: "+util::ToString(framesToDebug)+"; name: "+m_taskflow.name()+"; subflow graph size:"+util::ToString(subflow.graph.size())+" ┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬");
                util::DebugLog(m_taskflow.dump());
                util::DebugLog("[Game][SystemTransformPropagation][OnUpdate][DoEntityWork][Taskflow Graph Structure]\tframe: "+util::ToString(framesToDebug)+"; name: "+m_taskflow.name()+"; subflow graph size:"+util::ToString(subflow.graph.size())+" ┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴");
            }*/
            #endif
            
            // [tdbe] now process further down the hierarchy:
            const GameEntityObject* newRootEntity = entity;
            ChunkDispatcherForEntityHierarchyProcessing(subflow, entitySubpool, newRootEntity);
        };
        
        /// [tdbe] Job over elements of a chunk.
        /// [tdbe] The chunkIndex and count aligns across subpools, and subpool chunks of same index are next to each other (cpu cache coherent).
        /// (NOTE: but indexes within chunks don't necessarily align cross subpools! (not enforced, instead use e.g. <see cref="entity.GetComponentByTypeIndex()"/>))
        template<typename SubpoolT> void ArchetypeChildEntityJobInChunk(
            tf::Subflow& subflow,
            size_t chunkIndex,
            // [tdbe] the actual explicit unabiguous type (depending on the target pool) looks like this: 
            // const typename TiledGameDataPools<GameEntityObject, Transform, CParent, CChildren, CBounds>
            //      ::SubpoolTiledVector<GameEntityObject>& entitySubpool
            const SubpoolT& entitySubpool, 
            const GameEntityObject* parentEntityWeSeek)
        {
            for (size_t i = 0; i < entitySubpool.items[chunkIndex].size(); i++)
            {
                const GameEntityObject* entity = entitySubpool.items[chunkIndex][i];
            #pragma region Our "Entity Query"
                if (!entity || entity->id.IsCleared() || !entity->IsEnabled())
                    continue;
                bool archetypePass = entity->MatchesArchetype(
                    GameData::TypeUIDs.TRANSFORM_COMPONENTS | GameData::TypeUIDs.PARENT_COMPONENTS);
                if(!archetypePass)
                    continue;
                const CParent* parentComp = entity->GetComponentByTypeIndex<CParent>();
                if(!parentComp)
                    continue;
                GameEntity* parentEntity = parentComp->GetParent();
                // [tdbe] is the parent equal to our target
                if(!parentEntity || !parentEntity->IsEnabled() || parentEntity->id != parentEntityWeSeek->id)
                    continue;
            #pragma endregion Our "Entity Query"
                // [tdbe] NOTE: <See cref="tf::Subflow"/> .emplace operations are not thread safe if called concurrently from multiple threads on the same subflow.
                // This is why every time that I do an iteration and/or traverse a level deeper, I create a new child subflow.
                subflow.emplace([this, &entitySubpool, entity, parentEntity](tf::Subflow& child_subflow) {
                    DoEntityWork(child_subflow, entitySubpool, entity, parentEntity);
                });
            }
        };
        
        /// [tdbe] The recursive job spawning is handled using taskflow dynamic subflow.
        /// Parent tasks continue and complete without waiting for children tasks to finish. Uses <see cref="tf::Subflow"/>.
        template<typename SubpoolT>
        void ChunkDispatcherForEntityHierarchyProcessing(tf::Subflow& subflow, 
                                                        const SubpoolT& entitySubpool, const GameEntityObject* rootEntity)
        {
            for (uint32_t chunkIndex = 0; chunkIndex <= entitySubpool.MaxUsedTile(); chunkIndex++)
            {
                // [tdbe] NOTE: <See cref="tf::Subflow"/> .emplace operations are not thread safe if called concurrently from multiple threads on the same subflow.
                // This is why every time that I do an iteration and/or traverse a level deeper, I create a new child subflow.
                subflow.emplace([this, chunkIndex, &entitySubpool, rootEntity](tf::Subflow& childSubflow) 
                {
                    ArchetypeChildEntityJobInChunk(childSubflow, chunkIndex, entitySubpool, rootEntity);
                });
            }
        };
        
        /// [tdbe] Job over elements of a chunk.
        /// [tdbe] The chunkIndex and count aligns across subpools, and subpool chunks of same index are next to each other (cpu cache coherent).
        /// (NOTE: but indexes within chunks don't necessarily align cross subpools! (not enforced, instead use e.g. <see cref="entity.GetComponentByTypeIndex()"/>))
        template<typename SubpoolT> void ArchetypeRootEntityJobInChunk(
            tf::Subflow& subflow,
            size_t chunkIndex,
            // [tdbe] the actual explicit unabiguous type (depending on the target pool) looks like this: 
            // const typename TiledGameDataPools<GameEntityObject, Transform, CParent, CChildren, CBounds>
            //      ::SubpoolTiledVector<GameEntityObject>& entitySubpool
            const SubpoolT& entitySubpool)
        {
            // [tdbe] run tasks to find and process all root entities
            for (size_t i = 0; i < entitySubpool.items[chunkIndex].size(); i++)
            {
                const GameEntityObject* entity = entitySubpool.items[chunkIndex][i];
            #pragma region Our "Entity Query"
                if (!entity || entity->id.IsCleared() || !entity->IsEnabled())
                    continue;
                bool archetypePass = entity->MatchesArchetype(
                    GameData::TypeUIDs.TRANSFORM_COMPONENTS | GameData::TypeUIDs.PARENT_COMPONENTS);
                if(!archetypePass)
                    continue;
                const CParent* parentComp = entity->GetComponentByTypeIndex<CParent>();
                if(!parentComp)
                    continue;
                GameEntity* parentEntity = parentComp->GetParent();
                // [tdbe] this is how we check if the parent entity exists and is not expired
                if(parentEntity)
                    continue;
            #pragma endregion Our "Entity Query"
                // [tdbe] NOTE: <See cref="tf::Subflow"/> .emplace operations are not thread safe if called concurrently from multiple threads on the same subflow.
                // This is why every time that I do an iteration and/or traverse a level deeper, I create a new child subflow.
                subflow.emplace([this, &entitySubpool, entity, parentEntity](tf::Subflow& childSubflow) {
                    DoEntityWork(childSubflow, entitySubpool, entity, parentEntity);
                });
            }
        };
        
        /// [tdbe] Root entity job: runs one taskflow job per chunk in the entity subpool.
        /// Then recurses through children until the final leaf.
        /// NOTE: this function waits for all jobs to complete before returning.
        void RecursiveEntityTraversalTasksFromRootEntities()
        {
            m_taskflow = tf::Taskflow(); // Clear and reset every Update.            
            const auto& entitySubpool = GameData::Instance().mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>();

            for (uint32_t chunkIndex = 0; chunkIndex <= entitySubpool.MaxUsedTile(); chunkIndex++)
            {
                // [tdbe] add a task to the taskflow graph
                m_taskflow.emplace([this, chunkIndex, &entitySubpool](tf::Subflow& subflow) {
                    ArchetypeRootEntityJobInChunk(subflow, chunkIndex, entitySubpool);
                });
            }
            
            #ifdef DEBUG_THREADS
            if(framesToDebug > 0)
            {
                util::DebugLog("\n[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]\t\tframe: "+util::ToString(framesToDebug)+"; name: "+m_taskflow.name()+"; graph size:"+util::ToString(m_taskflow.num_tasks())+" ╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦");
                util::DebugLog("[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]\t\t┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬");
                util::DebugLog(m_taskflow.dump());
                util::DebugLog("[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]\t\t┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴");
            }
            #endif
            
            m_executor.run(m_taskflow).wait();
            
            #ifdef DEBUG_THREADS
            if(framesToDebug > 0)
            {
                util::DebugLog("[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]\t\tframe: "+util::ToString(framesToDebug)+"; name: "+m_taskflow.name()+"; graph size:"+util::ToString(m_taskflow.num_tasks())+" ╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩\n");
                framesToDebug--;
            }
            #endif
        };
    };
} // namespace Game