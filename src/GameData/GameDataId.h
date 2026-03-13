#pragma once
#include <typeindex>
#include <stdint.h>
#include <string>
#include <functional>

#include "../Utils/Util.h"

namespace Game
{
    /// [tdbe] <see cref="GameDataPool::GetFirstFree"/>
	struct GameDataId
	{
        static const uint32_t FREE = 0;
        /// [tdbe] Essentially used as a weak reference in the data spans in <see cref="GameData"/>.
        /// worldIndex:typeUID:chnukIndex:index:version and typeIndex
        /// The ID is a little big/verbose but the aim is to not compromize real-world game-making convenience.
        struct ID 
        {
            /// [tdbe] index in owning vector/array. 2^32, +-2,147,483,647 -> the max number of items in an owning
            /// vector/array is 2,147,483,647.
            int32_t index = 0;
            /// [tdbe] Version 0 means deleted/free/clear/unused.
            /// u2^32, 0 to 4,294,967,295 -> the total max number of times you can change items in the owning
            /// vector/array while still maintaining unique IDs.
            uint32_t version = 0;
            
            /// [tdbe] We don't have advanced chunking but we have Tiled pools. Chunky Tiles.
            uint16_t chunkIndex = 0;

            /// [tdbe] the above entries make up an ID relative to the container<this item type>. 
            /// This a custom uid of the type of element.
            uint16_t typeUID = 0;
            
            /// [tdbe] the above entries can be found in one of multiple game worlds.
            int worldIndex = 0;

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
                return util::ToString(worldIndex) + ":" + util::ToString(typeUID) + ":" + util::ToString(chunkIndex) + ":" + util::ToString(index) + ":" + util::ToString(version);
            }

            bool Equals(GameDataId::ID other) const
            {
                return index == other.index && version == other.version && chunkIndex == other.chunkIndex &&
                       typeUID == other.typeUID && worldIndex == other.worldIndex;
            }

            bool operator==(const GameDataId::ID& other) const
            {
                return Equals(other);
            }

            bool operator!=(const GameDataId::ID& other) const
            {
                return !operator==(other);
            }

            bool operator<(const GameDataId::ID& other) const
            {
                if(worldIndex != other.worldIndex) return worldIndex < other.worldIndex;
                if(typeUID != other.typeUID) return typeUID < other.typeUID;
                if(chunkIndex != other.chunkIndex) return chunkIndex < other.chunkIndex;
                if(index != other.index) return index < other.index;
                return version < other.version;
            }
        } id;

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false)
        {
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[Game][GameDataId]\t Id Cleared: " + this->id.PrintGlobalUID());
            #endif
            id.Clear();
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged()
        {
            #ifdef DEBUG_VERBOSE
            //util::DebugLog("[Game][GameComponent]\t On NotifyItemVersionChanged: " + this->id.PrintGlobalUID());
            #endif
        };

        GameDataId(GameDataId::ID id = { 0, 0, 0, 0, 0, std::type_index(typeid(int)) })
        {
            this->id.index = id.index;
            this->id.version = id.version;
            this->id.chunkIndex = id.chunkIndex;
            this->id.typeIndex = id.typeIndex;
            this->id.typeUID = id.typeUID;
            this->id.worldIndex = id.worldIndex;
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

namespace std
{
    template<>
    struct hash<Game::GameDataId::ID>
    {
        size_t operator()(const Game::GameDataId::ID& id) const noexcept
        {
            size_t h1 = hash<int32_t>{}(id.index);
            size_t h2 = hash<uint32_t>{}(id.version);
            size_t h3 = hash<uint32_t>{}(id.chunkIndex);
            size_t h4 = hash<uint16_t>{}(id.typeUID);
            size_t h5 = hash<uint16_t>{}(id.worldIndex);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4);
        }
    };
}