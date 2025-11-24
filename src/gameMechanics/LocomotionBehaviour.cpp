#pragma once
#include "LocomotionBehaviour.h"
#include "../Utils/Util.h"
#include "../GameData/Entities/GameEntityObject.h"
#include "../GameData/PlayerObject.h"
#include "../GameData/Components/Transform.h"
#include "../GameData/Components/Material.h"
#include "../GameData/GameData.h"
#include <stdio.h>
//#include <glm/gtx/matrix_decompose.hpp>
using namespace Game;
using namespace Behaviours;

void LocomotionBehaviour::SetTeleportRequest(glm::vec3 destination)
{
    teleportRequest.targetDestination = destination;
    teleportRequest.state = TeleportRequest::State::Requested;
}

LocomotionBehaviour::LocomotionBehaviour(PlayerObject& playerObject, 
                                        GameDataId::ID floorGridId, 
                                        GameDataId::ID ceilingGridId,
                                        GameDataId::ID icosphereSkyboxId, 
                                        GameDataId::ID chaperoneSkyboxId, 
                                        GameDataId::ID handsMaterialId, 
                                        float movementSpeedScaler, 
                                        float movementAccelerationPow, 
                                        float rotationSpeedScaler)
: playerObject(playerObject)
{
    this->movementSpeedScaler = movementSpeedScaler;
    this->movementAccelerationPow = movementAccelerationPow;
    this->rotationSpeedScaler = rotationSpeedScaler;
    this->floorGridId = floorGridId;
    this->ceilingGridId = ceilingGridId;
    this->icosphereSkyboxId = icosphereSkyboxId;
    this->chaperoneSkyboxId = chaperoneSkyboxId;
    this->handsMaterialId = handsMaterialId;

    Material* floorGridMat = GameData::Instance().gameVFXObjects->GetItem(floorGridId)
        ->GetComponentByTypeIndex<Material>();
    Material* ceilingGridMat = GameData::Instance().gameVFXObjects->GetItem(ceilingGridId)
        ->GetComponentByTypeIndex<Material>();
    Material* handsMat = GameData::Instance().materialComponents->GetItem(handsMaterialId);
    
    Material* chaperoneSkyMat =
        GameData::Instance()
            .gameVFXObjects->GetItem(chaperoneSkyboxId)
            ->GetComponentByTypeIndex<Material>();

    Transform* floorGridTrans = GameData::Instance().gameVFXObjects->GetItem(floorGridId)
        ->GetComponentByTypeIndex<Transform>();
    Transform* skyTrans = GameData::Instance().gameVFXObjects->GetItem(chaperoneSkyboxId)
        ->GetComponentByTypeIndex<Transform>();

    origFloorGridMatr = floorGridTrans->GetWorldMatrix();
    origSkyboxMatr = skyTrans->GetWorldMatrix();
    prevHandsMatVisible = handsMat->IsVisible();
    moveStateData = {};

    floorGridMat->SetVisible(false);
    ceilingGridMat->SetVisible(false);
    chaperoneSkyMat->SetVisible(false);
    ceilingGridMat->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
    floorGridMat->dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
    floorGridMat->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
    handsMat->dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
    chaperoneSkyMat->dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
    chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
}

