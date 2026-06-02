#pragma once
#include "../Utils/Util.h"
#include "../GameData/GameData.h"

#include "../GameData/Components/CMaterial.h"
#include "../GameData/Components/CLight.h"
#include "../GameData/Components/CParent.h"

/// [tdbe] No actual scripting layer, just a less-holy place where we can configure our e.g. game world items setup, scenes, object positions, colors etc.
namespace Scripting
{
	struct GameScripting
	{

	};

    /// [tdbe] configure our e.g. game world items, object positions, colors etc.
	bool SceneSetup(GameData& gameData)
    {
        util::DebugLog("\n[Scripting][SceneSetup]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        util::DebugLog("[Scripting][SceneSetup]\t 🎥 Scripted / scene objects setup.");
        // -------- [tdbe] edit any material properties here. --------
#pragma region Materials
        // TODO: move these material property scripting blocks into something more compact.
        // at least do a material2.CopyFrom(material1)

        CMaterial* skyMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("skyMaterialComp"));
        skyMaterial->vertShaderName = "shaders/Sky.vert.spv";
        skyMaterial->fragShaderName = "shaders/Sky.frag.spv";
        skyMaterial->pipelineData.blendEnable = VK_FALSE;
        skyMaterial->pipelineData.depthTestEnable = VK_FALSE;
        skyMaterial->pipelineData.depthWriteEnable = VK_TRUE;
        skyMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
        skyMaterial->dynamicUniformData.colorMultiplier = glm::vec4(0.7f, 0.9f, 1.0f, 1.0f);
        skyMaterial->dynamicUniformData.brdfData = glm::vec4(0.00125f, 0.005, 1.0f, 0.0f);
        skyMaterial->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] Todo: sky index of refraction? :)

        CMaterial* diffuseMetalishMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("diffuseMetalishMaterialComp"));
        diffuseMetalishMaterial->vertShaderName = "shaders/Diffuse.vert.spv";
        diffuseMetalishMaterial->fragShaderName = "shaders/Diffuse.frag.spv";
        diffuseMetalishMaterial->pipelineData.blendEnable = VK_FALSE;
        diffuseMetalishMaterial->pipelineData.depthTestEnable = VK_TRUE;
        diffuseMetalishMaterial->pipelineData.depthWriteEnable = VK_TRUE;
        diffuseMetalishMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        diffuseMetalishMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
        diffuseMetalishMaterial->dynamicUniformData.brdfData = glm::vec4(0.758f, 0.650346f, 1.0f, 0.25f);
        diffuseMetalishMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        CMaterial* diffuseStoneMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("diffuseStoneMaterialComp"));
        diffuseStoneMaterial->vertShaderName = "shaders/Diffuse.vert.spv";
        diffuseStoneMaterial->fragShaderName = "shaders/Diffuse.frag.spv";
        diffuseStoneMaterial->pipelineData.blendEnable = VK_FALSE;
        diffuseStoneMaterial->pipelineData.depthTestEnable = VK_TRUE;
        diffuseStoneMaterial->pipelineData.depthWriteEnable = VK_TRUE;
        diffuseStoneMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        diffuseStoneMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
        diffuseStoneMaterial->dynamicUniformData.brdfData = glm::vec4(0.08f, 0.1750346f, 1.0f, 0.0f);
        diffuseStoneMaterial->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 0.0f); // [tdbe] gold paint index of refraction

        CMaterial* textMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("textMaterialComp"));
        textMaterial->vertShaderName = "shaders/Diffuse.vert.spv";
        textMaterial->fragShaderName = "shaders/Diffuse.frag.spv";
        textMaterial->pipelineData.blendEnable = VK_FALSE;
        textMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        textMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
        textMaterial->dynamicUniformData.brdfData = glm::vec4(0.358f, 0.1750346f, 1.0f, 0.0f);
        textMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction


        CMaterial* logoMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("logoMaterialComp"));
        logoMaterial->vertShaderName = "shaders/Diffuse.vert.spv";
        logoMaterial->fragShaderName = "shaders/Diffuse.frag.spv";
        logoMaterial->pipelineData.blendEnable = VK_FALSE;
        logoMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        logoMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
        logoMaterial->dynamicUniformData.brdfData = glm::vec4(0.358f, 0.1750346f, 1.0f, 0.0f);
        logoMaterial->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        // [tdbe] ^ notice all the (entities with these) materials above all have the same pipeline, they'll be batched because they're also
        // reserved in relative order in the <see cref="GameData"/> materials pool.
        // reserved in relative order in the <see cref="GameData"/> materials pool.

        CMaterial* groundMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("groundMaterialComp"));
        groundMaterial->vertShaderName = "shaders/Ground.vert.spv";
        groundMaterial->fragShaderName = "shaders/Ground.frag.spv";
        groundMaterial->pipelineData.blendEnable = VK_FALSE;
        groundMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        // groundMaterial->dynamicUniformData.colorMultiplier = glm::vec4(0.1f, 0.08f, 0.12f, 1.0f);
        groundMaterial->dynamicUniformData.colorMultiplier = glm::vec4(0.14f, 0.09f, 0.12f, 1.0f);
        groundMaterial->dynamicUniformData.brdfData = glm::vec4(0.08f, 0.15346f, 1.0f, 0.0f);//0.2750346f
        groundMaterial->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        CMaterial* lightMaterial = // [tdbe] represents/displays the visible "bulb" or "fixture" of a light component
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("lightMaterialComp"));
        lightMaterial->vertShaderName = "shaders/Light.vert.spv";
        lightMaterial->fragShaderName = "shaders/Light.frag.spv";
        lightMaterial->pipelineData.blendEnable = VK_FALSE;
        lightMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        lightMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        lightMaterial->dynamicUniformData.brdfData = glm::vec4(0.0358f, 0.346f, 1.0f, 0.0f);
        lightMaterial->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        CMaterial* tentacleMaterial = 
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("tentacleLightMaterialComp"));
        tentacleMaterial->vertShaderName = "shaders/LightTentacle.vert.spv";
        tentacleMaterial->fragShaderName = "shaders/LightTentacle.frag.spv";
        tentacleMaterial->pipelineData.blendEnable = VK_FALSE;
        tentacleMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        tentacleMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        tentacleMaterial->dynamicUniformData.brdfData = glm::vec4(0.0358f, 0.4346f, 1.0f, 0.0f);
        tentacleMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        CMaterial* squidMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("squidMaterialComp"));
        squidMaterial->vertShaderName = "shaders/TripShader.vert.spv";
        squidMaterial->fragShaderName = "shaders/TripShader.frag.spv";
        squidMaterial->pipelineData.blendEnable = VK_FALSE;
        squidMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        squidMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        squidMaterial->dynamicUniformData.brdfData = glm::vec4(0.0358f, 0.50346f, 1.0f, 0.66f);
        squidMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.5f); // [tdbe] gold paint index of refraction

        CMaterial* eyeMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("diffuseEyesMaterialComp"));
        eyeMaterial->vertShaderName = "shaders/EyeShader.vert.spv";
        eyeMaterial->fragShaderName = "shaders/EyeShader.frag.spv";
        eyeMaterial->pipelineData.blendEnable = VK_FALSE;
        eyeMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        eyeMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        eyeMaterial->dynamicUniformData.brdfData = glm::vec4(0.0358f, 0.50346f, 1.0f, 1.0f);
        eyeMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.5f); // [tdbe] gold paint index of refraction
        
        CMaterial* handsMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("handsMaterialComp"));
        handsMaterial->vertShaderName = "shaders/Hands.vert.spv";
        handsMaterial->fragShaderName = "shaders/Hands.frag.spv";
        handsMaterial->pipelineData.blendEnable = VK_FALSE;
        handsMaterial->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        handsMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
        handsMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
        handsMaterial->dynamicUniformData.brdfData = glm::vec4(0.50f, 0.88f, 1.0f, 0.0f);
        handsMaterial->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        CMaterial* diffuseTripIcosphereMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("diffuseTripIcosphereMaterialComp"));
        // [tdbe] the only thing that makes an instanced material instanced, is the instanceCount > 1.
        // (and the vertex shader consuming gl_InstanceIndex)
        diffuseTripIcosphereMaterial->instanceCount = 104u;
        diffuseTripIcosphereMaterial->firstInstance = 1u; 
        diffuseTripIcosphereMaterial->vertShaderName = "shaders/TripShader.vert.spv";
        diffuseTripIcosphereMaterial->fragShaderName = "shaders/TripShader.frag.spv";
        diffuseTripIcosphereMaterial->pipelineData.blendEnable = VK_FALSE;
        diffuseTripIcosphereMaterial->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        diffuseTripIcosphereMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
        diffuseTripIcosphereMaterial->dynamicUniformData.colorMultiplier = glm::vec4(1.0f);
        diffuseTripIcosphereMaterial->dynamicUniformData.brdfData = glm::vec4(0.358f, 0.150f, 1.0f, 1.0f);
        diffuseTripIcosphereMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction

        // [tdbe] NOTE: the order in which the materials exist in the data pool matters. (and not just for batching)
        // E.g. opaque rendered before transparent, then the vfx materials are last.
        // this is already set up in <see cref="GameData::LoadMaterials()"/>.

        CMaterial* glassMaterialB = gameData.mainEntityWorld->materialComponents->GetItem(
            gameData.namedMaterialComponentIDs.left.at("glassTransparentBackfaceMaterialComp"));
        glassMaterialB->vertShaderName = "shaders/DiffuseTransparent.vert.spv";
        glassMaterialB->fragShaderName = "shaders/DiffuseTransparent.frag.spv";
        glassMaterialB->pipelineData.blendEnable = VK_TRUE;
        glassMaterialB->pipelineData.depthTestEnable = VK_TRUE;
        glassMaterialB->pipelineData.depthWriteEnable = VK_TRUE;
        glassMaterialB->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        glassMaterialB->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        glassMaterialB->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        glassMaterialB->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        glassMaterialB->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        glassMaterialB->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        glassMaterialB->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        glassMaterialB->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
        // [tdbe] Note: the renderer only reads the unioform data (non-pipeline data) from the first material assigned
        // to an entity (this backface is the 2nd).
        glassMaterialB->SetVisible(true);

        CMaterial* glassMaterialF = gameData.mainEntityWorld->materialComponents->GetItem(
            gameData.namedMaterialComponentIDs.left.at("glassTransparentFrontfaceMaterialComp"));
        glassMaterialF->vertShaderName = "shaders/DiffuseTransparent.vert.spv";
        glassMaterialF->fragShaderName = "shaders/DiffuseTransparent.frag.spv";
        glassMaterialF->pipelineData.blendEnable = VK_TRUE;
        glassMaterialF->pipelineData.depthTestEnable = VK_TRUE;
        glassMaterialF->pipelineData.depthWriteEnable = VK_TRUE;
        glassMaterialF->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        glassMaterialF->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        glassMaterialF->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        glassMaterialF->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        glassMaterialF->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        glassMaterialF->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        glassMaterialF->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        glassMaterialF->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        glassMaterialF->dynamicUniformData.colorMultiplier = glm::vec4(0.9f, 1.0f, 0.95f, 0.215f);
        glassMaterialF->dynamicUniformData.brdfData = glm::vec4(0.55848f, 0.075046f, 1.0f, 0.0625f);
        glassMaterialF->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction
        glassMaterialF->SetVisible(true);

        CMaterial* bikeMaterialB = 
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("bikeTransparentBackfaceMaterialComp"));
        bikeMaterialB->vertShaderName = "shaders/DiffuseTransparent.vert.spv";
        bikeMaterialB->fragShaderName = "shaders/DiffuseTransparent.frag.spv";
        bikeMaterialB->pipelineData.blendEnable = VK_TRUE;
        bikeMaterialB->pipelineData.depthTestEnable = VK_TRUE;
        bikeMaterialB->pipelineData.depthWriteEnable = VK_TRUE;
        bikeMaterialB->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        bikeMaterialB->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        bikeMaterialB->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        bikeMaterialB->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        bikeMaterialB->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        bikeMaterialB->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        bikeMaterialB->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        bikeMaterialB->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
        // [tdbe] Note: the renderer only reads the unioform data (non-pipeline data) from the first material assigned to an entity (this backface is the 2nd).
        bikeMaterialB->SetVisible(true);

        CMaterial* bikeMaterialF =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("bikeTransparentFrontfaceMaterialComp"));
        bikeMaterialF->vertShaderName = "shaders/DiffuseTransparent.vert.spv";
        bikeMaterialF->fragShaderName = "shaders/DiffuseTransparent.frag.spv";
        bikeMaterialF->pipelineData.blendEnable = VK_TRUE;
        bikeMaterialF->pipelineData.depthTestEnable = VK_TRUE;
        bikeMaterialF->pipelineData.depthWriteEnable = VK_TRUE;
        bikeMaterialF->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        bikeMaterialF->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        bikeMaterialF->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        // bikeMaterialF->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
        // bikeMaterialF->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
        bikeMaterialF->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        bikeMaterialF->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        bikeMaterialF->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        bikeMaterialF->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        bikeMaterialF->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        bikeMaterialF->dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 0.0f, 0.1f, 0.66f);// (1.0f, 0.0f, 0.1f, 0.76f)
        bikeMaterialF->dynamicUniformData.brdfData = glm::vec4(0.55848f, 0.175046f, 1.0f, 0.0625f);//0.175046f//0.4050346f
        bikeMaterialF->dynamicUniformData.ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction
        bikeMaterialF->SetVisible(true);

        CMaterial* diffuseTransparentInstancedB = 
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("diffuseTransparentBackfaceInstancedMaterialComp"));
        // [tdbe] the only thing that makes an instanced material instanced, is the instanceCount > 1.
        // (and the vertex shader consuming gl_InstanceIndex)
        diffuseTransparentInstancedB->instanceCount = 75u;
        diffuseTransparentInstancedB->firstInstance = 0u;
        diffuseTransparentInstancedB->vertShaderName = "shaders/DiffuseTransparent.vert.spv";
        diffuseTransparentInstancedB->fragShaderName = "shaders/DiffuseTransparent.frag.spv";
        diffuseTransparentInstancedB->pipelineData.blendEnable = VK_TRUE;
        diffuseTransparentInstancedB->pipelineData.depthTestEnable = VK_TRUE;
        diffuseTransparentInstancedB->pipelineData.depthWriteEnable = VK_TRUE;
        diffuseTransparentInstancedB->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        diffuseTransparentInstancedB->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        diffuseTransparentInstancedB->pipelineData.dstColorBlendFactor =
            VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        diffuseTransparentInstancedB->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        diffuseTransparentInstancedB->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        diffuseTransparentInstancedB->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        diffuseTransparentInstancedB->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        diffuseTransparentInstancedB->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
        // [tdbe] Note: the renderer only reads the unioform data (non-pipeline data) from the first material assigned to an entity (this backface is the 2nd).
        diffuseTransparentInstancedB->SetVisible(true);

        CMaterial* diffuseTransparentInstancedF = 
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("diffuseTransparentFrontfaceInstancedMaterialComp"));
        // [tdbe] the only thing that makes an instanced material instanced, is the instanceCount > 1.
        // (and the vertex shader consuming gl_InstanceIndex)
        diffuseTransparentInstancedF->instanceCount = 75u;
        diffuseTransparentInstancedF->firstInstance = 0u;
        diffuseTransparentInstancedF->vertShaderName = "shaders/DiffuseTransparent.vert.spv";
        diffuseTransparentInstancedF->fragShaderName = "shaders/DiffuseTransparent.frag.spv";
        diffuseTransparentInstancedF->pipelineData.blendEnable = VK_TRUE;
        diffuseTransparentInstancedF->pipelineData.depthTestEnable = VK_TRUE;
        diffuseTransparentInstancedF->pipelineData.depthWriteEnable = VK_TRUE;
        diffuseTransparentInstancedF->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        diffuseTransparentInstancedF->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        diffuseTransparentInstancedF->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        diffuseTransparentInstancedF->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        diffuseTransparentInstancedF->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        diffuseTransparentInstancedF->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        diffuseTransparentInstancedF->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        diffuseTransparentInstancedF->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        diffuseTransparentInstancedF->dynamicUniformData.colorMultiplier = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        diffuseTransparentInstancedF->dynamicUniformData.brdfData = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
        diffuseTransparentInstancedF->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction
        diffuseTransparentInstancedF->SetVisible(true);

        CMaterial* skyOfChaperoneMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("skyOfChaperoneMaterialComp"));
        skyOfChaperoneMaterial->vertShaderName = "shaders/SkyOfChaperone.vert.spv";
        skyOfChaperoneMaterial->fragShaderName = "shaders/SkyOfChaperone.frag.spv";
        skyOfChaperoneMaterial->pipelineData.blendEnable = VK_TRUE;
        skyOfChaperoneMaterial->pipelineData.depthTestEnable = VK_TRUE;
        skyOfChaperoneMaterial->pipelineData.depthWriteEnable = VK_TRUE;
        skyOfChaperoneMaterial->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS;
        skyOfChaperoneMaterial->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        skyOfChaperoneMaterial->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        skyOfChaperoneMaterial->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        skyOfChaperoneMaterial->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        skyOfChaperoneMaterial->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        skyOfChaperoneMaterial->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        skyOfChaperoneMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
        skyOfChaperoneMaterial->dynamicUniformData.colorMultiplier = glm::vec4(0.7f, 0.9f, 1.0f, 1.0f);
        skyOfChaperoneMaterial->dynamicUniformData.brdfData = glm::vec4(0.00125f, 0.005, 1.0f, 0.0f);
        skyOfChaperoneMaterial->dynamicUniformData.ior =
            glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] Todo: sky index of refraction? :)
        skyOfChaperoneMaterial->SetVisible(false);

        CMaterial* floorGridMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("floorGridMaterialComp"));
        floorGridMaterial->vertShaderName = "shaders/GridGround.vert.spv";
        floorGridMaterial->fragShaderName = "shaders/GridGround.frag.spv";
        floorGridMaterial->pipelineData.blendEnable = VK_TRUE;
        floorGridMaterial->pipelineData.depthTestEnable = VK_FALSE;
        floorGridMaterial->pipelineData.depthWriteEnable = VK_FALSE;
        floorGridMaterial->pipelineData.depthCompareOp = VK_COMPARE_OP_LESS;
        floorGridMaterial->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        floorGridMaterial->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        floorGridMaterial->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        floorGridMaterial->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        floorGridMaterial->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        floorGridMaterial->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        floorGridMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        floorGridMaterial->dynamicUniformData.colorMultiplier = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        floorGridMaterial->SetVisible(false);

        CMaterial* ceilingGridMaterial =
            gameData.mainEntityWorld->materialComponents->GetItem(gameData.namedMaterialComponentIDs.left.at("ceilingGridMaterialComp"));
        ceilingGridMaterial->vertShaderName = "shaders/GridSimple.vert.spv";
        ceilingGridMaterial->fragShaderName = "shaders/GridSimple.frag.spv";
        ceilingGridMaterial->pipelineData.blendEnable = VK_TRUE;
        ceilingGridMaterial->pipelineData.depthTestEnable = VK_FALSE;
        ceilingGridMaterial->pipelineData.depthWriteEnable = VK_FALSE;
        ceilingGridMaterial->pipelineData.depthCompareOp = VK_COMPARE_OP_ALWAYS;
        ceilingGridMaterial->pipelineData.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
        ceilingGridMaterial->pipelineData.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        ceilingGridMaterial->pipelineData.colorBlendOp = VK_BLEND_OP_ADD;
        ceilingGridMaterial->pipelineData.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        ceilingGridMaterial->pipelineData.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        ceilingGridMaterial->pipelineData.alphaBlendOp = VK_BLEND_OP_ADD;
        ceilingGridMaterial->pipelineData.cullMode = VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;
        ceilingGridMaterial->dynamicUniformData.colorMultiplier = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        ceilingGridMaterial->dynamicUniformData.perMaterialFragmentFlags.x = 0.15f; // [tdbe] the tunnelvision radius
        ceilingGridMaterial->SetVisible(false);
