#pragma once
#include <string>
#include <vector>   

#include "../GameDataId.h"
#include "../GameData.h"

namespace Game
{
    struct GameEntityObject;// [tdbe] newb-friendly-note: predeclaring here because we're only storing a pointer to the owner (and we need to avoid circular dependency)

    /// [tdbe] Note on chunking, memory layout, cache: there's no distinction in here between shared components and non-shared, so the expandable data ie "owners" is a pointer to somewhere on the heap.
    struct GameComponent : GameDataId
    {
      public:
        /// [tdbe] ECS Note: serve a const reference to unique heap data, but owners can change (in addition to some version ids maybe becoming outdated). 
        /// [tdbe] Use the owner fetching methods in derived components which return a safe copy,
        /// especially if there isn't a huge amount of owners.
        const std::vector<GameDataId::ID>& GetOwnerIDs() const;
        size_t CountValidOwners() const;

        void AddOwnerId(GameDataId::ID owner);
        void ClearOwnerId(GameDataId::ID owner);
        void ClearOwnerIDs();

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: accessing this should be restricted to <see cref"GameDataPool"/>
        /// Clear this item (and mark it as Free in its pool).
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override;
        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: accessing this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override;

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorlds"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        GameComponent(GameDataId::ID id = {}, GameDataId::ID owner = {});
        virtual ~GameComponent();

      private:
        /// [tdbe] References for immediate/scripting convenience. A component may have maxint owners or even 0 owners (e.g. a lone material).
        /// NOTE: each must be marked as free, e.g. via <see cref="NotifyItemCleared"/>.
        /// todo: should enforce even at ancestor level: some components must (really should) have only one owner... like the Light or the Transform.
        std::unique_ptr<std::vector<GameDataId::ID>> owners;
        /// [tdbe] Also find anyone that caches our ID and clear that also (e.g. our owners).
        /// NOTE: if this entity has dependencies outside of the immediate memory chunks, and you wanted to be maximally efficient clearing millions of items, 
        /// you wouldn't hop around memory with this function, you'd instead construct some global command buffers marking all the entities 
        /// and all the components the game wants to clear on this frame, and then run a sync point with a job on the buffers coherently contiguously.
        void ClearItemDependencies();
    };
} // namespace Game