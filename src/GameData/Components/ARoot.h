#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"

namespace Game
{
	/// [tdbe] Root "Attribute" component for entity hierarchy. Only exists if there is no Parent, and there is at least one Child.
	/// Why have a Root instead of adding/removing Parent (and Children)? Easier to start iterating from only the Root entities, instead of querying by absences.
	/// Related to <see cref="Parent"/>, <see cref="Transform"/>, <see cref="Children"/> and <see cref="SystemTRSParentingPropagation"/>".
	/// [RequireOwnerRestriction(1)]
	struct ARoot : public GameComponent
	{
		GameEntity* GetOwner() const;
				
		/// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
		virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
		{
			#ifdef DEBUG_VERBOSE
			util::DebugLog("[Component][Parent]\t clearing this item: " + this->id.PrintGlobalUID());
			#endif
			GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
		};

		/// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
		virtual void NotifyItemVersionChanged() override
		{
			GameComponent::NotifyItemVersionChanged();
		};

		/// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
		ARoot(GameDataId::ID id = {}, GameDataId::ID owner = {}) : GameComponent(id, owner)
        {
        };
		~ARoot(){};

	  private:
		GameDataId::ID parentId;
	};
} // namespace Game
