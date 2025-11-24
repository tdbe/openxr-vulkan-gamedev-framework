#pragma once
#include "../Utils/Util.h"
#include "HandsBehaviour.h"
#include "../GameData/Components/Transform.h"
#include "../GameData/GameData.h"
#include "../GameData/PlayerObject.h"

using namespace Game;
using namespace Behaviours;

HandsBehaviour::HandsBehaviour(PlayerObject& playerObject,
                               GameDataId::ID sudaBeam01,
                               GameDataId::ID handLight01,
                               GameDataId::ID sudaBeam02,
                               GameDataId::ID handLight02 
                               ): playerObject(playerObject)
{
    this->sudaBeam01 = sudaBeam01;
    this->handLight01 = handLight01;
    this->sudaBeam02 = sudaBeam02;
    this->handLight02 = handLight02;
    GameEntityObject* sudaBeam01Geo = GameData::Instance().gameEntityObjects->GetItem(sudaBeam01);
    GameEntityObject* handLight01Geo = GameData::Instance().gameEntityObjects->GetItem(handLight01);
    GameEntityObject* sudaBeam02Geo = GameData::Instance().gameEntityObjects->GetItem(sudaBeam02);
    GameEntityObject* handLight02Geo = GameData::Instance().gameEntityObjects->GetItem(handLight02);
    sudaBeam01Geo->SetEnabled(false);
    handLight01Geo->SetEnabled(false);
    sudaBeam02Geo->SetEnabled(false);
    handLight02Geo->SetEnabled(false);
}

void HandsBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics)
{
    Transform* worldRootTrans = GameData::Instance().gameEntityObjects->GetItem(playerObject.worldRootId)->GetComponentByTypeIndex<Transform>();
    GameEntityObject* handLeftGeo = GameData::Instance().gameVFXObjects->GetItem(playerObject.handLeftId);
    Transform* handLeftTrans = handLeftGeo->GetComponentByTypeIndex<Transform>();
    GameEntityObject* handRightGeo = GameData::Instance().gameVFXObjects->GetItem(playerObject.handRightId);
    Transform* handRightTrans = handRightGeo->GetComponentByTypeIndex<Transform>();
    glm::mat4 worldMatrix = worldRootTrans->GetWorldMatrix();
    glm::mat4 handLeftMatr = worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT];
    glm::mat4 handRightMatr = worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT];

    handLeftMatr = glm::translate(handLeftMatr, { -0.04f, -0.04f, -0.015f });
    handLeftMatr = glm::scale(handLeftMatr, { 0.925f, 0.925f, 0.925f });
    handLeftTrans->SetWorldMatrix(handLeftMatr);

    handRightMatr = glm::translate(handRightMatr, { 0.04f, -0.04f, -0.015f });
    handRightMatr = glm::scale(handRightMatr, { -1.0f, 1.0f, 1.0f });
    handRightMatr = glm::scale(handRightMatr, { 0.925f, 0.925f, 0.925f });
    handRightTrans->SetWorldMatrix(handRightMatr);

    bool forceInventoryEquipped = false;
    XrActionStateFloat equipInputLeft = inputData.grabState[(int)Inputspace::ControllerEnum::LEFT];
    XrActionStateFloat equipInputRight = inputData.grabState[(int)Inputspace::ControllerEnum::RIGHT];
    // [tdbe] here I go though too much trouble to turn an analog input into a tap signal, and also consider the opposite hand as a negative input.
    const float minAnalogInput = 0.33f;
    const float maxAnalogInput = 0.66f;
    bool leftEquippedInputRequestedLow = (!equipInputLeft.isActive || 
                                           equipInputLeft.isActive && equipInputLeft.currentState < minAnalogInput) &&
                                         (!equipInputRight.isActive || 
                                          equipInputRight.isActive && equipInputRight.currentState < minAnalogInput);
    bool rightEquippedInputRequestedLow = (!equipInputRight.isActive || 
                                            equipInputRight.isActive && equipInputRight.currentState < minAnalogInput) &&
                                          (!equipInputLeft.isActive || 
                                           equipInputLeft.isActive && equipInputLeft.currentState < minAnalogInput);

    if (leftEquippedInputRequestedLow)
        inventoryLeftInputCleared = true;
    if (rightEquippedInputRequestedLow)
        inventoryRightInputCleared = true;

    bool leftEquippedInputRequestedHigh = equipInputLeft.isActive && 
                                 equipInputLeft.currentState > maxAnalogInput && 
                                 (!equipInputRight.isActive || equipInputRight.currentState < minAnalogInput) &&
                                 !playerObject.IsPlayerInState(PlayerStates::ChaperoneState) &&
                                 inventoryLeftInputCleared;
    bool rightEquippedInputRequestedHigh =
                                  equipInputRight.isActive && 
                                  equipInputRight.currentState > maxAnalogInput && 
                                  (!equipInputLeft.isActive || equipInputLeft.currentState < minAnalogInput) &&
                                  !playerObject.IsPlayerInState(PlayerStates::ChaperoneState) &&
                                  inventoryRightInputCleared;

    if (leftEquippedInputRequestedHigh)
        inventoryLeftInputClearedAndHigh = true;
    if (rightEquippedInputRequestedHigh)
        inventoryRightInputClearedAndHigh = true;

    if (playerObject.IsPlayerInState(PlayerStates::ChaperoneState))
    {
        inventoryLeftInputCleared = false;
        inventoryLeftInputClearedAndHigh = false;
        inventoryRightInputCleared = false;
        inventoryRightInputClearedAndHigh = false;
    }

    bool leftAnalogTapDetected = false;
    bool rightAnalogTapDetected = false;
    if (inventoryLeftInputClearedAndHigh && leftEquippedInputRequestedLow)
        leftAnalogTapDetected = true;
    if (inventoryRightInputClearedAndHigh && rightEquippedInputRequestedLow)
        rightAnalogTapDetected = true;

    // [tdbe] TODO: parenting (which requires a system with threads for updating matrixes)
    GameEntityObject* sudaBeam01Geo = GameData::Instance().gameEntityObjects->GetItem(sudaBeam01);
    GameEntityObject* handLight01Geo = GameData::Instance().gameEntityObjects->GetItem(handLight01);
    GameEntityObject* sudaBeam02Geo = GameData::Instance().gameEntityObjects->GetItem(sudaBeam02);
    GameEntityObject* handLight02Geo = GameData::Instance().gameEntityObjects->GetItem(handLight02);
    if ((forceInventoryEquipped || leftAnalogTapDetected) && !sudaBeam01Geo->IsEnabled())
    {
        inventoryLeftInputCleared = false;
        inventoryLeftInputClearedAndHigh = false;
        sudaBeam01Geo->SetEnabled(true);
        handLight01Geo->SetEnabled(true);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.5f);
    }
    else if (leftAnalogTapDetected && sudaBeam01Geo->IsEnabled())
    {
        inventoryLeftInputCleared = false;
        inventoryLeftInputClearedAndHigh = false;
        sudaBeam01Geo->SetEnabled(false);
        handLight01Geo->SetEnabled(false);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.33f);
    }

    if ((forceInventoryEquipped || rightAnalogTapDetected) && !sudaBeam02Geo->IsEnabled())
    {
        inventoryRightInputCleared = false;
        inventoryRightInputClearedAndHigh = false;
        sudaBeam02Geo->SetEnabled(true);
        handLight02Geo->SetEnabled(true);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.5f);
    }
    else if (rightAnalogTapDetected && sudaBeam02Geo->IsEnabled())
    {
        inventoryRightInputCleared = false;
        inventoryRightInputClearedAndHigh = false;
        sudaBeam02Geo->SetEnabled(false);
        handLight02Geo->SetEnabled(false);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.33f);
    }

    if (sudaBeam01Geo->IsEnabled())
    {
        Transform* sudaBeam01Trans = sudaBeam01Geo->GetComponentByTypeIndex<Transform>();
        Transform* handLight01Trans = handLight01Geo->GetComponentByTypeIndex<Transform>();

        glm::mat4 sudaBeam01Matr =
            worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT];
        sudaBeam01Matr = glm::translate(sudaBeam01Matr, { 0.00f, -0.08f, -0.460f });
        sudaBeam01Matr = glm::translate(sudaBeam01Matr, { -0.005f, 0.338f, 0.0f });
        sudaBeam01Matr = glm::rotate(sudaBeam01Matr, glm::radians(30.0f), { 1.0f, 0.0f, 0.0f });
        auto dirMod = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), { 0.0f, 0.0f, 1.0f });
        sudaBeam01Matr = glm::rotate(sudaBeam01Matr, glm::radians(155.0f), glm::vec3(dirMod * glm::vec4( 0.0f, 0.0f, 1.0f, 0.0f )));
        sudaBeam01Trans->SetWorldMatrix(sudaBeam01Matr);

        glm::mat4 handLight01Matr =
            worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT];
        handLight01Matr = glm::translate(handLight01Matr, { 0.01f, -0.055f, -0.525f });
        handLight01Matr = glm::translate(handLight01Matr, { -0.015f, 0.35f, 0.0f });
        handLight01Matr = glm::rotate(handLight01Matr, glm::radians(30.0f), { 1.0f, 0.0f, 0.0f });
        handLight01Matr = glm::scale(handLight01Matr, glm::vec3(0.033f, 0.033f, 1.0f));// 7.5f
        handLight01Trans->SetWorldMatrix(handLight01Matr);
    }

    if (sudaBeam02Geo->IsEnabled())
    {
        Transform* sudaBeam02Trans = sudaBeam02Geo->GetComponentByTypeIndex<Transform>();
        Transform* handLight02Trans = handLight02Geo->GetComponentByTypeIndex<Transform>();

        glm::mat4 sudaBeam02Matr =
            worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT];
        sudaBeam02Matr = glm::translate(sudaBeam02Matr, { 0.00f, -0.08f, -0.460f });
        sudaBeam02Matr = glm::translate(sudaBeam02Matr, { 0.005f, 0.338f, 0.0f });
        sudaBeam02Matr = glm::rotate(sudaBeam02Matr, glm::radians(30.0f), { 1.0f, 0.0f, 0.0f });
        auto dirMod = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), { 0.0f, 0.0f, 1.0f });
        sudaBeam02Matr = glm::rotate(sudaBeam02Matr, glm::radians(45.0f), glm::vec3(dirMod * glm::vec4( 0.0f, 0.0f, 1.0f, 0.0f )));
        sudaBeam02Trans->SetWorldMatrix(sudaBeam02Matr);

        glm::mat4 handLight02Matr =
            worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT];
        handLight02Matr = glm::translate(handLight02Matr, { -0.01f, -0.055f, -0.525f });
        handLight02Matr = glm::translate(handLight02Matr, { 0.015f, 0.35f, 0.0f });
        handLight02Matr = glm::rotate(handLight02Matr, glm::radians(30.0f), { 1.0f, 0.0f, 0.0f });
        handLight02Matr = glm::scale(handLight02Matr, glm::vec3(0.033f, 0.033f, 1.0f));// 7.5f
        handLight02Trans->SetWorldMatrix(handLight02Matr);
    }
}   

HandsBehaviour::~HandsBehaviour()
{
    // [tdbe] do not delete/release the constructor (Model) references for obvious reasons
}
