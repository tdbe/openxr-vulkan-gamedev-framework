#pragma once
#include <stdio.h>
#include "../Utils/Util.h"
#include "InputTesterBehaviour.h"

using namespace Behaviours;

InputTesterBehaviour::InputTesterBehaviour()
{
}

void InputTesterBehaviour::Mechanic_GrabState(const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics)
{
    for(size_t i = 0; i<inputData.grabState.size(); i++)
    {
        if (inputData.grabState[i].isActive == XR_TRUE) 
        {
            if (inputData.grabState[i].currentState > 0.05f) 
            {
                printf("[InputTesterBehaviour][log] mechanic_GrabState: Grabbing! grabStateArr[i{%d}].currentState: %f\n", 
                        (int)i, inputData.grabState[i].currentState); 
                
                inputHaptics.RequestHapticFeedback((Inputspace::ControllerEnum)i);
                // [tdbe] or: inputHaptics.RequestHapticFeedback((Inputspace::ControllerEnum)i, 0.3, XR_MIN_HAPTIC_DURATION, XR_FREQUENCY_UNSPECIFIED);
            }
        }
    }
}

void InputTesterBehaviour::Update(const float deltaTime, const float gameTime, 
    const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics)
{
    Mechanic_GrabState(inputData, inputHaptics);

    for(size_t i = 0; i<inputData.selectClickState.size(); i++)
    {
        if(inputData.selectClickState[i].isActive && inputData.selectClickState[i].currentState)
        {
            printf("[InputTesterBehaviour][log] inputData.selectClickState[i{%d}].currentState: %d\n", (int)i, inputData.selectClickState[i].currentState);
        }

        if(inputData.menuClickState[i].isActive && inputData.menuClickState[i].currentState)
        {
            printf("[InputTesterBehaviour][log] inputData.menuClickState[i{%d}].currentState: %d\n", (int)i, inputData.menuClickState[i].currentState);
        }

        if(inputData.thumbStickState[i].isActive && 
            (std::abs(inputData.thumbStickState[i].currentState.x)>0.05f || std::abs(inputData.thumbStickState[i].currentState.y)>0.05f))
        {
            printf("[InputTesterBehaviour][log] inputData.thumbStickState[i{%d}].currentState: x{%f}, y{%f}\n", (int)i, inputData.thumbStickState[i].currentState.x, inputData.thumbStickState[i].currentState.y);
        }
        /*
        if(inputData.triggerState[i].isActive && 
            inputData.triggerState[i].currentState>0.05f)
        {
            printf("[InputTesterBehaviour][log] inputData.triggerState[i{%d}].currentState: %f\n", i, inputData.triggerState[i].currentState);
        }

        if (inputData.triggerClickState[i].isActive && inputData.triggerClickState[i].currentState)
        {
            util::DebugLog("[InputTesterBehaviour][log] inputData.triggerClickState[i" + util::ToString(i) + 
                            "].currentState: "+ util::ToString(inputData.triggerClickState[i].currentState));
        }
        */
        if (inputData.aClickState[i].isActive && inputData.aClickState[i].currentState)
        {
            util::DebugLog("[InputTesterBehaviour][log] inputData.aClickState[i" + util::ToString(i) +
                           "].currentState: " + util::ToString(inputData.aClickState[i].currentState));
        }

        if (inputData.bClickState[i].isActive && inputData.bClickState[i].currentState)
        {
            util::DebugLog("[InputTesterBehaviour][log] inputData.bClickState[i" + util::ToString(i) +
                           "].currentState: " + util::ToString(inputData.bClickState[i].currentState));
        }

        if (inputData.xClickState[i].isActive && inputData.xClickState[i].currentState)
        {
            util::DebugLog("[InputTesterBehaviour][log] inputData.xClickState[i" + util::ToString(i) +
                           "].currentState: " + util::ToString(inputData.xClickState[i].currentState));
        }

        if (inputData.yClickState[i].isActive && inputData.yClickState[i].currentState)
        {
            util::DebugLog("[InputTesterBehaviour][log] inputData.yClickState[i" + util::ToString(i) +
                           "].currentState: " + util::ToString(inputData.yClickState[i].currentState));
        }
    }
}

InputTesterBehaviour::~InputTesterBehaviour()
{
}