void LocomotionBehaviour::HandleVisualsState(const float deltaTime, const Inputspace::InputData &inputData, 
    const XrActionStateFloat& grabLeft, const XrActionStateFloat& grabRight, const float avgGrabInput, 
    TeleportRequest::State& teleportState, Inputspace::InputHaptics& inputHaptics)
{
    if (currentVisualsState == VisualsState::Clear && teleportState == TeleportRequest::State::Finished)
    {
        return;
    }

    Material* floorGridMat = GameData::Instance().gameVFXObjects->GetItem(floorGridId)
        ->GetComponentByTypeIndex<Material>();
    Material* ceilingGridMat = GameData::Instance().gameVFXObjects->GetItem(ceilingGridId)
        ->GetComponentByTypeIndex<Material>();
    Material* handsMat = GameData::Instance().materialComponents->GetItem(handsMaterialId);

    Material* chaperoneSkyMat = GameData::Instance().gameVFXObjects->GetItem(chaperoneSkyboxId)
            ->GetComponentByTypeIndex<Material>();

    Transform* worldRootTrans = GameData::Instance().gameEntityObjects->GetItem(playerObject.worldRootId)
        ->GetComponentByTypeIndex<Transform>();
    GameEntityObject* handLeftGeo = GameData::Instance().gameEntityObjects->GetItem(playerObject.handLeftId);
    GameEntityObject* handRightGeo = GameData::Instance().gameEntityObjects->GetItem(playerObject.handRightId);
    Transform* handLeftTrans = handLeftGeo->GetComponentByTypeIndex<Transform>();
    Transform* handRightTrans = handRightGeo->GetComponentByTypeIndex<Transform>();
    Transform* floorGridTrans = GameData::Instance().gameVFXObjects->GetItem(floorGridId)
        ->GetComponentByTypeIndex<Transform>();
    Transform* ceilingGridTrans = GameData::Instance().gameVFXObjects->GetItem(ceilingGridId)
        ->GetComponentByTypeIndex<Transform>();

    Transform* chaperoneSkyTrans =
        GameData::Instance().gameVFXObjects->GetItem(chaperoneSkyboxId)->GetComponentByTypeIndex<Transform>();
    
    const float chaperoneRingRadius =
        0.39f; // [tdbe] distance along the radius of the screen at which to draw a boundary (a circle)
    const float chaperoneRingLowestBounceRadius =
        0.27f; // [tdbe] during animations, shrink the circle to a minimum of this radius distance
    const float chaperoneRingHighestRadius =
        1.0f; // [tdbe] during animations, enlarge the circle to a maximum of this radius distance
    const float chaperoneRingLerpSpeed = 3.0f * (teleportState == TeleportRequest::State::Finished ? 1.0f : 0.3333f);
    auto handleAnyActiveState = [&]()
    {
        // [tdbe] Display the hands and grids above the scene geometry
        {
            if (currentVisualsState == VisualsState::Start)
            {
                floorGridMat->SetVisible(true);
                ceilingGridMat->SetVisible(true);
                chaperoneSkyMat->SetVisible(true);
                prevHandsEnabled.at(0) = handLeftGeo->IsEnabled();
                prevHandsEnabled.at(1) = handRightGeo->IsEnabled();
                prevHandsMatVisible = handsMat->IsVisible();
                handLeftGeo->SetEnabled(true);
                handRightGeo->SetEnabled(true);
                handsMat->SetVisible(true);
            }
            else if (currentVisualsState == VisualsState::End)
            {
                floorGridMat->SetVisible(false);
                ceilingGridMat->SetVisible(false);
                chaperoneSkyMat->SetVisible(false);
                handLeftGeo->SetEnabled(prevHandsEnabled.at(0));
                handRightGeo->SetEnabled(prevHandsEnabled.at(1));
                handsMat->SetVisible(prevHandsMatVisible);
            }
        }

        // [tdbe] Display the chaperone sky above the scene geometry (it will have a depth "hole" in the middle to
        // see the world).
        {
            if (currentVisualsState == VisualsState::Start)
            {
                handsMat->dynamicUniformData.perMaterialVertexFlags.w = 0.001f;// [tdbe] Display the hands above everything else
                ceilingGridMat->dynamicUniformData.perMaterialFragmentFlags.w = 0.002f;
                floorGridMat->dynamicUniformData.perMaterialVertexFlags.w = 0.002f;
                floorGridMat->dynamicUniformData.perMaterialFragmentFlags.w = 0.002f;
                chaperoneSkyMat->dynamicUniformData.perMaterialVertexFlags.w = 0.003f;// [tdbe] Display the chaperone above most things
                chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.w = 0.003f;// [tdbe] Display the chaperone above most things
            }
            else if (currentVisualsState == VisualsState::End)
            {
                handsMat->dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
                ceilingGridMat->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;  
                floorGridMat->dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
                floorGridMat->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
                chaperoneSkyMat->dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
                chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
            }
        }

        glm::mat4 worldRootMatr = worldRootTrans->GetWorldMatrix();
        /*
        // [tdbe] Stick the chaperoneSlicerTrans to your forehead (well, actually about as far away as the portal
        will be).
        //  (-0.033f would be centered on preview window's (right) eye)
        glm::vec3 objectSpaceForwardPortalLength = glm::vec3(0.0, -1.7f, 0.0f);//-1.7//-2.35
        glm::mat4 foreheadMatrix = inputData.eyePoseMatrixes[0];
        foreheadMatrix = glm::scale(foreheadMatrix, { 1.4f, 1.4f, 1.0f });
        foreheadMatrix = glm::rotate(foreheadMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        foreheadMatrix = glm::translate(foreheadMatrix, objectSpaceForwardPortalLength);
        foreheadMatrix = worldRootMatr * foreheadMatrix;
        chaperoneSlicerTrans->SetWorldMatrix(foreheadMatrix);
        */

        glm::mat4 matr = worldRootMatr * origFloorGridMatr;
        glm::mat4 floorGridMatr = matr;
        glm::mat4 ceilingGridMatr = matr;

        floorGridMatr[3].y = worldRootMatr[3].y;
        floorGridTrans->SetWorldMatrix(floorGridMatr);
        glm::mat4 skyMatr = worldRootMatr * origSkyboxMatr;
        skyMatr[3].y = worldRootMatr[3].y;
        chaperoneSkyTrans->SetWorldMatrix(skyMatr);
        ceilingGridMatr[3].y = worldRootMatr[3].y + 3;
        ceilingGridTrans->SetWorldMatrix(ceilingGridMatr);
    };

    auto handleStartState = [&](bool autoTransition = true)
    {
        float chapLerpv = chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x;

        // [tdbe] request haptics
        if (chapLerpv == chaperoneRingHighestRadius)
        {
            inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.5f);
            inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.5f);
        }

        // [tdbe] do some intro tunel-vision chaperone animation
        // (note: the items are turned on and off via isVisible further up)
        chapLerpv -= deltaTime * chaperoneRingLerpSpeed * 11.0f;
        if (chapLerpv < chaperoneRingLowestBounceRadius)
            chapLerpv = chaperoneRingLowestBounceRadius;

        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;

        float ringWobbleStability =
            util::remapInterval(glm::abs(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 1, 0);
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;

        float chaperoneFader =
            util::remapInterval(util::clampf01(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 0, 1);
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::Start (anim: {%f})\n", chapLerpv);
        if (autoTransition)
        {
            if (chapLerpv == chaperoneRingLowestBounceRadius)
                currentVisualsState = VisualsState::Intro;
            playerObject.SetPlayerState(PlayerStates::ChaperoneState, false);
        }
    };

    auto handleIntroState = [&](bool autoTransition = true)
    {
        // do some intro tunel-vision chaperone animation
        float chapLerpv = chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x;
        chapLerpv += deltaTime * chaperoneRingLerpSpeed;
        if (chapLerpv > chaperoneRingRadius)
            chapLerpv = chaperoneRingRadius;

        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;

        float ringWobbleStability =
            util::remapInterval(glm::abs(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 1, 0);
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;

        float chaperoneFader =
            util::remapInterval(util::clampf01(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 0, 1);
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::Intro (anim: {%f}, chaperoneRingRadius: {%f})\n", chapLerpv,
               chaperoneRingRadius);
        if (autoTransition)
        {
            if (chapLerpv == chaperoneRingRadius)
                currentVisualsState = VisualsState::Update;
            
            if (chapLerpv > chaperoneRingRadius / 2.0f)
                playerObject.SetPlayerState(PlayerStates::ChaperoneState, true);
        }
    };

    auto handleUpdateState = [&](bool autoTransition = true) 
    {
        // [tdbe] do some looping tunel-vision chaperone animation or just wait: actually I do it in the shader instead
        // printf("[LocomotionBehaviour][log] VisualsState::Update\n");
        if (autoTransition)
        {
            currentVisualsState = VisualsState::Outro;
        }
    };

    auto handleOutroState = [&](bool autoTransition = true) 
    {
        // do some outro chaperone animation
        float chapLerpv = chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x;
        chapLerpv += deltaTime * chaperoneRingLerpSpeed * 11.0f;
        if (chapLerpv > chaperoneRingHighestRadius)
            chapLerpv = chaperoneRingHighestRadius;

        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;

        float ringWobbleStability =
            util::remapInterval(glm::abs(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 1, 0);
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;

        float chaperoneFader =
            util::remapInterval(util::clampf01(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 0, 1);
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::Outro (anim: {%f}, chaperoneRingRadius: {%f})\n", chapLerpv,
               chaperoneRingRadius);
        if (autoTransition)
        {
            if (chapLerpv == chaperoneRingHighestRadius)
                currentVisualsState = VisualsState::End;
            else if (chapLerpv > chaperoneRingRadius * 2.0f)
                playerObject.SetPlayerState(PlayerStates::ChaperoneState, false);
        }
    };

    auto handleEndState = [&](bool autoTransition = true) 
    {
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.33f, XR_MIN_HAPTIC_DURATION, 0.33f);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.33f, XR_MIN_HAPTIC_DURATION, 0.33f);

        // [tdbe] clear any data here
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.x = chaperoneRingHighestRadius;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.x = chaperoneRingHighestRadius;

        float ringWobbleStability = chaperoneRingHighestRadius;
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.y = chaperoneRingHighestRadius;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.y = chaperoneRingHighestRadius;

        float chaperoneFader = chaperoneRingHighestRadius;
        chaperoneSkyMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGridMat->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::End\n");
        if (autoTransition)
        {
            currentVisualsState = VisualsState::Clear;
            playerObject.SetPlayerState(PlayerStates::ChaperoneState, false);
        }
    };

    if (currentVisualsState != VisualsState::Clear)
    {
        handleAnyActiveState();
    }

    if(currentVisualsState == VisualsState::Start)
    {
        handleStartState();
    }
    else if (currentVisualsState == VisualsState::Intro)
    {
        handleIntroState();
    }
    else if(currentVisualsState == VisualsState::Update)
    {
        handleUpdateState(teleportState == TeleportRequest::State::Ongoing);
    }
    else if(currentVisualsState == VisualsState::Outro)
    {
        handleOutroState();
    }
    else if (currentVisualsState == VisualsState::End)
    {
        handleEndState();
        if (teleportState == TeleportRequest::State::Ongoing)
            teleportState = TeleportRequest::State::Finished;
    }
}

