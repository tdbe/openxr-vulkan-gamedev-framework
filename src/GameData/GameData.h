#pragma once
#include <boost/bimap.hpp>
#include <string>
#include <array>
#include <vector>
#include <tuple>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <unordered_map>

#include "GameDataPool.h"
#include "TiledGameDataPools.h"
#include "GameDataId.h"

namespace Game
{
    // [tdbe] newb-friendly-note: predeclaring here so we can use pointers here and avoid circular dependency, we reference the real headers inside the .cpp
    struct MeshData;
    struct GameComponent;
    struct Transform;
    struct Parent;
    struct Children;
    struct Model;
    struct Bounds;
    struct ASquidNPC;
    struct AMysterySphere;
    struct Material;
    struct Light;
    struct GameEntity;
    struct GameEntityObject;
    struct PlayerObject;

    /// [tdbe] GameData Singleton; access/query data pools from anywhere.
    /// Note: if you wanted to be maximally efficient e.g. clearing millions of items, you wouldn't randomly hop around different memory spans; 
    /// you'd construct some global command buffer(s) marking all the entities and components the game wants to clear on this frame, 
    /// and then run a sync point with job(s) on the buffers coherently contiguously.
    struct GameData 
    {
      public:
        static uint32_t instanceIdSeed;
        /// [tdbe] a sort of RTTI (RunTimeTypeInformation) because we're a subscriber to events.
        /// (note: todo: right now this a quick addition only used here; the events are also mostly just for show for now)
        const std::string instanceId;

        /// [tdbe] for global uids, 
        /// - used to fetch different categories of items.
        /// - used to assemble archetype bitmasks e.g. on entities.
        /// create more here as you create components.
        static const struct TypeUIDs
        {
            // [tdbe] Note: uint64_t means max count of 64
            static const uint64_t FREE = 0ULL;
            static const uint64_t GAME_ENTITIES = 1ULL<<0;
            static const uint64_t GAME_ENTITY_OBJECTS = 1ULL<<1;
            
            static const uint64_t TRANSFORM_COMPONENTS = 1ULL<<2;
            static const uint64_t PARENT_COMPONENTS = 1ULL<<3;
            static const uint64_t CHILDREN_COMPONENTS = 1ULL<<4;
            static const uint64_t MODEL_COMPONENTS = 1ULL<<5;
            static const uint64_t BOUNDS_COMPONENTS = 1ULL<<6;
            static const uint64_t MATERIAL_COMPONENTS = 1ULL<<7;
            static const uint64_t LIGHT_COMPONENTS = 1ULL<<8;
            
            static const uint64_t A_NPC_MYSTERY_SPHERE = 1ULL<<62;
            static const uint64_t A_NPC_SQUID = 1ULL<<63;
            
            static const inline std::vector<uint64_t> typeUIDsForPools = {GAME_ENTITY_OBJECTS, TRANSFORM_COMPONENTS, PARENT_COMPONENTS, CHILDREN_COMPONENTS, BOUNDS_COMPONENTS, A_NPC_SQUID, A_NPC_MYSTERY_SPHERE};
            
            static std::uint64_t FromTypeIndex(std::type_index typeIndex);
            static std::type_index ToTypeIndex(uint64_t typeUID);
            static std::string ToString(const uint64_t typeUID);
            
            static bool IsTypeUIDEntity(uint64_t uid)
            {
                return uid <= GameData::TypeUIDs::GAME_ENTITY_OBJECTS;
            }
        } TypeUIDs; 

