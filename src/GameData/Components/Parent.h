#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"

namespace Game
{
	/// [tdbe] Parent component for entity hierarchy. 
	/// Related to <see cref="Transform"/>, <see cref="SystemTRSParentingPropagation"/>", and maybe <see cref="Children"/>.
	/// [RequireOwnerRestriction(1)]
	struct Parent : public GameComponent
	{
		GameEntity* GetOwner() const;
				
		GameEntity* GetParent() const
		{
			if(parentId.IsCleared())
				return nullptr;
			return GameData::Instance().GetEntity(parentId);
		};

		/// [tdbe] ecs performance & racing warning: <param name="ripple"> also calls <see cref="AddOwnerToChildrenOfParent"/></param>
		void SetParent(GameDataId::ID newParentId, bool ripple = true);
		
		/// [tdbe] loop & ecs performance & racing warning: <param name="ripple"> also calls <see cref="RemoveOwnerFromChildrenOfParent"/></param>
		void ClearParent(bool ripple = true);

		/// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
		virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
		{
			#ifdef DEBUG_VERBOSE
			if(!unsafe)
				util::DebugLog("[Component][Parent]\t clearing this item: " + this->id.PrintGlobalUID());
			#endif
			if(!unsafe)
				ClearParent(!unsafe);
			GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
		};

		/// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
		virtual void NotifyItemVersionChanged() override
		{
			GameComponent::NotifyItemVersionChanged();
		};

		/// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
		Parent(GameDataId::ID id = {}, GameDataId::ID owner = {});
		~Parent();

	  private:
		/// [tdbe] ecs performance & racing warning: This is an immediate way to jump to 
		/// the parent entity's Children component and remove itself from that list.
		void RemoveOwnerFromChildrenOfParent();
		
		/// [tdbe] ecs performance & racing warning: This is an immediate way to jump to 
		/// the parent entity's Children component and add itself to that list.
		void AddOwnerToChildrenOfParent();
		
		GameDataId::ID parentId;
	};
} // namespace Game
