#include "InputTesterBehaviour.h"

#include <stdio.h>

InputTesterBehaviour::InputTesterBehaviour()
{
}

void InputTesterBehaviour::Mechanic_GrabState(const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics){
    for(size_t i = 0; i<inputData.grabState.size(); i++){
        if (inputData.grabState[i].isActive == XR_TRUE) {
            if (inputData.grabState[i].currentState > 0.05f) {
                printf("\n[InputTesterBehaviour][log] mechanic_GrabState: Grabbing! grabStateArr[i{%d}].currentState: %f", 
                        (int)i, inputData.grabState[i].currentState); 
                
                inputHaptics.RequestHapticFeedback((Inputspace::ControllerEnum)i);
                // [tdbe] or: inputHaptics.RequestHapticFeedback((Inputspace::ControllerEnum)i, 0.3, XR_MIN_HAPTIC_DURATION, XR_FREQUENCY_UNSPECIFIED);
            }
        }
    }
}

void InputTesterBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics, 
                            const glm::mat4 &inverseCameraMatrix){
    Mechanic_GrabState(inputData, inputHaptics);

    for(size_t i = 0; i<inputData.selectClickState.size(); i++){
        if(inputData.selectClickState[i].isActive && inputData.selectClickState[i].currentState){
            printf("\n[InputTesterBehaviour][log] inputData.selectClickState[i{%d}].currentState: %d", i, inputData.selectClickState[i].currentState);
        }

        if(inputData.menuClickState[i].isActive && inputData.menuClickState[i].currentState){
            printf("\n[InputTesterBehaviour][log] inputData.menuClickState[i{%d}].currentState: %d", i, inputData.menuClickState[i].currentState);
        }

        if(inputData.thumbStickState[i].isActive && 
            (std::abs(inputData.thumbStickState[i].currentState.x)>0.05f || std::abs(inputData.thumbStickState[i].currentState.y)>0.05f)){
            printf("\n[InputTesterBehaviour][log] inputData.thumbStickState[i{%d}].currentState: x{%f}, y{%f}", i, inputData.thumbStickState[i].currentState.x, inputData.thumbStickState[i].currentState.y);
        }

        //if(inputData.triggerState[i].isActive && 
        //    inputData.triggerState[i].currentState>0.05f){
        //    printf("\n[InputTesterBehaviour][log] inputData.triggerState[i{%d}].currentState: %f", i, inputData.triggerState[i].currentState);
        //}
    }
}

InputTesterBehaviour::~InputTesterBehaviour(){
}