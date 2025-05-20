#pragma once
#include "Context.h"
#include "Input.h"
#include "InputData.h"
#include "Headset.h"
#include "MeshData.h"
#include "MirrorView.h"
#include "GameData.h"
#include "Renderer.h"
#include "gameMechanics/GameBehaviour.h"
#include "gameMechanics/HandsBehaviour.h"
#include "gameMechanics/InputTesterBehaviour.h"
#include "gameMechanics/WorldObjectsMiscBehaviour.h"
#include "gameMechanics/LocomotionBehaviour.h"
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <stdio.h>

namespace
{
constexpr float flySpeedMultiplier = 2.5f;
}

int main()
{
  Context context;
  if (!context.isValid())
  {
    return EXIT_FAILURE;
  }

  MirrorView mirrorView(&context);
  if (!mirrorView.isValid())
  {
    return EXIT_FAILURE;
  }

  if (!context.createDevice(mirrorView.getSurface())) // [tdbe] the mirrorView is only used for checking compatibility
  {
    return EXIT_FAILURE;
  }

  Headset headset(&context);
  if (!headset.isValid())
  {
    return EXIT_FAILURE;
  }

  
  Inputspace::Input inputSystem(context.getXrInstance(), headset.getXrSession());
  if (!inputSystem.isValid())
  {
    return EXIT_FAILURE;
  }

  Model quadModel, ruinsModel, carModelLeft, carModelRight, beetleModel, bikeModel, handModelLeft, handModelRight,
    cubeModel, logoModel1, logoModel2, textLocomotionModel, icosphereModel, icosphereSmoothModel = {};
  std::vector<Model*> models = { &quadModel, &ruinsModel, &carModelLeft, &carModelRight, &beetleModel,
    &bikeModel, &handModelLeft, &handModelRight, &cubeModel, &logoModel1, &logoModel2, &textLocomotionModel, &icosphereModel, &icosphereSmoothModel };
  
  // [tdbe] Just having different materials won't really affect rendering performance; rederer queues per-mesh right now, sampling materials which are identical by default.
  // Materials are a collection of kinds of data that modify the vulkan descriptor or pipeline used, only if you change a corresponding property.
  Material floorGridMaterial, ceilingGridMaterial, groundMaterial, diffuseMaterial, bikeMaterial, skyMaterial,
    logoMaterial,
    handsMaterial = {};
  // [tdbe] init any non-default material props here.  
  diffuseMaterial.vertShaderName = "shaders/Diffuse.vert.spv";
  diffuseMaterial.fragShaderName = "shaders/Diffuse.frag.spv";
  diffuseMaterial.dynamicUniformData.colorMultiplier = glm::vec4(1.0f);

  groundMaterial.vertShaderName = "shaders/Diffuse.vert.spv";
  groundMaterial.fragShaderName = "shaders/Diffuse.frag.spv";
  groundMaterial.dynamicUniformData.colorMultiplier = glm::vec4(0.05f, 0.04f, 0.06f, 1.0f);
 
  logoMaterial.vertShaderName = "shaders/Diffuse.vert.spv";
  logoMaterial.fragShaderName = "shaders/Diffuse.frag.spv";
  logoMaterial.pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
  logoMaterial.dynamicUniformData.colorMultiplier = glm::vec4(1.0f);

  handsMaterial.vertShaderName = "shaders/Hands.vert.spv";
  handsMaterial.fragShaderName = "shaders/Hands.frag.spv";
  handsMaterial.pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
  handsMaterial.dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
  
  // [tdbe] NOTE: For new/transparent materials, blendEnable and blend ops below matter,
  // but also the (depth) order of the gameObjects you send the renderer also matters. (e.g. render your transparents in order at the end)
  // TODO: It's also generally a good idea to fully define material properties, so these material creation blocks should be moved into some functions/templates.
  bikeMaterial.vertShaderName = "shaders/DiffuseTransparent.vert.spv";
  bikeMaterial.fragShaderName = "shaders/DiffuseTransparent.frag.spv";
  bikeMaterial.pipelineData.blendEnable = VK_TRUE;
  bikeMaterial.pipelineData.depthTestEnable = VK_TRUE;
  bikeMaterial.pipelineData.depthWriteEnable = VK_TRUE;
  bikeMaterial.pipelineData.depthCompareOp = VK_COMPARE_OP_LESS;
  bikeMaterial.pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
  bikeMaterial.pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  // bikeMaterial.pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
  // bikeMaterial.pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
  bikeMaterial.pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
  bikeMaterial.pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  bikeMaterial.pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  bikeMaterial.pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
  bikeMaterial.pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
  bikeMaterial.dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 0.0f, 0.1f, 0.76f);

  skyMaterial.vertShaderName = "shaders/Sky.vert.spv";
  skyMaterial.fragShaderName = "shaders/Sky.frag.spv";
  skyMaterial.pipelineData.blendEnable = VK_TRUE;
  skyMaterial.pipelineData.depthTestEnable = VK_TRUE;
  skyMaterial.pipelineData.depthWriteEnable = VK_TRUE;
  skyMaterial.pipelineData.depthCompareOp = VK_COMPARE_OP_LESS;
  skyMaterial.pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
  skyMaterial.pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  skyMaterial.pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
  skyMaterial.pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  skyMaterial.pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  skyMaterial.pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
  skyMaterial.pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
  skyMaterial.dynamicUniformData.colorMultiplier = glm::vec4(0.7f, 0.9f, 1.0f, 1.0f);

  floorGridMaterial.vertShaderName = "shaders/GridGround.vert.spv";
  floorGridMaterial.fragShaderName = "shaders/GridGround.frag.spv";
  floorGridMaterial.pipelineData.blendEnable = VK_TRUE;
  floorGridMaterial.pipelineData.depthTestEnable = VK_TRUE;
  floorGridMaterial.pipelineData.depthWriteEnable = VK_FALSE;
  floorGridMaterial.pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
  floorGridMaterial.pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  floorGridMaterial.pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
  floorGridMaterial.pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  floorGridMaterial.pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  floorGridMaterial.pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
  floorGridMaterial.pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
  floorGridMaterial.dynamicUniformData.colorMultiplier = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

  ceilingGridMaterial.vertShaderName = "shaders/GridSimple.vert.spv";
  ceilingGridMaterial.fragShaderName = "shaders/GridSimple.frag.spv";
  ceilingGridMaterial.pipelineData.blendEnable = VK_TRUE;
  ceilingGridMaterial.pipelineData.depthTestEnable = VK_TRUE;
  ceilingGridMaterial.pipelineData.depthWriteEnable = VK_FALSE;
  ceilingGridMaterial.pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
  ceilingGridMaterial.pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  ceilingGridMaterial.pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
  ceilingGridMaterial.pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  ceilingGridMaterial.pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  ceilingGridMaterial.pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
  ceilingGridMaterial.pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
  ceilingGridMaterial.dynamicUniformData.colorMultiplier = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
  ceilingGridMaterial.dynamicUniformData.perMaterialFragmentFlags.x = 0.15f; // [tdbe] the tunnelvision radius

  std::vector<Material*> materials = { 
      &diffuseMaterial, &groundMaterial, &logoMaterial, &handsMaterial, &skyMaterial, 
      &bikeMaterial, &floorGridMaterial, &ceilingGridMaterial
  };
  
  GameObject worldRoot = GameObject();
  worldRoot.worldMatrix = glm::mat4(1.0f);
  GameObject handLeft = GameObject(&handModelLeft, &handsMaterial, true, "handLeft");
  GameObject handRight = GameObject(&icosphereSmoothModel, &handsMaterial, true, "handRight");
  GameObject ground = GameObject(&quadModel, &groundMaterial, true, "ground");
  GameObject floorGrid = GameObject(&quadModel, &floorGridMaterial, true, "floorGrid");
  GameObject ceilingGrid = GameObject(&quadModel, &ceilingGridMaterial, true, "ceilingGrid");
  GameObject ruins = GameObject(&ruinsModel, &diffuseMaterial, true, "ruins");
  GameObject carLeft = GameObject(&carModelLeft, &diffuseMaterial, true, "carLeft");
  GameObject carRight = GameObject(&carModelRight, &diffuseMaterial, true, "carRight");
  GameObject beetle = GameObject(&beetleModel, &diffuseMaterial, true, "beetle");
  GameObject bike = GameObject(&bikeModel, &bikeMaterial, true, "bike");
  GameObject logo1 = GameObject(&logoModel1, &logoMaterial, true, "logo1");
  GameObject logo2 = GameObject(&logoModel2, &logoMaterial, true, "logo2");
  GameObject textLocomotion = GameObject(&textLocomotionModel, &logoMaterial, true, "textLocomotion");
  GameObject cube = GameObject(&cubeModel, &diffuseMaterial, true, "cube");
  GameObject icosphereSmooth = GameObject(&icosphereSmoothModel, &diffuseMaterial, true, "icosphereSmooth");
  GameObject icosphereSkybox = GameObject(&icosphereModel, &skyMaterial, true, "skybox");
  std::vector<GameObject*> gameObjects = {
      &ground, &ruins, &carLeft, &carRight, &beetle, &handLeft, &handRight, &cube, &icosphereSmooth,
      &logo1, &logo2, &textLocomotion, &bike, &icosphereSkybox, &floorGrid, &ceilingGrid
  };
  PlayerObject playerObject = PlayerObject("XR Player 1", &worldRoot, &handLeft, &handRight);
  
  ground.worldMatrix = glm::translate(glm::scale(worldRoot.worldMatrix, { 256, 256, 256 }), { 0.0f, 0.0f, 0.0f });
  floorGrid.worldMatrix = glm::scale(worldRoot.worldMatrix, { 128, 128, 128 });
  ceilingGrid.worldMatrix = glm::scale(worldRoot.worldMatrix, { 128, 128, 128 });
  ceilingGrid.isVisible = false;
  carLeft.worldMatrix =
    glm::rotate(glm::translate(worldRoot.worldMatrix, { -3.5f, 0.0f, -7.0f }), glm::radians(75.0f), { 0.0f, 1.0f, 0.0f });
  carRight.worldMatrix =
    glm::rotate(glm::translate(worldRoot.worldMatrix, { 8.0f, 0.0f, -15.0f }), glm::radians(-15.0f), { 0.0f, 1.0f, 0.0f });
  beetle.worldMatrix =
    glm::rotate(glm::translate(worldRoot.worldMatrix, { -3.5f, 0.0f, -0.5f }), glm::radians(-125.0f), { 0.0f, 1.0f, 0.0f });
  logo1.worldMatrix = glm::translate(worldRoot.worldMatrix, { 0.0f, 3.0f, -10.0f });
  logo2.worldMatrix = glm::translate(worldRoot.worldMatrix, { 0.0f, 3.0f, -10.0f });
  bike.worldMatrix = glm::rotate(glm::translate(worldRoot.worldMatrix, { 0.5f, 0.0f, -4.5f }), 0.2f, { 0.0f, 1.0f, 0.0f });
  //cube.worldMatrix = glm::scale(glm::translate(worldRoot.worldMatrix, { 4.0f, 2.0f, -2.5f }), { 0.5f, 0.5f, 0.5f });
  cube.worldMatrix = glm::scale(glm::translate(worldRoot.worldMatrix, { 0.5f, -0.35f, -4.5f }), { 0.5f, 0.5f, 0.5f });
  icosphereSmooth.worldMatrix = glm::scale(glm::translate(worldRoot.worldMatrix, { 2.0f, 2.0f, -2.5f }), { 0.5f, 0.5f, 0.5f });
  icosphereSkybox.worldMatrix = glm::scale(glm::rotate(glm::translate(worldRoot.worldMatrix, { 0.0f, 0.0f, 0.0f }), 0.71f, { 0.0f, 1.0f, 0.0f }), { 192.0f, 192.0f, 192.0f });
  textLocomotion.worldMatrix = glm::scale(glm::rotate(glm::translate(worldRoot.worldMatrix, { 2.825f, 0.835f, -1.7f }), -1.5708f, { 0.0f, 1.0f, 0.0f }), { 0.25f, 0.25f, 0.25f });

  MeshData* meshData = new MeshData;
  if (!meshData->loadModel("models/quad.obj", MeshData::Color::White, models, 0u, 1u))
  {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Ruins.obj", MeshData::Color::White, models, 1u, 1u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Car.obj", MeshData::Color::White, models, 2u, 2u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Beetle.obj", MeshData::Color::White, models, 4u, 1u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Bike.obj", MeshData::Color::White, models, 5u, 1u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Hand.obj", MeshData::Color::White, models, 6u, 2u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/cube.obj", MeshData::Color::White, models, 8u, 1u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Logo_OpenXR_Vulkan.obj", MeshData::Color::White, models, 9u, 1u)) {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Logo_Examples.obj", MeshData::Color::White, models, 10u, 1u))
  {
      return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/Text_Locomotion_Flat.obj", MeshData::Color::White, models, 11u, 1u))
  {
      return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/icosphere_subdiv4.obj", MeshData::Color::White, models, 12u, 1u))
  {
    return EXIT_FAILURE;
  }

  if (!meshData->loadModel("models/icosphere_subdiv4_smooth.obj", MeshData::Color::White, models, 13u, 1u))
  {
    return EXIT_FAILURE;
  }

  Renderer renderer(&context, &headset, meshData, materials, gameObjects);
  if (!renderer.isValid())
  {
    return EXIT_FAILURE;
  }

  delete meshData;

  if (!mirrorView.connect(&headset, &renderer))
  {
    return EXIT_FAILURE;
  }

  // [tdbe] all game mechanics, initial resource allocation here, 
  // and then update tick later in game loop
  std::vector<GameBehaviour*> gameBehaviours = {
    new LocomotionBehaviour(playerObject, floorGrid, ceilingGrid, icosphereSkybox, handsMaterial, 1, 3, 1),
    new HandsBehaviour(playerObject),
    //new InputTesterBehaviour(),
    new WorldObjectsMiscBehaviour(bike, logoMaterial, handsMaterial)
  };
    
  static float gameTime = 0.0f;
  
  // Main loop
  std::chrono::high_resolution_clock::time_point previousTime = std::chrono::high_resolution_clock::now();
  while (!headset.isExitRequested() && !mirrorView.isExitRequested())
  {
    // Calculate the delta time in seconds
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
      // [tdbe] Update
      for(size_t i = 0; i < gameBehaviours.size(); i++)
      {
        gameBehaviours[i]->Update(deltaTime, gameTime, inputData, inputHaptics);
      }

      // [tdbe] apply all the haptics we accumulated in our behaviours above
      inputSystem.ApplyHapticFeedbackRequests(inputHaptics);
      
      // headset.setXrReferenceSpacePose(stage space update matrix);
      
      // [tdbe] TODO: do a xrRequestExitSession(session); ?

      // Render
      renderer.render(playerObject.worldRoot->worldMatrix, swapchainImageIndex, gameTime, inputData);
      
      const MirrorView::RenderResult mirrorResult = mirrorView.render(swapchainImageIndex);
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
    if (frameResult == Headset::BeginFrameResult::RenderFully || frameResult == Headset::BeginFrameResult::SkipRender)
    {
      headset.endFrame();
    }
  }

  for(size_t i=0; i<gameBehaviours.size(); i++){
    delete(gameBehaviours[i]);
  }

  context.sync(); // Sync before destroying so that resources are free
  return EXIT_SUCCESS;
}