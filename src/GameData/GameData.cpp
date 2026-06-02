
#include "../Utils/Util.h"

#include "GameData.h"
#include "MeshData.h"
#include "Components/Transform.h"
#include "Components/Parent.h"
#include "Components/Children.h"
#include "Components/Model.h"
#include "Components/Bounds.h"
#include "Components/Material.h"
#include "Components/Light.h"
#include "Attributes/ASquidNPC.h"
#include "Attributes/AMysterySphere.h"
#include "Entities/GameEntityObject.h"
#include "Entities/GameEntity.h"
#include "PlayerObject.h"

using namespace Game;
using namespace boost;

uint32_t GameData::instanceIdSeed = 0;

GameData::GameData()
{    
    const_cast<std::string&>(instanceId) = "GameData_" + util::ToString(instanceIdSeed++);  
    util::DebugLog("[Game][GameData][Singleton]\t This is the source of all data pools. Singleton instanceId: \"" + instanceId + "\".");
}

GameData& Game::GameData::operator=(GameData const& copy)
{
    util::DebugError("[Game][GameData][=]\t Can't copy GameData, it's a singleton.");
    return *this;
}

/// [tdbe] (deserialize, allocate, and basic init of the current scene/world)
bool GameData::LoadGameWorlds()
{
    util::DebugLog("\n[Game][GameData][LoadGameWorlds]\t.....................................................................................................................................");
    util::DebugLog("[Game][GameData][LoadGameWorlds]\t\t\t\t Loading Game World(s):");
    util::DebugLog("[Game][GameData][LoadGameWorlds]\t Loading, deserializing, creating pools for entities and components, hooking some events, creating some quick access maps:");

    mainEntityWorld = new GameWorld();
    npcEntitiesWorld = new GameWorld();
    vfxEntityWorld = new GameWorld();
    gameWorlds.resize(2);
    gameWorlds.at(0) = mainEntityWorld;
    //gameWorlds.at(1) = npcEntitiesWorld;
    gameWorlds.at(1) = vfxEntityWorld;

    bool success = true;
    success = success && LoadModels();
    success = success && LoadMaterials();
    success = success && LoadGameLights();

    HookOnGameObjectEvents();
    success = success && LoadGameEntityObjects();
    success = success && LoadVFXEntityObjects();
    success = success && LoadPlayers();

    util::DebugLog("[Game][GameData][LoadGameWorlds]\t\t\t\t Loaded Game World(s).");
    util::DebugLog("[Game][GameData][LoadGameWorlds]\t.....................................................................................................................................\n");
    
    return success;
}

GameComponent* GameData::GetComponent(GameDataId::ID id)
{
    if (id.typeUID == TypeUIDs.TRANSFORM_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Transform>().GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.PARENT_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Parent>().GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.CHILDREN_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Children>().GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.MODEL_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->modelComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.BOUNDS_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Bounds>().GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.MATERIAL_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->materialComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.LIGHT_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->lightComponents->GetItem(id);
    }
    else
    {
        return nullptr;
    }
}

template <typename EntityT, typename PoolT>
GameEntity* CompileTimeEntityTypeChecker(PoolT* pool, GameDataId::ID id)
{
    if constexpr (std::is_base_of_v<GameEntity, EntityT> &&
                  PoolT::template ContainsType<EntityT>())
    {
        return pool->GetSubpoolByType<EntityT>().GetItem(id);
    }
    else
    {
        return nullptr;
    }
}

GameEntity* GameData::GetEntity(GameDataId::ID id)
{
    if (id.typeUID == TypeUIDs.GAME_ENTITY_OBJECTS)
    {
        return CompileTimeEntityTypeChecker<GameEntityObject>(gameWorlds[id.worldIndex]->entityArchetypePool, id);
    }
    else if (id.typeUID == TypeUIDs.GAME_ENTITIES)
    {
        return CompileTimeEntityTypeChecker<GameEntity>(gameWorlds[id.worldIndex]->entityArchetypePool, id);
    }
    return nullptr;
}

