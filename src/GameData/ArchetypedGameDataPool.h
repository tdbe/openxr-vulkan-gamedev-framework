#pragma once
#include <vector>
#include <tuple>

#include "../Utils/Util.h"
#include "GameDataId.h"

namespace Game
{
    struct GameEntity;
    struct GameComponent;
    struct UIDTypeCheckHelper
    {
        static bool IsTypeUIDEntity(uint64_t uid);
    };


    /// <summary>
    /// [tdbe] This is the components "archetype" (slot wise) for default game world entities. The pool is tiled but the archetype is not enforced (see Notes for strategy).
    /// It's basically the same as <see cref="GameDataPool"/> but with more than 1 type templates.
    ///
    /// Note: 1: the meta here would be to generate different structures with different amount of component templates based on needed archetypes. We don't really care about that too much because:
    /// Note: 2: each entity maintains its own archetype mask, and right now we don't bother to maintain or enforce per-chunk archetype / masks at all. 
    /// A <see cref="ArchetypedGameDataPool"/> is performant and cache coherent enough even when partially/randomly allocated with components (we're making games not benchmarks).
    /// Plus we have multiple <see cref="GameWorld"/>'s (pools) to sort special things like e.g. bullets.
    ///
    /// [tdbe] [ArchetypedGameDataPool] This is a ECS "chunked" (split into tiles of equal <see cref="tileSize"/> count), 
    /// contiguous (but fragmentable (mark items as reusable)) heap array (vector) pool,
    /// of entity or component style objects,
    /// allocated once, with the <see cref="maxPossiblePoolSize"/>, and never resized.
    /// It has best™ average-case performance, cache-coherency, no deletions, no garbage, and great UX via detailed ID handles.
    /// Ted talk inside.
    /// </summary>
    ///
    /// Not for Shared Components (e.g. materials and meshes), or Sparse Components (e.g Lights)
    /// For regular unique components and attributes e.g.:
    ///     transform, parent, children, bounds, physicsbody, physicscolider, etc.
    /// <typeparam name="TypeX"> "where TypeX : derived from GameDataId" </typeparam>
    // [tdbe] newb-friendly-note: remember variadic arguments myFunc(Args... args)? It works for variadic types as well.
    template <typename... Types> struct ArchetypedGameDataPool
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
            - Game Entity Objects hold the ID(s) of the components they own.
            - Each Game Component Object holds the ID(s) to the owner(s).
            If something changes, these ids are updated or expired.
            - The pool is Tiled (chunked, but fixed size (number of elements) tiles)
                - this means you can send a chunk to a thread and it fits comfortably in cpu cache.

            - Use one pool per type, and a group of pools is called a <see cref="GameWorld"/>.
            
            Ideal strategy for many objects: each frame you go through everything ideally once, load into cache the chunks of
        that you want to work on, then run your jobs (preferably pushing to a command buffer). You'd also probably want a list of heap arrays,
        to store different kinds of game objects e.g. scenery, bullets etc.

            - <see cref="GameDataPool"/> of component Transform, Material, Model, Light etc.
            etc.
            - <see cref="GameDataPool"/> of entities (Game Entity Objects)

            Fetching:
                - iterate entities array (in parallel) (via chunks (the chunk the entity is in also holds the components for that entity)):
                    - do a "component query": each entity has a component archetype mask.
                    - get the component id by type via the entity's components.
                - iterate component array (in parallel) (via chunks) checking the owner(s).
            Processing:
                - since threading (jobs) are highly encouraged, you should from your jobs and queries, set up a queue of sync point / atomic operations (a "command buffer"), which you then run after the simulation step.

        </ [tdbe] GameDataPool Structure for entities/components/objects >
        */
        
        enum SpotInPool
        {
            FAIL = 0,// depends on context; couldn't get a spot; could be full.
            UNINITIALIZED,// could be we reserved the space but didn't emplace/construct. E.g. in case we allowed that to happen in the constructor.
            USED,
            FREE
        };
        
