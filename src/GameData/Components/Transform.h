#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"

namespace Game
{
	/// [tdbe] Matrix & Pose information, local and world, for Translate Rotate Scale of Entity.
    /// [tdbe] TODO: could use an "isDirty" (TRS changed) for <see cref="SystemTRSParentingPropagation"/>", but realistically / ecs / jobs wise it would need to manage timestamps.
    /// [RequireOwnerRestriction(1)]
	struct Transform : public GameComponent
	{
        GameEntity* GetOwner() const
        {
            std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
            GameEntity* found = nullptr;
            if(!ownerIDs[0].IsCleared())
            {
                found = GameData::Instance().GetEntity(ownerIDs[0]);
            }
            return found;
        };
        
        /// [tdbe] automatically updates localPose
        void SetWorldPose(util::Posef newWorldPose)
        {
            UpdateLocalPoseFromDeltaWorldPose(newWorldPose);
            worldPose = newWorldPose;
        };
        
        util::Posef GetWorldPose() const
        {
            return worldPose;
        };

        /// [tdbe] automatically updates worldPose and localPose on the spot
        void SetWorldMatrix(glm::mat4 newWorldMatrix)
        {
            util::Posef newWorldPose = util::matrixToPose(newWorldMatrix);
            UpdateLocalPoseFromDeltaWorldPose(newWorldPose);
            worldMatrix = newWorldMatrix;
            worldPose = newWorldPose;
        };

        /// [tdbe] automatically fetched from worldPose and localPose on the spot
        glm::mat4 GetWorldMatrix()
        {
            UpdateWorldMatrixFromWorldPose();
            return worldMatrix;
        };
        
        /// [tdbe] automatically updates worldPose
        void SetLocalPose(util::Posef newLocalPose)
        {
            UpdateWorldPoseFromDeltaLocalPose(newLocalPose);
            localPose = newLocalPose;
        };
        
        /// [tdbe] sets the localPose without changing the worldPose
        void ParentTo(util::Posef parentWorldPose)
        {
            localPose.position = worldPose.position - parentWorldPose.position;
            localPose.scale = worldPose.scale / parentWorldPose.scale;
            localPose.orientation = worldPose.orientation * glm::inverse(parentWorldPose.orientation);
        };
        
        /// [tdbe] sets the localPose to worldPose
        void Unparent()
        {
            localPose = worldPose;
        };
        
        util::Posef GetLocalPose() const
        {
            return localPose;
        };
        
        /// [tdbe] automatically updates localPose and worldPose on the spot
        void SetLocalMatrix(glm::mat4 newLocalMatrix)
        {
            util::Posef newLocalPose = util::matrixToPose(newLocalMatrix);
            UpdateWorldPoseFromDeltaLocalPose(newLocalPose);
            localMatrix = newLocalMatrix;
            localPose = newLocalPose;
        };

        /// [tdbe] automatically updates localPose and worldPose on the spot
        glm::mat4 GetLocalMatrix()
        {
            UpdateLocalMatrixFromLocalPose();
            return localMatrix;
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
        {
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[Component][Transform]\t clearing this item: " + this->id.PrintGlobalUID());
            #endif
            GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            worldPose = util::makeIdentity();
            worldMatrix = glm::mat4(1.0f);
            localPose = util::makeIdentity();
            localMatrix = glm::mat4(1.0f);
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override 
        {
            GameComponent::NotifyItemVersionChanged();
        };

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        Transform(GameDataId::ID id = {}, GameDataId::ID owner = {}) : GameComponent(id, owner)
        {
        };
        ~Transform(){};

	  private:
        void UpdateWorldMatrixFromWorldPose()
        {
            worldMatrix = util::poseToMatrix(worldPose);
        }
        
        void UpdateWorldPoseFromWorldMatrix()
        {
            worldPose = util::matrixToPose(worldMatrix);
        }
        
        void UpdateLocalPoseFromDeltaWorldPose(util::Posef newWorldPose)
        {
            localPose.position += worldPose.position - newWorldPose.position;
            localPose.scale *= newWorldPose.scale / worldPose.scale;
            glm::quat diff = worldPose.orientation * glm::inverse(newWorldPose.orientation);
            localPose.orientation = diff * localPose.orientation;
        }
        
        void UpdateWorldPoseFromDeltaLocalPose(util::Posef newLocalPose)
        {
            worldPose.position += localPose.position - newLocalPose.position;
            worldPose.scale *= newLocalPose.scale / localPose.scale;
            glm::quat diff = localPose.orientation * glm::inverse(newLocalPose.orientation);
            worldPose.orientation = diff * worldPose.orientation;
        }
        
        void UpdateLocalPoseFromLocalMatrix()
        {
            localPose = util::matrixToPose(localMatrix);
        }
        
        void UpdateLocalMatrixFromLocalPose()
        {
            localMatrix = util::poseToMatrix(localPose);
        }
      
        /// [tdbe] TRS. Created from the worldPose and master-stored into the worldPose (matrixes degrade over time)
        /// [tdbe] coordinate system: Y is up, Z is forward
        glm::mat4 worldMatrix = glm::mat4(1.0f);
        
        /// [tdbe] losslessly stores position, rotation, and scale
        /// [tdbe] coordinate system: Y is up, Z is forward
        util::Posef worldPose = util::makeIdentity();
        
        /// [tdbe] TRS. Created from the localPose and master-stored into the localPose (matrixes degrade over time)
        /// [tdbe] coordinate system: Y is up, Z is forward
        glm::mat4 localMatrix = glm::mat4(1.0f);
        
        /// [tdbe] losslessly stores position, rotation, and scale
        /// [tdbe] coordinate system: Y is up, Z is forward
        util::Posef localPose = util::makeIdentity();
	};

} // namespace Game