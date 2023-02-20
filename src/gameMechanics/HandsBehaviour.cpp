#include "HandsBehaviour.h"

HandsBehaviour::HandsBehaviour(Model &handModelLeft, Model &handModelRight):
                handModelLeft(handModelLeft), handModelRight(handModelRight)
{
}

void HandsBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics,  
                            const glm::mat4 &inverseCameraMatrix){
    handModelLeft.worldMatrix = inverseCameraMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT];
    handModelLeft.worldMatrix = glm::translate(handModelLeft.worldMatrix, { 0.0f, 0.0f, -0.015f });
    handModelRight.worldMatrix = inverseCameraMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT];
    handModelRight.worldMatrix = glm::scale(handModelRight.worldMatrix, { -1.0f, 1.0f, 1.0f });
    handModelRight.worldMatrix = glm::translate(handModelRight.worldMatrix, { 0.0f, 0.0f, -0.015f });
}   

HandsBehaviour::~HandsBehaviour(){
    // [tdbe] do not delete/release the constructor (Model) references for obvious reasons
}
