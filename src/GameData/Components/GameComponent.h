#pragma once
#include <string>
#include <vector>   

#include "../GameDataId.h"
#include "../GameData.h"

namespace Game
{
    struct GameEntityObject;// [tdbe] newb-friendly-note: predeclaring here because we're only storing a pointer to the owner (and we need to avoid circular dependency)

    struct GameComponent : GameDataId
    {
      public:
        std::vector<GameDataId::ID> GetOwnerIDs() const;
        size_t CountValidOwners() const;

        void AddOwnerId(GameDataId::ID owner);
        void ClearOwnerId(GameDataId::ID owner);
        void ClearOwnerIDs();

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        /// Clear this item (and mark it as Free in its pool).
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override;
        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override;

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        GameComponent(GameDataId::ID id = {}, GameDataId::ID owner = {});
        virtual ~GameComponent();

      private:
        /// [tdbe] References for immediate/scripting convenience. A component may have maxint owners or even 0 owners (e.g. a lone material).
        /// Note: must be marked as free on <see cref="NotifyItemCleared"/>.
        /// todo: should enforce even at ancestor level: some components must (really should) have only one owner... like the Light or the Transform.
        std::vector<GameDataId::ID> owners;
        /// [tdbe] Also find anyone that caches our ID and clear that also (e.g. our owners).
        /// Note: if you wanted to be maximally efficient clearing millions of items, you wouldn't hop around memory with this function, you'd instead 
        /// construct some global command buffers marking all the entities and all the components the game wants to clear on this frame, 
        /// and then run a sync point with a job on the buffers coherently contiguously.
        void ClearItemDependencies();
    };
} // namespace Game