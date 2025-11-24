#pragma once
#include "../Utils/Util.h"
#include "../GameData/Entities/GameEntityObject.h"
#include "../GameData/Components/Material.h"
#include "../GameData/Components/Transform.h"
#include "WorldObjectsMiscBehaviour.h"
#include "../GameData/GameData.h"

using namespace Game;
using namespace Behaviours;

WorldObjectsMiscBehaviour::WorldObjectsMiscBehaviour(GameDataId::ID bikeObject,
                                                     GameDataId::ID bikeLightObject,
                                                     GameDataId::ID textMat,
                                                     GameDataId::ID logoMat,
                                                     GameDataId::ID handsMat)
{
    this->bikeObject = bikeObject;
    this->bikeLightObject = bikeLightObject;
    this->textMat = textMat;
    this->logoMat = logoMat;
    this->handsMat = handsMat;
}

void WorldObjectsMiscBehaviour::Mechanic_bikeObject(const float gameTime)
{
    float radang = gameTime * 0.2f;
    Transform* bikeTrans = GameData::Instance()
                               .gameEntityObjects->GetItem(bikeObject)
                               ->GetComponentByTypeIndex<Transform>();
    glm::mat4 bikeMatr = glm::mat4(1.0f);
    bikeMatr[3] = bikeTrans->GetWorldMatrix()[3];
    bikeMatr = glm::rotate(bikeMatr, radang, { 0.0f, 1.0f, 0.0f });
    bikeTrans->SetWorldMatrix(bikeMatr);
    
    bikeMatr[3].y += 1.0f;
    bikeMatr = glm::scale(bikeMatr, glm::vec3(8.448f, 8.448f, 3.25f));
    GameData::Instance().gameEntityObjects->GetItem(bikeLightObject)
                               ->GetComponentByTypeIndex<Transform>()
                               ->SetWorldMatrix(bikeMatr);
    
}

glm::vec4 WorldObjectsMiscBehaviour::RotateMatColor(const float gameTime, const float minBrightness)
{
    float pow = 1.2f;
    //float minBrightness = 0.33f;
    float piOffset = 2.0f * util::PI / 3.0f;
    float speed = gameTime * 0.75f;
    return
            glm::vec4(
                util::remapInterval(2.0f * glm::sin(       piOffset + speed), 0.0f, 2.0f, minBrightness, 1.0f),
                util::remapInterval(2.0f * glm::sin(2.0f * piOffset + speed), 0.0f, 2.0f, minBrightness, 1.0f),
                util::remapInterval(2.0f * glm::sin(                  speed), 0.0f, 2.0f, minBrightness, 1.0f),
                1.0f
            );
}

glm::vec4 WorldObjectsMiscBehaviour::RotateMatColorUnrealistic(const float gameTime, const float minBrightness)
{
    float pow = 1.2f;
    //float minBrightness = -0.666f;
    float piOffset = 2.0f * util::PI / 3.0f;
    float speed = gameTime * 0.5f;
    return
        glm::vec4(
            glm::max(minBrightness, glm::sin(       piOffset + speed)),
            glm::max(minBrightness, glm::sin(2.0f * piOffset + speed)),
            glm::max(minBrightness, glm::sin(                  speed)),
            1.0f);
}

void WorldObjectsMiscBehaviour::Update(const float deltaTime, const float gameTime, 
    const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics)
{
    Mechanic_bikeObject(gameTime);
    GameData::Instance().materialComponents->GetItem(textMat)->dynamicUniformData.colorMultiplier = 
        RotateMatColor(gameTime, 0.33f);
        // RotateMatColorUnrealistic(gameTime);
    GameData::Instance().materialComponents->GetItem(logoMat)->dynamicUniformData.colorMultiplier = 
        RotateMatColor(gameTime, 0.95f);
        // RotateMatColorUnrealistic(gameTime);
    GameData::Instance().materialComponents->GetItem(handsMat)->dynamicUniformData.colorMultiplier =
        RotateMatColor(gameTime, 0.33f);
        //RotateMatColorUnrealistic(gameTime);

    auto id01 = GameData::Instance().namedGameObjectIDs["tentacle01"];
    for (int i = 1; i < 7; i++)
    {
        // float rotationStep = i * 45.0f - 30.0f;
        float rotationStep = i * 60.0f - 30.0f + 10.0f;
        float customAngle = 0.0f;
        glm::vec3 customPos = glm::vec3(0.0f);
        if (i == 2) // blue
        {
            customAngle = 7.25f;
            customPos = glm::vec3(0.0f, -0.45f, 0.0f);
        }
        else if (i == 3) // magenta
        {
            customAngle = -62.0f;
            customPos = glm::vec3(0.0f, 3.3f, -1.7f);
        }
        else if (i == 4) // red
        {
            customAngle = -2.5f;
            customPos = glm::vec3(0.0f, 0.15f, 0.0f);
        }
        else if (i == 5) // yellow
        {
            customAngle = 2.5f;                        // 10.0f;
            customPos = glm::vec3(0.0f, -0.15f, 0.0f); //-0.75f
        }
        else if (i == 6) // green
        {
            customAngle = 2.5f;
            customPos = glm::vec3(0.0f, -0.15f, 0.0f);
        }
        GameData::Instance().gameEntityObjects->items[id01.index + i - 1]
            ->GetComponentByTypeIndex<Transform>()
            ->SetWorldMatrix(glm::scale(
                glm::rotate(
                    glm::translate(
                        glm::rotate(glm::translate(glm::rotate(glm::translate(glm::mat4(1.0), { 3.625f, 2.66f, -10.125f }),
                                                               glm::radians(rotationStep), { 0.0f, 1.0f, 0.0f }),
                                                   { 2.75f, -0.25f, 2.75f }),
                                    glm::radians(45.0f), { 0.0f, 1.0f, 0.0f }),
                        customPos),
                    glm::radians(customAngle), { 1.0f, 0.0f, 0.0f }),
                { 0.033f, 0.033f, 7.75f }));
    }
}

WorldObjectsMiscBehaviour::~WorldObjectsMiscBehaviour()
{
}