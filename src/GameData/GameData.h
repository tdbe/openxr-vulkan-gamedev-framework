#pragma once
#include <boost/bimap.hpp>
#include <string>
#include <array>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <unordered_map>

#include "GameDataPool.h"
#include "GameDataId.h"

namespace Game
{
    // [tdbe] newb-friendly-note: predeclaring here so we can use pointers here and avoid circular dependency, we reference the real headers inside the .cpp
    struct MeshData;
    struct GameComponent;
    struct Transform;
    struct Parent;
    struct Children;
    struct ARoot;
    struct Model;
    struct Bounds;
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

        /// [tdbe] for global uids, and used to fetch different categories of items, you can create more here.
        static const struct TypeUIDs
        {
            static const uint16_t FREE = GameDataId::FREE;
            static const uint16_t GAME_ENTITY_OBJECTS = 100;
            static const uint16_t GAME_ENTITIES = 200;
            static const uint16_t TRANSFORM_COMPONENTS = 300;
            static const uint16_t PARENT_COMPONENTS = 310;
            static const uint16_t CHILDREN_COMPONENTS = 311;
            static const uint16_t ROOT_ATTRIBUTE_COMPONENTS = 315;
            static const uint16_t MODEL_COMPONENTS = 400;
            static const uint16_t BOUNDS_COMPONENTS = 500;
            static const uint16_t MATERIAL_COMPONENTS = 600;
            static const uint16_t LIGHT_COMPONENTS = 700;
            static std::string ToString(const uint16_t id)
            {
                if (id == GameDataId::FREE)
                    return "FREE";
                else if (id == GAME_ENTITY_OBJECTS)
                    return "GAME_ENTITY_OBJECTS";
                else if (id == GAME_ENTITIES)
                    return "GAME_ENTITIES";
                else if (id == TRANSFORM_COMPONENTS)
                    return "TRANSFORM_COMPONENTS";
                else if (id == PARENT_COMPONENTS)
                    return "PARENT_COMPONENTS";
                else if (id == CHILDREN_COMPONENTS)
                    return "CHILDREN_COMPONENTS";
                else if (id == ROOT_ATTRIBUTE_COMPONENTS)
                    return "ROOT_ATTRIBUTE_COMPONENTS";
                else if (id == MODEL_COMPONENTS)
                    return "MODEL_COMPONENTS";
                else if (id == BOUNDS_COMPONENTS)
                    return "BOUNDS_COMPONENTS";
                else if (id == MATERIAL_COMPONENTS)
                    return "MATERIAL_COMPONENTS";
                else if (id == LIGHT_COMPONENTS)
                    return "LIGHT_COMPONENTS";
                else
                    return "~~~PLEASE_DEFINE~~~";
            };
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
        } AllocationMagicNumbers;

        /// [tdbe] GameWorlds are just a way to sort and conceptually chunk classes of entities + components.
        /// You might want a "bullets entity world", a "game entity object world", a "vfx world" etc.
        /// [tdbe] Tiles: elements don't have to be in order "index per column" but they have to all belong to each other in the current tile.
        /// (Because of pool reuse + tiling, (re)adding a component asks for the tile of the owner entity (stored in entity ID).)
        /// (The "chunking" does not measure size (e.g. 64kb) it's just based on number of slots, most flexible for components & gamedev.)
        /// (If you're not using a pool then don't allocate it.)
        /// [tdbe] TODO: Nice to have: the tile (chunk) enforce and expose an archetype for the purpose of knowing ahead of time what is in a chunk while querying all chunks.
        struct GameWorld
        {
          #pragma region Regular Components
            /// [tdbe] components with ids and versions ((weak) "references"); and know their owner(s).
            /// The transform is one per game entity.
            GameDataPool<Transform>* transformComponents = nullptr;
            GameDataPool<Parent>* parentComponents = nullptr;
            GameDataPool<Children>* childrenComponents = nullptr;
            GameDataPool<ARoot>* rootAttributeComponents = nullptr;
            /// [tdbe] components with ids and versions ((weak) "references"); and know their owner(s).
            /// Bounds (AABB) - technically is created per model, and is free if you don't have a model, and it's stored per entity.
            GameDataPool<Bounds>* boundsComponents = nullptr;
          #pragma endregion Regular Components
            
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
            /// The first light is directional (the main directional light)
            GameDataPool<Light>* lightComponents = nullptr;
          #pragma region Sparse Components
          
            /// [tdbe] entities with ids and versions ((weak) "references"); and know their components. 
            /// plus the derived GameEntityObject has other little conveniences like events (and name fetching if it's scriptable).
            /// <see cref="GameEntity"/> or <see cref="GameEntityObject"/>-- TODO: we can't solve this with std:any and Templates unfortunately. So for now just using the heavier semi oop derived type: <see cref="GameEntityObject"/>.
            GameDataPool<GameEntityObject>* gameEntityObjects = nullptr;
        };
        
#pragma region StorageData
        /// [tdbe] data buffer loaded from e.g. 3d objects in storage
        MeshData* meshData = nullptr;

        void DeleteAllMeshData();
        /// [tdbe] This is mostly here to draw attention to the <see cref="Model"/> --> <see cref="MeshData"/> --> <see cref="DataBuffer"/> relationship.
        /// Not very useful: 
        /// 1). We move all possible 3d models to the gpu on <see cref="LoadGameWorld"/>, and then never replace any parts of those vertex buffers (unless we unload/reload). 
        /// 2). We'd need a better data streaming strategy than arbitrary recreation of the whole buffer.
        void UnLoadModelMesh(Model* model);
#pragma endregion StorageData

#pragma region GameComponent
        /// Note: todo: might be nice to manage some kind of custom pointer that invalidates itself when the item version changes.
        GameComponent* GetComponent(GameDataId::ID id);
        /// [tdbe] ecs note: <param name="unsafe"> If true, it won't clean itself up from any references / owners.</param>
        void ClearComponent(GameDataId::ID id, bool unsafe = false);
#pragma endregion GameComponent

#pragma region GameEntity
        /// Note: todo: might be nice to manage some kind of custom pointer that invalidates itself when the item version changes.
        GameEntity* GetEntity(GameDataId::ID id);
        /// [tdbe] ecs note: <param name="unsafe"> If true, it won't clean itself up from any references / owners.</param>
        void ClearEntity(GameDataId::ID id, bool unsafe = false);
#pragma endregion GameEntity

#pragma region GameWorld
        GameWorld* entityObjectsWorld = nullptr;
        /// [tdbe] vfx objects need to be at the end of the list (because their materials need special late drawcalls)
        GameWorld* vfxEntityObjectsWorld = nullptr;
        std::vector<GameWorld*> gameWorlds;
        int GameWorldsIndexOf(GameWorld* world)
        {
            for(int i = 0; i < gameWorlds.size(); i++)
            {
                if(gameWorlds[i] == world)
                    return i;
            }
            return -1;
        };
#pragma endregion GameWorld

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

        bool LoadGameWorld();
        /// [tdbe] Run on all the buffers marking them as clear
        /// (contiguously if <param name="fast"/> is true (but then it doesn't detatch owners/children/components))
        bool UnLoadGameWorld(bool fast = true);

        static GameData& Instance()
        {
            static GameData instance;
            return instance;
        }
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