        template <typename SVT> struct SubpoolTiledVector
        {
            /// [tdbe] [tiles][items]
            std::vector<std::vector<SVT*>> items;

            std::string GetTopTypeStr() const { return this->topTypeStr; };
            uint32_t GetMaxPossiblePoolSize() const { return this->maxPossiblePoolSize; };
            int16_t GetWorldIndex() const { return this->worldIndex; };
            uint64_t GetTypeUID() const { return this->typeUID; };
            uint32_t GetFirstEmptyIndex() const { return this->firstEmptyIndex; };
            uint32_t GetTileCount() const { return 0; };
            uint32_t GetMaxUsedIndex() const { return this->maxUsedIndex; };
            uint32_t GetCurrentVersion() const { return this->currentVersion; };
            uint32_t GetValidSize() const { return this->validSize; };
            uint32_t GetTileSize() const { return this->tileSize; };
            
            /// [tdbe] Global number of items which are valid (in use) (are not free/cleared) (including all tiles).
            /// NOTE: the pool can be fragmented, so use <see cref="Size()"/> to get the iteratable "count".
            uint32_t ValidSize() const { return this->validSize; };
            
            /// [tdbe] Number of items which are free/cleared (are not in use).
            uint32_t FreeSize() const
            {
                return this->maxPossiblePoolSize - this->validSize;
            };
            /// [tdbe] Flattened size for iteration. It's actually the <see cref="maxUsedIndex"/> + 1.
            uint32_t Size() const
            {
                return this->maxUsedIndex + 1;
            };
            uint32_t MaxSize() const
            {
                return this->maxPossiblePoolSize;
            };
            
            /// [tdbe] Returns an item if it exists and it's valid, else a nullptr.
            /// Note: this pointer is to a reusable slot in the pool. So use use and track handles (IDs), see version and <see cref="GameDataId::IsCleared"/> etc.
            // [tdbe] newb-friendly-note: you'll get linker errors if you declare but don't define template
            // functimons in the header file. (the compiler won't read the definition and won't know if/how to handle the various types, 
            // (and of course won't explain this to you in hoo-man terms or any terms))
            SVT* GetItem(const GameDataId::ID id) const
            {
                if (IsIdValidItem(id))
                {
                    return this->items[id.chunkIndex][id.indexInChunk];
                }
                else
                {
                    return nullptr;
                }
            };
            /// [tdbe] Reserve the first valid item marked as free, if no free items available, returns nullptr.
            /// Note: the pointer might in the future point to a reused or other free item, 
            /// so use handles (IDs) instead of pool pointers, <see cref="GameDataId::IsCleared"/>.
            ///
            /// <param name="skipThisManyFreeSlots"> For advanced use e.g. you want to leave some free contiguous 
            /// space to place similar T items together later e.g. materials of the same type of pipeline.
            /// NOTE: the skip is global (across all tiles (chunks))</param>
            /// <param name="ownerEntityTileId"> When you're adding unique components, you want them in the same 
            /// tile (chunk) as the owning entity of the same <see cref="ArchetypedGameDataPool"/>, so specify that entity here.
            /// TODO: this param is a bit awkward because this <see cref="ArchetypedGameDataPool"/> is meant to 
            /// hold entities alongside components (they are both <see cref="SVT"/>). </param>
            SVT* GetFreeItem(const uint32_t skipThisManyFreeSlots = 0, const int32_t ownerEntityTileId = -1)
            {
                GameDataId::ID id = {};
                SpotInPool status = ownerEntityTileId == -1 || UIDTypeCheckHelper::IsTypeUIDEntity(typeUID) ? 
                                    GetFirstFree(id, skipThisManyFreeSlots)
                                    : GetFirstFree(id, skipThisManyFreeSlots, ownerEntityTileId);
                #ifdef DEBUG_VERBOSE
                util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<" + this->topTypeStr + ">][owner chunk id: " + util::ToString(ownerEntityTileId) + "]\t " + id.PrintGlobalUID());
                #endif
                if (status == SpotInPool::FAIL)
                {
                    util::DebugError("[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<" + this->topTypeStr +
                                    ">]\t Somehow fetched a SpotInPool::FAIL?");
                    return nullptr;
                }
                else if (status == SpotInPool::UNINITIALIZED)
                {
                    util::DebugError("[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<" + this->topTypeStr +
                                    ">]\t Somehow fetched a SpotInPool::UNINITIALIZED.");
                    return nullptr;
                }
                else if (status == SpotInPool::UNINITIALIZED)
                {
                    #ifdef DEBUG_VERBOSE
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<" + this->topTypeStr +
                                    ">]\t Fetched a SpotInPool::UNINITIALIZED.");
                    #endif
                    return nullptr;
                }

