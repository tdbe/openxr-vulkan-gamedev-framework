#include "HandsBehaviour.h"

HandsBehaviour::HandsBehaviour(PlayerObject& playerObject):
                playerObject(playerObject)
{
}

void HandsBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics){
    playerObject.handLeft->worldMatrix = playerObject.head->worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT];
    playerObject.handLeft->worldMatrix = glm::translate(playerObject.handLeft->worldMatrix, { 0.0f, 0.0f, -0.015f });
    playerObject.handRight->worldMatrix = playerObject.head->worldMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT];
    playerObject.handRight->worldMatrix = glm::scale(playerObject.handRight->worldMatrix, { -1.0f, 1.0f, 1.0f });
    playerObject.handRight->worldMatrix = glm::translate(playerObject.handRight->worldMatrix, { 0.0f, 0.0f, -0.015f });
}   

HandsBehaviour::~HandsBehaviour(){
    // [tdbe] do not delete/release the constructor (Model) references for obvious reasons
}