#pragma endregion Materials

        // -------- [tdbe] edit any "game object" properties here. --------
#pragma region GameObjects
        auto& gameEntityObjects = gameData.mainEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>();
        auto& vfxGameEntityObjects = gameData.vfxEntityWorld->entityArchetypePool->GetSubpoolByType<GameEntityObject>();
        GameEntityObject* worldRoot = gameEntityObjects.GetItem(gameData.playerObjects[0]->worldRootId);
        CTransform* worldRootTrans = worldRoot->GetComponentByTypeIndex<CTransform>();
        glm::mat4 worldRootMatr = glm::mat4(1.0f);
        worldRootTrans->SetWorldMatrix(worldRootMatr); // [tdbe] origin, render origin

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("icosphereSkybox_world"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::rotate(glm::translate(worldRootMatr, { 0.0f, 0.0f, 0.0f }), 0.71f,
                                                    { 0.0f, 1.0f, 0.0f }),
                                        { 500.12f, 500.12f, 500.12f }));
        
        util::DebugLog("~~~~[Scripting] setting ground size: ");
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("ground"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::rotate(
                                glm::translate(
                                    glm::scale(worldRootMatr, 
                                        { 128, 128, 128 }), 
                                    { 0.0f, 0.0f, 0.0f }),
                                glm::radians(-45.0f), { 0.0f, 1.0f, 0.0f }));

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("ruins"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::rotate(glm::translate(worldRootMatr, { 0.0f, 0.0f, 0.0f }),
                                         glm::radians(0.0f), { 0.0f, 1.0f, 0.0f }));

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("carLeft"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::rotate(glm::translate(worldRootMatr, 
                                                        { -4.35f, 0.0f, -1.7f }),//{ -3.5f, 0.0f, -0.5f }),
                                         glm::radians(150.0f), { 0.0f, 1.0f, 0.0f }));//75.0f
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("carRight"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::rotate(glm::translate(worldRootMatr, { 8.4f, 0.0f, -14.5f }),
                                         glm::radians(-37.0f), { 0.0f, 1.0f, 0.0f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("beetle"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(
                                        glm::rotate(
                                                    glm::translate(worldRootMatr,
                                                                  { -3.0f, 0.0f, -7.5f }),//{ -3.5f, 0.0f, -7.0f }),
                                                    glm::radians(-125.0f), { 0.0f, 1.0f, 0.0f }),
                                        { 1.1f, 1.1f, 1.1f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("beetleGlass"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::rotate(glm::translate(worldRootMatr, 
                                                                  { -3.0f, 0.0f, -7.5f }),
                                                    glm::radians(-125.0f), { 0.0f, 1.0f, 0.0f }),
                                        { 1.1f, 1.1f, 1.1f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("logo1"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::translate(worldRootMatr, { 0.0f, 3.0f, -10.0f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("logo2"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::translate(worldRootMatr, { 0.0f, 3.0f, -10.0f }));
        auto* bike = gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("bike"));
        bike->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::translate(glm::rotate(worldRootMatr, 
                                                        0.2f, { 0.0f, 1.0f, 0.0f }), 
                                         { 0.0f, 0.0f, -4.5f }));
        auto* testSquid = gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("testSquid"));
        auto transSquid = testSquid->GetComponentByTypeIndex<CTransform>();
        //transSquid->SetWorldMatrix(glm::translate(glm::rotate(worldRootMatr, 
        //                                                    1.5708f, { 0.0f, 0.0f, 1.0f }),
        //                                        { 1.6f, 1.0f, -5.0f }));
        testSquid->GetComponentByTypeIndex<CParent>()->SetParent(bike->id);
        auto squidLocalPose = transSquid->GetLocalPose();
        auto squidWorldPose = transSquid->GetWorldPose();
        squidLocalPose.scale = glm::vec3{0.25f, 0.25f, 0.25f};
        squidLocalPose.position = glm::vec3{0.0f, 1.6f, -0.85f};
        //                                                     90 degrees *4 because of the parent's rotation (and this is the local rotation)
        squidLocalPose.orientation = util::quaternionFromAngleAxis(1.5708f*4, { 0.0f, 0.0f, 1.0f });
        transSquid->SetLocalPose(squidLocalPose);
        
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("cube"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::rotate(glm::translate(worldRootMatr, 
                                                                    { 0.0f, -0.45f, -4.5f }),
                                                    -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }),
                                        { 0.5f, 0.5f, 0.5f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("textLocomotion"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(
                glm::scale(glm::rotate(glm::translate(worldRootMatr, { 2.825f, 0.835f, -1.7f }),
                                       -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }),
                           { 0.25f, 0.25f, 0.25f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("textSudaBeam"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::rotate(glm::translate(worldRootMatr, { 2.825f, 0.2325f, -1.3f }),//2.825f, 0.23f, -1.7f
                                                    -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }),
                                        { 0.225f, 0.225f, 0.225f }));
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("textSeeControlsMd"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::rotate(glm::translate(worldRootMatr, { 2.825f, 0.205f, -3.2f }),
                                                    -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }),
                                        { 0.2f, 0.2f, 0.2f }));                  
        
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("icosphereSmoothForInstancing"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::translate(worldRootMatr, { -2.25f, 1.25f, -14.5f }),
                                        { 0.5f, 0.5f, 0.5f }));

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("icosphereSmoothTripInstancing"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::translate(worldRootMatr, { 0.0f, 0.0f, 0.0f }),// { 2.0f, 2.0f, -2.5f }
                                        { 0.7f, 0.7f, 0.7f }));

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("monke"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::translate(worldRootMatr, { 0.0f, 0.0f, 0.5f }));// [tdbe] mesh is offset and baked from blender

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("monkeEye1"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::translate(worldRootMatr, { 9.87879f, 1.99395f, -10.586f + 0.5f }),
                                        { 0.283856f, 0.283856f, 0.283856f }));

        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("monkeEye2"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::translate(worldRootMatr, { 10.3927f, 2.55881f, -9.76025f + 0.5f}),
                                        { 0.283856f, 0.283856f, 0.283856f }));
        
        gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("squid"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::translate(worldRootMatr, { 3.62f, 2.5f, -9.95f }),//-10.125f
                                        { 0.75f, 0.75f, 0.75f }));
        
        // -------- [tdbe] set any non-default game VFX object props here.
        vfxGameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("icosphereSkybox_chaperone"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(glm::rotate(glm::translate(worldRootMatr, { 0.0f, 0.0f, 0.0f }), 0.71f,
                                                    { 0.0f, 1.0f, 0.0f }),
                                        { 500.12f, 500.12f, 500.12f }));

        util::DebugLog("~~~~[Scripting] setting floorGrid. ");
        vfxGameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("floorGrid"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(worldRootMatr, { 256, 256, 256 }));
        util::DebugLog("~~~~[Scripting] setting ceilingGrid. ");
        vfxGameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("ceilingGrid"))
            ->GetComponentByTypeIndex<CTransform>()
            ->SetWorldMatrix(glm::scale(worldRootMatr, { 256, 256, 256 }));
#pragma endregion GameObjects

        // -------- [tdbe] edit any lights properties here. --------
#pragma region Lights
        // [tdbe] tube light: z: tube length, x (and/or) y: tube radius

        CLight* dirLightComp = gameData.mainEntityWorld->lightComponents->GetItem(gameData.namedLightComponentIDs.left.at("mainDirectionalLightComp"));
        CTransform* dirLightTrans = gameEntityObjects.GetItem(gameData.namedGameObjectIDs.left.at("mainDirectionalLight"))
                ->GetComponentByTypeIndex<CTransform>();
        glm::mat4 dirLightMatr = dirLightTrans->GetWorldMatrix();
        dirLightMatr[3] = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f); // [tdbe] for directional light, set the direction only
        dirLightTrans->SetWorldMatrix(dirLightMatr);
        dirLightComp->SetRenderProperties(glm::vec4(1.0f, 1.0f, 0.87f, 1.0f), CLight::LightTypes::LIGHT_TYPE_DIRECTIONAL);
        dirLightComp->SetVisible(true);
        
        //Light* bikeLightComp =
        //    gameData.lightComponents->GetItem(gameData.namedLightComponentIDs.left.at("bikeLightComp"]);
        //bikeLightComp->SetRenderProperties(glm::vec4(1.0f, 0.0f, 0.0f,0.0048828125f), 5.0f, Light::LightTypes::LIGHT_TYPE_TUBE);
        //bikeLightComp->SetVisible(true);

        CLight* handLight01Comp = gameData.mainEntityWorld->lightComponents->GetItem(gameData.namedLightComponentIDs.left.at("handLight01Comp"));
        // [tdbe] z: tube length, x (and/or) y: tube radius
        handLight01Comp->SetRenderProperties(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), CLight::LightTypes::LIGHT_TYPE_TUBE);
        handLight01Comp->SetVisible(true);

        CLight* handLight02Comp = gameData.mainEntityWorld->lightComponents->GetItem(gameData.namedLightComponentIDs.left.at("handLight02Comp"));
        // [tdbe] z: tube length, x (and/or) y: tube radius
        handLight02Comp->SetRenderProperties(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), CLight::LightTypes::LIGHT_TYPE_TUBE);
        handLight02Comp->SetVisible(true);

        glm::vec4 tentacleColors[6] = {
            glm::vec4(0.0, 1.0, 1.0, 1.0), // cyan
            glm::vec4(0.0, 0.0, 1.0, 1.0), // blue
            glm::vec4(1.0, 0.0, 1.0, 1.0), // magenta
            glm::vec4(1.0, 0.0, 0.0, 1.0), // red
            glm::vec4(1.0, 1.0, 0.0, 1.0), // yellow
            glm::vec4(0.0, 1.0, 0.0, 1.0) // green
        };
        auto id01 = GameData::Instance().namedLightComponentIDs.left.at("tentacleLightComp01");
        for (int i = 1; i < 7; i++)
        {
            CLight* tentacleLightComp = gameData.mainEntityWorld->lightComponents->items[id01.chunkIndex][id01.indexInChunk + i - 1];
            // [tdbe] z: tube length, x (and/or) y: tube radius
            tentacleLightComp->SetRenderProperties(tentacleColors[i-1], 1.0, 
                                                   CLight::LightTypes::LIGHT_TYPE_TENTACLE);
            
            tentacleLightComp->SetVisible(true);
        }

#pragma endregion Lights
        util::DebugLog("[Scripting][SceneSetup]\t 🎥 Scripted / scene objects setup done.");
        util::DebugLog("[Scripting][SceneSetup]\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return true;
	}

} // namespace Scripting