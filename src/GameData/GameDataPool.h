#pragma once
#include <vector>

#include "../Utils/Util.h"
#include "GameDataId.h"

namespace Game
{
    struct GameEntity;
    struct GameComponent;

    /// <summary>
    /// [tdbe] This is a contiguous (but fragmentable (mark items as reusable)) heap array (vector) pool of entity style objects,
    /// allocated once, with the <see cref="maxPossibleSize"/>, and never resized.
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
        int32_t maxUsedIndex = 0;

        /// [tdbe] contains both active and "deleted" (marked free) items
        std::vector<T*> items;
        /// [tdbe] Number of items which are valid (in use) (are not free/cleared).
        /// NOTE: the pool can be fragmented, so use <see cref="Size()"/> to get the iteratable "count".
        int32_t ValidSize() const
        {
            return (int32_t)validSize;
        };
        /// [tdbe] Number of items which are free/cleared (are not in use).
        int32_t FreeSize() const
        {
            return (int32_t)(maxPossibleSize - validSize);
        };
        /// [tdbe] Size for actual iteration. It's actually the <see cref="maxUsedIndex"/> + 1.
        int32_t Size() const
        {
            return maxUsedIndex + 1;
        };
        int32_t MaxSize() const
        {
            return maxPossibleSize;
        };

        /// [tdbe] Returns an item if it exists and it's valid, else a nullptr.
        /// Note: this pointer might point to a reused or free item. So use handles (IDs), <see cref="GameDataId::IsCleared"/>.
        // [tdbe] newb-friendly-note: you'll get linker errors if you declare but don't define template
        // functimons in the header file. (the compiler won't read the definition and won't know if/how to handle the various types, 
        // (and of course won't explain this to you in hu-man terms or any terms))
        T* GetItem(GameDataId::ID id) const
        {
            if (IsIdValidItem(id))
            {
                return items[id.index];
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
            util::DebugLog("[GameDataPool][GetFreeItem<" + topTypeStr + ">]\t "+id.PrintGlobalUID());
            if (status == SpotInPool::FAIL)
            {
                return nullptr;
            }
            else if (status == SpotInPool::UNINITIALIZED)
            {
                util::DebugError("[GameDataPool][GetFreeItem<" + topTypeStr +
                                 ">]\t Somehow we forgot to initialize the GameDataPool. If "
                                 "this was intended, change this function.");
                return nullptr;
            }

            items[id.index]->NotifyItemVersionChanged();
            return items[id.index];
        };

        /// [tdbe] Marks the pool item as empty without clearing memory, and update <see cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>.
        /// We also notify the item to reset its members. 
        /// And to clear any cached ids to itself, which although lightweight, is less efficient / cache coherent. 
        /// (But if you set <param name="unsafe"/> to false, it won't clear anything cross-buffer, e.g. won't access its components or owners.)
        void ClearItem(T* item, bool unsafe = false, bool clearDataLoadedFromStorage = false)
        {
            GameDataId* gid = static_cast<GameDataId*>(item);
            util::DebugLog("[GameDataPool][ClearItem<" + topTypeStr + ">]\t "+item->id.PrintGlobalUID());
            if (!IsIdValidItem(gid->id))
            {
                util::DebugError("[GameDataPool][ClearItem<" + topTypeStr +">]\t There's a mistake: you're trying to clear id \"" +
                                 util::ToString(gid->id.index) + "\", which is already empty! This should never happen!");
            }
            else
            {
                if (firstEmptyIndex > gid->id.index)
                    firstEmptyIndex = gid->id.index;

                if (maxUsedIndex < gid->id.index)
                    maxUsedIndex = gid->id.index;
            }

            gid->NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            validSize--;
        };

        /// [tdbe] Marks the pool items as empty without clearing memory, and update <see cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>.
        /// We also notify each item to reset its members. 
        /// And to clear any cached ids to itself, which although lightweight, is less efficient / cache coherent. 
        /// (But if you set <param name="unsafe"/> to false, it won't clear anything cross-buffer, e.g. won't access its components or owners.)
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

            if (items.size() <= maxUsedIndex)
            {
                util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr + ">]\t Clearing anyway, but items.size(): \"" +
                               util::ToString(items.size()) + "\" <= maxUsedIndex: \"" + util::ToString(maxUsedIndex) +"\"!? Did you resize the pool?");
                max = (uint32_t)items.size();
            }

