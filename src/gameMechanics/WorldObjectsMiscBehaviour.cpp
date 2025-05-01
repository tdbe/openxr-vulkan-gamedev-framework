#include "WorldObjectsMiscBehaviour.h"


WorldObjectsMiscBehaviour::WorldObjectsMiscBehaviour(GameObject& bikeObject, Material& logoMat): bikeObject(bikeObject), logoMat(logoMat)
{
}

void WorldObjectsMiscBehaviour::mechanic_bikeObject(const float gameTime){
    float radang = gameTime * 0.2f;
    bikeObject.worldMatrix =
        glm::rotate(glm::translate(glm::mat4(1.0f), { 0.5f, 0.0f, -4.5f }), radang, { 0.0f, 1.0f, 0.0f });
}

void WorldObjectsMiscBehaviour::rotateMatColor(const float gameTime){
    
    logoMat.dynamicUniformData.colorMultiplier = glm::vec4(
        glm::max(0.2f, glm::sin((float)glm::pow(gameTime,1.2))), 
        glm::max(0.2f, glm::sin((float)glm::pow(gameTime*0.3f,1.2))), 
        glm::max(0.2f, glm::sin((float)glm::pow(gameTime*0.6f,1.2))), 
        1.0f
    );
}

void WorldObjectsMiscBehaviour::Update(const float deltaTime, const float gameTime, 
                            const Inputspace::InputData &inputData,
                            Inputspace::InputHaptics &inputHaptics
                            ){
    mechanic_bikeObject(gameTime);
    rotateMatColor(gameTime);
}

WorldObjectsMiscBehaviour::~WorldObjectsMiscBehaviour(){
}