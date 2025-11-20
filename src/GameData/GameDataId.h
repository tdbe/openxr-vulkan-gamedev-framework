#pragma once
#include <typeindex>
#include <stdint.h>
#include <string>

#include "../Utils/Util.h"

namespace Game
{
    /// [tdbe] <see cref="GameDataPool::GetFirstFree"/>
	struct GameDataId
	{
        static const uint32_t FREE = 0;
        /// [tdbe] Essentially used as a weak reference in the data spans in <see cref="GameData"/>.
        /// globalUIDSeed:index:version and typeIndex
        struct ID 
        {
            /// [tdbe] index in owning vector/array. 2^32, +-2,147,483,647 -> the max number of items in an owning
            /// vector/array is 2,147,483,647.
            int32_t index = 0;
            /// [tdbe] Version 0 means deleted/free/clear/unused.
            /// u2^32, 0 to 4,294,967,295 -> the total max number of times you can change items in the owning
            /// vector/array while still maintaining unique IDs.
            uint32_t version = 0;

            /// [tdbe] the above entries make up an ID relative to the container of this item. This one is a global UID seed,
            /// aka the index of the container of this item.
            uint16_t globalUIDSeed = 0;

            /// [tdbe] Allows static cast find by type (but doesn't find your object if it's derived from this type.
            /// (obv must set this to the topmost inheritor of this class e.g. a <see cref="GameEntityObject"/>)
            std::type_index typeIndex = std::type_index(typeid(int));

            /// [tdbe] counts as if deleted
            bool IsCleared() const
            {
                return version == GameDataId::FREE;
            }

            /// [tdbe] counts as if deleted
            /// todo: this should be restricted to <see cref"GameDataPool"/>
            void Clear()
            {
                version = GameDataId::FREE;
            }

            std::string PrintGlobalUID() const
            {
                return util::ToString(globalUIDSeed) + ":" + util::ToString(index) + ":" + util::ToString(version);
            }

            bool Equals(GameDataId::ID other) const
            {
                return index == other.index && version == other.version &&
                       globalUIDSeed == other.globalUIDSeed;
            }

            bool operator==(const GameDataId::ID& other) const
            {
                return Equals(other);
            }

            bool operator!=(const GameDataId::ID& other) const
            {
                return !operator==(other);
            }
        } id;

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false)
        {
            util::DebugLog("[Game][GameDataId]\t Id Cleared: " + this->id.PrintGlobalUID());
            id.Clear();
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged()
        {
            //util::DebugLog("[Game][GameComponent]\t On NotifyItemVersionChanged: " + this->id.PrintGlobalUID());
        };

        GameDataId(GameDataId::ID id = { 0, 0, 0, std::type_index(typeid(int)) })
        {
            this->id.index = id.index;
            this->id.version = id.version;
            this->id.typeIndex = id.typeIndex;
            this->id.globalUIDSeed = id.globalUIDSeed;
		};
        ~GameDataId() {};
	};

    /// [tdbe] Don't bother with something like this here. There's no gamedev-performance benefit to the extra management overhead. (<see cref="GameDataPool.h"/> description for options/tradeoffs)
    /*
    struct LinkedGameDataId
    {
        GameDataId prevItem;// [tdbe] previous empty or used
        GameDataId id;// [tdbe] current empty or used
        GameDataId nextItem;// [tdbe] next empty or used
    };*/
    } // namespace Game