                this->items[id.chunkIndex][id.indexInChunk]->NotifyItemVersionChanged();
                return this->items[id.chunkIndex][id.indexInChunk];
            };

            /// [tdbe] Marks the pool item as empty without clearing memory, and update <see cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>.
            /// We also notify the item to reset its members. 
            /// And to clear any cached ids to itself, which although lightweight, is less efficient / cache coherent. 
            /// (But if you set <param name="unsafe"/> to false, it won't clear anything cross-buffer, e.g. won't access its components or owners.)
            void ClearItem(SVT* item, const bool unsafe = false, const bool clearDataLoadedFromStorage = false)
            {
                GameDataId* gid = static_cast<GameDataId*>(item);
                #ifdef DEBUG_VERBOSE
                util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItem<" + this->topTypeStr + ">]\t "+item->id.PrintGlobalUID());
                #endif
                if (!IsIdValidItem(gid->id))
                {
                    util::DebugError("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItem<" + this->topTypeStr +">]\t There's a mistake: you're trying to clear id \"" +
                                    gid->id.PrintGlobalUID()
                                    + "\", which is already empty! This should never happen!");
                }
                else
                {
                    if (this->firstEmptyIndex > (uint32_t)gid->id.indexInChunk + gid->id.chunkIndex * this->tileSize)
                        this->firstEmptyIndex = gid->id.indexInChunk + gid->id.chunkIndex * this->tileSize;

                    if (this->maxUsedIndex < (uint32_t)gid->id.indexInChunk + gid->id.chunkIndex * this->tileSize)
                        this->maxUsedIndex = gid->id.indexInChunk + gid->id.chunkIndex * this->tileSize;
                }

                gid->NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
                this->validSize--;
            };

            /// [tdbe] Marks the pool items as empty without clearing memory, and update <see cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>.
            /// We also notify each item to reset its members. 
            /// And to clear any cached ids to itself, which although lightweight, is less efficient / cache coherent. 
            /// (But if you set <param name="unsafe"/> to true, it won't clear any slow cross-buffer stuff, e.g. won't update its components or owners.)
            void ClearItems(const bool alsoDestroy = false, const bool unsafe = false, const bool clearDataLoadedFromStorage = false)
            {
                if (this->items.empty()) return;
                if (alsoDestroy)
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr + ">]\t Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: " + util::ToString(alsoDestroy) + "; (destroy both used and cleared items).");
                else
                    util::DebugLog("\n[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr + ">]\t Cearing the used pool items.");
                if (unsafe)
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr + ">]\t Also unsafe: "+util::ToString(unsafe)+"; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or \"dangling\" children). So you can clear them yourself after this in a more efficient / cache coherent pass.");
                if (clearDataLoadedFromStorage)
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr + ">]\t Also clearDataLoadedFromStorage: "+util::ToString(clearDataLoadedFromStorage)+"; for example a model will delete the serialized mesh data, or a texture its image. You don't want this unless you're not using it again in the currently loaded game world.");
                uint32_t max = this->maxUsedIndex + 1;
                if (this->items.size() * this->tileSize <= this->maxUsedIndex)
                {
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr + ">]\t Clearing anyway, but items.size() * tileSize: \"" +
                                util::ToString(this->items.size() * this->tileSize) + "\" <= maxUsedIndex: \"" + util::ToString(this->maxUsedIndex) +"\"!? Did you resize the pool?");
                    max = (uint32_t)this->items.size() * this->tileSize;
                }
                for (uint32_t i = 0; i < max; i++)
                {
                    uint32_t tileIndex = (uint32_t)((double)i / (double)this->tileSize);
                    uint32_t indexInTile = i % this->tileSize;
                    auto item = this->items[tileIndex][indexInTile];
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
                            util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr +
                                        ">]\t Delete item only: already marked as cleared/unused in pool: " + gid->id.PrintGlobalUID() + ".");
                        else
                            util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<" + this->topTypeStr +
                                        ">]\t Skipping already marked as cleared/unused in pool: " + gid->id.PrintGlobalUID() + ".");
                        #endif
                    }
                }

                this->firstEmptyIndex = 0;
                this->maxUsedIndex = 0;
                this->validSize = 0;

                // [tdbe] not needed here and also it breaks the new tuple foreach
                //if (alsoDestroy)
                //    delete this;
            };
            
            void Init(const uint32_t maxPossiblePoolSize, const uint32_t tileSize, const uint64_t typeUID, const int16_t worldIndex)
            {
                this->maxPossiblePoolSize = maxPossiblePoolSize;
                this->tileSize = tileSize;
                this->typeUID = typeUID;
                this->topTypeStr = typeid(SVT).name();
                this->worldIndex = worldIndex;
                util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: "+
                    util::ToString(maxPossiblePoolSize)+", tileSize: "+util::ToString(tileSize)+", typeUID: "+util::ToString(typeUID)+", topTypeStr: "+this->topTypeStr+", worldIndex: "+util::ToString(worldIndex));
            };
            
            SubpoolTiledVector()
            {
                util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.");
            };
            
            ~SubpoolTiledVector()
            {
                util::DebugLog("[ArchetypedGameDataPool][~SubpoolTiledVector][Destructed<" + this->topTypeStr + ">] and all its heap items.\n");
            };
            
            SubpoolTiledVector(SubpoolTiledVector const& copy)
            {
                util::DebugError("\n[ArchetypedGameDataPool][SubpoolTiledVector] NotImplementedException. Don't copy this / pass by value.");
            };
            SubpoolTiledVector& operator=(SubpoolTiledVector const& copy) 
            {
                util::DebugError("\n[ArchetypedGameDataPool][SubpoolTiledVector] NotImplementedException. Don't copy this / pass by value.");
                return *this;
            };

            SubpoolTiledVector(SubpoolTiledVector&& rcOther)
            {
                util::DebugError("\n[ArchetypedGameDataPool][SubpoolTiledVector] NotImplementedException. Don't move this.");
            }
            
          // ----------------------------------------------------
          private:
            /// [tdbe] max size of the array, unless you declare it with a smaller size.
            uint32_t maxPossiblePoolSize = std::numeric_limits<uint32_t>::max();
            /// [tdbe] this marks the end of the used items so we don't have to iterate past it.
            uint32_t maxUsedIndex = 0;
            
            /// [tdbe] a Version is a number of how many items were ever created in total in this <see cref="GameDataPool"/>
            /// it is the latest (largest) <see cref="GameDataId.version"/> and ensures the <see cref="GameDataId"/>'s
            /// are unique.
            /// [tdbe] note: a newly allocated pool will still have incremental versions across positions e.g. items[0].v == 1, items[1].v == 2 etc. (instead of 0 and 0)
            uint32_t currentVersion = 0u;
            
            /// [tdbe] item in the array (global across all tiles) that is empty or is marked as empty as far as we're concerned
            uint32_t firstEmptyIndex = 0u;
            uint64_t typeUID = 0u;
            
            std::string topTypeStr = "T";
            uint32_t validSize = 0u;
            uint32_t tileSize = 1u;
            int worldIndex = 0;
            
            bool ScanForNextEmptyIndex(uint32_t& saveIndexTo, const uint32_t startFrom = 0)
            {
                if (this->currentVersion <= startFrom)
                {
                    saveIndexTo = startFrom;
                    return true;
                }

                for (uint32_t i = startFrom; i < this->maxPossiblePoolSize; i++)
                {
                    uint32_t tileIndex = (uint32_t)((double)i / (double)this->tileSize);
                    uint32_t indexInTile = i % this->tileSize;
                    if (this->items[tileIndex][indexInTile]->id.IsCleared())
                    {
                        
                        saveIndexTo = i;
                        return true;
                    }
                }

                for (uint32_t i = 0; i < startFrom; i++)
                {
                    uint32_t tileIndex = (uint32_t)((double)i / (double)this->tileSize);
                    uint32_t indexInTile = i % this->tileSize;
                    if (this->items[tileIndex][indexInTile]->id.IsCleared())
                    {
                        saveIndexTo = i;
                        return true;
                    }
                }

                saveIndexTo = this->maxPossiblePoolSize;
                return false;
            };
            
            /// [tdbe] Get a new item ID set in the next available free slot in our items vector, and update <see
            /// cref="firstEmptyIndex"/> and <see cref="maxUsedIndex"/>. You must emplace the item yourself.
            SpotInPool GetFirstFree(GameDataId::ID& itemId, uint32_t const skipThisManyFreeSlots = 0, const int32_t forcedTile = -1)
            {
                SpotInPool success;
                uint32_t firstEmptyIndexPlus = skipThisManyFreeSlots;
                if(forcedTile == -1)
                {
                    firstEmptyIndexPlus += this->firstEmptyIndex; 
                }
                else
                {
                    bool found = ScanForNextEmptyIndex(firstEmptyIndexPlus, this->tileSize * forcedTile);
                    if(!found || firstEmptyIndexPlus >= this->tileSize * (forcedTile + 1))
                        util::DebugError("[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<" + this->topTypeStr +
                                            ">]\t a new slot was requested in specifically this tile index: " + util::ToString(forcedTile) +
                                            ", however we couldn't get an index in that tile: " + util::ToString(firstEmptyIndexPlus) +
                                            ", (tile size: " + util::ToString(this->tileSize) + "). This should never happen (this pool is of non-shared components unique to the owner entity)! Did you forget to clean up an old unmanaged dangling component and it's now filling this tile?");
                }
                
                if (firstEmptyIndexPlus == this->maxPossiblePoolSize)
                {
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<" + this->topTypeStr + ">]\t firstEmptyIndexPlus: \"" + util::ToString(firstEmptyIndexPlus) +
                                "\", == maxPossiblePoolSize! This pool is full!");
                    success = SpotInPool::FAIL;
                    itemId = {};
                    return success;
                }
                uint32_t tileIndex = (uint32_t)((double)firstEmptyIndexPlus / (double)this->tileSize);
                uint32_t indexInTile = firstEmptyIndexPlus % this->tileSize;
                // [tdbe] reserved to capacity() but not yet constructed at the current index.
                if (this->items.size() <= tileIndex || this->items[tileIndex].size() <= indexInTile || this->items[tileIndex][indexInTile] == nullptr)
                {
                    success = SpotInPool::UNINITIALIZED;
                    itemId.version = ++this->currentVersion;
                    this->validSize++;
                    itemId.indexInChunk = indexInTile;
                    itemId.typeUID = typeUID;
                    itemId.worldIndex = this->worldIndex;
                    itemId.chunkIndex = tileIndex;
                    itemId.typeIndex = std::type_index(typeid(SVT));
                    if (this->maxUsedIndex < firstEmptyIndexPlus)
                        this->maxUsedIndex = firstEmptyIndexPlus;
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<" + this->topTypeStr + ">]\t firstEmptyIndexPlus: \"" + util::ToString(firstEmptyIndexPlus) +
                                "\", BUT the vector('s item) is not yet constructed at the current index ["+util::ToString(tileIndex)+"]["+util::ToString(indexInTile)+"], items.size(): "+util::ToString(this->items.size()));
                }
                else
                {
                    if (this->items[tileIndex][indexInTile]->id.version != GameDataId::FREE)
                    {
                        success = SpotInPool::USED;
                        itemId = {};
                        if (skipThisManyFreeSlots != 0)
                            util::DebugError("[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<" + this->topTypeStr +
                                            ">]\t the version of firstEmptyIndexPlus: " + util::ToString(firstEmptyIndexPlus) +
                                            ", with id \"" + this->items[tileIndex][indexInTile]->id.PrintGlobalUID() +
                                            "\", was not empty! This should never happen!");
                    }
                    else
                    {
                        success = SpotInPool::FREE;
                        this->items[tileIndex][indexInTile]->id.version = ++this->currentVersion;
                        this->validSize++;
                        if (this->maxUsedIndex < firstEmptyIndexPlus)
                            this->maxUsedIndex = firstEmptyIndexPlus;
                        itemId = this->items[tileIndex][indexInTile]->id;
                        #ifdef DEBUG_VERBOSE
                        util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<" + this->topTypeStr + ">]\t Found free item at index: " + util::ToString(firstEmptyIndexPlus) + ", with id: " + itemId.PrintGlobalUID() +
                                    ", validSize: " + util::ToString(this->validSize) + ", currentVersion: " + util::ToString(this->currentVersion));
                        #endif
                    }
                }

                if ((success == SpotInPool::FREE || success == SpotInPool::UNINITIALIZED))// && skipThisManyFreeSlots == 0
                    ScanForNextEmptyIndex(this->firstEmptyIndex, firstEmptyIndexPlus + 1);// this->firstEmptyIndex

                return success;
            };

            bool IsIdValidItem(const GameDataId::ID id) const
            {
                uint32_t tileIndex = (uint32_t)((double)id.indexInChunk / (double)this->tileSize);
                uint32_t indexInTile = id.indexInChunk % this->tileSize;
                if (this->items.size() <= tileIndex || 
                    this->items[tileIndex].size() <= indexInTile)
                {
                    return false;
                }

                if (id.version == GameDataId::FREE)
                {
                    util::DebugLog("[ArchetypedGameDataPool][SubpoolTiledVector][GetItem<" + this->topTypeStr + ">]\t the version of id \"" + id.PrintGlobalUID() +
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
        
        /// [tdbe] use with lambda forEachSubpool([](auto& subpool) { ... });
        template <typename Func> void forEachSubpool(Func&& f) {
            std::apply([&f](auto&... subpools) {
                (f(subpools), ...);
            }, items);
        }
        
        /// [tdbe] See <see cref="items"/>. A subpool is the chunks of entities or of components.
        template <typename T> SubpoolTiledVector<T>& GetSubpoolByType()
        {
            return std::get<SubpoolTiledVector<T>>(items);
        }
        
        static constexpr std::size_t NumTypesInArchetypePool() {
            return sizeof...(Types);
        }
        
        /// [tdbe] All tiles are the same size. It's items[0].size().
        uint32_t TileSize() const
        {
            return tileSize;
        };
        
        /// [tdbe] All tiles are the same size. It's items[0].size().
        uint32_t NumTiles() const
        {
            return std::get<0>(items).items.size();
        };
        
        void ClearItems(bool alsoDestroy = false, bool unsafe = false, bool clearDataLoadedFromStorage = false)
        {
            forEachSubpool([alsoDestroy, unsafe, clearDataLoadedFromStorage](auto& subpoolVec)
            {
                subpoolVec.ClearItems(alsoDestroy, unsafe, clearDataLoadedFromStorage);
            });
        }
        
        ArchetypedGameDataPool(std::vector<uint64_t> typeUIDs, const uint16_t tileSize, const uint32_t maxPossiblePoolSize = 0, const int16_t worldIndex = 0)
        : tileSize(tileSize), worldIndex(worldIndex)
        {
            std::size_t numTypes = sizeof...(Types);
            util::DebugLog("\n[ArchetypedGameDataPool][Constructing an Archetyped Pool]\t\t------------------");
            util::DebugLog("[ArchetypedGameDataPool][Constructing an Archetyped Pool] it's a variadic archetype of "+ util::ToString(numTypes) +" subpools.");
            tileCount = (uint32_t)((double)maxPossiblePoolSize / (double)tileSize);
            if(tileCount == 0u)
                tileCount = 1u;
            uint32_t tCount = tileCount;
            size_t index = 0;
            forEachSubpool([maxPossiblePoolSize, tCount, tileSize, &typeUIDs, worldIndex, &index](auto& subpool) 
            {
                subpool.items.resize(tCount);// [tdbe] newb-friendly-note: no nullptr means it gets default-constructed
                subpool.Init(maxPossiblePoolSize, tileSize, typeUIDs[index++], worldIndex);// the tuple default constructed the subpools
            });
            
            // [tdbe] Construct the whole span. That's what we want for best-average-case gamedev/memory.
            // We also want each chunk for each Type to be allocated next to each other, so the whole archetype fits in cache.
            for (uint32_t tileIdx = 0; tileIdx < tileCount; tileIdx++)
            {
                VariadicIndexedLoopForSubpoolConstructor(std::index_sequence_for<Types...>{}, tileIdx);
            }
            util::DebugLog("[ArchetypedGameDataPool][Constructed Archetyped Pool " + util::BitMaskToString_64u(archetypeMask) + "] and all its subpools and heap items.");
            util::DebugLog("\n[ArchetypedGameDataPool][Constructing an Archetyped Pool]\t\t------------------\n");
        };

        /// [tdbe] Actually dispose of the allocated data
        ~ArchetypedGameDataPool()
        {
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[~ArchetypedGameDataPool][Destructing Archetyped Pool " + util::BitMaskToString_64u(archetypeMask) + "] and all its subpools and heap items.");
            #endif
            forEachSubpool([](auto& subpool) 
            {
                for (uint32_t tileIdx = 0; tileIdx < subpool.items.size(); tileIdx++)
                {
                    for (uint32_t i = 0; i < subpool.items[tileIdx].size(); i++)
                    {
                        if (subpool.items[tileIdx][i] != nullptr)
                        {
                            delete subpool.items[tileIdx][i];
                        }
                    }
                }
                subpool.items.clear();
            });
            archetypeMask = 0ULL;
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[~ArchetypedGameDataPool][Destructed Archetyped Pool " + util::BitMaskToString_64u(archetypeMask) + "] and all its subpools and heap items.\n");
            #endif
        };

        ArchetypedGameDataPool(ArchetypedGameDataPool const& copy)
        {
            util::DebugError("\n[ArchetypedGameDataPool] NotImplementedException. Don't copy this / pass by value.");
        };
        ArchetypedGameDataPool& operator=(ArchetypedGameDataPool const& copy) 
        {
            util::DebugError("\n[ArchetypedGameDataPool] NotImplementedException. Don't copy this / pass by value.");
            return *this;
        };

        ArchetypedGameDataPool(ArchetypedGameDataPool&& rcOther)
        {
            util::DebugError("\n[ArchetypedGameDataPool] NotImplementedException. Don't move this.");
        }
        
        private:
            /// [tdbe] std::vector<T*> contains both active and "deleted" (marked free) items
            /// [tdbe] std::vector<std::vector<T*>> tiles / "chunks" (we split into [tile][item] to fit in cache and be thread friendy).
            /// [tdbe] std::tuple<std::vector<std::vector<T*>>> subpools of tiles of items, e.g. items{T1(chunks(items)), T2(chunks(items))}.
            // [tdbe] newb-friendly-note: the constructor of the pool needs to make sure the actual data the vectors are pointing to, is constructed sequentially or otherwise tries to guarantee a contiguous distribution per tile in the heap memory (and also sequentially cross sub-pool chunk wise (T1 chunk1 next to T2 chunk1 etc. then T1 chunk2 and T2 chunk2 etc.)).
            std::tuple<SubpoolTiledVector<Types>...> items;// std::tuple<std::vector<std::vector<Types*>>...> items;
    
            /// [tdbe] 1 means no split. Splits the subpools into "chunks" of fixed element count size.
            uint32_t tileSize = 1u;// 128 is a good average case number to flexibly fit in cache with any contents and amongst everything else.
            /// [tdbe] how many tiles in each subpool
            uint32_t tileCount = 0u;
    
            /// [tdbe] which types are in this pool
            uint64_t archetypeMask = 0ULL;
            
            int worldIndex = 0;

            /// [tdbe] this ... business is an intermediary step to unpack over variadic type indices and loop,
            /// that helps us have a variadic tuple and also heap allocate in the specific chunk coherent order we need.
            template <std::size_t... Is> void VariadicIndexedLoopForSubpoolConstructor(std::index_sequence<Is...>, const uint32_t tileIdx)
            {
                // For each index I in {0,1,2,...}, do:
                (VariadicSubpoolConstructor<Is>(tileIdx), ...);  // C++17 fold expression
            }

            /// [tdbe] here we continue our constructor while having the I-th variadic type (we specifically know we're on vector<Types[I]*>)
            template <std::size_t I> void VariadicSubpoolConstructor(const uint32_t tileIdx)
            {
                using T = typename std::tuple_element<I, std::tuple<Types...>>::type;
                auto& subpool = std::get<I>(items);// [tdbe] get the I-th subpool<T*>. I needs to be a compile time constant.
                
                subpool.items[tileIdx].resize(tileSize, nullptr);
                for (uint32_t i = 0; i < tileSize; i++)
                {
                    subpool.items[tileIdx][i] = new T();
                    GameDataId* gid = static_cast<GameDataId*>(subpool.items[tileIdx][i]);
                    gid->id.worldIndex = worldIndex;
                    gid->id.typeUID = subpool.GetTypeUID();
                    gid->id.chunkIndex = tileIdx;
                    gid->id.indexInChunk = i;
                    gid->id.version = GameDataId::FREE;
                    gid->id.typeIndex = std::type_index(typeid(T));
                }
                
                archetypeMask |= subpool.GetTypeUID();
                util::DebugLog("\n[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<" + subpool.GetTopTypeStr() + ">] T: "+ typeid(T).name() + 
                                ", maxPossiblePoolSize: " + util::ToString(subpool.GetMaxPossiblePoolSize()) + 
                                ", world: " + util::ToString(subpool.GetWorldIndex()) + 
                                ", typeUID: " + util::ToString(subpool.GetTypeUID()) + "_" + subpool.GetTopTypeStr() +
                                ", firstEmptyIndex: " + util::ToString(subpool.GetFirstEmptyIndex()) +
                                ", tiles: " + util::ToString(tileCount) + 
                                ", tileSize: " + util::ToString(tileSize) + 
                                ", subpool.items.size(): "+util::ToString(subpool.items.size()));
            }
    };
}