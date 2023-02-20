#include "WorldObjectsMiscBehaviour.h"


WorldObjectsMiscBehaviour::WorldObjectsMiscBehaviour(Model& bikeModel): bikeModel(bikeModel)
{
}

void WorldObjectsMiscBehaviour::mechanic_bikeModel(const float gameTime){
    bikeModel.worldMatrix =
        glm::rotate(glm::translate(glm::mat4(1.0f), { 0.5f, 0.0f, -4.5f }), gameTime * 0.2f, { 0.0f, 1.0f, 0.0f });
}

void WorldObjectsMiscBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics, 
                            const glm::mat4 &inverseCameraMatrix){
    mechanic_bikeModel(gameTime);
}

WorldObjectsMiscBehaviour::~WorldObjectsMiscBehaviour(){
}