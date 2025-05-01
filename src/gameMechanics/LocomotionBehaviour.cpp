#include "LocomotionBehaviour.h"
#include <stdio.h>

LocomotionBehaviour::LocomotionBehaviour(PlayerObject& playerObject, float movementSpeedScaler_, float movementAccelerationPow_, float rotationSpeedScaler_):
                                        playerObject(playerObject)
{
    movementSpeedScaler = movementSpeedScaler_;
    movementAccelerationPow = movementAccelerationPow_;
    rotationSpeedScaler = rotationSpeedScaler_;
    moveStateData = {};
}

void LocomotionBehaviour::HandleVisualsState(const float deltaTime, const Inputspace::InputData &inputData, XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, Inputspace::InputHaptics &inputHaptics){
    
    if(currentVisualsState == VisualsState::Start){
        
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.15f, XR_MIN_HAPTIC_DURATION, 0.25f);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.15f, XR_MIN_HAPTIC_DURATION, 0.25f);

        printf("\n[LocomotionBehaviour][log] VisualsState::Start");
        currentVisualsState = VisualsState::Update;
    }
    else if(currentVisualsState == VisualsState::Update){
        // use a tunel vision animation 
        printf("\n[LocomotionBehaviour][log] VisualsState::Update");
        currentVisualsState = VisualsState::End;
    }
    else if(currentVisualsState == VisualsState::End){
        // [tdbe] clear any data here
        printf("\n[LocomotionBehaviour][log] VisualsState::End");
  
    }
    else if(currentVisualsState == VisualsState::StartBackwards){

        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.15f, XR_MIN_HAPTIC_DURATION, 0.25f);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.15f, XR_MIN_HAPTIC_DURATION, 0.25f);

        printf("\n[LocomotionBehaviour][log] VisualsState::StartBackwards");
        currentVisualsState = VisualsState::UpdateBackwards;
    }
    else if(currentVisualsState == VisualsState::UpdateBackwards){
        printf("\n[LocomotionBehaviour][log] VisualsState::UpdateBackwards");
        currentVisualsState = VisualsState::EndBackwards;
    }
    else if(currentVisualsState == VisualsState::EndBackwards){
        // [tdbe] clear any data here
        printf("\n[LocomotionBehaviour][log] VisualsState::EndBackwards");
        currentVisualsState = VisualsState::Clear;
    }
    else if(currentVisualsState == VisualsState::Clear){
    }
    
}

void LocomotionBehaviour::HandleMovementState(const float deltaTime, const Inputspace::InputData &inputData, XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, Inputspace::InputHaptics &inputHaptics){
    
    if(currentMovementState == MovementState::Start){
        moveStateData.prevPosLeft = glm::vec3(( inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT])[3]);//inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::LEFT].position;
        moveStateData.prevPosRight = glm::vec3(( inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT])[3]);//inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::RIGHT].position;
        moveStateData.prevPosMiddle = 0.5f*(moveStateData.prevPosLeft + moveStateData.prevPosRight);
        moveStateData.prevPosMiddle.y = 0;

        moveStateData.prevDirLeftRight = moveStateData.prevPosRight - moveStateData.prevPosLeft;
        moveStateData.prevDirLeftRight.y = 0;
        moveStateData.prevDirLeftRight = moveStateData.prevDirLeftRight / (float)moveStateData.prevDirLeftRight.length();

        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);

        printf("\n[LocomotionBehaviour][log] MovementState::Start");
        currentMovementState = MovementState::Update;
    }
    else if(currentMovementState == MovementState::Update){
        moveStateData.posLeft = glm::vec3(( inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT])[3]);//inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::LEFT].position;
        moveStateData.posRight = glm::vec3(( inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT])[3]);//inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::RIGHT].position;
        moveStateData.posMiddle = 0.5f*(moveStateData.posLeft + moveStateData.posRight);
        moveStateData.posMiddle.y = 0;
        moveStateData.moveDir = moveStateData.posMiddle - moveStateData.prevPosMiddle;
        moveStateData.moveInputSpeed = (float)moveStateData.moveDir.length();
        moveStateData.moveDir = moveStateData.moveDir / moveStateData.moveInputSpeed;

        // [tdbe] TODO: 
        //          Perhaps add an inertia to be able to do flick moves :)
        //          And if you have a larger world: A mode with a bit of an upward leap, like in that Lucid Trips VR game.
        
        // [tdbe] move player along moveDir, with a speed scaled by hand movement speed.
        float moveSpeed = avgGrabInput * movementSpeedScaler * glm::pow(moveStateData.moveInputSpeed, movementAccelerationPow);
        glm::vec3 moveVec = -100.0f * moveStateData.moveDir * moveSpeed * deltaTime;
        //printf("\n[LocomotionBehaviour][log] moveSpeed: {%f}, moveVec: {%f}{%f}{%f}", moveSpeed, moveVec.x, moveVec.y, moveVec.z);
        playerObject.head->worldMatrix = glm::translate(playerObject.head->worldMatrix, moveVec);
        playerObject.handLeft->worldMatrix = glm::translate(playerObject.handLeft->worldMatrix, -moveVec);
        moveVec.x = -moveVec.x;// because right hand is a flipped left hand model
        playerObject.handRight->worldMatrix = glm::translate(playerObject.handRight->worldMatrix, -moveVec);

        // [tdbe] rotate player based on line between the hands
        moveStateData.dirLeftRight = moveStateData.posRight - moveStateData.posLeft;
        moveStateData.dirLeftRight.y = 0;
        moveStateData.dirLeftRight = moveStateData.dirLeftRight / (float)moveStateData.dirLeftRight.length();
        glm::vec3 norm = glm::vec3(0,1,0);
        float radang = util::vectorAngleAroundNormal(moveStateData.dirLeftRight,moveStateData.prevDirLeftRight, norm);
        radang = 100.0f * avgGrabInput * rotationSpeedScaler * radang * deltaTime;
        //printf("\n[LocomotionBehaviour][log] rotation angle rad: %f", radang);
        glm::vec3 camPos = glm::vec3(playerObject.head->worldMatrix[3]);
        playerObject.head->worldMatrix = glm::rotate(playerObject.head->worldMatrix, radang, norm);

        moveStateData.prevPosLeft = moveStateData.posLeft;
        moveStateData.prevPosRight = moveStateData.posRight;
        moveStateData.prevPosMiddle = moveStateData.posMiddle;
        moveStateData.prevDirLeftRight = moveStateData.dirLeftRight;
        //printf("\n[LocomotionBehaviour][log] MovementState::Update");
    }
    else if(currentMovementState == MovementState::End){
        // [tdbe] clear any data here
        
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);

        printf("\n[LocomotionBehaviour][log] MovementState::End");
        currentMovementState = MovementState::Clear;
    }
    if(currentMovementState == MovementState::Clear){
    }
}

void LocomotionBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics){
    XrActionStateFloat grabLeft = inputData.grabState[(int)Inputspace::ControllerEnum::LEFT];
    XrActionStateFloat grabRight = inputData.grabState[(int)Inputspace::ControllerEnum::RIGHT];
    float avgGrabInput = .5f*(grabLeft.currentState + grabRight.currentState);
    if(grabLeft.isActive && grabLeft.isActive)
    {
        // [tdbe] Change visuals state
        {
            if(avgGrabInput>.5f && grabLeft.currentState > .25f && grabRight.currentState > .25f){
                if(currentVisualsState != VisualsState::Start &&
                    currentVisualsState != VisualsState::Update &&
                    currentVisualsState != VisualsState::End)
                {
                    currentVisualsState = VisualsState::Start;
                }
            }
            else{
                if(currentVisualsState != VisualsState::StartBackwards &&
                    currentVisualsState != VisualsState::UpdateBackwards && 
                    currentVisualsState != VisualsState::EndBackwards && 
                    currentVisualsState != VisualsState::Clear)
                {
                    currentVisualsState = VisualsState::StartBackwards;
                }
            }
            
        }
        // [tdbe] Change move state
        //        Handle move mechanics only after specific visual animations finish
        {
            if(avgGrabInput>.95){
                if(currentVisualsState != VisualsState::Start && 
                    currentVisualsState != VisualsState::Update &&
                    currentMovementState != MovementState::Update)
                {
                    currentMovementState = MovementState::Start;
                }
            }
            else{
                if(currentMovementState != MovementState::Clear){
                    currentMovementState = MovementState::End;
                }
            }
        }
    
    
    }
    else{
        if(currentVisualsState != VisualsState::Clear &&
            currentVisualsState != VisualsState::End &&
            currentVisualsState != VisualsState::UpdateBackwards )
            {
            currentVisualsState = VisualsState::StartBackwards;
        }
        if(currentMovementState != MovementState::Clear){
            currentMovementState = MovementState::End;
        }
    }

    // [tdbe] Scene Panning and Rotating style.
    {
    HandleVisualsState(deltaTime, inputData, grabLeft, grabRight, avgGrabInput, inputHaptics);
    HandleMovementState(deltaTime, inputData, grabLeft, grabRight, avgGrabInput, inputHaptics);
    }

    // [tdbe] Flagging so other interactions scripts can know they shouldn't e.g. grab stuff 
    //        while in inappropriate states.
    if(currentVisualsState == VisualsState::Clear && currentMovementState == MovementState::Clear){
        playerObject.playerActiveStates[(int)PlayerStates::LocomotionState] = true;
    }
    else{
        playerObject.playerActiveStates[(int)PlayerStates::LocomotionState] = false;
    }
}   

LocomotionBehaviour::~LocomotionBehaviour(){
    
}