            for (uint32_t i = 0; i < max; i++)
            {
                GameDataId* gid = static_cast<GameDataId*>(items[i]);
                if (!gid->id.IsCleared())// silent version of IsIdValidItem(gid->id)
                {
                    gid->NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
                }
                else
                {
                    if (alsoDestroy)
                        util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr +
                                       ">]\t Delete item only: already marked as cleared/unused in pool: " + gid->id.PrintGlobalUID() + ".");
                    else
                        util::DebugLog("[GameDataPool][ClearItems<" + topTypeStr +
                                       ">]\t Skipping already marked as cleared/unused in pool: " + gid->id.PrintGlobalUID() + ".");
                }
            }

            firstEmptyIndex = 0;
            maxUsedIndex = 0;
            validSize = 0;

            // [tdbe] the destructor will actually delete all the items
            if (alsoDestroy)
                delete this;
        };

        GameDataPool(int maxPossibleSize = 0, uint16_t globalUIDSeed = 0, std::string topTypeStr = "T")
        : maxPossibleSize(maxPossibleSize), globalUIDSeed(globalUIDSeed), topTypeStr(topTypeStr)
        {
            this->maxUsedIndex = 0;
            this->firstEmptyIndex = 0;
            this->currentVersion = GameDataId::FREE;
            // [tdbe] Construct the whole span. That's what we want for best-average-case gamedev/memory.
            items.resize(maxPossibleSize, nullptr);
            for (int i = 0; i < items.size(); i++)
            {
                items[i] = new T();
                GameDataId* gid = static_cast<GameDataId*>(items[i]);
                gid->id.globalUIDSeed = globalUIDSeed;
                gid->id.index = i;
                gid->id.version = GameDataId::FREE;
                gid->id.typeIndex = std::type_index(typeid(T));
            }
            util::DebugLog("\n[GameDataPool][Constructed<" + topTypeStr + ">] maxPossibleSize: \"" + 
                            util::ToString(maxPossibleSize) + "\", globalUIDSeed: \"" + util::ToString(globalUIDSeed) + "_" + topTypeStr +
                            "\", firstEmptyIndex: " + util::ToString(firstEmptyIndex) +", T: " +
                            typeid(T).name() + ".");// [tdbe] typeid(T)::name() is only human-readable in Visual C++ :(
        };

        /// [tdbe] Actually dispose of the allocated data
        ~GameDataPool()
        {
            // (clears the allocated heap memory)
            for (int i = 0; i < items.size(); i++)
            {
                if (items[i] != nullptr)
                {
                    delete items[i]; // [tdbe] calls the destructor of T, (GameDataId, GameComponent / GameEntity etc).
                }
            }
            items.clear();
            util::DebugLog("[GameDataPool][Destructed<" + topTypeStr + ">] and all its heap items.\n");
        };

        GameDataPool(GameDataPool const& copy)
        {
            util::DebugError("\n[GameDataPool] NotImplementedException. Don't copy this / pass by value.");
        };
        GameDataPool& operator=(GameDataPool const& copy) 
        {
            util::DebugError("\n[GameDataPool] NotImplementedException. Don't copy this / pass by value.");
            return *this;
        };

        GameDataPool(GameDataPool&& rcOther)
        {
            util::DebugError("\n[GameDataPool] NotImplementedException. Don't move this.");
        }

      private:
        enum SpotInPool
        {
            FAIL = 0,// [tdbe] depends on context; couldn't get a spot; could be full.
            UNINITIALIZED,// [tdbe] could be we reserved the space but didn't emplace/construct. E.g. in case we allowed that to happen in the constructor.
            USED,
            FREE
        };
        /// a Version is a global number of how many items were created in total in this <see cref="GameDataPool"/>
        /// it is the latest (largest) <see cref="GameDataId.version"/> and ensures the <see cref="GameDataId"/>'s
        /// are unique.
        uint32_t currentVersion = 0;
        /// [tdbe] max size of the array, unless you declare it with a smaller size.
        int32_t maxPossibleSize = std::numeric_limits<int32_t>::max();
        /// [tdbe] item in the array that is empty or is marked as empty as far as we're concerned
        int32_t firstEmptyIndex = 0;
        uint16_t globalUIDSeed = 0;
        std::string topTypeStr = "T";
        int32_t validSize = 0;

        bool ScanForNextEmptyIndex(uint32_t startFrom = 0)
        {
            if (currentVersion <= startFrom)
            {
                firstEmptyIndex = startFrom;
                return true;
            }

            for (uint32_t i = startFrom; i < (uint32_t)maxPossibleSize; i++)
            {
                if (items[i]->id.IsCleared())
                {
                    firstEmptyIndex = items[i]->id.index;
                    return true;
                }
            }

            // [tdbe] start from 0, maybe there's some free items we skipped (on purpose)
            for (uint32_t i = 0; i < startFrom; i++)
            {
                if (items[i]->id.IsCleared())
                {
                    firstEmptyIndex = items[i]->id.index;
                    return true;
                }
            }

            firstEmptyIndex = maxPossibleSize;
            return false;
        };

        /// [tdbe] Get a new item ID set in the next available free slot in our items vector, and update <see
        /// cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>. You must emplace the item yourself.
        SpotInPool GetFirstFree(GameDataId::ID& itemId, uint32_t skipThisManyFreeSlots = 0)
        {
            SpotInPool success;
            int firstEmptyIndexPlus = skipThisManyFreeSlots + firstEmptyIndex;
            if (firstEmptyIndexPlus == maxPossibleSize)
            {
                util::DebugLog("[GameDataPool][GetFirstFree<" + topTypeStr + ">]\t firstEmptyIndexPlus: \"" + util::ToString(firstEmptyIndexPlus) +
                               "\", == maxPossibleSize! This pool is full!");
                success = SpotInPool::FAIL;
                itemId = {};
                return success;
            }

            // [tdbe] reserved to capacity() but not yet constructed at the current index.
            if (items.size() <= firstEmptyIndexPlus || items[firstEmptyIndexPlus] == nullptr)
            {
                success = SpotInPool::UNINITIALIZED;
                itemId.version = ++currentVersion;
                validSize++;
                itemId.index = firstEmptyIndexPlus;
                itemId.globalUIDSeed = globalUIDSeed;
                itemId.typeIndex = std::type_index(typeid(T));
                if (maxUsedIndex < itemId.index)
                    maxUsedIndex = itemId.index;
                util::DebugLog("[GameDataPool][GetFirstFree<" + topTypeStr + ">]\t firstEmptyIndexPlus: \"" + util::ToString(firstEmptyIndexPlus) +
                               "\", BUT the vector('s item) is not yet constructed at the current index");
            }
            else
            {
                if (items[firstEmptyIndexPlus]->id.version != GameDataId::FREE)
                {
                    success = SpotInPool::USED;
                    itemId = {};
                    if (skipThisManyFreeSlots != 0)
                        util::DebugError("[GameDataPool][GetFirstFree<" + topTypeStr +
                                         ">]\t the version of firstEmptyIndexPlus: " + util::ToString(firstEmptyIndexPlus) +
                                         ", with id \"" + items[firstEmptyIndexPlus]->id.PrintGlobalUID() +
                                         "\", was not empty! This should never happen!");
                }
                else
                {
                    success = SpotInPool::FREE;
                    items[firstEmptyIndexPlus]->id.version = ++currentVersion;
                    validSize++;
                    if (maxUsedIndex < items[firstEmptyIndexPlus]->id.index)
                        maxUsedIndex = items[firstEmptyIndexPlus]->id.index;
                    itemId = items[firstEmptyIndexPlus]->id;

                    util::DebugLog("[GameDataPool][GetFirstFree<" + topTypeStr + ">]\t Found free item at index: " + util::ToString(firstEmptyIndexPlus) + ", with id: " + itemId.PrintGlobalUID() +
                                   ", validSize: " + util::ToString(validSize) + ", currentVersion: " + util::ToString(currentVersion));
                }
            }

            if ((success == SpotInPool::FREE || success == SpotInPool::UNINITIALIZED))// && skipThisManyFreeSlots == 0
                ScanForNextEmptyIndex(items[firstEmptyIndexPlus]->id.index + 1);// firstEmptyIndex

            return success;
        };

        bool IsIdValidItem(GameDataId::ID id) const
        {
            if (items.size() <= id.index)
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