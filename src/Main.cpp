// [tdbe] instead of using #define DEBUGs, uncomment the line(s) in CMakeLists.txt: #target_compile_definitions(${TARGET_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>) # Add a clean DEBUG prepocessor define if applicable
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
#include "Scripting/GameBehaviours/GameBehaviour.h"
#include "Scripting/GameBehaviours/HandsBehaviour.h"
#include "Scripting/GameBehaviours/InputTesterBehaviour.h"
#include "Scripting/GameBehaviours/LocomotionBehaviour.h"
#include "Scripting/GameBehaviours/WorldObjectsMiscBehaviour.h"
#include "GameData/Components/Material.h"
#include "GameData/Components/Light.h"
#include "GameData/Components/Transform.h"
#include "GameData/Entities/GameEntityObject.h"
#include "Scripting/Scripting.hpp"
#include "Systems/SystemTransformPropagation.h"
using namespace Game;
using namespace Behaviours;
using namespace Scripting;

/// <summary>
/// [tdbe] "Say hello intrepid heroes!" This is a cutting edge poor-man's "game engine": ECS, PBR, single pass OpenXR.
/// The repo will be heavily (even redundantly) commented, like a very accessible blog post. 
/// Purpose of the project is to be performant, share gamedev wisdom and good programmer ux; do gamedev The Right Way™.
/// But it's also 1-person-no-budget, and you got it for free on the internet, so expect a bit of shortcuts, WIP, and no warranty.
/// See the github for open source licence, tl;dr: MIT: use it anywhere, but credit us in a traceable way, and if it's not private then please also let us know about it.
/// https://github.com/tdbe/openxr-vulkan-gamedev-framework / https://blog.deferredreality.com/openxr-vulkan-c++-gamedev-boilerplate
/// </summary>
int main()
{
    util::PrintToLogFile("", false);// clear the previous log file
    util::DebugLog("\n[Game][Main][Starting]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    #ifdef DEBUG
        util::DebugLog("\n[Game][Main][Starting]\t\t DEBUG flag enabled from CMakeLists.txt. For regular notification log messages for the Debug build.");
    #endif
    #ifdef DEBUG_VERBOSE
        util::DebugLog("\n[Game][Main][Starting]\t\t DEBUG_VERBOSE flag enabled from CMakeLists.txt. For messages triggered by objects/entities that might spam a lot, e.g. get pool item, parent/children changed, or item cleared.");
    #endif
    #ifdef DEBUG_THREADS
        // [tdbe] NOTE: for debugging & inspection, you can use:
        // Windows Performance Recorder (WPR) + Windows Performance Analyzer (WPA)
        // or Perfview.
        // And for deeper inspection, Intel VTune Profiler (x86, also works on AMD, and linux) which also records cache misses and other analysis inside bottlenecks.
        // Unfortunately, as CPU/memory profilers 'from the outside', these don't have as much convenient feedback or direct integration, as Renderdoc or Unity Job Profiler.
        // But we have these DEBUG_THREADS taskflow.dump()'s at least.
        util::DebugLog("\n[Game][Main][Starting]\t\t DEBUG_THREADS flag enabled from CMakeLists.txt. For messages printing the state of jobs / threads / taskflow graphs.");
    #endif
    #ifdef DEBUG_RELEASE
        util::DebugLog("\n[Game][Main][Starting]\t\t DEBUG_RELEASE flag enabled from CMakeLists.txt. For regular notification log messages but for the Release build.");
    #endif
    util::DebugLog("\n");
    
    Context context;
    if (!context.IsValid())
    {
        return EXIT_FAILURE;
    }

    // [tdbe] I recommend to not use fullscreen/scaling because I made the windowed mode default to the unscaled size of the headset's eye texture.
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
    
    // [tdbe] just getting some headset info
    const XrInstance xrInstance = context.getXrInstance();
    const XrSystemId xrSystemId = context.getXrSystemId();
    XrSystemProperties systemProperties{XR_TYPE_SYSTEM_PROPERTIES};
    XrResult xrResult = xrGetSystemProperties(xrInstance, xrSystemId, &systemProperties);
    std::string headsetActualMFString(systemProperties.systemName);
    util::DebugLog("[Game][Main]\t\t [OO] XR System Name: "+ headsetActualMFString + ". Note you can change your active xr system via each platform's apps' settings (e.g. steam or oculus).");

    GameData& gameData = GameData::Instance();
    bool success = gameData.LoadGameWorlds();
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

    GameEntityObject* worldRoot = gameData.mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>().GetItem(gameData.playerObjects[0]->worldRootId);
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
    
    if(util::StrContains(headsetActualMFString, "AetherVR"))
    {
        util::Posef firstPose = worldRootTrans->GetWorldPose();
        firstPose.position.y = 1.7f;
        worldRootTrans->SetWorldPose(firstPose);
        util::DebugLog("[Game][Main]\t\t Offsetting initial world root because we're running a virtual headset. worldRootTrans: "+ util::ToString(worldRootTrans->GetWorldPose().position));
    }

    Renderer renderer = Renderer(&context, &headset);
    // [tdbe] the aim should always be to set up gpu bufferas once, with the max number of items you'll use in this game world,
    // the same idea as with the <see cref="GameDataPool"/>. (It doesn't cost gpu power to just have it there.)
    renderer.SetUpRenderProcesses(gameData.meshData, gameData);
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
                                gameData.namedGameObjectIDs.left.at("floorGrid"),
                                gameData.namedGameObjectIDs.left.at("ceilingGrid"), 
                                gameData.namedGameObjectIDs.left.at("icosphereSkybox_world"),
                                gameData.namedGameObjectIDs.left.at("icosphereSkybox_chaperone"),
                                gameData.namedMaterialComponentIDs.left.at("handsMaterialComp"), 
                                1.0f, 
                                3.1f, 
                                1),
        new HandsBehaviour(*gameData.playerObjects[0],
                            // [tdbe] the "player inventory":
                            gameData.namedGameObjectIDs.left.at("sudaBeam01"),
                            gameData.namedGameObjectIDs.left.at("handLight01"), 
                            gameData.namedGameObjectIDs.left.at("sudaBeam02"),
                            gameData.namedGameObjectIDs.left.at("handLight02")
                            ),
        //new InputTesterBehaviour(),
        new WorldObjectsMiscBehaviour(gameData.namedGameObjectIDs.left.at("bike"), 
                                      gameData.namedGameObjectIDs.left.at("bikeLight"),
                                      gameData.namedMaterialComponentIDs.left.at("textMaterialComp"),
                                      gameData.namedMaterialComponentIDs.left.at("logoMaterialComp"),
                                      gameData.namedMaterialComponentIDs.left.at("handsMaterialComp"))
    };

    bool highQualityMirrorView = true;// [tdbe] made the mirror view the same size and aspect ratio as the headset, scaled down if it doesn't fit your monitor.
    bool forceNoScaleDown = true;// [tdbe] Warning: if you set this to true, the window might be larger than your monitor if the monitor's resolution isn't taller and wider than the headset eye resolution.
    if (!mirrorView.connect(&headset, &renderer, highQualityMirrorView, forceNoScaleDown))
    {
        return EXIT_FAILURE;
    }
    
    SystemTransformPropagation transformPropagationSystem;
    transformPropagationSystem.OnCreate();
    static float gameTime = 0.0f;
    // Main loop
    util::DebugLog("\n[Game][Main]\t\t『⛬』🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞");
    util::DebugLog("[Game][Main]\t\t Starting Game Loop:");
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
            util::DebugLog("[Game][Main]\t\t Headset::BeginFrameResult::Error");
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
                util::DebugLog("[Game][Main]\t\t inputSystem Sync failure.");
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

            transformPropagationSystem.OnUpdate();

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
                            gameData);

            const MirrorView::RenderResult mirrorResult = mirrorView.Render(swapchainImageIndex);
            if (mirrorResult == MirrorView::RenderResult::Error)
            {
                util::DebugLog("[Game][Main]\t\t mirrorView.Render failure.");
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
    util::DebugLog("\n[Game][Main]\t\t🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞『⛬』");
    util::DebugLog("[Game][Main]\t\t Game Loop ended. Cleaning up.");
    
    transformPropagationSystem.OnDestroy();
    
    for (size_t i = 0; i < gameBehaviours.size(); i++)
    {
        delete (gameBehaviours[i]);
    }
    
    context.sync(); // Sync before destroying so that resources are free
    
    gameData.UnLoadGameWorlds(true);

    util::DebugLog("\n[Game][Main][EXIT_SUCCESS]\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    return EXIT_SUCCESS;
}