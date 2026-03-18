
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
#include "Entities/GameEntityObject.h"
#include "PlayerObject.h"

using namespace Game;
using namespace boost;

uint32_t GameData::instanceIdSeed = 0;

GameData::GameData()
{    
    const_cast<std::string&>(instanceId) = "GameData_" + util::ToString(instanceIdSeed++);  
    util::DebugLog("[Game][GameData][Singleton]\t All data pools are here. instanceId: \"" + instanceId + "\".");
}

GameData& Game::GameData::operator=(GameData const& copy)
{
    util::DebugError("[Game][GameData][=]\t Can't copy GameData, it's a singleton.");
    return *this;
}

/// [tdbe] (deserialize, allocate, and basic init of the current scene/world)
bool GameData::LoadGameWorlds()
{
    util::DebugLog(
        "[Game][GameData][LoadGameWorlds]\t .........................................................................................................................");
    util::DebugLog(
        "[Game][GameData][LoadGameWorlds]\t Loading, deserializing, creating pools for entities and components, hooking some events, creating some quick access maps:");

    entityObjectsWorld = new GameWorld();
    vfxEntityObjectsWorld = new GameWorld();
    gameWorlds = {entityObjectsWorld, vfxEntityObjectsWorld};

    bool success = true;
    success = success && LoadModels();
    success = success && LoadMaterials();
    success = success && LoadGameLights();

    HookOnGameObjectEvents();
    success = success && LoadGameEntityObjects();
    success = success && LoadVFXEntityObjects();
    success = success && LoadPlayers();

    util::DebugLog("[Game][GameData][LoadGameWorlds]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadGameWorlds]\t\t Loaded Game World(s).");
    return success;
}

