#include "LocomotionBehaviour.h"
#include <stdio.h>

LocomotionBehaviour::LocomotionBehaviour(PlayerObject& playerObject,
    GameObject& holePlaneTempChaperone, float movementSpeedScaler_, float movementAccelerationPow_, 
    float rotationSpeedScaler_) : playerObject(playerObject), holePlaneTempChaperone(holePlaneTempChaperone)
{
    movementSpeedScaler = movementSpeedScaler_;
    movementAccelerationPow = movementAccelerationPow_;
    rotationSpeedScaler = rotationSpeedScaler_;
    moveStateData = {};
}

void LocomotionBehaviour::HandleVisualsState(const float deltaTime, const Inputspace::InputData &inputData, 
    XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, 
    Inputspace::InputHaptics& inputHaptics)
{
    // [tdbe] Stick a plane to your forehead / bridge of your nose. 
    // (This is not the right way to do a graphics overlay but I didn't do the "post processing" layer yet.)
    glm::vec3 objectSpaceForwardArmLength = glm::vec3(0.5f, 0.0f, 0.0f);
    //glm::vec3 objectSpaceForwardArmLength = glm::vec3(0.3f, -0.033f, 0.1f);// centered on preview
    glm::vec3 groundNormal = { 0.0f, 1.0f, 0.0f };
    glm::mat4 viewRotationMatrix = inputData.eyePoseMatrixes[0];
    holePlaneTempChaperone.worldMatrix = viewRotationMatrix;
    holePlaneTempChaperone.worldMatrix = glm::rotate(holePlaneTempChaperone.worldMatrix, glm::radians(90.0f), groundNormal);
    holePlaneTempChaperone.worldMatrix = glm::translate(holePlaneTempChaperone.worldMatrix, objectSpaceForwardArmLength);
    holePlaneTempChaperone.worldMatrix = playerObject.worldRoot->worldMatrix * holePlaneTempChaperone.worldMatrix;

    if(currentVisualsState == VisualsState::Start)
    {
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.5f);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.5f, XR_MIN_HAPTIC_DURATION, 0.5f);

        // do some intro tunel-vision chaperone animation
        holePlaneTempChaperone.isVisible = true;

        printf("\n[LocomotionBehaviour][log] VisualsState::Start");
        currentVisualsState = VisualsState::Intro;
    }
    else if (currentVisualsState == VisualsState::Intro)
    {

      // do some intro tunel-vision chaperone animation

      printf("\n[LocomotionBehaviour][log] VisualsState::Intro");
      currentVisualsState = VisualsState::Update;
    }
    else if(currentVisualsState == VisualsState::Update)
    {
        // do some looping tunel-vision chaperone animation or just wait
        printf("\n[LocomotionBehaviour][log] VisualsState::Update");
    }
    else if(currentVisualsState == VisualsState::Outro)
    {
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.33f, XR_MIN_HAPTIC_DURATION, 0.33f);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.33f, XR_MIN_HAPTIC_DURATION, 0.33f);
        
        // do some outro chaperone animation

        printf("\n[LocomotionBehaviour][log] VisualsState::Outro");
        currentVisualsState = VisualsState::End;
    }
    else if (currentVisualsState == VisualsState::End)
    {
      // [tdbe] clear any data here

      printf("\n[LocomotionBehaviour][log] VisualsState::End");
      currentVisualsState = VisualsState::Clear;
    }
    else if(currentVisualsState == VisualsState::Clear)
    {
      holePlaneTempChaperone.isVisible = false;
    }
}

