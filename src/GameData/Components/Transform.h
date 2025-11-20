#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"

namespace Game
{
	/// [tdbe] Matrix information for Translate Rotate Scale of object
    /// [RequireOwnerRestriction(1)]
	struct Transform : public GameComponent
	{
        GameEntity* GetOwner() const
        {
            std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
            GameEntity* found = nullptr;
            for (int i = 0; i < ownerIDs.size(); i++)
            {
                found = GameData::Instance().GetEntity(ownerIDs[i]);
                break;
            }
            return found;
        };

        void SetWorldMatrix(glm::mat4 worldMatrix)
        {
            this->worldMatrix = worldMatrix;
        };

        glm::mat4 GetWorldMatrix() const
        {
            return worldMatrix;
        };

        glm::mat4* GetWorldMatrixPtr()
        {
            return &worldMatrix;
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
        {
            util::DebugLog("[Component][Transform]\t clearing this item: " + this->id.PrintGlobalUID());
            GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            worldMatrix = worldMatrix = glm::mat4(1.0f);
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
        // [tdbe] coordinate system: Y is up, Z is forward
        glm::mat4 worldMatrix = glm::mat4(1.0f);
	};

} // namespace Game