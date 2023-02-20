#pragma once
#include "Context.h"
#include "Input.h"
#include "InputData.h"
#include "Headset.h"
#include "MeshData.h"
#include "MirrorView.h"
#include "Model.h"
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
  glm::mat4 cameraMatrix = glm::mat4(1.0f); // Transform from world to stage space

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

  Model gridModel, ruinsModel, carModelLeft, carModelRight, beetleModel, bikeModel, handModelLeft, handModelRight,
    logoModel = {};
  std::vector<Model*> models = { &gridModel, &ruinsModel,    &carModelLeft,   &carModelRight, &beetleModel,
                                 &bikeModel, &handModelLeft, &handModelRight, &logoModel };

  gridModel.worldMatrix = ruinsModel.worldMatrix = glm::mat4(1.0f);
  carModelLeft.worldMatrix =
    glm::rotate(glm::translate(glm::mat4(1.0f), { -3.5f, 0.0f, -7.0f }), glm::radians(75.0f), { 0.0f, 1.0f, 0.0f });
  carModelRight.worldMatrix =
    glm::rotate(glm::translate(glm::mat4(1.0f), { 8.0f, 0.0f, -15.0f }), glm::radians(-15.0f), { 0.0f, 1.0f, 0.0f });
  beetleModel.worldMatrix =
    glm::rotate(glm::translate(glm::mat4(1.0f), { -3.5f, 0.0f, -0.5f }), glm::radians(-125.0f), { 0.0f, 1.0f, 0.0f });
  logoModel.worldMatrix = glm::translate(glm::mat4(1.0f), { 0.0f, 3.0f, -10.0f });
  bikeModel.worldMatrix = glm::rotate(glm::translate(glm::mat4(1.0f), { 0.5f, 0.0f, -4.5f }), 0.2f, { 0.0f, 1.0f, 0.0f });

  MeshData* meshData = new MeshData;
  if (!meshData->loadModel("models/Grid.obj", MeshData::Color::FromNormals, models, 0u, 1u)) {
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

  if (!meshData->loadModel("models/Logo.obj", MeshData::Color::White, models, 8u, 1u)) {
    return EXIT_FAILURE;
  }

  Renderer renderer(&context, &headset, meshData, models);
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
    new LocomotionBehaviour(cameraMatrix, handModelLeft, handModelRight, 1, 3, 1),
    new HandsBehaviour(handModelLeft, handModelRight),
    //new InputTesterBehaviour(),
    new WorldObjectsMiscBehaviour(bikeModel)
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
      
      if (!inputSystem.Sync(headset.getXrSpace(), headset.getXrFrameState().predictedDisplayTime, 
                            headset.getEyePoses(), headset.getSessionState()))
      {
        return EXIT_FAILURE;
      }
      const Inputspace::InputData& inputData = inputSystem.GetInputData();
      Inputspace::InputHaptics& inputHaptics = inputSystem.GetInputHaptics();
      
      gameTime += deltaTime;

      // [tdbe] Update
      gameBehaviours[0]->Update(deltaTime, gameTime, inputData, inputHaptics, cameraMatrix);
      const glm::mat4 inverseCameraMatrix = glm::inverse(cameraMatrix);
      for(size_t i = 1u; i < gameBehaviours.size(); i++){
        gameBehaviours[i]->Update(deltaTime, gameTime, inputData, inputHaptics, inverseCameraMatrix);
      }
      inputSystem.ApplyHapticFeedbackRequests(inputHaptics);

      // [tdbe] TODO: do a xrRequestExitSession(session); ?

      // Render
      renderer.render(cameraMatrix, swapchainImageIndex, gameTime);

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