#pragma once
#include "../../Utils/Util.h"
#include "Light.h"
#include "Transform.h"
#include "../Entities/GameEntityObject.h"

using namespace Game;

Light::Light(GameDataId::ID id, GameDataId::ID owner) : GameComponent(id, owner)
{
}

GameEntity* Light::GetOwner() const
{
    std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
    GameEntity* found = nullptr;
    for (int i = 0; i < ownerIDs.size(); i++)
    {
        found = GameData::Instance().GetEntity(ownerIDs[i]);
        break;
    }
    return found;
}

void Light::NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage)
{
    util::DebugLog("[Component][Light]\t clearing this item: " + this->id.PrintGlobalUID());
    GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
    shaderMatrix = glm::mat4(1.0f);
    colorAndIntensity = glm::vec4(1.0f);
    isVisible = true;// [tdbe] don't worry, items with empty versions don't get rendered
}

void Light::NotifyItemVersionChanged()
{
    GameComponent::NotifyItemVersionChanged();
}

glm::mat4 Light::GetWorldMatrix()
{
    if (cachedTransformComponent == nullptr)
    {
        GameDataId::ID ownerId = GetOwnerIDs().front();
        auto owningEntity = static_cast<GameEntityObject*>(GameData::Instance().GetEntity(ownerId));
        auto transformId = owningEntity->GetComponentIDsByTypeIndex<Transform>().front();// [tdbe] very aggressive programming but you should always have an owner and a transform, and there are exceptions thrown upstream 
        cachedTransformComponent = static_cast<Transform*>(GameData::Instance().GetComponent(transformId));
    }
    return cachedTransformComponent->GetWorldMatrix();
}

void Light::SetRenderProperties(int lightType)
{
    this->lightType = lightType;
    SetShaderProperties();
}

void Light::SetRenderProperties(glm::vec4 colorAndIntensity)
{
    this->colorAndIntensity = colorAndIntensity;
    SetShaderProperties();
}

void Light::SetRenderProperties(glm::vec3 color)
{
    this->colorAndIntensity = glm::vec4(color, colorAndIntensity.w);
    SetShaderProperties();
}

void Light::SetRenderProperties(glm::vec4 colorAndIntensity, float radiusMultiplier)
{
    this->radiusMultiplier = radiusMultiplier;
    this->colorAndIntensity = colorAndIntensity;
    SetShaderProperties();
}

void Light::SetRenderProperties(glm::vec4 colorAndIntensity, int lightType)
{
    this->lightType = lightType;
    this->colorAndIntensity = colorAndIntensity;
    SetShaderProperties();
}

void Light::SetRenderProperties(glm::vec4 colorAndIntensity, float radiusMultiplier, int lightType)
{
    this->radiusMultiplier = radiusMultiplier;
    this->lightType = lightType;
    this->colorAndIntensity = colorAndIntensity;
    SetShaderProperties();
}

void Light::SetRenderProperties(float radiusMultiplier, int lightType)
{
    this->radiusMultiplier = radiusMultiplier;
    this->lightType = lightType;
    SetShaderProperties();
}

void Light::SetRenderProperties(float radiusMultiplier)
{
    this->radiusMultiplier = radiusMultiplier;
    SetShaderProperties();
}

glm::mat4 Light::GetShaderMatrix()
{
    SetShaderProperties();// [tdbe] doing this just to update with an eventual latest Transform Matrix
    return shaderMatrix;
}

void Light::SetVisible(bool visible)
{
    isVisible = visible;
    SetShaderProperties();
}

bool Light::IsVisible()
{
    return id.version != GameComponent::FREE && isVisible;
}

