#pragma once
#include "../Utils/Util.h"

#include "GameData.h"
#include "MeshData.h"
#include "Components/Transform.h"
#include "Components/Model.h"
#include "Components/Bounds.h"
#include "Components/Material.h"
#include "Components/Light.h"
#include "Entities/GameEntityObject.h"
#include "PlayerObject.h"

using namespace Game;

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
bool GameData::LoadGameWorld()
{
    util::DebugLog(
        "[Game][GameData][LoadGameWorld]\t .........................................................................................................................");
    util::DebugLog(
        "[Game][GameData][LoadGameWorld]\t Loading, deserializing, creating pools for entities and components, hooking some events, creating some quick access maps:");

    bool success = true;
    success = success && LoadModels();
    success = success && LoadMaterials();
    success = success && LoadGameLights();

    HookOnGameObjectEvents();
    success = success && LoadGameEntityObjects();
    success = success && LoadPlayers();

    return success;
}

GameComponent* GameData::GetComponent(GameDataId::ID id)
{
    if (id.globalUIDSeed == GlobalUIDSeeds.TRANSFORM_COMPONENTS)
    {
        return transformComponents->GetItem(id);
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.MODEL_COMPONENTS)
    {
        return modelComponents->GetItem(id);
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.BOUNDS_COMPONENTS)
    {
        return boundsComponents->GetItem(id);
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.MATERIAL_COMPONENTS)
    {
        return materialComponents->GetItem(id);
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.LIGHT_COMPONENTS)
    {
        return lightComponents->GetItem(id);
    }
    else
    {
        return nullptr;
    }
}

GameEntity* GameData::GetEntity(GameDataId::ID id)
{
    if (id.globalUIDSeed == GlobalUIDSeeds.GAME_ENTITY_OBJECTS)
    {
        return gameEntityObjects->GetItem(id);
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.GAME_VFX_OBJECTS)
    {
        return gameVFXObjects->GetItem(id);
    }
    else
    {
        return nullptr;
    }
}

void GameData::ClearComponent(GameDataId::ID id)
{
    if (id.globalUIDSeed == GlobalUIDSeeds.TRANSFORM_COMPONENTS)
    {
        transformComponents->ClearItem(transformComponents->GetItem(id));
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.MODEL_COMPONENTS)
    {
        modelComponents->ClearItem(modelComponents->GetItem(id));
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.BOUNDS_COMPONENTS)
    {
        boundsComponents->ClearItem(boundsComponents->GetItem(id));
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.MATERIAL_COMPONENTS)
    {
        materialComponents->ClearItem(materialComponents->GetItem(id));
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.LIGHT_COMPONENTS)
    {
        lightComponents->ClearItem(lightComponents->GetItem(id));
    }
}

void GameData::ClearEntity(GameDataId::ID id)
{
    if (id.globalUIDSeed == GlobalUIDSeeds.GAME_ENTITY_OBJECTS)
    {
        gameEntityObjects->ClearItem(gameEntityObjects->GetItem(id));
    }
    else if (id.globalUIDSeed == GlobalUIDSeeds.GAME_VFX_OBJECTS)
    {
        gameVFXObjects->ClearItem(gameVFXObjects->GetItem(id));
    }
}