void GameData::ClearComponent(GameDataId::ID id, bool unsafe)
{
    if (id.typeUID == TypeUIDs.TRANSFORM_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Transform>().ClearItem(gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Transform>().GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.MODEL_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->modelComponents->ClearItem(gameWorlds[id.worldIndex]->modelComponents->GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.BOUNDS_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Bounds>().ClearItem(gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<Bounds>().GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.MATERIAL_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->materialComponents->ClearItem(gameWorlds[id.worldIndex]->materialComponents->GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.LIGHT_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->lightComponents->ClearItem(gameWorlds[id.worldIndex]->lightComponents->GetItem(id), unsafe);
    }
}

void GameData::ClearEntity(GameDataId::ID id, bool unsafe)
{
    if (id.typeUID == TypeUIDs.GAME_ENTITY_OBJECTS)
    {
        gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<GameEntityObject>().ClearItem(gameWorlds[id.worldIndex]->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.GAME_ENTITIES)
    {
        //gameWorlds[id.worldIndex]->gameEntities->ClearItem(gameWorlds[id.worldIndex]->gameEntities->GetItem(id), unsafe);
        // TODO:
        util::DebugError("[GameData][ClearEntity] 'NotImplementedException': see GameWorld::gameEntityObjects");
    }
}

bool GameData::LoadModels()
{
    util::DebugLog("\n[Game][GameData][LoadModels]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadModels]\t\t Loading Models");
    bool success = true;
    int entityObjectsWorldIndex = GameWorldsIndexOf(mainEntityWorld);
    if(mainEntityWorld->modelComponents != nullptr) { util::DebugError("[GameData][LoadModels]\t Somebody forgot to clear their pool (mainEntityWorld)!"); mainEntityWorld->modelComponents->ClearItems(false); }
    mainEntityWorld->modelComponents = new GameDataPool<Model>(AllocationMagicNumbers::MAX_MODELS, 
                                                                    AllocationMagicNumbers::MAX_MODELS, entityObjectsWorldIndex,
                                                                    TypeUIDs.MODEL_COMPONENTS);
    
    DeleteAllMeshData(); // [tdbe] (meshes are kept on the gpu)
    meshData = new MeshData();

    Model* gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/quad.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"quadModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/ground_displaced_4096.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"groundModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Ruins.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"ruinsModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Car.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"carModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Beetle_glassless.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"beetleModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Beetle_glass_only.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"beetleGlassModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Bike.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"bikeModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Hand.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"handModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/cube.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"cubeModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Logo_OpenXR_Vulkan.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"logoModel1Comp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Logo_Framework.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"logoModel2Comp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_Locomotion_Flat.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"textLocomotionModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_Suda_Beam_Flat.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"textSudaBeamModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_See_Controls_md.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"textSeeControlsMdModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv4_half_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"icosphereModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv4_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"icosphereSmoothModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv3_0.75_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"icosphereRoughModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/tube_light_1_03.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"tube_light_1_03", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/SudaBeam.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"sudaBeamModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Squid_Happy_Grumpy.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"squidModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = mainEntityWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/SuzanneHighQuality20k.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"suzanneMonkeModelComp", gco->id});
    ConfiguredGameModel(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX 
    
    return success;
}

// [tdbe] Note: the order in which you set up your materials is the order in which objects get rendered
bool GameData::LoadMaterials()
{
    util::DebugLog("\n[Game][GameData][LoadMaterials]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadMaterials]\t\t Loading Materials");
    bool success = true;
    
    int entityObjectsWorldIndex = GameWorldsIndexOf(mainEntityWorld);
    //int npcEntityObjectsWorldIndex = GameWorldsIndexOf(npcEntitiesWorld);
    int vfxEntityWorldIndex = GameWorldsIndexOf(vfxEntityWorld);
    
    if(mainEntityWorld->materialComponents != nullptr) { util::DebugError("[GameData][LoadMaterials]\t Somebody forgot to clear their pool!"); mainEntityWorld->materialComponents->ClearItems(false); }
    mainEntityWorld->materialComponents = new GameDataPool<Material>(AllocationMagicNumbers::MAX_MATERIALS, AllocationMagicNumbers::MAX_MATERIALS, 
                                                                        entityObjectsWorldIndex, TypeUIDs.MATERIAL_COMPONENTS);
    
    if(vfxEntityWorld->materialComponents != nullptr) { util::DebugError("[GameData][LoadMaterials]\t Somebody forgot to clear their pool (vfx entities)!"); vfxEntityWorld->materialComponents->ClearItems(false); }
    vfxEntityWorld->materialComponents = new GameDataPool<Material>(AllocationMagicNumbers::MAX_VFX_MATERIALS, AllocationMagicNumbers::MAX_VFX_MATERIALS, 
                                                                           vfxEntityWorldIndex, TypeUIDs.MATERIAL_COMPONENTS);

    Material* gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"skyMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseMetalishMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseStoneMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseTripIcosphereMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseEyesMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);
    
    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"textMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"logoMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] ^ all the (entities with the) materials above are meant to have the same diffuse style blend pipeline,
    // so they'll be batched in the <see cref="Renderer"/> because the materials are reserved here in relative order in the pool.

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"groundMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] customization / hack: we skip <see cref="skip"/> free slots in case we want to 
    // add more materials with the same pipeline as above, during runtime, that we want batched.
    uint32_t skip = 20;
    std::tuple<uint32_t, uint32_t> lastDiffuseMaterialAt(0u, gco->id.indexInChunk);// we'd have to share this with whoever adds new mats at runtime
    
    gco = mainEntityWorld->materialComponents->GetFreeItem(skip);
    namedMaterialComponentIDs.insert({"squidMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"lightMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"tentacleLightMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] Transparent materials (todo: add a job for sorting objects.
    // Per pixel sorting with a Order-independent transparency spv? 
    // But rather than packing sorting pixels I'd rather raytrance into ..something indirect, volumes, nanites..)

    // [tdbe] Note: here I set up 2 materials per transparent material, so I can have 2 pipelines for the same mesh:
    // 1. render the backfaces only, as transparent (and zwrite)
    // 2. render the frontfaces only, as transparent
    // (otherwise the lack of triangle/any sorting will result in the same object's backfaces sometimes being rendered on top of its frontfaces)
    // (an entity (and its model component) can have multiple materials, the engine doesn't care / enforce it but only copies the unioform data from the first entry.)

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseTransparentBackfaceInstancedMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"bikeTransparentBackfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseTransparentFrontfaceInstancedMaterialComp", gco->id});
    ConfiguredGameMaterial(gco); 

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"bikeTransparentFrontfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"glassTransparentBackfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);
    gco = mainEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"glassTransparentFrontfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] VFX materials

    gco = vfxEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"skyOfChaperoneMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);
    
    gco = vfxEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"floorGridMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = vfxEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"ceilingGridMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = vfxEntityWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"handsMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

    return success;
}

bool GameData::LoadGameLights()
{
    util::DebugLog("\n[Game][GameData][LoadLights]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadLights]\t\t Loading Lights");
    bool success = true;
    
    int entityObjectsWorldIndex = GameWorldsIndexOf(mainEntityWorld);
    
    if(mainEntityWorld->lightComponents != nullptr) { util::DebugError("[GameData][LoadGameLights]\t Somebody forgot to clear their pool!"); mainEntityWorld->lightComponents->ClearItems(false); }
    mainEntityWorld->lightComponents = new GameDataPool<Light>(AllocationMagicNumbers::LIGHTS_COUNT, 
                                                AllocationMagicNumbers::LIGHTS_COUNT, 
                                                entityObjectsWorldIndex,
                                                TypeUIDs.LIGHT_COMPONENTS);

    Light* gco = mainEntityWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"mainDirectionalLightComp", gco->id});
    ConfiguredGameLight(gco);

    for (int i = 1; i < 7; i++)
    {
        gco = mainEntityWorld->lightComponents->GetFreeItem();
        namedLightComponentIDs.insert({"tentacleLightComp0" + util::ToString(i, true), gco->id});
        ConfiguredGameLight(gco);
    }

    gco = mainEntityWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"handLight01Comp", gco->id});
    ConfiguredGameLight(gco);

    gco = mainEntityWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"handLight02Comp", gco->id});
    ConfiguredGameLight(gco);

    gco = mainEntityWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"bikeLightComp", gco->id});
    ConfiguredGameLight(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

    return success;
}