GameComponent* GameData::GetComponent(GameDataId::ID id)
{
    if (id.typeUID == TypeUIDs.TRANSFORM_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->transformComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.PARENT_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->parentComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.CHILDREN_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->childrenComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.ROOT_ATTRIBUTE_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->rootAttributeComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.MODEL_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->modelComponents->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.BOUNDS_COMPONENTS)
    {
        return gameWorlds[id.worldIndex]->boundsComponents->GetItem(id);
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

GameEntity* GameData::GetEntity(GameDataId::ID id)
{
    if (id.typeUID == TypeUIDs.GAME_ENTITY_OBJECTS)
    {
        return gameWorlds[id.worldIndex]->gameEntityObjects->GetItem(id);
    }
    else if (id.typeUID == TypeUIDs.GAME_ENTITIES)
    {
        //return gameWorlds[id.worldIndex]->gameEntities->GetItem(id);
        // TODO:
        util::DebugError("[GameData][ClearEntity] 'NotImplementedException': see GameWorld::gameEntityObjects");
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

void GameData::ClearComponent(GameDataId::ID id, bool unsafe)
{
    if (id.typeUID == TypeUIDs.TRANSFORM_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->transformComponents->ClearItem(entityObjectsWorld->transformComponents->GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.MODEL_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->modelComponents->ClearItem(gameWorlds[id.worldIndex]->modelComponents->GetItem(id), unsafe);
    }
    else if (id.typeUID == TypeUIDs.BOUNDS_COMPONENTS)
    {
        gameWorlds[id.worldIndex]->boundsComponents->ClearItem(gameWorlds[id.worldIndex]->boundsComponents->GetItem(id), unsafe);
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
        gameWorlds[id.worldIndex]->gameEntityObjects->ClearItem(gameWorlds[id.worldIndex]->gameEntityObjects->GetItem(id), unsafe);
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
    int entityObjectsWorldIndex = GameWorldsIndexOf(entityObjectsWorld);
    if(entityObjectsWorld->modelComponents != nullptr) { util::DebugError("[GameData][LoadModels]\t Somebody forgot to clear their pool (entityObjectsWorld)!"); entityObjectsWorld->modelComponents->ClearItems(false); }
    entityObjectsWorld->modelComponents = new GameDataPool<Model>(AllocationMagicNumbers::MAX_MODELS, entityObjectsWorldIndex,
                                              TypeUIDs.MODEL_COMPONENTS,
                                              TypeUIDs.ToString(TypeUIDs.MODEL_COMPONENTS));
    
    DeleteAllMeshData(); // [tdbe] (meshes are kept on the gpu)
    meshData = new MeshData();

    Model* gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/quad.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"quadModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/ground_displaced_4096.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"groundModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Ruins.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"ruinsModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Car.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"carModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Beetle_glassless.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"beetleModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Beetle_glass_only.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"beetleGlassModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Bike.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"bikeModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Hand.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"handModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/cube.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"cubeModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Logo_OpenXR_Vulkan.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"logoModel1Comp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Logo_Framework.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"logoModel2Comp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_Locomotion_Flat.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"textLocomotionModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_Suda_Beam_Flat.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"textSudaBeamModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_See_Controls_md.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"textSeeControlsMdModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv4_half_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"icosphereModelComp", gco->id});
    ConfiguredGameModel(gco);
    
    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv4_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"icosphereSmoothModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv3_0.75_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"icosphereRoughModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/tube_light_1_03.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"tube_light_1_03", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/SudaBeam.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"sudaBeamModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Squid_Happy_Grumpy.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert({"squidModelComp", gco->id});
    ConfiguredGameModel(gco);

    gco = entityObjectsWorld->modelComponents->GetFreeItem();
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
    
    int entityObjectsWorldIndex = GameWorldsIndexOf(entityObjectsWorld);
    int vfxEntityObjectsWorldIndex = GameWorldsIndexOf(vfxEntityObjectsWorld);
    
    if(entityObjectsWorld->materialComponents != nullptr) { util::DebugError("[GameData][LoadMaterials]\t Somebody forgot to clear their pool!"); entityObjectsWorld->materialComponents->ClearItems(false); }
    entityObjectsWorld->materialComponents = new GameDataPool<Material>(AllocationMagicNumbers::MAX_MATERIALS, entityObjectsWorldIndex, TypeUIDs.MATERIAL_COMPONENTS,
                                                    TypeUIDs.ToString(TypeUIDs.MATERIAL_COMPONENTS));
    
    if(vfxEntityObjectsWorld->materialComponents != nullptr) { util::DebugError("[GameData][LoadMaterials]\t Somebody forgot to clear their pool (vfx entities)!"); vfxEntityObjectsWorld->materialComponents->ClearItems(false); }
    vfxEntityObjectsWorld->materialComponents = new GameDataPool<Material>(AllocationMagicNumbers::MAX_VFX_MATERIALS, vfxEntityObjectsWorldIndex, TypeUIDs.MATERIAL_COMPONENTS,
                                                    TypeUIDs.ToString(TypeUIDs.MATERIAL_COMPONENTS));

    Material* gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"skyMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseMetalishMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseStoneMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseTripIcosphereMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseEyesMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);
    
    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"textMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"logoMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] ^ all the (entities with the) materials above are meant to have the same diffuse style blend pipeline,
    // so they'll be batched in the <see cref="Renderer"/> because the materials are reserved here in relative order in the pool.

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"groundMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] customization / hack: we skip <see cref="skip"/> free slots in case we want to 
    // add more materials with the same pipeline as above, during runtime, that we want batched.
    uint32_t skip = 20;
    uint32_t lastDiffuseMaterialAt = gco->id.index;// we'd have to share this with whoever adds new mats at runtime
    
    gco = entityObjectsWorld->materialComponents->GetFreeItem(skip);
    namedMaterialComponentIDs.insert({"squidMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"lightMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
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

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseTransparentBackfaceInstancedMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"bikeTransparentBackfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"diffuseTransparentFrontfaceInstancedMaterialComp", gco->id});
    ConfiguredGameMaterial(gco); 

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"bikeTransparentFrontfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"glassTransparentBackfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);
    gco = entityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"glassTransparentFrontfaceMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    // [tdbe] VFX materials

    gco = vfxEntityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"skyOfChaperoneMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);
    
    gco = vfxEntityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"floorGridMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = vfxEntityObjectsWorld->materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert({"ceilingGridMaterialComp", gco->id});
    ConfiguredGameMaterial(gco);

    gco = vfxEntityObjectsWorld->materialComponents->GetFreeItem();
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
    
    int entityObjectsWorldIndex = GameWorldsIndexOf(entityObjectsWorld);
    
    if(entityObjectsWorld->lightComponents != nullptr) { util::DebugError("[GameData][LoadGameLights]\t Somebody forgot to clear their pool!"); entityObjectsWorld->lightComponents->ClearItems(false); }
    entityObjectsWorld->lightComponents = new GameDataPool<Light>(AllocationMagicNumbers::LIGHTS_COUNT, 
                                              entityObjectsWorldIndex,
                                              TypeUIDs.LIGHT_COMPONENTS, 
                                              TypeUIDs.ToString(TypeUIDs.LIGHT_COMPONENTS));

    Light* gco = entityObjectsWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"mainDirectionalLightComp", gco->id});
    ConfiguredGameLight(gco);

    for (int i = 1; i < 7; i++)
    {
        gco = entityObjectsWorld->lightComponents->GetFreeItem();
        namedLightComponentIDs.insert({"tentacleLightComp0" + util::ToString(i, true), gco->id});
        ConfiguredGameLight(gco);
    }

    gco = entityObjectsWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"handLight01Comp", gco->id});
    ConfiguredGameLight(gco);

    gco = entityObjectsWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"handLight02Comp", gco->id});
    ConfiguredGameLight(gco);

    gco = entityObjectsWorld->lightComponents->GetFreeItem();
    namedLightComponentIDs.insert({"bikeLightComp", gco->id});
    ConfiguredGameLight(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

    return success;
}