void LocomotionBehaviour::HandleMovementState(const float deltaTime, const Inputspace::InputData &inputData, 
    const XrActionStateFloat& grabLeft, const XrActionStateFloat& grabRight, const float avgGrabInput, 
    const TeleportRequest& teleportRequest, Inputspace::InputHaptics &inputHaptics)
{
    if (currentMovementState == MovementState::Clear && teleportRequest.state == TeleportRequest::State::Finished)
    {
        return;
    }

    Transform* worldRootTrans = GameData::Instance()
                                        .gameEntityObjects->GetItem(playerObject.worldRootId)
                                        ->GetComponentByTypeIndex<Transform>();
    glm::mat4 worldRootMatr = worldRootTrans->GetWorldMatrix();

    auto handleStartState = [&](bool autoTransition = true)
    {
        moveStateData.prevPosLeft =
            glm::vec3((inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT])
                          [3]); // inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::LEFT].position;
        moveStateData.prevPosRight =
            glm::vec3((inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT])
                          [3]); // inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::RIGHT].position;
        moveStateData.prevPosMiddle = 0.5f * (moveStateData.prevPosLeft + moveStateData.prevPosRight);
        moveStateData.prevPosMiddle.y = 0;

        moveStateData.prevDirLeftRight = moveStateData.prevPosRight - moveStateData.prevPosLeft;
        moveStateData.prevDirLeftRight.y = 0;
        moveStateData.prevDirLeftRight =
            moveStateData.prevDirLeftRight / (float)moveStateData.prevDirLeftRight.length();

        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);

        printf("[LocomotionBehaviour][log] \tMovementState::Start\n");

        if (autoTransition)
        {
            if (currentVisualsState == VisualsState::Update || currentVisualsState == VisualsState::Outro)
            {
                currentMovementState = MovementState::Update;
            }
        }
    };

    auto handleUpdateState = [&](bool autoTransition = true)
    {
        Transform* handLeftTrans =  GameData::Instance()
                                       .gameEntityObjects->GetItem(playerObject.handLeftId)
                                       ->GetComponentByTypeIndex<Transform>();
        Transform* handRightTrans = GameData::Instance()
                                        .gameEntityObjects->GetItem(playerObject.handRightId)
                                        ->GetComponentByTypeIndex<Transform>();
        Transform* skyTrans =       GameData::Instance().gameEntityObjects->GetItem(icosphereSkyboxId)
                                        ->GetComponentByTypeIndex<Transform>();

        moveStateData.posLeft =
            glm::vec3((inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT])
                          [3]); // inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::LEFT].position;
        moveStateData.posRight =
            glm::vec3((inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT])
                          [3]); // inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::RIGHT].position;
        moveStateData.posMiddle = 0.5f * (moveStateData.posLeft + moveStateData.posRight);
        moveStateData.posMiddle.y = 0;
        moveStateData.moveDir = moveStateData.posMiddle - moveStateData.prevPosMiddle;
        moveStateData.moveInputSpeed = (float)moveStateData.moveDir.length();
        moveStateData.moveDir = moveStateData.moveDir / moveStateData.moveInputSpeed;

        // [tdbe] TODO:
        //  Perhaps add an inertia to be able to do flick moves :)
        //  And if you have a larger world: A mode with a bit of an upward leap, like in that Lucid Trips VR game. (but
        //  lock-on chaperone until you land)
        glm::mat4 handLeftMatr = handLeftTrans->GetWorldMatrix();
        glm::mat4 handRightMatr = handRightTrans->GetWorldMatrix();

        // [tdbe] move player along moveDir, with a speed scaled by hand movement speed.
        float moveSpeed =
            avgGrabInput * movementSpeedScaler * glm::pow(moveStateData.moveInputSpeed, movementAccelerationPow);
        // [tdbe] extra speed from thumbsticks
        XrActionStateVector2f moveSpeedBoostLeftXAS = inputData.thumbStickState[(int)Inputspace::ControllerEnum::LEFT];
        float moveSpeedBoostLeft = !moveSpeedBoostLeftXAS.isActive ?
                                       0.0f :
                                       glm::clamp(glm::abs(moveSpeedBoostLeftXAS.currentState.x) +
                                                      glm::abs(moveSpeedBoostLeftXAS.currentState.y),
                                                  0.0f, 1.0f);
        XrActionStateVector2f moveSpeedBoostRightXAS =
            inputData.thumbStickState[(int)Inputspace::ControllerEnum::RIGHT];
        float moveSpeedBoostRight = !moveSpeedBoostRightXAS.isActive ?
                                        0.0f :
                                        glm::clamp(glm::abs(moveSpeedBoostRightXAS.currentState.x) +
                                                       glm::abs(moveSpeedBoostRightXAS.currentState.y),
                                                   0.0f, 1.0f);
        float speedBoost = moveSpeedBoostLeft + moveSpeedBoostRight;
        moveSpeed += speedBoost * moveSpeed;
        glm::vec3 moveVec = -100.0f * moveStateData.moveDir * moveSpeed * deltaTime;
        // printf("[LocomotionBehaviour][log] moveSpeed: {%f}, moveVec: {%f}{%f}{%f}, deltaTime: {%f},
        // moveStateData.moveDir: {%f}{%f}{%f}\n", moveSpeed, moveVec.x, moveVec.y, moveVec.z, deltaTime,
        // moveStateData.moveDir.x, moveStateData.moveDir.y, moveStateData.moveDir.z);
        worldRootMatr = glm::translate(worldRootMatr, moveVec);
        handLeftTrans->SetWorldMatrix(glm::translate(handLeftMatr, -moveVec));
        moveVec.x = -moveVec.x; // because right hand is a flipped left hand model
        handRightTrans->SetWorldMatrix(glm::translate(handRightMatr, -moveVec));
        glm::mat4 skyMatr = worldRootMatr * origSkyboxMatr;
        skyMatr[3].y = worldRootMatr[3].y;
        skyTrans->SetWorldMatrix(skyMatr);

        // [tdbe] rotate player based on line between the hands
        float distBetweenHands = glm::distance(moveStateData.posRight, moveStateData.posLeft);
        moveStateData.dirLeftRight = moveStateData.posRight - moveStateData.posLeft;
        moveStateData.dirLeftRight.y = 0;
        moveStateData.dirLeftRight = moveStateData.dirLeftRight / (float)moveStateData.dirLeftRight.length();
        glm::vec3 norm = glm::vec3(0, 1, 0);
        float radang = util::vectorAngleAroundNormal(moveStateData.dirLeftRight, moveStateData.prevDirLeftRight, norm);
        radang = distBetweenHands * 150.0f * avgGrabInput * rotationSpeedScaler * radang * deltaTime;
        // printf("[LocomotionBehaviour][log] rotation angle rad: %f\n", radang);
        worldRootTrans->SetWorldMatrix(glm::rotate(worldRootMatr, radang, norm));

        moveStateData.prevPosLeft = moveStateData.posLeft;
        moveStateData.prevPosRight = moveStateData.posRight;
        moveStateData.prevPosMiddle = moveStateData.posMiddle;
        moveStateData.prevDirLeftRight = moveStateData.dirLeftRight;
        //printf("[LocomotionBehaviour][log] \tMovementState::Update\n");
        if (autoTransition)
        {
            currentMovementState = MovementState::End;
        }
    };

    auto handleEndState = [&](bool autoTransition = true)
    {
        // [tdbe] clear any data here

        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);

        printf("[LocomotionBehaviour][log] \tMovementState::End\n");
        if (autoTransition)
        {
            currentMovementState = MovementState::Clear;
        }
    };

    if(currentMovementState == MovementState::Start)
    {
        handleStartState();
    }
    else if (currentMovementState == MovementState::Update)
    {
        if (teleportRequest.state == TeleportRequest::State::Ongoing)
            worldRootMatr[3] = glm::vec4(teleportRequest.targetDestination, 1.0f);
        handleUpdateState(teleportRequest.state == TeleportRequest::State::Ongoing);
    }
    else if(currentMovementState == MovementState::End)
    {
        handleEndState();
    }
}