bool GameData::LoadGameEntityObjects()
{
    util::DebugLog("\n[Game][GameData][LoadGameEntityObjects]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadGameEntityObjects]\t\t Loading Game Entity Objects (main mainEntityWorld)");
    bool success = true;
    int entityObjectsWorldIndex = GameWorldsIndexOf(mainEntityWorld);

    if (mainEntityWorld->entityArchetypePool != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool (entityArchetypePool)!"); mainEntityWorld->entityArchetypePool->ClearItems(false); }
    mainEntityWorld->entityArchetypePool = new TiledGameDataPools<GameEntityObject, Transform, Parent, Children, Bounds, ASquidNPC, AMysterySphere>(
                                                        TypeUIDs.typeUIDsForPools,
                                                        AllocationMagicNumbers::POOL_TILE_DEFAULT_SIZE, 
                                                        AllocationMagicNumbers::MAX_GAME_ENTITY_OBJECTS,
                                                        entityObjectsWorldIndex);
    
    GameEntityObject* gento = nullptr;
    GameComponent* comp = nullptr;
    Transform* trans = nullptr;
    Parent* parent = nullptr;
    Children* children = nullptr;
    Bounds* bounds = nullptr;

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("worldRoot");// [tdbe] don't worry the name is not stored on the entity, there's a separate bidirectional hash map for scriptable objects.
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);// [tdbe] we are specifying we want a spot in the same chunk as the entity we just requested.
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    namedGameObjectIDs.insert({"worldRoot", gento->id});
    ConfiguredGameObject(gento);

    // [tdbe] (the following order does not affect render/batching order; that order's in the material pool)

    // [tdbe] entities with Lights
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("mainDirectionalLight");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("mainDirectionalLightComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    ConfiguredGameObject(gento);

    for (int i = 1; i < 7; i++)
    {
        gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
        gento->SetName("tentacle0" + util::ToString(i, true));
        trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
        trans->AddOwnerId(gento->id);
        gento->AddComponentId(trans->id);
        parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
        parent->AddOwnerId(gento->id);
        gento->AddComponentId(parent->id);
        children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
        children->AddOwnerId(gento->id);
        gento->AddComponentId(children->id);
        comp = GetComponent(namedLightComponentIDs.left.at("tentacleLightComp0" + util::ToString(i, true)));
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        static_cast<Light*>(comp)->SetVisible(false);
        comp = GetComponent(namedModelComponentIDs.left.at("tube_light_1_03"));
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
        bounds->SetBoundsAABB(static_cast<Model*>(comp));
        bounds->AddOwnerId(gento->id);
        gento->AddComponentId(bounds->id);
        comp = GetComponent(namedMaterialComponentIDs.left.at("tentacleLightMaterialComp"));
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        ConfiguredGameObject(gento);
    }    

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("handLight01");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("handLight01Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    comp = GetComponent(namedModelComponentIDs.left.at("tube_light_1_03"));// [tdbe] Todo: need a procedural capsule that can be squished while preserving hemispherical ends
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("lightMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("handLight02");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("handLight02Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    comp = GetComponent(namedModelComponentIDs.left.at("tube_light_1_03"));// [tdbe] Todo: need a procedural capsule that can be squished while preserving hemispherical ends
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("lightMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("bikeLight");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("bikeLightComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    // comp = GetComponent(namedModelComponentIDs["tube_light_1_03"]);// [tdbe] Todo: need a procedural capsule that can
    // be squished while preserving hemispherical ends comp->AddOwnerId(gento->id); gento->AddComponentId(comp->id);
    // bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    // bounds->SetBoundsAABB(static_cast<Model*>(comp));
    // bounds->AddOwnerId(gento->id);
    // gento->AddComponentId(bounds->id);
    // comp = GetComponent(namedMaterialComponentIDs["lightMaterialComp"]);
    // comp->AddOwnerId(gento->id);
    // gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    // [tdbe] world sky

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("icosphereSkybox_world");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("skyMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    // [tdbe] regular game entities
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("ground");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("groundModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("groundMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("ruins");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("ruinsModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("carLeft");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("carModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("carRight");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("carModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("beetle");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("beetleModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("beetleGlass");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("beetleGlassModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("glassTransparentFrontfaceMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("glassTransparentBackfaceMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("bike");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("bikeModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("bikeTransparentFrontfaceMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("bikeTransparentBackfaceMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("logo1");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("logoModel1Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("logoMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("logo2");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("logoModel2Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("logoMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("textLocomotion");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("textLocomotionModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("textMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("textSudaBeam");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("textSudaBeamModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("textMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("textSeeControlsMd");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("textSeeControlsMdModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("textMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("cube");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("cubeModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("icosphereSmoothTripInstancing");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseTripIcosphereMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("icosphereSmoothForInstancing");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseTransparentFrontfaceInstancedMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseTransparentBackfaceInstancedMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("sudaBeam01");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("sudaBeamModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("sudaBeam02");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("sudaBeamModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("squid");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("squidModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("squidMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("testSquid");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("squidModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("squidMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("monke");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("suzanneMonkeModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("monkeEye1");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereRoughModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseEyesMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("monkeEye2");
    trans = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereRoughModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = mainEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseEyesMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX (max game objects in this case) (but also check each components' max)

    return success;
}

/// [tdbe] vfx objects are rendered at the end of the queue for the sake of the chaperone / depth etc.
bool GameData::LoadVFXEntityObjects()
{
    util::DebugLog("\n[Game][GameData][LoadVFXEntityObjects]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadVFXEntityObjects]\t\t Loading Game VFX Objects (vfxEntityWorld)");
    bool success = true;
    int vfxEntityWorldIndex = GameWorldsIndexOf(vfxEntityWorld);
    
    if (vfxEntityWorld->entityArchetypePool != nullptr) { util::DebugError("[GameData][LoadGameVFXEntityObjects]\t Somebody forgot to clear their pool (vfxEntityWorld->entityArchetypePool)!"); vfxEntityWorld->entityArchetypePool->ClearItems(false); }
     vfxEntityWorld->entityArchetypePool = new TiledGameDataPools<GameEntityObject, Transform, Parent, Children, Bounds, ASquidNPC, AMysterySphere>(
                                                        TypeUIDs.typeUIDsForPools,
                                                        AllocationMagicNumbers::POOL_TILE_DEFAULT_SIZE, 
                                                        AllocationMagicNumbers::MAX_VFX_GAME_ENTITY_OBJECTS,
                                                        vfxEntityWorldIndex);

    GameEntityObject* gento = nullptr;
    GameComponent* comp = nullptr;
    Transform* trans = nullptr;
    Parent* parent = nullptr;
    Children* children = nullptr;
    Bounds* bounds = nullptr;

    gento = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("worldRoot");
    trans = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    ConfiguredGameObject(gento);
    

    gento = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("icosphereSkybox_chaperone");
    trans = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = mainEntityWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("icosphereModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("skyOfChaperoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("floorGrid");
    trans = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = mainEntityWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("quadModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("floorGridMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("ceilingGrid");
    trans = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = mainEntityWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("quadModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("ceilingGridMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("handLeft");
    trans = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = mainEntityWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("handModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("handsMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetFreeItem();
    gento->SetName("handRight");
    trans = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Transform>().GetFreeItem(0, gento->id.chunkIndex);
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Parent>().GetFreeItem(0, gento->id.chunkIndex);
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Children>().GetFreeItem(0, gento->id.chunkIndex);
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = mainEntityWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("handModelComp"));// stole model from main world
    // comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = vfxEntityWorld->entityArchetypePool->GetSubpoolByType<Bounds>().GetFreeItem(0, gento->id.chunkIndex);
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("handsMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX (max game objects in this case) (but also check each components' max)

    return success;
}

bool GameData::LoadPlayers()
{
    util::DebugLog("\n[Game][GameData][LoadPlayers]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadPlayers]\t\t Loading Players:");
    bool success = true;
    playerObjects.resize(AllocationMagicNumbers.MAX_PLAYER_OBJECTS);
    playerObjects.at(0) = new PlayerObject(namedGameObjectIDs.left.at("worldRoot"), 
                                           namedGameObjectIDs.left.at("handLeft"),
                                           namedGameObjectIDs.left.at("handRight"), 
                                           "XR Player 1");

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX
    
    util::DebugLog("[Game][GameData][LoadPlayers]\t\t Loaded Players.");
    util::DebugLog("[Game][GameData][LoadPlayers]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    return success;
}

#pragma region LoaderLogging
void Game::GameData::ConfiguredGameObject(GameEntityObject* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorlds][GameEntityObject]\t Configured {name: \"" + newObject->GetName() + "\", id: \"" + 
                    newObject->id.PrintGlobalUID() + "\", is std::type_index(typeid(GameEntityObject)): " +
                    util::ToString(newObject->id.typeIndex == std::type_index(typeid(GameEntityObject))) + ".");
}

void Game::GameData::ConfiguredGameModel(Model* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorlds][Component][Model]\t Configured component with id: \"" + newObject->id.PrintGlobalUID() +
                   "\", is std::type_index(typeid(Model)): " + util::ToString(newObject->id.typeIndex == std::type_index(typeid(Model))) + ".");
}

void Game::GameData::ConfiguredGameMaterial(Material* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorlds][Component][Material]\t Configured component with id: \"" + newObject->id.PrintGlobalUID() + 
                    "\", is std::type_index(typeid(Material)): " + util::ToString(newObject->id.typeIndex == std::type_index(typeid(Material))) + ".");
}

void GameData::ConfiguredGameLight(Light* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorlds][Component][Light]\t Configured component with id: \"" + newObject->id.PrintGlobalUID() +
                   "\", is std::type_index(typeid(Light)): " + util::ToString(newObject->id.typeIndex == std::type_index(typeid(Light))) + ".");
}
#pragma endregion LoaderLogging

#pragma region Events
void GameData::OnGameEntityObjectAddedHandler(GameEntityObject* newObject)
{
    util::DebugLog("[Game][GameData][GameEntityObject]\t Using: {name: \"" + newObject->GetName() + "\", id: \"" +
                   newObject->id.PrintGlobalUID() + "\", is std::type_index(typeid(GameEntityObject)): " +
                   util::ToString(newObject->id.typeIndex == std::type_index(typeid(GameEntityObject))) + ".");
}

void GameData::OnGameEntityObjectRemovedHandler(GameEntityObject* oldObject)
{
    util::DebugLog("[Game][GameData][GameEntityObject]\t Disusing: {name: \"" + oldObject->GetName() + "\", id: \"" +
                   oldObject->id.PrintGlobalUID() + "\" .\n");
}

void GameData::HookOnGameObjectEvents()
{
    GameEntityObject::SubscribeGameEntityObjectEvents(
                    // [tdbe] we need to specify an object wrapper and closure, it's not just sending a function pointer
        instanceId, [this](GameEntityObject* newObject) { this->OnGameEntityObjectAddedHandler(newObject); },
        instanceId, [this](GameEntityObject* oldObject) { this->OnGameEntityObjectRemovedHandler(oldObject); }); 
}

void GameData::UnhookOnGameObjectEvents()
{
    GameEntityObject::UnsubscribeGameEntityObjectEvents(instanceId, instanceId);
}
#pragma endregion Events

void GameData::UnLoadModelMesh(Model* model)
{
    meshData->UnLoadModelMesh(model);
}

void GameData::DeleteAllMeshData()
{
    delete meshData;
}

bool Game::GameData::UnLoadGameWorlds(bool fast)
{
    util::DebugLog("\n[Game][GameData][UnLoadGameWorlds]\t.....................................................................................................................................");
    util::DebugLog("[Game][GameData][UnLoadGameWorlds]\t\t\t\t Unloading Game World(s):");
    util::DebugLog("[Game][GameData][UnLoadGameWorlds]\t Unloading entities and components, unhooking events, clearing any maps:");
    
    namedModelComponentIDs.clear();
    namedMaterialComponentIDs.clear();
    namedLightComponentIDs.clear();

    namedGameObjectIDs.clear();
    
    
    UnhookOnGameObjectEvents();
    if(mainEntityWorld->entityArchetypePool != nullptr)
    {
        mainEntityWorld->entityArchetypePool->ClearItems(true, fast);
        mainEntityWorld->entityArchetypePool = nullptr;
    }
    if(vfxEntityWorld->entityArchetypePool != nullptr)
    {
        vfxEntityWorld->entityArchetypePool->ClearItems(true, fast);
        vfxEntityWorld->entityArchetypePool = nullptr;
    }

    if(mainEntityWorld->modelComponents != nullptr)
    {
        mainEntityWorld->modelComponents->ClearItems(true, fast);
        mainEntityWorld->modelComponents = nullptr;
    }
    if(mainEntityWorld->materialComponents != nullptr)
    {
        mainEntityWorld->materialComponents->ClearItems(true, fast);
        mainEntityWorld->materialComponents = nullptr;
    }
    if(mainEntityWorld->lightComponents != nullptr)
    {
        mainEntityWorld->lightComponents->ClearItems(true, fast);
        mainEntityWorld->lightComponents = nullptr;
    }
    
    if(vfxEntityWorld->modelComponents != nullptr)
    {
        vfxEntityWorld->modelComponents->ClearItems(true, fast);
        vfxEntityWorld->modelComponents = nullptr;
    }
    if(vfxEntityWorld->materialComponents != nullptr)
    {
        vfxEntityWorld->materialComponents->ClearItems(true, fast);
        vfxEntityWorld->materialComponents = nullptr;
    }
    if(vfxEntityWorld->lightComponents != nullptr)
    {
        vfxEntityWorld->lightComponents->ClearItems(true, fast);
        vfxEntityWorld->lightComponents = nullptr;
    }
    
    mainEntityWorld = nullptr;
    vfxEntityWorld = nullptr;
    
    util::DebugLog("[Game][GameData][UnLoadGameWorlds]\t\t\t\t Unloaded Game World(s).");
    util::DebugLog("[Game][GameData][UnLoadGameWorlds]\t.....................................................................................................................................\n");
    
    //std::exception("NotImplementedException");
    return true;
}

void Game::GameData::DeletePlayers()
{
    for (PlayerObject* player : playerObjects)
        delete player;
    playerObjects.clear();
    util::DebugLog("[Game][GameData][GameData]\t Deleted Players.");
}

void Game::GameData::DeleteEntityPools()
{
    bool fast = true;
    if(mainEntityWorld != nullptr && mainEntityWorld->entityArchetypePool != nullptr)
    {
        mainEntityWorld->entityArchetypePool->ClearItems(true, fast);
        mainEntityWorld->entityArchetypePool->~TiledGameDataPools();
        mainEntityWorld->entityArchetypePool = nullptr;
    }
    if(vfxEntityWorld != nullptr && vfxEntityWorld->entityArchetypePool != nullptr)
    {
        vfxEntityWorld->entityArchetypePool->ClearItems(true, fast);
        vfxEntityWorld->entityArchetypePool->~TiledGameDataPools();
        vfxEntityWorld->entityArchetypePool = nullptr;
    }
    util::DebugLog("[Game][GameData][GameData]\t Deleted Entity Pools.");
}

void Game::GameData::DeleteComponentPools()
{
    bool fast = true;
    if(mainEntityWorld != nullptr)
    {
        if(mainEntityWorld->entityArchetypePool != nullptr)
        {
            mainEntityWorld->entityArchetypePool->ClearItems(true, fast);
            mainEntityWorld->entityArchetypePool->~TiledGameDataPools();
            mainEntityWorld->entityArchetypePool = nullptr;
        }
        if(mainEntityWorld->modelComponents != nullptr)
        {
            mainEntityWorld->modelComponents->ClearItems(true, fast);
            mainEntityWorld->modelComponents->~GameDataPool();
            mainEntityWorld->modelComponents = nullptr;
        }
        if(mainEntityWorld->materialComponents != nullptr)
        {
            mainEntityWorld->materialComponents->ClearItems(true, fast);
            mainEntityWorld->materialComponents->~GameDataPool();
            mainEntityWorld->materialComponents = nullptr;
        }
        if(mainEntityWorld->lightComponents != nullptr)
        {
            mainEntityWorld->lightComponents->ClearItems(true, fast);
            mainEntityWorld->lightComponents->~GameDataPool();
            mainEntityWorld->lightComponents = nullptr;
        }
    }
    
    if(vfxEntityWorld != nullptr)
    {
        if(vfxEntityWorld->entityArchetypePool != nullptr)
        {
            vfxEntityWorld->entityArchetypePool->ClearItems(true, fast);
            vfxEntityWorld->entityArchetypePool->~TiledGameDataPools();
            vfxEntityWorld->entityArchetypePool = nullptr;
        }
        if(vfxEntityWorld->modelComponents != nullptr)
        {
            vfxEntityWorld->modelComponents->ClearItems(true, fast);
            vfxEntityWorld->modelComponents->~GameDataPool();
            vfxEntityWorld->modelComponents = nullptr;
        }
        if(vfxEntityWorld->materialComponents != nullptr)
        {
            vfxEntityWorld->materialComponents->ClearItems(true, fast);
            vfxEntityWorld->materialComponents->~GameDataPool();
            vfxEntityWorld->materialComponents = nullptr;
        }
        if(vfxEntityWorld->lightComponents != nullptr)
        {
            vfxEntityWorld->lightComponents->ClearItems(true, fast);
            vfxEntityWorld->lightComponents->~GameDataPool();
            vfxEntityWorld->lightComponents = nullptr;
        }
    }
    util::DebugLog("[Game][GameData][GameData]\t Deleted Component Pools.");
}

void Game::GameData::DeleteWorlds()
{
     for (GameWorld* world : gameWorlds)
     {
        if(world != nullptr)
            delete world;
     }
    gameWorlds.clear();
    util::DebugLog("[Game][GameData][GameData]\t Deleted Worlds.");
}

/// [tdbe] TODO: At this point these have already been unloaded with the game world(s) <see cref="UnLoadGameWorlds"/>. When we have a clearer picture of loading/unloading/streaming worlds, we can refactor or remove these calls.
GameData::~GameData()
{
    util::DebugLog("\n[Game][GameData][~GameData]\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][~GameData]\t Deleting Game Data: players, entity pools, component pools, worlds. These all should have been unloaded already with the world(s).");
    
    DeletePlayers();
    DeleteEntityPools();
    DeleteComponentPools();
    DeleteWorlds();
    util::DebugLog("[Game][GameData][~GameData]\t Deleted Game Data.");
    util::DebugLog("[Game][GameData][~GameData]\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

std::uint64_t GameData::TypeUIDs::FromTypeIndex(std::type_index typeIndex)
{
    if(typeIndex == std::type_index(typeid(GameEntity)))
    {
        return GAME_ENTITIES;
    }
    else if(typeIndex == std::type_index(typeid(GameEntityObject)))
    {
        return GAME_ENTITY_OBJECTS;
    }
    else if(typeIndex == std::type_index(typeid(Transform)))
    {
        return TRANSFORM_COMPONENTS;
    }
    else if(typeIndex == std::type_index(typeid(Parent)))
    {
        return PARENT_COMPONENTS;
    }
    else if(typeIndex == std::type_index(typeid(Children)))
    {
        return CHILDREN_COMPONENTS;
    }
    else if(typeIndex == std::type_index(typeid(Model)))
    {
        return MODEL_COMPONENTS;
    }
    else if(typeIndex == std::type_index(typeid(Bounds)))
    {
        return BOUNDS_COMPONENTS;
    }
    else if(typeIndex == std::type_index(typeid(Material)))
    {
        return MATERIAL_COMPONENTS;
    }
    else if(typeIndex == std::type_index(typeid(Light)))
    {
        return LIGHT_COMPONENTS;
    }
    else
    {
        return 0;    
    }
}

std::type_index GameData::TypeUIDs::ToTypeIndex(uint64_t typeUID)
{
    if(typeUID == GAME_ENTITIES)
    {
        return std::type_index(typeid(GameEntity));
    }
    else if(typeUID == GAME_ENTITY_OBJECTS)
    {
        return std::type_index(typeid(GameEntityObject));
    }
    else if(typeUID == TRANSFORM_COMPONENTS)
    {
        return std::type_index(typeid(Transform));
    }
    else if(typeUID == PARENT_COMPONENTS)
    {
        return std::type_index(typeid(Parent));
    }
    else if(typeUID == CHILDREN_COMPONENTS)
    {
        return std::type_index(typeid(Children));
    }
    else if(typeUID == MODEL_COMPONENTS)
    {
        return std::type_index(typeid(Model));
    }
    else if(typeUID == BOUNDS_COMPONENTS)
    {
        return std::type_index(typeid(Bounds));
    }
    else if(typeUID == MATERIAL_COMPONENTS)
    {
        return std::type_index(typeid(Material));
    }
    else if(typeUID == LIGHT_COMPONENTS)
    {
        return std::type_index(typeid(Light));
    }
    else
    {
        return std::type_index(typeid(void));
    }
}

std::string GameData::TypeUIDs::ToString(const uint64_t typeUID)
{
    if (typeUID == FREE)
        return "FREE";
    else if (typeUID == GAME_ENTITY_OBJECTS)
        return "struct Game::GameEntityObject";
    else if (typeUID == GAME_ENTITIES)
        return "struct Game::GameEntity";
    else if (typeUID == TRANSFORM_COMPONENTS)
        return "struct Game::Transform";
    else if (typeUID == PARENT_COMPONENTS)
        return "struct Game::Parent";
    else if (typeUID == CHILDREN_COMPONENTS)
        return "struct Game::Children";
    else if (typeUID == MODEL_COMPONENTS)
        return "struct Game::Bounds";
    else if (typeUID == BOUNDS_COMPONENTS)
        return "struct Game::Bounds";
    else if (typeUID == MATERIAL_COMPONENTS)
        return "struct Game::Material";
    else if (typeUID == LIGHT_COMPONENTS)
        return "struct Game::Light";
    else
        return "~~~PLEASE_DEFINE~~~";
};