#pragma once
#include "../Components/GameComponent.h"
#include "../GameDataId.h"

namespace Game
{
	/// [tdbe] Attributes are technically just components and for the record there's nothing in our setup that prevents them from storing small data or references.
	/// [RequireOwnerRestriction(1)]
	struct GameAttribute : public GameComponent
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

		/// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
		virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
		{
			#ifdef DEBUG_VERBOSE
			if(!unsafe)
				util::DebugLog("[Attribute]\t clearing this item: " + this->id.PrintGlobalUID());
			#endif
			GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
		};

		/// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
		virtual void NotifyItemVersionChanged() override
		{
			GameComponent::NotifyItemVersionChanged();
		};

		/// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
		GameAttribute(GameDataId::ID id = {}, GameDataId::ID owner = {})
		{
		};
		~GameAttribute() {};

	  private:

	};
} // namespace Game
