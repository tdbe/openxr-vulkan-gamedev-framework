#pragma once
// [tdbe] instead of using #define DEBUG, uncomment this line in CMakeLists.txt: #target_compile_definitions(${TARGET_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>) # Add a clean DEBUG prepocessor define if applicable
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

#include "OpenXrAndVulkan/Context.h"
#include "GameData/GameData.h"
#include "OpenXrAndVulkan/Headset.h"
#include "OpenXrInput/Input.h"
#include "OpenXrInput/InputData.h"
#include "GameData/MeshData.h"
#include "OpenXrAndVulkan/MirrorView.h"
#include "OpenXrAndVulkan/Renderer.h"
#include "gameMechanics/GameBehaviour.h"
#include "gameMechanics/HandsBehaviour.h"
#include "gameMechanics/InputTesterBehaviour.h"
#include "gameMechanics/LocomotionBehaviour.h"
#include "gameMechanics/WorldObjectsMiscBehaviour.h"
#include "GameData/Components/Material.h"
#include "GameData/Components/Light.h"
#include "GameData/Components/Transform.h"
#include "GameData/Entities/GameEntityObject.h"
#include "Scripting/Scripting.hpp"
using namespace Game;
using namespace Behaviours;
using namespace Scripting;

/// <summary>
/// [tdbe] Hello intrepid heroes! This repo will be heavily (& redundantly) commented, as if it's a blog post.
/// Purpose of project is to be performant, useful, with wisdom & good programmer ux; do gamedev The Right Way ™. 
/// But it's also 0 budget and you got it for free on the internet so expect a bit of shortcuts, WIP, and no warranty.
/// Cutting edge poor-man's "game engine": ECS, PBR, single pass, OpenXR.
/// </summary>
int main()
{
    Context context;
    if (!context.IsValid())
    {
        return EXIT_FAILURE;
    }

    // [tdbe] I recommend to not use fullscreen. I made the windowed mode size the same as the headset's eye texture.
    // (as long as it's not larger than the monitor, if it is larger, it will scale but preserve aspect ratio).
    // Fullscreen mode will crop the and also scale the eye texture.
    bool fullscreen = false; 
    MirrorView mirrorView(&context, fullscreen);
    if (!mirrorView.IsValid())
    {
        return EXIT_FAILURE;
    }

     // [tdbe] the mirrorView param / surface is only used in here for checking compatibility
    if (!context.createDevice(mirrorView.getSurface()))
    {
        return EXIT_FAILURE;
    }

    Headset headset(&context);
    if (!headset.IsValid())
    {
        return EXIT_FAILURE;
    }

    Inputspace::Input inputSystem(context.getXrInstance(), headset.getXrSession());
    if (!inputSystem.IsValid())
    {
        return EXIT_FAILURE;
    }

    GameData& gameData = GameData::Instance();
    bool success = gameData.LoadGameWorld();
    /*                      (deserialize, allocate, basic init)
                            bool LoadModels();
                            bool LoadMaterials();
                            bool LoadGameLights();
                            bool LoadGameEntityObjects();
                            bool LoadPlayers();
    */
    if (!success)
    {
        return EXIT_FAILURE;
    }

    GameEntityObject* worldRoot = gameData.gameEntityObjects->GetItem(gameData.playerObjects[0]->worldRootId);
    Transform* worldRootTrans = worldRoot->GetComponentByTypeIndex<Transform>();

    success = Scripting::SceneSetup(gameData);
    /*
                Material Components
                Object Entities
                Light Components
    */
    if (!success)
    {
        return EXIT_FAILURE;
    }

    Renderer renderer = Renderer(&context, &headset);
    // [tdbe] the aim should always be to set up gpu bufferas once, with the max number of items you'll use in this game world,
    // the same idea as with the <see cref="GameDataPool"/>. (It doesn't cost gpu power to just have it there.)
    renderer.SetUpRenderProcesses(gameData.meshData, gameData.materialComponents, gameData.gameEntityObjects,
                                   gameData.gameVFXObjects, gameData.lightComponents);
    if (!renderer.IsValid())
    {
        return EXIT_FAILURE;
    }

    // [tdbe] The mesh data gets mapped and copied to the gpu side and lives there.
    // We don't need it on the cpu side. Even if we wanted to procedurally edit some vertices etc, 
    // we'd still do it on the GPU, and maybe bring back or replace just parts of that buffer.
    // The general idea just like with the descriptor sets / uniform data, as well as the <see cref="GameDataPool"/>
    // is we minimize memory expansion/contraction/allocation. We define our memory spans / buffers preferrably once, and then reuse them.
    gameData.DeleteAllMeshData();
    
    // [tdbe] Init game mechanics. Resource bindings here, then tick their update below.
    // Note: we want to show up front (parameters) what items each behaviour will touch.
    // Note: if a behaviour(s) can be replaced by a System that runs a command buffer in a job over a whole buffer/chunk, then IT SHOULD! :)
    std::vector<GameBehaviour*> gameBehaviours = {
        // [tdbe] must be first because it moves everything
        new LocomotionBehaviour(*gameData.playerObjects[0], 
                                gameData.namedVFXObjectIDs["floorGrid"],
                                gameData.namedVFXObjectIDs["ceilingGrid"], 
                                gameData.namedGameObjectIDs["icosphereSkybox"],
                                gameData.namedVFXObjectIDs["icosphereSkybox"],
                                gameData.namedMaterialComponentIDs["handsMaterialComp"], 
                                1.0f, 
                                3.1f, 
                                1),
        new HandsBehaviour(*gameData.playerObjects[0],
                            // [tdbe] the "player inventory":
                            gameData.namedGameObjectIDs["sudaBeam01"],
                            gameData.namedGameObjectIDs["handLight01"], 
                            gameData.namedGameObjectIDs["sudaBeam02"],
                            gameData.namedGameObjectIDs["handLight02"]
                            ),
        //new InputTesterBehaviour(),
        new WorldObjectsMiscBehaviour(gameData.namedGameObjectIDs["bike"], 
                                      gameData.namedGameObjectIDs["bikeLight"],
                                      gameData.namedMaterialComponentIDs["textMaterialComp"],
                                      gameData.namedMaterialComponentIDs["logoMaterialComp"],
                                      gameData.namedMaterialComponentIDs["handsMaterialComp"])
    };

    bool highQualityMirrorView = true;// [tdbe] made the mirror view the same size and aspect ratio as the headset, scaled down if it doesn't fit your monitor.
    bool forceNoScaleDown = true;// [tdbe] Warning: if you set this to true, the window might be larger than your monitor if the monitor's resolution isn't taller and wider than the headset eye resolution.
    if (!mirrorView.connect(&headset, &renderer, highQualityMirrorView, forceNoScaleDown))
    {
        return EXIT_FAILURE;
    }
    
    static float gameTime = 0.0f;
    // Main loop
    std::chrono::high_resolution_clock::time_point previousTime = std::chrono::high_resolution_clock::now();
    while (!headset.isExitRequested() && !mirrorView.isExitRequested())
    {
        const std::chrono::high_resolution_clock::time_point nowTime = std::chrono::high_resolution_clock::now();
        const long long elapsedNanoseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - previousTime).count();
        const float deltaTime = static_cast<float>(elapsedNanoseconds) / 1e9f;
        previousTime = nowTime;

        mirrorView.processWindowEvents();

        uint32_t swapchainImageIndex; // [tdbe] this is for one multiview swapchain image (two eyes one image)
        const Headset::BeginFrameResult frameResult = headset.beginFrame(swapchainImageIndex);
        if (frameResult == Headset::BeginFrameResult::Error)
        {
            return EXIT_FAILURE;
        }
        else if (frameResult == Headset::BeginFrameResult::SkipFully)
        {
            continue;
        }
        else if (frameResult == Headset::BeginFrameResult::RenderFully)
        {
            if (!inputSystem.Sync(headset.getXrSpace(), headset.getEyePoses(),
                                  headset.getXrFrameState().predictedDisplayTime, headset.getSessionState()))
            {
                return EXIT_FAILURE;
            }
            const Inputspace::InputData& inputData = inputSystem.GetInputData();
            Inputspace::InputHaptics& inputHaptics = inputSystem.GetInputHaptics();

            gameTime += deltaTime;
            // [tdbe] Behaviour Update loop
            for (size_t i = 0; i < gameBehaviours.size(); i++)
            {
                gameBehaviours[i]->Update(deltaTime, gameTime, inputData, inputHaptics);
            }
            
            // [tdbe] apply all the haptics we accumulated in our behaviours above
            inputSystem.ApplyHapticFeedbackRequests(inputHaptics);

            // headset.setXrReferenceSpacePose(stage space update matrix);

            // [tdbe] TODO: do a xrRequestExitSession(session); ?

            // [tdbe] Render. (The ideal is indirect rendering, and) 
            // Prefer less drawcalls, less cpu-gpu communication: 
            // - one draw call per material "instanced geometry" style, 
            // - or one draw call per mesh but grouped by material.
            // - or at least grouped by pipeline (e.g. shader / blending).
            renderer.Render(worldRootTrans->GetWorldMatrix(),
                            swapchainImageIndex, 
                            gameTime,
                            inputData,
                            gameData.playerObjects[0]->IsPlayerInState(PlayerStates::ChaperoneState),
                            gameData.materialComponents, 
                            gameData.gameEntityObjects,
                            gameData.gameVFXObjects, 
                            gameData.lightComponents);

            const MirrorView::RenderResult mirrorResult = mirrorView.Render(swapchainImageIndex);
            if (mirrorResult == MirrorView::RenderResult::Error)
            {
                return EXIT_FAILURE;
            }

            const bool mirrorViewVisible = (mirrorResult == MirrorView::RenderResult::Visible);
            renderer.submit(mirrorViewVisible);

            if (mirrorViewVisible)
            {
                mirrorView.present();
            }
        }
        if (frameResult == Headset::BeginFrameResult::RenderFully ||
            frameResult == Headset::BeginFrameResult::SkipRender)
        {
            headset.endFrame();
        }
    }
    
    for (size_t i = 0; i < gameBehaviours.size(); i++)
    {
        delete (gameBehaviours[i]);
    }
    
    gameData.UnLoadGameWorld(true);
    gameData.~GameData();

    context.sync(); // Sync before destroying so that resources are free

    util::DebugLog("[Game][Main][EXIT_SUCCESS]\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    return EXIT_SUCCESS;
}