void LocomotionBehaviour::Update(const float deltaTime, const float gameTime, 
    const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics)
{
    XrActionStateBoolean resetPosInputLeft = inputData.xClickState[(int)Inputspace::ControllerEnum::LEFT];
    XrActionStateBoolean resetPosInputRight = inputData.aClickState[(int)Inputspace::ControllerEnum::RIGHT];

    bool forceOn = false;
    XrActionStateFloat grabLeft = inputData.grabState[(int)Inputspace::ControllerEnum::LEFT];
    XrActionStateFloat grabRight = inputData.grabState[(int)Inputspace::ControllerEnum::RIGHT];
    float avgGrabInput = .5f*(grabLeft.currentState + grabRight.currentState);

    {
        // [tdbe] Request to teleport the player to position to 0,0,0.
        // Note: on other controllers the names of the inputData buttons (e.g. x, a, select) may differ,
        // but <see cref="Input.cpp"/> will have mapped some (closest) equivalents.
        bool resetPositionRequested = false;
        XrActionStateBoolean resetPosLeftXAS1 = inputData.xClickState[(int)Inputspace::ControllerEnum::LEFT];
        XrActionStateBoolean resetPosLeftXAS2 = inputData.aClickState[(int)Inputspace::ControllerEnum::LEFT];
        XrActionStateBoolean resetPosLeftXAS3 = inputData.menuClickState[(int)Inputspace::ControllerEnum::LEFT];
        XrActionStateBoolean resetPosLeftXAS4 = inputData.selectClickState[(int)Inputspace::ControllerEnum::LEFT];
        XrActionStateBoolean resetPosRightXAS1 = inputData.xClickState[(int)Inputspace::ControllerEnum::RIGHT];
        XrActionStateBoolean resetPosRightXAS2 = inputData.aClickState[(int)Inputspace::ControllerEnum::RIGHT];
        XrActionStateBoolean resetPosRightXAS3 = inputData.menuClickState[(int)Inputspace::ControllerEnum::RIGHT];
        XrActionStateBoolean resetPosRightXAS4 = inputData.selectClickState[(int)Inputspace::ControllerEnum::RIGHT];
        if (resetPosLeftXAS1.isActive && resetPosRightXAS1.isActive && resetPosLeftXAS1.currentState &&
                resetPosRightXAS1.currentState ||
            resetPosLeftXAS1.isActive && resetPosRightXAS2.isActive && resetPosLeftXAS1.currentState &&
                resetPosRightXAS2.currentState ||
            resetPosLeftXAS2.isActive && resetPosRightXAS1.isActive && resetPosLeftXAS2.currentState &&
                resetPosRightXAS1.currentState ||
            resetPosLeftXAS2.isActive && resetPosRightXAS2.isActive && resetPosLeftXAS2.currentState &&
                resetPosRightXAS2.currentState ||
            resetPosLeftXAS3.isActive && resetPosRightXAS3.isActive && resetPosLeftXAS3.currentState &&
                resetPosRightXAS3.currentState ||
            resetPosLeftXAS3.isActive && resetPosRightXAS4.isActive && resetPosLeftXAS3.currentState &&
                resetPosRightXAS4.currentState ||
            resetPosLeftXAS4.isActive && resetPosRightXAS3.isActive && resetPosLeftXAS4.currentState &&
                resetPosRightXAS3.currentState ||
            resetPosLeftXAS4.isActive && resetPosRightXAS4.isActive && resetPosLeftXAS4.currentState &&
                resetPosRightXAS4.currentState)
        {
            resetPositionRequested = true;
        }

        bool alreadyTeleportingToOrigin = teleportRequest.state != TeleportRequest::State::Finished &&
                                          teleportRequest.targetDestination == teleportRequest.origin;
        if (resetPositionRequested && !alreadyTeleportingToOrigin)
        {
            SetTeleportRequest(teleportRequest.origin);
        }
    }

    if (teleportRequest.state != TeleportRequest::State::Finished)
    {
        if (teleportRequest.state == TeleportRequest::State::Requested)
        {
            printf("[LocomotionBehaviour][log] TeleportRequest::State::Requested\n");
            teleportRequest.state = TeleportRequest::State::Ongoing;
            currentVisualsState = VisualsState::Start;
            currentMovementState = MovementState::Start;
        }
    }
    else if (forceOn || grabLeft.isActive && grabRight.isActive)
    {
        // [tdbe] Set visuals state
        {
            if(forceOn || avgGrabInput > .66f && grabLeft.currentState > .33f && grabRight.currentState > .33f)
            {
                if( currentVisualsState != VisualsState::Start &&
                    currentVisualsState != VisualsState::Intro &&
                    currentVisualsState != VisualsState::Update &&
                    currentVisualsState != VisualsState::Outro &&
                    currentVisualsState != VisualsState::End)
                {
                    currentVisualsState = VisualsState::Start;
                }
            }
            else
            {
                if( currentVisualsState != VisualsState::Outro &&
                    currentVisualsState != VisualsState::End && 
                    currentVisualsState != VisualsState::Clear)
                {
                    currentVisualsState = VisualsState::Outro;
                }
            }
            
        }
        // [tdbe] Set move state
        {
            if(forceOn || avgGrabInput > .66f && grabLeft.currentState > .33f && grabRight.currentState > .33f)
            {
                if( currentVisualsState != VisualsState::Start && 
                    currentVisualsState != VisualsState::Intro &&
                    currentMovementState != MovementState::Start &&
                    currentMovementState != MovementState::Update)
                {
                    currentMovementState = MovementState::Start;
                }
            }
            else
            {
                if (currentMovementState != MovementState::Clear)
                {
                    currentMovementState = MovementState::End;
                }
            }
        }
    }
    else
    {
        if( currentVisualsState != VisualsState::Clear &&
            currentVisualsState != VisualsState::Outro &&
            currentVisualsState != VisualsState::End )
        {
            currentVisualsState = VisualsState::Outro;
        }
        if(currentMovementState != MovementState::Clear)
        {
            currentMovementState = MovementState::End;
        }
    }

    {
        HandleMovementState(deltaTime, inputData, grabLeft, grabRight, avgGrabInput, teleportRequest, inputHaptics);
        HandleVisualsState(deltaTime, inputData, grabLeft, grabRight, avgGrabInput, teleportRequest.state, inputHaptics);
    }

    // [tdbe] Flagging so other interactions scripts can know they shouldn't e.g. grab stuff 
    // while in inappropriate states.
    if (currentMovementState == MovementState::Update)
    {
        playerObject.SetPlayerState(PlayerStates::LocomotionState, true);
    }
    else
    {
        playerObject.SetPlayerState(PlayerStates::LocomotionState, false);
    }
}   

LocomotionBehaviour::~LocomotionBehaviour(){
    
}