void LocomotionBehaviour::HandleMovementState(const float deltaTime, const Inputspace::InputData &inputData, 
    XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, 
    Inputspace::InputHaptics &inputHaptics)
{
    
    if(currentMovementState == MovementState::Start)
    {
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
    else if(currentMovementState == MovementState::Update)
    {
        moveStateData.posLeft = glm::vec3(( inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT])[3]);//inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::LEFT].position;
        moveStateData.posRight = glm::vec3(( inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT])[3]);//inputData.controllerGripPoses[(int)Inputspace::ControllerEnum::RIGHT].position;
        moveStateData.posMiddle = 0.5f*(moveStateData.posLeft + moveStateData.posRight);
        moveStateData.posMiddle.y = 0;
        moveStateData.moveDir = moveStateData.posMiddle - moveStateData.prevPosMiddle;
        moveStateData.moveInputSpeed = (float)moveStateData.moveDir.length();
        moveStateData.moveDir = moveStateData.moveDir / moveStateData.moveInputSpeed;

        // [tdbe] TODO: 
        //  Perhaps add an inertia to be able to do flick moves :)
        //  And if you have a larger world: A mode with a bit of an upward leap, like in that Lucid Trips VR game.
        
        // [tdbe] move player along moveDir, with a speed scaled by hand movement speed.
        float moveSpeed = avgGrabInput * movementSpeedScaler * glm::pow(moveStateData.moveInputSpeed, movementAccelerationPow);
        glm::vec3 moveVec = -100.0f * moveStateData.moveDir * moveSpeed * deltaTime;
        //printf("\n[LocomotionBehaviour][log] moveSpeed: {%f}, moveVec: {%f}{%f}{%f}, deltaTime: {%f}, moveStateData.moveDir: {%f}{%f}{%f}", moveSpeed, moveVec.x, moveVec.y, moveVec.z, deltaTime, moveStateData.moveDir.x, moveStateData.moveDir.y, moveStateData.moveDir.z);
        playerObject.worldRoot->worldMatrix = glm::translate(playerObject.worldRoot->worldMatrix, moveVec);
        playerObject.handLeft->worldMatrix = glm::translate(playerObject.handLeft->worldMatrix, -moveVec);
        moveVec.x = -moveVec.x;// because right hand is a flipped left hand model
        playerObject.handRight->worldMatrix = glm::translate(playerObject.handRight->worldMatrix, -moveVec);

        // [tdbe] rotate player based on line between the hands
        float distBetweenHands = glm::distance(moveStateData.posRight, moveStateData.posLeft);
        moveStateData.dirLeftRight = moveStateData.posRight - moveStateData.posLeft;
        moveStateData.dirLeftRight.y = 0;
        moveStateData.dirLeftRight = moveStateData.dirLeftRight / (float)moveStateData.dirLeftRight.length();
        glm::vec3 norm = glm::vec3(0,1,0);
        float radang = util::vectorAngleAroundNormal(moveStateData.dirLeftRight, moveStateData.prevDirLeftRight, norm);
        radang = distBetweenHands * 150.0f * avgGrabInput * rotationSpeedScaler * radang * deltaTime;
        //printf("\n[LocomotionBehaviour][log] rotation angle rad: %f", radang);
        playerObject.worldRoot->worldMatrix = glm::rotate(playerObject.worldRoot->worldMatrix, radang, norm);

        moveStateData.prevPosLeft = moveStateData.posLeft;
        moveStateData.prevPosRight = moveStateData.posRight;
        moveStateData.prevPosMiddle = moveStateData.posMiddle;
        moveStateData.prevDirLeftRight = moveStateData.dirLeftRight;
        printf("\n[LocomotionBehaviour][log] MovementState::Update");
    }
    else if(currentMovementState == MovementState::End)
    {
        // [tdbe] clear any data here
        
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);

        printf("\n[LocomotionBehaviour][log] MovementState::End");
        currentMovementState = MovementState::Clear;
    }

    if(currentMovementState == MovementState::Clear)
    {
    }
}

void LocomotionBehaviour::Update(const float deltaTime, const float gameTime, 
    const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics)
{
    XrActionStateFloat grabLeft = inputData.grabState[(int)Inputspace::ControllerEnum::LEFT];
    XrActionStateFloat grabRight = inputData.grabState[(int)Inputspace::ControllerEnum::RIGHT];
    float avgGrabInput = .5f*(grabLeft.currentState + grabRight.currentState);
    if(grabLeft.isActive && grabLeft.isActive)
    {
        // [tdbe] Set visuals state
        {
            if(avgGrabInput > .5f && grabLeft.currentState > .25f && grabRight.currentState > .25f)
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
            if(avgGrabInput > .95)
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
                if(currentMovementState != MovementState::Clear)
                {
                    currentMovementState = MovementState::End;
                }
            }
        }
    }
    else{
        if( currentVisualsState != VisualsState::Clear &&
            currentVisualsState != VisualsState::Outro &&
            currentVisualsState != VisualsState::End )
        {
            currentVisualsState = VisualsState::Outro;
        }
        if(currentMovementState != MovementState::Clear){
            currentMovementState = MovementState::End;
        }
    }

    {
    HandleMovementState(deltaTime, inputData, grabLeft, grabRight, avgGrabInput, inputHaptics);
    HandleVisualsState(deltaTime, inputData, grabLeft, grabRight, avgGrabInput, inputHaptics);
    }

    // [tdbe] Flagging so other interactions scripts can know they shouldn't e.g. grab stuff 
    // while in inappropriate states.
    if (currentMovementState == MovementState::Update)
    {
        playerObject.playerActiveStates[(int)PlayerStates::LocomotionState] = true;
    }
    else
    {
        playerObject.playerActiveStates[(int)PlayerStates::LocomotionState] = false;
    }
}   

LocomotionBehaviour::~LocomotionBehaviour(){
    
}