bool GameData::LoadModels()
{
    bool success = true;

    if(modelComponents != nullptr) { util::DebugError("[GameData][LoadModels]\t Somebody forgot to clear their heap allocations!");  modelComponents->ClearItems(false); }
    modelComponents = new GameDataPool<Model>(AllocationMagicNumbers::MAX_MODELS, 
                                              GlobalUIDSeeds.MODEL_COMPONENTS,
                                              GlobalUIDSeeds.ToString(GlobalUIDSeeds.MODEL_COMPONENTS));
    DeleteAllMeshData();
    meshData = new MeshData();

    Model* gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/quad.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("quadModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/ground_displaced_4096.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("groundModelComp", gco->id);
    ConfiguredGameModel(gco);
    
    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Ruins.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("ruinsModelComp", gco->id);
    ConfiguredGameModel(gco);
    
    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Car.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("carModelComp", gco->id);
    ConfiguredGameModel(gco);
    
    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Beetle_glassless.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("beetleModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Beetle_glass_only.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("beetleGlassModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Bike.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("bikeModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Hand.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("handModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/cube.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("cubeModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Logo_OpenXR_Vulkan.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("logoModel1Comp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Logo_Framework.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("logoModel2Comp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_Locomotion_Flat.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("textLocomotionModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_Suda_Beam_Flat.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("textSudaBeamModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Text_See_Controls_md.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("textSeeControlsMdModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv4_half_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("icosphereModelComp", gco->id);
    ConfiguredGameModel(gco);
    
    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv4_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("icosphereSmoothModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/icosphere_subdiv3_0.75_smooth.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("icosphereRoughModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/tube_light_1_03.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("tube_light_1_03", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/SudaBeam.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("sudaBeamModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/Squid_Happy_Grumpy.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("squidModelComp", gco->id);
    ConfiguredGameModel(gco);

    gco = modelComponents->GetFreeItem();
    if (!meshData->LoadModel("models/SuzanneHighQuality20k.obj", MeshData::Color::White, gco))
        return false;
    namedModelComponentIDs.insert_or_assign("suzanneMonkeModelComp", gco->id);
    ConfiguredGameModel(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX 
    
    return success;
}

// [tdbe] Note: the order in which you set up your materials is the order in which objects get rendered
bool GameData::LoadMaterials()
{
    bool success = true;
    
    if(materialComponents != nullptr) { util::DebugError("[GameData][LoadMaterials]\t Somebody forgot to clear their heap allocations!");  materialComponents->ClearItems(false); }
    materialComponents = new GameDataPool<Material>(AllocationMagicNumbers::MAX_MATERIALS, GlobalUIDSeeds.MATERIAL_COMPONENTS,
                                                    GlobalUIDSeeds.ToString(GlobalUIDSeeds.MATERIAL_COMPONENTS));

    Material* gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("skyMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("diffuseMetalishMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("diffuseStoneMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("diffuseTripIcosphereMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("diffuseEyesMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);
    
    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("textMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("logoMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    // [tdbe] ^ all the (entities with the) materials above are meant to have the same diffuse style blend pipeline,
    // so they'll be batched in the <see cref="Renderer"/> because the materials are reserved here in relative order in the pool.

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("groundMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    // [tdbe] customization / hack: we skip <see cref="skip"/> free slots in case we want to 
    // add more materials with the same pipeline as above, during runtime, that we want batched.
    uint32_t skip = 20;
    uint32_t lastDiffuseMaterialAt = gco->id.index;// we'd have to share this with whoever adds new mats at runtime
    
    gco = materialComponents->GetFreeItem(skip);
    namedMaterialComponentIDs.insert_or_assign("squidMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("lightMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("tentacleLightMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    // [tdbe] Transparent materials (todo: add a job for sorting objects.
    // Per pixel sorting with a Order-independent transparency spv? 
    // But rather than packing sorting pixels I'd rather raytrance into ..something indirect, volumes, nanites..)

    // [tdbe] Note: here I set up 2 materials per transparent material, so I can have 2 pipelines for the same mesh:
    // 1. render the backfaces only, as transparent (and zwrite)
    // 2. render the frontfaces only, as transparent
    // (otherwise the lack of triangle/any sorting will result in the same object's backfaces sometimes being rendered on top of its frontfaces)
    // (an entity (and its model component) can have multiple materials, the engine doesn't care / enforce it but only copies the unioform data from the first entry.)

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("diffuseTransparentBackfaceInstancedMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("bikeTransparentBackfaceMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("diffuseTransparentFrontfaceInstancedMaterialComp", gco->id);
    ConfiguredGameMaterial(gco); 

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("bikeTransparentFrontfaceMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("glassTransparentBackfaceMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);
    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("glassTransparentFrontfaceMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    // [tdbe] VFX materials

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("skyOfChaperoneMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);
    
    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("floorGridMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("ceilingGridMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    gco = materialComponents->GetFreeItem();
    namedMaterialComponentIDs.insert_or_assign("handsMaterialComp", gco->id);
    ConfiguredGameMaterial(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

    return success;
}

bool GameData::LoadGameLights()
{
    bool success = true;

    if(lightComponents != nullptr) { util::DebugError("[GameData][LoadGameLights]\t Somebody forgot to clear their heap allocations!");  lightComponents->ClearItems(false); }
    lightComponents = new GameDataPool<Light>(AllocationMagicNumbers::LIGHTS_COUNT, 
                                              GlobalUIDSeeds.LIGHT_COMPONENTS, 
                                              GlobalUIDSeeds.ToString(GlobalUIDSeeds.LIGHT_COMPONENTS));

    Light* gco = lightComponents->GetFreeItem();
    namedLightComponentIDs.insert_or_assign("mainDirectionalLightComp", gco->id);
    ConfiguredGameLight(gco);

    for (int i = 1; i < 7; i++)
    {
        gco = lightComponents->GetFreeItem();
        namedLightComponentIDs.insert_or_assign("tentacleLightComp0" + util::ToString(i, true), gco->id);
        ConfiguredGameLight(gco);
    }

    gco = lightComponents->GetFreeItem();
    namedLightComponentIDs.insert_or_assign("handLight01Comp", gco->id);
    ConfiguredGameLight(gco);

    gco = lightComponents->GetFreeItem();
    namedLightComponentIDs.insert_or_assign("handLight02Comp", gco->id);
    ConfiguredGameLight(gco);

    gco = lightComponents->GetFreeItem();
    namedLightComponentIDs.insert_or_assign("bikeLightComp", gco->id);
    ConfiguredGameLight(gco);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

    return success;
}

bool GameData::LoadGameEntityObjects()
{
    bool success = true;
    
    if (gameEntityObjects != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their heap allocations!");  gameEntityObjects->ClearItems(false); }
    gameEntityObjects = new GameDataPool<GameEntityObject>(AllocationMagicNumbers.MAX_GAME_ENTITY_OBJECTS,
                                                           GlobalUIDSeeds.GAME_ENTITY_OBJECTS,
                                                           GlobalUIDSeeds.ToString(GlobalUIDSeeds.GAME_ENTITY_OBJECTS));
    if(gameVFXObjects != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their heap allocations!");  gameVFXObjects->ClearItems(false); }
    gameVFXObjects = new GameDataPool<GameEntityObject>(AllocationMagicNumbers.MAX_VFX_GAME_ENTITY_OBJECTS,
                                                        GlobalUIDSeeds.GAME_VFX_OBJECTS,
                                                        GlobalUIDSeeds.ToString(GlobalUIDSeeds.GAME_VFX_OBJECTS));
    if(transformComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their heap allocations!");  transformComponents->ClearItems(false); }
    transformComponents = new GameDataPool<Transform>(AllocationMagicNumbers.MAX_GAME_ENTITY_OBJECTS, 
                                                      GlobalUIDSeeds.TRANSFORM_COMPONENTS,
                                                      GlobalUIDSeeds.ToString(GlobalUIDSeeds.TRANSFORM_COMPONENTS));
    if(boundsComponents != nullptr) { util::DebugError("[GameData][LoadGameEntityObjects]\t Somebody forgot to clear their heap allocations!");  boundsComponents->ClearItems(false); }
    boundsComponents = new GameDataPool<Bounds>(AllocationMagicNumbers::MAX_MODELS, 
                                                      GlobalUIDSeeds.BOUNDS_COMPONENTS,
                                                      GlobalUIDSeeds.ToString(GlobalUIDSeeds.BOUNDS_COMPONENTS));
    GameEntityObject* gento = nullptr;
    GameComponent* comp = nullptr;
    Transform* trans = nullptr;
    Bounds* bounds = nullptr;

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("worldRoot");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    // [tdbe] (the following order does not affect render/batching order; that order's in the material pool)

    // [tdbe] entities with Lights
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("mainDirectionalLight");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedLightComponentIDs["mainDirectionalLightComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    for (int i = 1; i < 7; i++)
    {
        gento = gameEntityObjects->GetFreeItem();
        gento->SetName("tentacle0" + util::ToString(i, true));
        trans = transformComponents->GetFreeItem();
        trans->AddOwnerId(gento->id);
        gento->AddComponentId(trans->id);
        comp = GetComponent(namedLightComponentIDs["tentacleLightComp0" + util::ToString(i, true)]);
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        static_cast<Light*>(comp)->SetVisible(false);
        comp = GetComponent(namedModelComponentIDs["tube_light_1_03"]);
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        bounds = boundsComponents->GetFreeItem();
        bounds->SetBoundsAABB(static_cast<Model*>(comp));
        bounds->AddOwnerId(gento->id);
        gento->AddComponentId(bounds->id);
        comp = GetComponent(namedMaterialComponentIDs["tentacleLightMaterialComp"]);
        comp->AddOwnerId(gento->id);
        gento->AddComponentId(comp->id);
        namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
        ConfiguredGameObject(gento);
    }    

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("handLight01");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedLightComponentIDs["handLight01Comp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    comp = GetComponent(namedModelComponentIDs["tube_light_1_03"]);// [tdbe] Todo: need a procedural capsule that can be squished while preserving hemispherical ends
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["lightMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("handLight02");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedLightComponentIDs["handLight02Comp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    comp = GetComponent(namedModelComponentIDs["tube_light_1_03"]);// [tdbe] Todo: need a procedural capsule that can be squished while preserving hemispherical ends
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["lightMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("bikeLight");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedLightComponentIDs["bikeLightComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    static_cast<Light*>(comp)->SetVisible(false);
    // comp = GetComponent(namedModelComponentIDs["tube_light_1_03"]);// [tdbe] Todo: need a procedural capsule that can
    // be squished while preserving hemispherical ends comp->AddOwnerId(gento->id); gento->AddComponentId(comp->id);
    // bounds = boundsComponents->GetFreeItem();
    // bounds->SetBoundsAABB(static_cast<Model*>(comp));
    // bounds->AddOwnerId(gento->id);
    // gento->AddComponentId(bounds->id);
    // comp = GetComponent(namedMaterialComponentIDs["lightMaterialComp"]);
    // comp->AddOwnerId(gento->id);
    // gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    // [tdbe] world sky

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSkybox");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["icosphereSmoothModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["skyMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    // [tdbe] regular game entities
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("ground");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["groundModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["groundMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("ruins");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["ruinsModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseStoneMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("carLeft");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["carModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseMetalishMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("carRight");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["carModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseMetalishMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("beetle");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["beetleModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseMetalishMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("beetleGlass");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["beetleGlassModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["glassTransparentFrontfaceMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["glassTransparentBackfaceMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("bike");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["bikeModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["bikeTransparentFrontfaceMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["bikeTransparentBackfaceMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("logo1");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["logoModel1Comp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["logoMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("logo2");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["logoModel2Comp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["logoMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("textLocomotion");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["textLocomotionModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["textMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("textSudaBeam");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["textSudaBeamModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["textMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("textSeeControlsMd");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["textSeeControlsMdModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["textMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("cube");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["cubeModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseStoneMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSmoothTripInstancing");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["icosphereSmoothModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseTripIcosphereMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("icosphereSmoothForInstancing");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["icosphereSmoothModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseTransparentFrontfaceInstancedMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseTransparentBackfaceInstancedMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("sudaBeam01");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["sudaBeamModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseMetalishMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("sudaBeam02");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["sudaBeamModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseMetalishMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    
    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("squid");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["squidModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["squidMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("monke");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["suzanneMonkeModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseStoneMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("monkeEye1");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["icosphereRoughModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseEyesMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameEntityObjects->GetFreeItem();
    gento->SetName("monkeEye2");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["icosphereRoughModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["diffuseEyesMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedGameObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    

    // [tdbe] vfx objects are rendered at the end of the queue for the sake of the chaperone / depth etc.
    // ~~~~~~~~~~~~~ gameVFXObjects-> ~~~~~~~~~~~~~
    gento = gameVFXObjects->GetFreeItem();
    gento->SetName("icosphereSkybox");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["icosphereModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["skyOfChaperoneMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedVFXObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameVFXObjects->GetFreeItem();
    gento->SetName("floorGrid");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["quadModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["floorGridMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedVFXObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameVFXObjects->GetFreeItem();
    gento->SetName("ceilingGrid");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["quadModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    comp = GetComponent(namedMaterialComponentIDs["ceilingGridMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedVFXObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);
    util::DebugLog("[Game][GameData][LoadGameWorld][GameEntityObject]\t Done configuring entities.\n");

    gento = gameVFXObjects->GetFreeItem();
    gento->SetName("handLeft");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["handModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["handsMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedVFXObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    gento = gameVFXObjects->GetFreeItem();
    gento->SetName("handRight");
    trans = transformComponents->GetFreeItem();
    trans->AddOwnerId(gento->id);
    gento->AddComponentId(trans->id);
    comp = GetComponent(namedModelComponentIDs["handModelComp"]);
    // comp = GetComponent(namedModelComponentIDs["icosphereSmoothModelComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    bounds = boundsComponents->GetFreeItem();
    bounds->SetBoundsAABB(static_cast<Model*>(comp));
    bounds->AddOwnerId(gento->id);
    gento->AddComponentId(bounds->id);
    comp = GetComponent(namedMaterialComponentIDs["handsMaterialComp"]);
    comp->AddOwnerId(gento->id);
    gento->AddComponentId(comp->id);
    namedVFXObjectIDs.insert_or_assign(gento->GetName(), gento->id);
    ConfiguredGameObject(gento);

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX (max game objects in this case) (but also check each components' max)

    return success;
}

bool GameData::LoadPlayers()
{
    bool success = true;
    playerObjects.resize(AllocationMagicNumbers.MAX_PLAYER_OBJECTS);
    playerObjects.at(0) = new PlayerObject(namedGameObjectIDs["worldRoot"], 
                                           namedVFXObjectIDs["handLeft"],
                                           namedVFXObjectIDs["handRight"], 
                                           "XR Player 1");

    // [tdbe] NOTE: when you add a thing here, remember to check if it fits in AllocationMagicNumbers::MAX_XXXX

    return success;
}

#pragma region LoaderLogging
void Game::GameData::ConfiguredGameObject(GameEntityObject* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorld][GameEntityObject]\t Configured {name: \"" + newObject->GetName() + "\", id: \"" + 
                    newObject->id.PrintGlobalUID() + "\", is std::type_index(typeid(GameEntityObject)): " +
                    util::ToString(newObject->id.typeIndex == std::type_index(typeid(GameEntityObject))) + ".");
}

void Game::GameData::ConfiguredGameModel(Model* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorld][Component][Model]\t Configured component with id: \"" + newObject->id.PrintGlobalUID() +
                   "\", is std::type_index(typeid(Model)): " + util::ToString(newObject->id.typeIndex == std::type_index(typeid(Model))) + ".");
}

void Game::GameData::ConfiguredGameMaterial(Material* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorld][Component][Material]\t Configured component with id: \"" + newObject->id.PrintGlobalUID() + 
                    "\", is std::type_index(typeid(Material)): " + util::ToString(newObject->id.typeIndex == std::type_index(typeid(Material))) + ".");
}

void GameData::ConfiguredGameLight(Light* newObject)
{
    util::DebugLog("[Game][GameData][LoadGameWorld][Component][Light]\t Configured component with id: \"" + newObject->id.PrintGlobalUID() +
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
    util::DebugLog("[Game][GameData][UnLoadGameWorld]\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    util::DebugLog("[Game][GameData][UnLoadGameWorld]\t Unloading entities and components, unhooking events, clearing any maps:");
    //DeleteAllMeshData();
    
    namedModelComponentIDs.clear();
    namedMaterialComponentIDs.clear();
    namedLightComponentIDs.clear();

    namedGameObjectIDs.clear();
    namedVFXObjectIDs.clear();
    
    UnhookOnGameObjectEvents();
    gameEntityObjects->ClearItems(true, fast);
    gameVFXObjects->ClearItems(true, fast);

    transformComponents->ClearItems(true, fast);
    modelComponents->ClearItems(true, fast);
    boundsComponents->ClearItems(true, fast);
    materialComponents->ClearItems(true, fast);
    lightComponents->ClearItems(true, fast);


    for (PlayerObject* player : playerObjects)
        delete player;
    playerObjects.clear();
    
    //std::exception("NotImplementedException");
    return true;
}

GameData::~GameData()
{

}