        static const struct AllocationMagicNumbers
        {
            static const uint32_t MAX_GAME_ENTITY_OBJECTS = 100;
            static const uint32_t MAX_VFX_GAME_ENTITY_OBJECTS = 6;
            static const uint32_t MAX_MODELS = 32;
            static const uint32_t MAX_MATERIALS = 50;
            static const uint32_t MAX_VFX_MATERIALS = 4;
            static const uint32_t LIGHTS_COUNT = 10;// [tdbe] remember to change LIGHT_COUNT in _Lighting.glsl, and maybe in Light.vert and LightTentacle.vert
            static const uint32_t DEFAULT_COMPONENTS_PER_GAME_ENTITY_OBJECT = 16;
            static const uint32_t MAX_PLAYER_OBJECTS = 1;
            static const uint16_t POOL_TILE_DEFAULT_SIZE = 128;
        } AllocationMagicNumbers;

#pragma region GameWorld        
        /// [tdbe] GameWorlds are just a way to sort and conceptually group classes of entities + components.
        /// You might want a "bullets entity world", a "game entity object world", a "vfx world" etc.
        /// [tdbe] Tiles: elements don't have to be in order "index per column" but they have to all belong to each other in the current tile (chunk).
        /// (Because of pool reuse + tiling, (re)adding a component asks for the tile of the owner entity (stored in entity ID).)
        /// (The "chunking" does not measure size (e.g. 64kb) it's just based on number of slots, <see cref="AllocationMagicNumbers"/>.)
        /// If you're not using a pool then don't allocate it.
        /// [tdbe] TODO: Nice to have: the tile (chunk) enforce and expose an archetype for the purpose of knowing ahead of time what is in a chunk while querying all chunks.
        struct GameWorld
        {
            /// [tdbe] Note: regarding "[RequireOwnerRestriction(1)]". To support multiple of the same component on the same entity, we need a heap buffer component like <see cref="Children"/>.
          #pragma region Entities and Unique Components
            /// [tdbe] <see cref="GameEntity"/> or <see cref="GameEntityObject"/>: entities with ids and versions ((weak) "references"); and know their components. 
            /// plus the derived GameEntityObject has other little conveniences like events (and name fetching if it's scriptable). Entities and components have ids and versions ((weak) "references"); and know their owner(s).
            /// [tdbe] NOTE: The easiest way is for us to pre-allocate the <see cref="TiledGameDataPools"/> with all possible Components (and Attributes) for any world (we don't do code generation / just in time / any time accounting work). 
            /// So "Entity doesn't have component x" means that component slot is a Free version (and the Entity's archetype mask doesn't contain it) (we could even leave the whole tiled component subvector null in the pool but there is a small max number of components possible (e.g. 64), and, when tiled/chunked, these data structures are small enough to all fit in cpu cache).
            /// So we have "different archetypes per pool per world", and can also change the archetype of the <see cref="TiledGameDataPools"/> during play time.
            /// Importantly we're also able to store an array of <see cref="GameWorld"/>'s. (as opposed to a game worlds tuple, dependent on compile time constants, with variadic types for the archetyped pool, but it's not very useful or usable.)
            /// [tdbe] Note: <see cref="Bounds"/> (AABB) - technically is created per model, and is free (empty) if you don't have a model, but it's stored per entity and editable.
            TiledGameDataPools<GameEntityObject, Transform, Parent, Children, Bounds, ASquidNPC, AMysterySphere>* 
            entityArchetypePool = nullptr;// TODO: you need to remember to add to TypeUIDs and to this template, every new component or attribute manually.
          #pragma endregion Entities And Unique Components
            
          #pragma region Shared Components
            /// [tdbe] entities with ids and versions ((weak) "references"); and know their owner(s).
            /// multiple Models can use the same MeshData; we load the meshData into models
            GameDataPool<Model>* modelComponents = nullptr;
            /// [tdbe] components with ids and versions ((weak) "references"); and know their owner(s).
            /// Just having different materials won't really affect rendering performance; rederer queues per-model right now. 
            /// We have global, per mesh, and per material data, all found in these Materials. The data modifies the
            /// vulkan descriptor or pipeline used if you change a corresponding property.
            GameDataPool<Material>* materialComponents = nullptr;
          #pragma endregion Shared Components
        
          #pragma region Sparse Components  
            /// [tdbe] components with ids and versions ((weak) "references"); and know their owner(s).
            /// [tdbe] The first light is directional (the main directional light)
            GameDataPool<Light>* lightComponents = nullptr;
          #pragma endregion Sparse Components
          
          #pragma region Buffer Components  
            /// [tdbe] components with ids and versions ((weak) "references"); and know their owner(s).
            /// [tdbe] This is for large components that would break the cache-coherency of a chunked or tiled pool. For example components that store arrays of data.
          #pragma endregion Buffer Components
        };

        GameWorld* mainEntityWorld = nullptr;
        GameWorld* npcEntitiesWorld = nullptr;
        /// [tdbe] vfx objects need to be processsed at the end (because their materials need special late drawcalls)
        GameWorld* vfxEntityWorld = nullptr;
        /// [tdbe] NOTE: when you create a new game world you need to add it here so you can fetch it later e.g. from IDs or for rendering.
        /// [tdbe] NOTE: The index because is also saved in the component and entity IDs for reference. 
        std::vector<GameWorld*> gameWorlds;
        int GameWorldsIndexOf(GameWorld* gameWorld){
            for (size_t i=0; i < gameWorlds.size(); i++){
                if(gameWorlds[i] == gameWorld)
                        return i;
            }
            return -1;
        }

#pragma endregion GameWorld

#pragma region StorageData
        /// [tdbe] data buffer loaded from e.g. 3d objects in storage
        MeshData* meshData = nullptr;

