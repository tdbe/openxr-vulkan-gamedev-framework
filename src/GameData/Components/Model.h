#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"

namespace Game
{
    /// [tdbe] The mesh is part of a global memory span of indices for the locations of vertices (positions, normals) and
    /// triangle indices on the mesh. <see cref="MeshData"/> 
    /// Here we just store the start location and count of the indices for one mesh.
    /// One mesh/model can be rendered multiple times with different materials etc. 
    /// (If no batching is done) the default strategy is to render one model per draw call, 
    /// but it could be batched per material or more clever ways.
    struct Model final : public GameComponent
    {
      public:
        size_t firstIndex = 0u;
        size_t indexCount = 0u;
        /// [tdbe] object-space mesh bounds; not processed by the entity's Transform Matrix. 
        /// Use the <see cref="Bounds"/> and <see cref="Transform"/> components instead.
        glm::vec3 minPointAABB = glm::vec3(0.0f);
        // [tdbe] object-space mesh bounds; not processed by the entity's Transform Matrix.
        /// Use the <see cref="Bounds"/> and <see cref="Transform"/> components instead.
        glm::vec3 maxPointAABB = glm::vec3(0.0f);

        std::vector<GameEntity*> GetOwners() const
        {
            std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
            std::vector<GameEntity*> foundVec = std::vector<GameEntity*>();
            for (GameDataId::ID entId : ownerIDs)
            {
                auto comp = GameData::Instance().GetEntity(entId);
                foundVec.emplace_back(comp);
            }
            return foundVec;
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
        {
            util::DebugLog("[Component][Model]\t clearing this item: " + this->id.PrintGlobalUID());
            GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            firstIndex = 0u;
            indexCount = 0u;
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override 
        {
            GameComponent::NotifyItemVersionChanged();
        };

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        Model(GameDataId::ID id = {}, GameDataId::ID owner = {}) : GameComponent(id, owner)
        {
        };
        ~Model() {};
    };
}