bool GameData::LoadGameEntityObjects()
{
    util::DebugLog("\n[Game][GameData][LoadGameEntityObjects]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][LoadGameEntityObjects]\t\t Loading Game Entity Objects (main entityObjectsWorld)");
    bool success = true;
    int entityObjectsWorldIndex = GameWorldsIndexOf(entityObjectsWorld);

    if (entityObjectsWorld->gameEntityObjects != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool (gameEntityObjects)!"); entityObjectsWorld->gameEntityObjects->ClearItems(false); }
    entityObjectsWorld->gameEntityObjects = new GameDataPool<GameEntityObject>(AllocationMagicNumbers.MAX_GAME_ENTITY_OBJECTS,
                                                           entityObjectsWorldIndex,
                                                           TypeUIDs.GAME_ENTITY_OBJECTS,
                                                           TypeUIDs.ToString(TypeUIDs.GAME_ENTITY_OBJECTS));
    if(entityObjectsWorld->transformComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool (transformComponents)!"); entityObjectsWorld->transformComponents->ClearItems(false); }
    entityObjectsWorld->transformComponents = new GameDataPool<Transform>(AllocationMagicNumbers.MAX_GAME_ENTITY_OBJECTS, 
                                                      entityObjectsWorldIndex,
                                                      TypeUIDs.TRANSFORM_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.TRANSFORM_COMPONENTS));
    if(entityObjectsWorld->parentComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool (parentComponents)!"); entityObjectsWorld->parentComponents->ClearItems(false); }
    entityObjectsWorld->parentComponents = new GameDataPool<Parent>(AllocationMagicNumbers.MAX_GAME_ENTITY_OBJECTS, 
                                                      entityObjectsWorldIndex,
                                                      TypeUIDs.PARENT_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.PARENT_COMPONENTS));
    if(entityObjectsWorld->childrenComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool (childrenComponents)!"); entityObjectsWorld->childrenComponents->ClearItems(false); }
    entityObjectsWorld->childrenComponents = new GameDataPool<Children>(AllocationMagicNumbers.MAX_GAME_ENTITY_OBJECTS, 
                                                      entityObjectsWorldIndex,
                                                      TypeUIDs.CHILDREN_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.CHILDREN_COMPONENTS));
    
    if(entityObjectsWorld->boundsComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool!"); entityObjectsWorld->boundsComponents->ClearItems(false); }
    entityObjectsWorld->boundsComponents = new GameDataPool<Bounds>(AllocationMagicNumbers::MAX_MODELS, 
                                                      entityObjectsWorldIndex,
                                                      TypeUIDs.BOUNDS_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.BOUNDS_COMPONENTS));
    
    GameEntityObject* gento = nullptr;
    GameComponent* comp = nullptr;
    Transform* trans = nullptr;
    Parent* parent = nullptr;
    Children* children = nullptr;
    Bounds* bounds = nullptr;

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("worldRoot");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    namedGameObjectIDs.insert({"worldRoot", gento->id});
    ConfiguredGameObject(gento);

    // [tdbe] (the following order does not affect render/batching order; that order's in the material pool)

    // [tdbe] entities with Lights
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("mainDirectionalLight");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("mainDirectionalLightComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    ConfiguredGameObject(gento);

    for (int i = 1; i < 7; i++)
    {
        gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
        gento->SetName("tentacle0" + util::ToString(i, true));
        trans = entityObjectsWorld->transformComponents->GetFreeItem();
        trans->AddOwnerId(gento->id);
        gento->AddComponentId(trans->id);
        parent = entityObjectsWorld->parentComponents->GetFreeItem();
        parent->AddOwnerId(gento->id);
        gento->AddComponentId(parent->id);
        children = entityObjectsWorld->childrenComponents->GetFreeItem();
        children->AddOwnerId(gento->id);
        gento->AddComponentId(children->id);
        comp = GetComponent(namedLightComponentIDs.left.at("tentacleLightComp0" + util::ToString(i, true)));
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        static_cast<Light*>(comp)->SetVisible(false);
        comp = GetComponent(namedModelComponentIDs.left.at("tube_light_1_03"));
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
        bounds->SetBoundsAABB(static_cast<Model*>(comp));
        bounds->AddOwnerId(gento->id);
        gento->AddComponentId(bounds->id);
        comp = GetComponent(namedMaterialComponentIDs.left.at("tentacleLightMaterialComp"));
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        ConfiguredGameObject(gento);
    }    

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("handLight01");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("handLight01Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    comp = GetComponent(namedModelComponentIDs.left.at("tube_light_1_03"));// [tdbe] Todo: need a procedural capsule that can be squished while preserving hemispherical ends
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("lightMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("handLight02");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("handLight02Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    comp = GetComponent(namedModelComponentIDs.left.at("tube_light_1_03"));// [tdbe] Todo: need a procedural capsule that can be squished while preserving hemispherical ends
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("lightMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("bikeLight");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedLightComponentIDs.left.at("bikeLightComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    // comp = GetComponent(namedModelComponentIDs["tube_light_1_03"]);// [tdbe] Todo: need a procedural capsule that can
    // be squished while preserving hemispherical ends comp->AddOwnerId(gento->id); gento->AddComponentId(comp->id);
    // bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    // bounds->SetBoundsAABB(static_cast<Model*>(comp));
    // bounds->AddOwnerId(gento->id);
    // gento->AddComponentId(bounds->id);
    // comp = GetComponent(namedMaterialComponentIDs["lightMaterialComp"]);
    // comp->AddOwnerId(gento->id);
    // gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    // [tdbe] world sky

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSkybox_world");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
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
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("ground");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("groundModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("groundMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("ruins");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("ruinsModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("carLeft");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("carModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("carRight");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("carModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("beetle");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("beetleModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("beetleGlass");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("beetleGlassModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
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
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("bike");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("bikeModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
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

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("logo1");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("logoModel1Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("logoMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("logo2");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("logoModel2Comp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("logoMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("textLocomotion");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("textLocomotionModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("textMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("textSudaBeam");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("textSudaBeamModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("textMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("textSeeControlsMd");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("textSeeControlsMdModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("textMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("cube");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("cubeModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSmoothTripInstancing");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseTripIcosphereMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSmoothForInstancing");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
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

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("sudaBeam01");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("sudaBeamModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("sudaBeam02");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("sudaBeamModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);
    
    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("squid");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("squidModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("squidMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("monke");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("suzanneMonkeModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("monkeEye1");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereRoughModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("diffuseEyesMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = entityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("monkeEye2");
    trans = entityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = entityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = entityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = GetComponent(namedModelComponentIDs.left.at("icosphereRoughModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = entityObjectsWorld->boundsComponents->GetFreeItem();
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
    util::DebugLog("[Game][GameData][LoadVFXEntityObjects]\t\t Loading Game VFX Objects (vfxEntityObjectsWorld)");
    bool success = true;
    int vfxEntityObjectsWorldIndex = GameWorldsIndexOf(vfxEntityObjectsWorld);
    
    if (vfxEntityObjectsWorld->gameEntityObjects != nullptr) { util::DebugError("[GameData][LoadGameVFXEntityObjects]\t Somebody forgot to clear their pool (vfxEntityObjectsWorld->gameEntityObjects)!"); vfxEntityObjectsWorld->gameEntityObjects->ClearItems(false); }
    vfxEntityObjectsWorld->gameEntityObjects = new GameDataPool<GameEntityObject>(AllocationMagicNumbers.MAX_VFX_GAME_ENTITY_OBJECTS,
                                                        vfxEntityObjectsWorldIndex,
                                                        TypeUIDs.GAME_ENTITY_OBJECTS,
                                                        TypeUIDs.ToString(TypeUIDs.GAME_ENTITY_OBJECTS));
    if(vfxEntityObjectsWorld->transformComponents != nullptr) { util::DebugError("[GameData][LoadGameVFXEntityObjects]\t Somebody forgot to clear their pool (transformComponents)!"); vfxEntityObjectsWorld->transformComponents->ClearItems(false); }
    vfxEntityObjectsWorld->transformComponents = new GameDataPool<Transform>(AllocationMagicNumbers.MAX_VFX_GAME_ENTITY_OBJECTS, 
                                                      vfxEntityObjectsWorldIndex,
                                                      TypeUIDs.TRANSFORM_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.TRANSFORM_COMPONENTS));
    if(vfxEntityObjectsWorld->parentComponents != nullptr) { util::DebugError("[GameData][LoadGameVFXEntityObjects]\t Somebody forgot to clear their pool (parentComponents)!"); vfxEntityObjectsWorld->parentComponents->ClearItems(false); }
    vfxEntityObjectsWorld->parentComponents = new GameDataPool<Parent>(AllocationMagicNumbers.MAX_VFX_GAME_ENTITY_OBJECTS, 
                                                      vfxEntityObjectsWorldIndex,
                                                      TypeUIDs.PARENT_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.PARENT_COMPONENTS));
    if(vfxEntityObjectsWorld->childrenComponents != nullptr) { util::DebugError("[GameData][LoadGameVFXEntityObjects]\t Somebody forgot to clear their pool (childrenComponents)!"); vfxEntityObjectsWorld->childrenComponents->ClearItems(false); }
    vfxEntityObjectsWorld->childrenComponents = new GameDataPool<Children>(AllocationMagicNumbers.MAX_VFX_GAME_ENTITY_OBJECTS, 
                                                      vfxEntityObjectsWorldIndex,
                                                      TypeUIDs.CHILDREN_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.CHILDREN_COMPONENTS));
    
    if(vfxEntityObjectsWorld->boundsComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their pool!"); vfxEntityObjectsWorld->boundsComponents->ClearItems(false); }
    vfxEntityObjectsWorld->boundsComponents = new GameDataPool<Bounds>(2, //just the hands
                                                      vfxEntityObjectsWorldIndex,
                                                      TypeUIDs.BOUNDS_COMPONENTS,
                                                      TypeUIDs.ToString(TypeUIDs.BOUNDS_COMPONENTS));

    GameEntityObject* gento = nullptr;
    GameComponent* comp = nullptr;
    Transform* trans = nullptr;
    Parent* parent = nullptr;
    Children* children = nullptr;
    Bounds* bounds = nullptr;

    gento = vfxEntityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("worldRoot");
    trans = vfxEntityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    ConfiguredGameObject(gento);
    

    gento = vfxEntityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSkybox_chaperone");
    trans = vfxEntityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = entityObjectsWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("icosphereModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("skyOfChaperoneMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("floorGrid");
    trans = vfxEntityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = entityObjectsWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("quadModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("floorGridMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("ceilingGrid");
    trans = vfxEntityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = entityObjectsWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("quadModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("ceilingGridMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("handLeft");
    trans = vfxEntityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = entityObjectsWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("handModelComp"));// stole model from main world
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = vfxEntityObjectsWorld->boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs.left.at("handsMaterialComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    ConfiguredGameObject(gento);

    gento = vfxEntityObjectsWorld->gameEntityObjects->GetFreeItem();
    gento->SetName("handRight");
    trans = vfxEntityObjectsWorld->transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    parent = vfxEntityObjectsWorld->parentComponents->GetFreeItem();
    parent->AddOwnerId(gento->id);
    gento->AddComponentId(parent->id);
    children = vfxEntityObjectsWorld->childrenComponents->GetFreeItem();
    children->AddOwnerId(gento->id);
    gento->AddComponentId(children->id);
    comp = entityObjectsWorld->modelComponents->GetItem(namedModelComponentIDs.left.at("handModelComp"));// stole model from main world
    // comp = GetComponent(namedModelComponentIDs.left.at("icosphereSmoothModelComp"));
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = vfxEntityObjectsWorld->boundsComponents->GetFreeItem();
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
    util::DebugLog("[Game][GameData][LoadPlayers]\t\t Loading Players");
    bool success = true;
    playerObjects.resize(AllocationMagicNumbers.MAX_PLAYER_OBJECTS);
    playerObjects.at(0) = new PlayerObject(namedGameObjectIDs.left.at("worldRoot"), 
                                           namedGameObjectIDs.left.at("handLeft"),
                                           namedGameObjectIDs.left.at("handRight"), 
                                           "XR Player 1");

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

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

bool Game::GameData::UnLoadGameWorld(bool fast)
{
    util::DebugLog("\n[Game][GameData][UnLoadGameWorld]\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][UnLoadGameWorld]\t Unloading entities and components, unhooking events, clearing any maps:");
    
    namedModelComponentIDs.clear();
    namedMaterialComponentIDs.clear();
    namedLightComponentIDs.clear();

    namedGameObjectIDs.clear();
    
    
    UnhookOnGameObjectEvents();
    entityObjectsWorld->gameEntityObjects->ClearItems(true, fast);
    vfxEntityObjectsWorld->gameEntityObjects->ClearItems(true, fast);

    entityObjectsWorld->transformComponents->ClearItems(true, fast);
    entityObjectsWorld->parentComponents->ClearItems(true, fast);
    entityObjectsWorld->childrenComponents->ClearItems(true, fast);
    entityObjectsWorld->rootAttributeComponents->ClearItems(true, fast);
    entityObjectsWorld->modelComponents->ClearItems(true, fast);
    entityObjectsWorld->boundsComponents->ClearItems(true, fast);
    entityObjectsWorld->materialComponents->ClearItems(true, fast);
    entityObjectsWorld->lightComponents->ClearItems(true, fast);
    
    vfxEntityObjectsWorld->transformComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->parentComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->childrenComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->rootAttributeComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->modelComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->boundsComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->materialComponents->ClearItems(true, fast);
    vfxEntityObjectsWorld->lightComponents->ClearItems(true, fast);
        
    //std::exception("NotImplementedException");
    return true;
}

void Game::GameData::DeletePlayers()
{
    for (PlayerObject* player : playerObjects)
        delete player;
    playerObjects.clear();
}

void Game::GameData::DeleteEntityPools()
{
    entityObjectsWorld->gameEntityObjects->~GameDataPool();
    vfxEntityObjectsWorld->gameEntityObjects->~GameDataPool();
}

void Game::GameData::DeleteComponentPools()
{
    entityObjectsWorld->transformComponents->~GameDataPool();
    entityObjectsWorld->parentComponents->~GameDataPool();
    entityObjectsWorld->childrenComponents->~GameDataPool();
    entityObjectsWorld->rootAttributeComponents->~GameDataPool();
    entityObjectsWorld->modelComponents->~GameDataPool();
    entityObjectsWorld->boundsComponents->~GameDataPool();
    entityObjectsWorld->materialComponents->~GameDataPool();
    entityObjectsWorld->lightComponents->~GameDataPool();
    
    vfxEntityObjectsWorld->transformComponents->~GameDataPool();
    vfxEntityObjectsWorld->parentComponents->~GameDataPool();
    vfxEntityObjectsWorld->childrenComponents->~GameDataPool();
    vfxEntityObjectsWorld->rootAttributeComponents->~GameDataPool();
    vfxEntityObjectsWorld->modelComponents->~GameDataPool();
    vfxEntityObjectsWorld->boundsComponents->~GameDataPool();
    vfxEntityObjectsWorld->materialComponents->~GameDataPool();
    vfxEntityObjectsWorld->lightComponents->~GameDataPool();
}

void Game::GameData::DeleteWorlds()
{
     for (GameWorld* world : gameWorlds)
        delete world;
    gameWorlds.clear();
}

GameData::~GameData()
{
    DeletePlayers();
    DeleteEntityPools();
    DeleteComponentPools();
    DeleteWorlds();
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
}