        void DeleteAllMeshData();
        /// [tdbe] This is mostly here to draw attention to the <see cref="Model"/> --> <see cref="MeshData"/> --> <see cref="DataBuffer"/> relationship.
        /// Not very useful: 
        /// 1). We move all possible 3d models to the gpu on <see cref="LoadGameWorlds"/>, and then never replace any parts of those vertex buffers (unless we unload/reload). 
        /// 2). We'd need a better data streaming strategy than arbitrary recreation of the whole buffer.
        void UnLoadModelMesh(Model* model);
#pragma endregion StorageData

#pragma region GameComponent
        /// [tdbe] Normally you want to fetch a component pool from a game world to acquire cache-coherent chunks. Otherwise this is for convenience and iteration preparing renderer draw calls.
        /// [tdbe] Note: todo: might be nice to manage some kind of custom pointer that invalidates itself when the item version changes.
        GameComponent* GetComponent(GameDataId::ID id);
        /// [tdbe] ecs note: <param name="unsafe"> If true, it won't clean itself up from any references / owners.</param>
        void ClearComponent(GameDataId::ID id, bool unsafe = false);
#pragma endregion GameComponent

#pragma region GameEntity
        /// [tdbe] Normally you want to fetch an entity pool from a game world to acquire cache-coherent chunks. Otherwise this is for convenience and iteration preparing renderer draw calls.
        /// [tdbe] Note: todo: might be nice to manage some kind of custom pointer that invalidates itself when the item version changes.
        GameEntity* GetEntity(GameDataId::ID id);
        /// [tdbe] ecs note: <param name="unsafe"> If true, it won't clean itself up from any references / owners.</param>
        void ClearEntity(GameDataId::ID id, bool unsafe = false);
#pragma endregion GameEntity

#pragma region Players
        /// [tdbe] for now a player is a collection of game entity object pointers, and states.
        std::vector<PlayerObject*> playerObjects;
#pragma endregion Players

#pragma region Scripting
        /// [tdbe] named shortcuts for convenience / scripting reasons; the actual entities are on <see cref="GameDataPool"/>'s.
        /// (across all game worlds and entity types)
        boost::bimap<std::string, GameDataId::ID> namedGameObjectIDs;

        /// [tdbe] named shortcuts for convenience / scripting reasons; the actual components are on <see cref="GameDataPool"/>'s.
        boost::bimap<std::string, GameDataId::ID> namedModelComponentIDs;
        /// [tdbe] named shortcuts for convenience / scripting reasons; the actual components are on <see cref="GameDataPool"/>'s.
        boost::bimap<std::string, GameDataId::ID> namedMaterialComponentIDs;
        /// [tdbe] named shortcuts for convenience / scripting reasons; the actual components are on <see cref="GameDataPool"/>'s.
        boost::bimap<std::string, GameDataId::ID> namedLightComponentIDs;
#pragma endregion Scripting

        bool LoadGameWorlds();
        /// [tdbe] Run on all the buffers marking them as clear
        /// (contiguously if <param name="fast"/> is true (but then it doesn't detatch owners/children/components))
        bool UnLoadGameWorlds(bool fast = true);

        static GameData& Instance()
        {
            static GameData instance;
            return instance;
        }
        /// [tdbe] You should have alreaady unloaded your game worlds at this point <see cref="UnLoadGameWorlds"/>
        ~GameData();

      private:
        GameData();
        GameData(GameData const& copy);// [tdbe] singleton; don't allow copy
        GameData& operator=(GameData const& copy);// [tdbe] singleton; don't allow copy

        bool LoadModels();
        bool LoadMaterials();
        bool LoadGameLights();
        bool LoadGameEntityObjects();
        bool LoadVFXEntityObjects();
        bool LoadPlayers();
        
        void DeletePlayers();
        void DeleteEntityPools();
        void DeleteComponentPools();
        void DeleteWorlds();

#pragma region Events
        /// [tdbe] (There's a nice multi-subscribe Visual C++ event system, with __hook, __unhook, __event, __raise, keywords etc., but only compilable from visual studio. So instead we emulate it in peasant land :))
        void HookOnGameObjectEvents();
        /// [tdbe] (There's a nice multi-subscribe Visual C++ event system, with __hook, __unhook, __event, __raise, keywords etc., but only compilable from visual studio. So instead we emulate it in peasant land :))
        void UnhookOnGameObjectEvents();
        /// [tdbe] added to pool (marked as not free)
        void OnGameEntityObjectAddedHandler(GameEntityObject* newObject);
        /// [tdbe] removed from pool (marked as free)
        void OnGameEntityObjectRemovedHandler(GameEntityObject* oldObject);
#pragma endregion Events
#pragma region LoaderLogging
        void ConfiguredGameObject(GameEntityObject* newObject);
        void ConfiguredGameModel(Model* newObject);
        void ConfiguredGameMaterial(Material* newObject);
        void ConfiguredGameLight(Light* newObject);
#pragma endregion LoaderLogging
    };
} // namespace Game