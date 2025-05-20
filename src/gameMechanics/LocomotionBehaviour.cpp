#include "LocomotionBehaviour.h"
#include <stdio.h>
//#include <glm/gtx/matrix_decompose.hpp>

LocomotionBehaviour::LocomotionBehaviour(PlayerObject& playerObject, GameObject& floorGrid, GameObject& ceilingGrid,
    GameObject& icosphereSkybox, Material& handsMaterial, float movementSpeedScaler, 
    float movementAccelerationPow, float rotationSpeedScaler) : playerObject(playerObject), floorGrid(floorGrid), 
    ceilingGrid(ceilingGrid), icosphereSkybox(icosphereSkybox), handsMaterial(handsMaterial)
{
    this->movementSpeedScaler = movementSpeedScaler;
    this->movementAccelerationPow = movementAccelerationPow;
    this->rotationSpeedScaler = rotationSpeedScaler;
    origFloorGrid = floorGrid.worldMatrix;
    origSkybox = icosphereSkybox.worldMatrix;
    moveStateData = {};

    floorGrid.isVisible = false;
    ceilingGrid.isVisible = false;
    floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
    ceilingGrid.material->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
    handsMaterial.dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
    icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
}

void LocomotionBehaviour::HandleVisualsState(const float deltaTime, const Inputspace::InputData &inputData, 
    XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, 
    Inputspace::InputHaptics& inputHaptics)
{
    if (currentVisualsState != VisualsState::Clear)
    {
        // [tdbe] Display the hands above everything else
        { 
            if (currentVisualsState == VisualsState::Start)
            {
                handsMaterial.dynamicUniformData.perMaterialVertexFlags.w = 0.001f;
            }
            else if (currentVisualsState == VisualsState::End)
            {
                handsMaterial.dynamicUniformData.perMaterialVertexFlags.w = 1.0f;
            }
        }

        // [tdbe] Display the grids above the scene geometry (it will have a depth "hole" in the middle to see the world).
        {
            if (currentVisualsState == VisualsState::Start)
            {
                floorGrid.isVisible = true;
                ceilingGrid.isVisible = true;
                floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.w = 0.002f;
                ceilingGrid.material->dynamicUniformData.perMaterialFragmentFlags.w = 0.002f;
            }
            else if (currentVisualsState == VisualsState::End)
            {
                floorGrid.isVisible = false;
                ceilingGrid.isVisible = false;
                floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
                ceilingGrid.material->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
            }
        }

        // [tdbe] Display the sky above the scene geometry (it will have a depth "hole" in the middle to see the world).
        {
            if (currentVisualsState == VisualsState::Start)
            {
                icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.w = 0.003f;
            }
            else if (currentVisualsState == VisualsState::End)
            {
                icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.w = 1.0f;
            }
        }

        /*
        // [tdbe] Example of how to stick a plane to your forehead / bridge of your nose. 
        glm::vec3 objectSpaceForwardArmLength = glm::vec3(0.4f, 0.0f, 0.0f);
        //glm::vec3 objectSpaceForwardArmLength = glm::vec3(0.4f, -0.033f, 0.1f);// centered on preview window's eye
        glm::vec3 groundNormal = { 0.0f, 1.0f, 0.0f };
        glm::mat4 viewRotationMatrix = inputData.eyePoseMatrixes[0];
        tempChaperone.worldMatrix = viewRotationMatrix;
        tempChaperone.worldMatrix = glm::scale(tempChaperone.worldMatrix, { 1.4f, 1.4f, 1.4f });
        tempChaperone.worldMatrix = glm::rotate(tempChaperone.worldMatrix, glm::radians(90.0f), groundNormal);
        tempChaperone.worldMatrix = glm::translate(tempChaperone.worldMatrix, objectSpaceForwardArmLength);
        tempChaperone.worldMatrix = playerObject.worldRoot->worldMatrix * tempChaperone.worldMatrix;
        */

        floorGrid.worldMatrix = playerObject.worldRoot->worldMatrix * origFloorGrid;
        ceilingGrid.worldMatrix = floorGrid.worldMatrix;
        if (currentVisualsState != VisualsState::End)
        {
          floorGrid.worldMatrix = glm::scale(floorGrid.worldMatrix, { 2.66f, 2.66f, 2.66f });
          ceilingGrid.worldMatrix = glm::scale(ceilingGrid.worldMatrix, { 2.66f, 2.66f, 2.66f });
        }

        icosphereSkybox.worldMatrix = playerObject.worldRoot->worldMatrix * origSkybox;
        floorGrid.worldMatrix[3].y = 0;
        icosphereSkybox.worldMatrix[3].y = 0;
        ceilingGrid.worldMatrix[3].y = 3;
    }

    float chaperoneRingRadius = 0.39f;// [tdbe] distance along the radius of the screen at which to draw a boundary (a circle)
    float chaperoneRingLowestBounceRadius = 0.27f;// [tdbe] during animations, shrink the circle to a minimum of this radius distance
    float chaperoneRingHighestRadius = 1.0f;// [tdbe] during animations, enlarge the circle to a maximum of this radius distance
    float chaperoneRingLerpSpeed = 3.0f;
    if(currentVisualsState == VisualsState::Start)
    {
        float chapLerpv = icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x;

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

        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;

        float ringWobbleStability =
            util::remapInterval(glm::abs(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 1, 0);
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;

        float chaperoneFader =
            util::remapInterval(util::clampf01(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 0, 1);
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::Start (anim: {%f})\n", chapLerpv);
        if (chapLerpv == chaperoneRingLowestBounceRadius)
            currentVisualsState = VisualsState::Intro;
    }
    else if (currentVisualsState == VisualsState::Intro)
    {
        // do some intro tunel-vision chaperone animation
        float chapLerpv = icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x;
        chapLerpv += deltaTime * chaperoneRingLerpSpeed;
        if (chapLerpv > chaperoneRingRadius)
            chapLerpv = chaperoneRingRadius;
        
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;

        float ringWobbleStability =
            util::remapInterval(glm::abs(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 1, 0);
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;

        float chaperoneFader =
            util::remapInterval(util::clampf01(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 0, 1);
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::Intro (anim: {%f})\n", chapLerpv);
        if (chapLerpv == chaperoneRingRadius)
            currentVisualsState = VisualsState::Update;
    }
    else if(currentVisualsState == VisualsState::Update)
    {
        // [tdbe] do some looping tunel-vision chaperone animation or just wait: actually I do it in the shader instead
        //printf("[LocomotionBehaviour][log] VisualsState::Update\n");
    }
    else if(currentVisualsState == VisualsState::Outro)
    {
        // do some outro chaperone animation
        float chapLerpv = icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x;
        chapLerpv += deltaTime * chaperoneRingLerpSpeed * 11.0f;
        if (chapLerpv > chaperoneRingHighestRadius)
            chapLerpv = chaperoneRingHighestRadius;

        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.x = chapLerpv;

        float ringWobbleStability =
            util::remapInterval(glm::abs(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 1, 0);
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.y = ringWobbleStability;

        float chaperoneFader =
            util::remapInterval(util::clampf01(chapLerpv - chaperoneRingRadius), 0, 1 - chaperoneRingRadius, 0, 1);
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::Outro (anim: {%f})\n", chapLerpv);
        if (chapLerpv == chaperoneRingHighestRadius)
            currentVisualsState = VisualsState::End;
    }
    else if (currentVisualsState == VisualsState::End)
    {
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.33f, XR_MIN_HAPTIC_DURATION, 0.33f);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.33f, XR_MIN_HAPTIC_DURATION, 0.33f);

        // [tdbe] clear any data here
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.x = chaperoneRingHighestRadius;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.x = chaperoneRingHighestRadius;

        float ringWobbleStability = chaperoneRingHighestRadius;
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.y = chaperoneRingHighestRadius;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.y = chaperoneRingHighestRadius;

        float chaperoneFader =
            chaperoneRingHighestRadius;
        icosphereSkybox.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;
        floorGrid.material->dynamicUniformData.perMaterialFragmentFlags.z = chaperoneFader;

        printf("[LocomotionBehaviour][log] VisualsState::End\n");
        currentVisualsState = VisualsState::Clear;
    }
    else if(currentVisualsState == VisualsState::Clear)
    {

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

        printf("[LocomotionBehaviour][log] MovementState::Start\n");
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
        //printf("[LocomotionBehaviour][log] moveSpeed: {%f}, moveVec: {%f}{%f}{%f}, deltaTime: {%f}, moveStateData.moveDir: {%f}{%f}{%f}\n", moveSpeed, moveVec.x, moveVec.y, moveVec.z, deltaTime, moveStateData.moveDir.x, moveStateData.moveDir.y, moveStateData.moveDir.z);
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
        //printf("[LocomotionBehaviour][log] rotation angle rad: %f\n", radang);
        playerObject.worldRoot->worldMatrix = glm::rotate(playerObject.worldRoot->worldMatrix, radang, norm);

        moveStateData.prevPosLeft = moveStateData.posLeft;
        moveStateData.prevPosRight = moveStateData.posRight;
        moveStateData.prevPosMiddle = moveStateData.posMiddle;
        moveStateData.prevDirLeftRight = moveStateData.dirLeftRight;
        //printf("[LocomotionBehaviour][log] MovementState::Update\n");
    }
    else if(currentMovementState == MovementState::End)
    {
        // [tdbe] clear any data here
        
        // [tdbe] request haptics
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::LEFT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);
        inputHaptics.RequestHapticFeedback(Inputspace::ControllerEnum::RIGHT, 0.25, XR_MIN_HAPTIC_DURATION, 0.25);

        printf("[LocomotionBehaviour][log] MovementState::End\n");
        currentMovementState = MovementState::Clear;
    }

    if(currentMovementState == MovementState::Clear)
    {
    }
}

void LocomotionBehaviour::Update(const float deltaTime, const float gameTime, 
    const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics)
{
    bool forceOn = false;
    XrActionStateFloat grabLeft = inputData.grabState[(int)Inputspace::ControllerEnum::LEFT];
    XrActionStateFloat grabRight = inputData.grabState[(int)Inputspace::ControllerEnum::RIGHT];
    float avgGrabInput = .5f*(grabLeft.currentState + grabRight.currentState);
    if (forceOn || grabLeft.isActive && grabLeft.isActive)
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