void Light::SetShaderProperties()
{
    glm::mat4 worldMatrix = GetWorldMatrix();
    glm::vec4 mainVec = glm::vec4(1.0f);
    glm::vec4 shapeVec0 = glm::vec4(1.0f);
    glm::vec4 shapeVec1 = glm::vec4(1.0f);
    glm::vec3 scale = glm::vec3(glm::length(glm::vec3(worldMatrix[0])), glm::length(glm::vec3(worldMatrix[1])), glm::length(glm::vec3(worldMatrix[2])));

    /// [tdbe] Types of lights based on the Scale. 
    /// You can get most of it done with just the tube and directional lights. But TODO: add missing light types.
    
    /// directional light.
    if (lightType == LightTypes::LIGHT_TYPE_DIRECTIONAL)
    {
        mainVec = worldMatrix[3];
        shapeVec0.w = lightType;
        shapeVec1.w = 1.0f;
    }
    /// point light.
    if (lightType == LightTypes::LIGHT_TYPE_POINT)
    {
        mainVec = worldMatrix[3];
        shapeVec0.w = lightType;
        shapeVec1.w = 1.0f;
    }
    /// sphere light. (scale X is radius)
    else if (lightType == LightTypes::LIGHT_TYPE_SPHERE)
    {
        mainVec = glm::vec4(worldMatrix[3].x, worldMatrix[3].y, worldMatrix[3].z, scale.x);
        shapeVec0.w = lightType;
        shapeVec1.w = 1.0f;
    }
    /// tube light. (scale Z is length, scale X and Y are the thickness (the same))
    else if (lightType == LightTypes::LIGHT_TYPE_TUBE || lightType == LightTypes::LIGHT_TYPE_TENTACLE)
    {
        float radiusScaleY = scale.y * radiusMultiplier;
        float lengthScaleZ = 1 / 2.0f;// [tdbe] the actual scale.z is baked in the worldMatrix
        shapeVec0 = worldMatrix * glm::vec4(0.0f, 0.0f, lengthScaleZ, 1.0f);
        shapeVec1 = worldMatrix * glm::vec4(0.0f, 0.0f, -lengthScaleZ, 1.0f);

        mainVec = glm::vec4(worldMatrix[3].x, worldMatrix[3].y, worldMatrix[3].z, radiusScaleY);
        shapeVec0.w = lightType;
        shapeVec1.w = scale.z;           
    }
    /// cube light.
    else if (lightType == LightTypes::LIGHT_TYPE_CUBE)
    {
        // std::exception("[Light] Cube Light NotImplementedException");
        mainVec.w = 1.0f;
        shapeVec0.w = lightType;
        shapeVec1.w = 1.0f;
    }
    /// 2D quad area light (scale Y is flat (ignored))
    else if (lightType == LightTypes::LIGHT_TYPE_QUAD)
    {
        // std::exception("[Light] Quad Light NotImplementedException");
        mainVec.w = 1.0f;
        shapeVec0.w = lightType;
        shapeVec1.w = 1.0f;
    }
    /// disc light. (scale Y is flat (ignored))
    else if (lightType == LightTypes::LIGHT_TYPE_DISC)
    {
        // std::exception("[Light] Disc Light NotImplementedException");
        mainVec.w = 1.0f;
        shapeVec0.w = lightType;
        shapeVec1.w = 1.0f;
    }

    bool validDimensions = mainVec.w > 0.0f || shapeVec0.w > 0.0f || shapeVec1.w > 0.0f;
    shaderMatrix[0] = glm::vec4(colorAndIntensity.x, colorAndIntensity.y, colorAndIntensity.z, 
                                isVisible && validDimensions ? colorAndIntensity.w : 0.0f);
    shaderMatrix[1] = mainVec;
    shaderMatrix[2] = shapeVec0;
    shaderMatrix[3] = shapeVec1;
    /*
    util::DebugLog("##Light [IsVisible: " + util::ToString(IsVisible()) + "][MyId: " + id.PrintGlobalUID() + "][Owners: " +
                   util::ToString(GetOwnerIDs().size()) +
                   "][Owner0: " + GetOwnerIDs().front().PrintGlobalUID() +
                   "; name: " + static_cast<GameEntityObject*>(GameData::Instance().GetEntity(GetOwnerIDs().front()))->GetName() +
                   "] scale: " + util::ToString(scale) +
                   " -- matrix: " + util::ToString(worldMatrix) + "; shaderMatrix: "+util::ToString(shaderMatrix));
    */
}

Light::~Light()
{
}