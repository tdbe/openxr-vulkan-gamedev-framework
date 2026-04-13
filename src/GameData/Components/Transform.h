#pragma once
#include "GameComponent.h"
#include "../Entities/GameEntityObject.h"
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
        
        /// [tdbe] Automatically updates the <see cref="localPose"/>. There is no stored worldPose. 
        /// <see cref="localPose"/> is king + the <see cref="cachedParentWorldPose"/>, because of the <see cref="SystemTransformPropagation"/>.
        void SetWorldPose(util::Posef newWorldPose)
        {
            if(!isParentedDetected)
            {
                localPose.position = newWorldPose.position;
                localPose.scale = newWorldPose.scale;
                localPose.orientation = newWorldPose.orientation;
                return;
            }
            // [tdbe] I'm not defending against zero scale or number abuse
            
            glm::vec3 inverseScale = glm::vec3(1.0f) / cachedParentWorldPose.scale;
            glm::quat inverseRotation = glm::inverse(cachedParentWorldPose.orientation);
                                                            
            localPose.position = inverseScale * inverseRotation * (newWorldPose.position - cachedParentWorldPose.position);
            localPose.scale = inverseScale * newWorldPose.scale;
            localPose.orientation = inverseRotation * newWorldPose.orientation;
            // [tdbe] whenever you create quaternions from not-quaternions, make sure to normalize them to drift and distortions
        };
        
        /// [tdbe] actually computes the world pose from the cachedParentWorldPose and our localPose
        util::Posef GetWorldPose() const
        {
            if(!isParentedDetected)
            {
                return localPose;
            }
            
            util::Posef worldPose;
            worldPose.position = cachedParentWorldPose.position + 
                                cachedParentWorldPose.orientation * (cachedParentWorldPose.scale * localPose.position);
            worldPose.scale = cachedParentWorldPose.scale * localPose.scale;
            worldPose.orientation = cachedParentWorldPose.orientation * localPose.orientation;
            // [tdbe] whenever you create quaternions from not-quaternions, make sure to normalize them to drift and distortions
            return worldPose;
        };

        /// [tdbe] Automatically localPose. There is no stored worldMatrix. 
        /// <see cref="localPose"/> is king + the <see cref="cachedParentWorldPose"/>, because of the <see cref="SystemTransformPropagation"/>.
        void SetWorldMatrix(glm::mat4 newWorldMatrix)
        {
            util::Posef newWorldPose = util::matrixToPose(newWorldMatrix);
            SetWorldPose(newWorldPose);
        };

        /// [tdbe] Automatically fetched from  <see cref="localPose"/> and <see cref="cachedParentWorldPose"/> on the spot.
        glm::mat4 GetWorldMatrix()
        {
            return util::poseToMatrix(GetWorldPose());
        };
        
        /// [tdbe] param to automatically update worldPose
        void SetLocalPose(util::Posef newLocalPose)
        {
            localPose = newLocalPose;
        };
        
        /// [tdbe] Updates the localPose, but behaves as if the object wasn't parented. As if you "locked" the child object in place while moving the parent. 
        /// There is no stored worldPose. <see cref="localPose"/> is king + the <see cref="cachedParentWorldPose"/>, because of the <see cref="SystemTransformPropagation"/>.
        void LockedParentWorldPoseUpdated(util::Posef newParentWorldPose)
        {
            util::Posef currentWorldPose = GetWorldPose();
            cachedParentWorldPose = newParentWorldPose;
            isParentedDetected = true;
            SetWorldPose(currentWorldPose);
        }
        
        /// [tdbe] Updates the localPose. There is no stored worldPose. 
        /// <see cref="localPose"/> is king + the <see cref="cachedParentWorldPose"/>, because of the <see cref="SystemTransformPropagation"/>.
        void OnParentWorldPoseUpdated(util::Posef newParentWorldPose)
        {
            cachedParentWorldPose = newParentWorldPose;
            isParentedDetected = true;
        };
        
        /// [tdbe] sets the localPose to worldPose
        void OnUnparent()
        {
            localPose = GetWorldPose();
            cachedParentWorldPose = util::makeIdentity();
            isParentedDetected = false;
        };
        
        void DebugPrintTransformValues()
        {
            GameEntityObject* owner = (GameEntityObject*)GetOwner();
            float angle;
            glm::vec3 axis;
            util::quaternionToAngleAxis(localPose.orientation, angle, axis);
            util::DebugLog("[Transform]["+owner->GetName()+"] position: "+util::ToString(localPose.position)+"; scale: "+util::ToString(localPose.scale)+"; orientation: "+util::ToString(localPose.orientation)+"; angle: "+util::ToString(angle)+"; axis: "+util::ToString(axis));
        };
        
        util::Posef GetLocalPose() const
        {
            return localPose;
        };
        
        /// [tdbe] automatically updates localPose. There is no stored localMatrix. 
        /// <see cref="localPose"/> is king + the <see cref="cachedParentWorldPose"/>, because of the <see cref="SystemTransformPropagation"/>.
        void SetLocalMatrix(glm::mat4 newLocalMatrix)
        {
            util::Posef newLocalPose = util::matrixToPose(newLocalMatrix);
            localPose = newLocalPose;
        };

        /// [tdbe] automatically updates localPose and worldPose on the spot
        glm::mat4 GetLocalMatrix()
        {
            return util::poseToMatrix(localPose);
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: accessing this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
        {
            #ifdef DEBUG_VERBOSE
            if(!unsafe)
                util::DebugLog("[Component][Transform]\t clearing this item: " + this->id.PrintGlobalUID());
            #endif
            GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            cachedParentWorldPose = util::makeIdentity();
            isParentedDetected = false;
            localPose = util::makeIdentity();
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: accessing this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override 
        {
            GameComponent::NotifyItemVersionChanged();
        };

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorlds"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        Transform(GameDataId::ID id = {}, GameDataId::ID owner = {}) : GameComponent(id, owner)
        {
        };
        ~Transform(){};

	  private:
        /// [tdbe] losslessly stores position, rotation, and scale (matrixes degrade over time)
        /// [tdbe] coordinate system: Y is up, Z is forward
        util::Posef cachedParentWorldPose = util::makeIdentity();
                
        /// [tdbe] losslessly stores position, rotation, and scale (matrixes degrade over time)
        /// [tdbe] coordinate system: Y is up, Z is forward
        util::Posef localPose = util::makeIdentity();
        
        bool isParentedDetected = false;
	};

} // namespace Game