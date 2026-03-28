#pragma once
#include <vector>

#include "../Utils/Util.h"
#include "GameDataId.h"

namespace Game
{
    struct GameEntity;
    struct GameComponent;

    /// <summary>
    /// [tdbe] This is a ECS "chunked" (split into tiles of equal <see cref="tileSize"/> count), 
    /// contiguous (but fragmentable (mark items as reusable)) heap array (vector) pool,
    /// of entity or component style objects,
    /// allocated once, with the <see cref="maxPossiblePoolSize"/>, and never resized.
    /// It has best™ average-case performance, cache-coherency, no deletions, no garbage, and great UX via detailed ID handles.
    /// Ted talk inside.
    /// </summary>
    /// <typeparam name="T"> "where T : derived from GameDataId" </typeparam>
    template <typename T> struct GameDataPool
    {
        /*
        < [tdbe] <see cref="GameDataPool"/> Structure for entities/components/objects >

            The Game Object/Entity Memory Management:
            The question is whether to Compact (by Swapping with the end item and Popping (deleting the last item)
        "Swap&Pop" to have tighter interation spans and better fit in cache) or Not to Compact (just mark as free,
        and avoid many derefs and alloc/free of the swaps). (excellent gems overviews here: https://gameprogrammingpatterns.com/object-pool.html
        and here https://gamedev.stackexchange.com/questions/33888/what-is-the-most-efficient-container-to-store-dynamic-game-objects-in)
            My pick: no compacting, let it fragment, everything stays where it was put, for its entire lifetime.
        (and track & reuse slots marked as empty)

            Structures, buffers, and access:
            - Game Entity Objects hold only (mostly) pointers to entries in various Component contiguous heap
        arrays.
            - Each Game Component Object holds a pointer to the game entity object that owns it.
            If something changes, these pointers are updated or nulled.

            Ideal strategy for many objects: each frame you go through everything ideally once, gather chunks of
        what you want to work on multiple times, then run your jobs. You'd also probably want a list of heap arrays,
        to store different kinds of game objects e.g. scenery, bullets etc. (maybe even swap & pop bullets to
        compact that particular heap array)

            - <see cref="GameDataPool"/> of component Transform, Material, Model, Light etc.
            etc.
            - <see cref="GameDataPool"/> of entities (Game Entity Objects)

            Fetching:
            - Getting component m of game entity n in the classic way is pretty standard without many clever
        performance wins:
            - iterate to / request n-th entity from entities array, then get its reference to the m-th component
        from the components heap array. (a component also has an id of its owning entity)

            - Things aren't chunked, or queued via queries to minimise sync points (no feature (needed yet)), so
        this isn't a performance win cache/memory wise. But you can iterate through (or delete/replace) objects in
        their heap array, really fast, and in a ECS System style.
        </ [tdbe] GameDataPool Structure for entities/components/objects >
        */

        /// [tdbe] this marks the end of the used items so we don't have to iterate past it.
        uint32_t maxUsedIndex = 0;

        /// [tdbe] contains both active and "deleted" (marked free) items, split into [tile][item] to fit in cache and be thread friendy.
        // [tdbe] newb-friendly-note: the constructor of the pool needs to make sure the actual data the vectors are pointing to, is constructed sequentially or otherwise tries to guarantee a contiguous distribution per tile in the heap memory.
        std::vector<std::vector<T*>> items;
        
        /// [tdbe] Global number of items which are valid (in use) (are not free/cleared) (including all tiles).
        /// NOTE: the pool can be fragmented, so use <see cref="Size()"/> to get the iteratable "count".
        uint32_t ValidSize() const
        {
            return validSize;
        };
        /// [tdbe] Number of items which are free/cleared (are not in use).
        uint32_t FreeSize() const
        {
            return maxPossiblePoolSize - validSize;
        };
        /// [tdbe] Flattened size for iteration. It's actually the <see cref="maxUsedIndex"/> + 1.
        uint32_t Size() const
        {
            return maxUsedIndex + 1;
        };
        uint32_t MaxSize() const
        {
            return maxPossiblePoolSize;
        };
        /// [tdbe] All tiles are the same size. It's items[0].size().
        uint32_t TileSize() const
        {
            return tileSize;
        };
        /// [tdbe] All tiles are the same size. It's items[0].size().
        uint32_t NumTiles() const
        {
            return items.size();
        };

        /// [tdbe] Returns an item if it exists and it's valid, else a nullptr.
        /// Note: this pointer is to a reusable slot in the pool. So use use and track handles (IDs), see version and <see cref="GameDataId::IsCleared"/> etc.
        // [tdbe] newb-friendly-note: you'll get linker errors if you declare but don't define template
        // functimons in the header file. (the compiler won't read the definition and won't know if/how to handle the various types, 
        // (and of course won't explain this to you in hoo-man terms or any terms))
        T* GetItem(GameDataId::ID id) const
        {
            if (IsIdValidItem(id))
            {
                return items[id.chunkIndex][id.indexInChunk];
            }
            else
            {
                return nullptr;
            }
        };
        /// [tdbe] Reserve the first valid item marked as free, if no free items available, returns nullptr.
        /// Note: the pointer might in the future might point to a reused or other free item. 
        /// So use handles (IDs) instead of pool pointers, <see cref="GameDataId::IsCleared"/>.
        /// <param name="skipThisManyFreeSlots"> For advanced use e.g. you want to leave some free contiguous 
        /// space to place similar T items together later e.g. materials of the same type of pipeline.</param>
        T* GetFreeItem(uint32_t skipThisManyFreeSlots = 0)
        {
            GameDataId::ID id = {};
            SpotInPool status = GetFirstFree(id, skipThisManyFreeSlots);
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[GameDataPool][GetFreeItem<" + topTypeStr + ">]\t "+id.PrintGlobalUID());
            #endif
            if (status == SpotInPool::FAIL)
            {
                util::DebugError("[GameDataPool][GetFreeItem<" + topTypeStr +
                                 ">]\t Somehow fetched a SpotInPool::FAIL?");
                return nullptr;
            }
            else if (status == SpotInPool::UNINITIALIZED)
            {
                util::DebugError("[GameDataPool][GetFreeItem<" + topTypeStr +
                                 ">]\t Somehow fetched a SpotInPool::UNINITIALIZED.");
                return nullptr;
            }
            else if (status == SpotInPool::UNINITIALIZED)
            {
                #ifdef DEBUG_VERBOSE
                util::DebugLog("[GameDataPool][GetFreeItem<" + topTypeStr +
                                 ">]\t Fetched a SpotInPool::UNINITIALIZED.");
                #endif
                return nullptr;
            }

            items[id.chunkIndex][id.indexInChunk]->NotifyItemVersionChanged();
            return items[id.chunkIndex][id.indexInChunk];
        };

        /// [tdbe] Marks the pool item as empty without clearing memory, and update <see cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>.
        /// We also notify the item to reset its members. 
        /// And to clear any cached ids to itself, which although lightweight, is less efficient / cache coherent. 
        /// (But if you set <param name="unsafe"/> to false, it won't clear anything cross-buffer, e.g. won't access its components or owners.)
        void ClearItem(T* item, bool unsafe = false, bool clearDataLoadedFromStorage = false)
        {
            GameDataId* gid = static_cast<GameDataId*>(item);
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[GameDataPool][ClearItem<" + topTypeStr + ">]\t "+item->id.PrintGlobalUID());
            #endif
            if (!IsIdValidItem(gid->id))
            {
                util::DebugError("[GameDataPool][ClearItem<" + topTypeStr +">]\t There's a mistake: you're trying to clear id \"" +
                                gid->id.PrintGlobalUID()
                                + "\", which is already empty! This should never happen!");
            }
            else
            {
                if (firstEmptyIndex > (uint32_t)gid->id.indexInChunk + gid->id.chunkIndex * tileSize)
                    firstEmptyIndex = gid->id.indexInChunk + gid->id.chunkIndex * tileSize;

                if (maxUsedIndex < (uint32_t)gid->id.indexInChunk + gid->id.chunkIndex * tileSize)
                    maxUsedIndex = gid->id.indexInChunk + gid->id.chunkIndex * tileSize;
            }

            gid->NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            validSize--;
        };

        /// [tdbe] Marks the pool items as empty without clearing memory, and update <see cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>.
        /// We also notify each item to reset its members. 
        /// And to clear any cached ids to itself, which although lightweight, is less efficient / cache coherent. 
        /// (But if you set <param name="unsafe"/> to true, it won't clear any slow cross-buffer stuff, e.g. won't update its components or owners.)
        void ClearItems(bool alsoDestroy = false, bool unsafe = false, bool clearDataLoadedFromStorage = false)
        {
            if (items.empty()) return;
            if (alsoDestroy)
                util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr + ">]\t Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: " + util::ToString(alsoDestroy) + "; (destroy both used and cleared items).");
            else
                util::DebugLog("\n[GameDataPool][ClearItems<" + topTypeStr + ">]\t Cearing the used pool items.");
            if (unsafe)
                util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr + ">]\t Also unsafe: "+util::ToString(unsafe)+"; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or \"dangling\" children). So you can clear them yourself after this in a more efficient / cache coherent pass.");
            if (clearDataLoadedFromStorage)
                util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr + ">]\t Also clearDataLoadedFromStorage: "+util::ToString(clearDataLoadedFromStorage)+"; for example a model will delete the serialized mesh data, or a texture its image. You don't want this unless you're not using it again in the currently loaded game world.");
            uint32_t max = maxUsedIndex + 1;

            if (items.size() * tileSize <= maxUsedIndex)
            {
                util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr + ">]\t Clearing anyway, but items.size() * tileSize: \"" +
                               util::ToString(items.size() * tileSize) + "\" <= maxUsedIndex: \"" + util::ToString(maxUsedIndex) +"\"!? Did you resize the pool?");
                max = (uint32_t)items.size() * tileSize;
            }
            for (uint32_t i = 0; i < max; i++)
            {
                uint32_t tileIndex = (uint32_t)((double)i / (double)tileSize);
                uint32_t indexInTile = i % tileSize;
                auto item = items[tileIndex][indexInTile];
                if(item == nullptr)
                    continue;
                GameDataId* gid = static_cast<GameDataId*>(item);
                if (!gid->id.IsCleared())
                {
                    gid->NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
                }
                else
                {
                    #ifdef DEBUG_VERBOSE
                    if (alsoDestroy)
                        util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr +
                                       ">]\t Delete item only: already marked as cleared/unused in pool: " + gid->id.PrintGlobalUID() + ".");
                    else
                        util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr +
                                       ">]\t Skipping already marked as cleared/unused in pool: " + gid->id.PrintGlobalUID() + ".");
                    #endif
                }
            }

            firstEmptyIndex = 0;
            maxUsedIndex = 0;
            validSize = 0;

            if (alsoDestroy)
                delete this;
        };

        GameDataPool(uint16_t tileSize, uint32_t maxPossiblePoolSize = 0, int16_t worldIndex = 0, uint64_t typeUID = 0, std::string topTypeStr = "T")
        : tileSize(tileSize), maxPossiblePoolSize(maxPossiblePoolSize), worldIndex(worldIndex), typeUID(typeUID), topTypeStr(topTypeStr)
        {
            this->maxUsedIndex = 0;
            this->firstEmptyIndex = 0;
            this->currentVersion = GameDataId::FREE;
            
            tileCount = (uint32_t)((double)maxPossiblePoolSize / (double)tileSize);
            if(tileCount == 0u)
                tileCount = 1u;
            // [tdbe] Construct the whole span. That's what we want for best-average-case gamedev/memory.
            items.resize(tileCount);
            for (uint32_t tileIdx = 0; tileIdx < tileCount; tileIdx++)
            {
                items[tileIdx].resize(tileSize, nullptr);
                
                for (uint32_t i = 0; i < tileSize; i++)
                {
                    items[tileIdx][i] = new T();
                    GameDataId* gid = static_cast<GameDataId*>(items[tileIdx][i]);
                    gid->id.worldIndex = worldIndex;
                    gid->id.typeUID = typeUID;
                    gid->id.chunkIndex = tileIdx;
                    gid->id.indexInChunk = i;
                    gid->id.version = GameDataId::FREE;
                    gid->id.typeIndex = std::type_index(typeid(T));
                }
            }
            util::DebugLog("\n[GameDataPool][Constructed<" + topTypeStr + ">] maxPossiblePoolSize: \"" + 
                            util::ToString(maxPossiblePoolSize) + "\", world: " + util::ToString(worldIndex) + ", typeUID: \"" + util::ToString(typeUID) + "_" + topTypeStr +
                            "\", firstEmptyIndex: " + util::ToString(firstEmptyIndex) +", T: " +
                            typeid(T).name() + ", tiles: " + util::ToString(tileCount) + ", tileSize: " + util::ToString(tileSize) + ", items.size(): "+util::ToString(items.size()));
        };

        /// [tdbe] Actually dispose of the allocated data
        ~GameDataPool()
        {
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[~GameDataPool][Destructing<" + topTypeStr + ">] and all its heap items.");
            #endif
            for (uint32_t tileIdx = 0; tileIdx < items.size(); tileIdx++)
            {
                for (uint32_t i = 0; i < items[tileIdx].size(); i++)
                {
                    if (items[tileIdx][i] != nullptr)
                    {
                        delete items[tileIdx][i];
                    }
                }
            }
            items.clear();
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[~GameDataPool][Destructed<" + topTypeStr + ">] and all its heap items.\n");
            #endif
        };

        GameDataPool(GameDataPool const& copy)
        {
            util::DebugError("\n[~GameDataPool] NotImplementedException. Don't copy this / pass by value.");
        };
        GameDataPool& operator=(GameDataPool const& copy) 
        {
            util::DebugError("\n[~GameDataPool] NotImplementedException. Don't copy this / pass by value.");
            return *this;
        };

        GameDataPool(GameDataPool&& rcOther)
        {
            util::DebugError("\n[~GameDataPool] NotImplementedException. Don't move this.");
        }

       private:
        /// [tdbe] 1 means no split. Splits the pool into "chunks" of fixed element count size.
        uint32_t tileSize = 1u;// 128 is a good average case number to flexibly fit in cache with any contents and amongst everything else.
        uint32_t tileCount = 0u;
        
        enum SpotInPool
        {
            FAIL = 0,// depends on context; couldn't get a spot; could be full.
            UNINITIALIZED,// could be we reserved the space but didn't emplace/construct. E.g. in case we allowed that to happen in the constructor.
            USED,
            FREE
        };
        /// [tdbe] a Version is a number of how many items were ever created in total in this <see cref="GameDataPool"/>
        /// it is the latest (largest) <see cref="GameDataId.version"/> and ensures the <see cref="GameDataId"/>'s
        /// are unique.
        /// [tdbe] note: a newly allocated pool will still have incremental versions across positions e.g. items[0].v == 1, items[1].v == 2 etc. (instead of 0 and 0)
        uint32_t currentVersion = 0u;
        /// [tdbe] max size of the array, unless you declare it with a smaller size.
        uint32_t maxPossiblePoolSize = std::numeric_limits<uint32_t>::max();
        /// [tdbe] item in the array (global across all tiles) that is empty or is marked as empty as far as we're concerned
        uint32_t firstEmptyIndex = 0u;
        uint64_t typeUID = 0u;
        int worldIndex = 0;
        std::string topTypeStr = "T";
        uint32_t validSize = 0u;

        bool ScanForNextEmptyIndex(uint32_t startFrom = 0)
        {
            if (currentVersion <= startFrom)
            {
                firstEmptyIndex = startFrom;
                return true;
            }

            for (uint32_t i = startFrom; i < maxPossiblePoolSize; i++)
            {
                uint32_t tileIndex = (uint32_t)((double)i / (double)tileSize);
                uint32_t indexInTile = i % tileSize;
                if (items[tileIndex][indexInTile]->id.IsCleared())
                {
                    
                    firstEmptyIndex = i;
                    return true;
                }
            }

            for (uint32_t i = 0; i < startFrom; i++)
            {
                uint32_t tileIndex = (uint32_t)((double)i / (double)tileSize);
                uint32_t indexInTile = i % tileSize;
                if (items[tileIndex][indexInTile]->id.IsCleared())
                {
                    firstEmptyIndex = i;
                    return true;
                }
            }

            firstEmptyIndex = maxPossiblePoolSize;
            return false;
        };

        /// [tdbe] Get a new item ID set in the next available free slot in our items vector, and update <see
        /// cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>. You must emplace the item yourself.
        SpotInPool GetFirstFree(GameDataId::ID& itemId, uint32_t skipThisManyFreeSlots = 0)
        {
            SpotInPool success;
            uint32_t firstEmptyIndexPlus = skipThisManyFreeSlots + firstEmptyIndex;
            if (firstEmptyIndexPlus == maxPossiblePoolSize)
            {
                util::DebugLog("[GameDataPool][GetFirstFree<" + topTypeStr + ">]\t firstEmptyIndexPlus: \"" + util::ToString(firstEmptyIndexPlus) +
                               "\", == maxPossiblePoolSize! This pool is full!");
                success = SpotInPool::FAIL;
                itemId = {};
                return success;
            }
            uint32_t tileIndex = (uint32_t)((double)firstEmptyIndexPlus / (double)tileSize);
            uint32_t indexInTile = firstEmptyIndexPlus % tileSize;
            // [tdbe] reserved to capacity() but not yet constructed at the current index.
            if (items.size() <= tileIndex || items[tileIndex].size() <= indexInTile || items[tileIndex][indexInTile] == nullptr)
            {
                success = SpotInPool::UNINITIALIZED;
                itemId.version = ++currentVersion;
                validSize++;
                itemId.indexInChunk = tileIndex;
                itemId.typeUID = typeUID;
                itemId.worldIndex = worldIndex;
                itemId.chunkIndex = tileIndex;
                itemId.typeIndex = std::type_index(typeid(T));
                if (maxUsedIndex < firstEmptyIndexPlus)
                    maxUsedIndex = firstEmptyIndexPlus;
                util::DebugLog("[GameDataPool][GetFirstFree<" + topTypeStr + ">]\t firstEmptyIndexPlus: \"" + util::ToString(firstEmptyIndexPlus) +
                               "\", BUT the vector('s item) is not yet constructed at the current index ["+util::ToString(tileIndex)+"]["+util::ToString(indexInTile)+"], items.size(): "+util::ToString(items.size()));
            }
            else
            {
                if (items[tileIndex][indexInTile]->id.version != GameDataId::FREE)
                {
                    success = SpotInPool::USED;
                    itemId = {};
                    if (skipThisManyFreeSlots != 0)
                        util::DebugError("[GameDataPool][GetFirstFree<" + topTypeStr +
                                         ">]\t the version of firstEmptyIndexPlus: " + util::ToString(firstEmptyIndexPlus) +
                                         ", with id \"" + items[tileIndex][indexInTile]->id.PrintGlobalUID() +
                                         "\", was not empty! This should never happen!");
                }
                else
                {
                    success = SpotInPool::FREE;
                    items[tileIndex][indexInTile]->id.version = ++currentVersion;
                    validSize++;
                    if (maxUsedIndex < firstEmptyIndexPlus)
                        maxUsedIndex = firstEmptyIndexPlus;
                    itemId = items[tileIndex][indexInTile]->id;
                    #ifdef DEBUG_VERBOSE
                    util::DebugLog("[GameDataPool][GetFirstFree<" + topTypeStr + ">]\t Found free item at index: " + util::ToString(firstEmptyIndexPlus) + ", with id: " + itemId.PrintGlobalUID() +
                                   ", validSize: " + util::ToString(validSize) + ", currentVersion: " + util::ToString(currentVersion));
                    #endif
                }
            }

            if ((success == SpotInPool::FREE || success == SpotInPool::UNINITIALIZED))// && skipThisManyFreeSlots == 0
                ScanForNextEmptyIndex(firstEmptyIndexPlus + 1);// firstEmptyIndex

            return success;
        };

        bool IsIdValidItem(GameDataId::ID id) const
        {
            uint32_t tileIndex = (uint32_t)((double)id.indexInChunk / (double)tileSize);
            uint32_t indexInTile = id.indexInChunk % tileSize;
            if (items.size() <= tileIndex || 
                items[tileIndex].size() <= indexInTile)
            {
                return false;
            }

            if (id.version == GameDataId::FREE)
            {
                util::DebugLog("[GameDataPool][GetItem<" + topTypeStr + ">]\t the version of id \"" + id.PrintGlobalUID() +
                               "\", is " + util::ToString(GameDataId::FREE) + " (expired or never used).");
                return false;
            }
            else
            {
                return true;
            }
        };
        // size_t CountValidItems() const;
        // using Type = typename T::GameDataId;
    };
}