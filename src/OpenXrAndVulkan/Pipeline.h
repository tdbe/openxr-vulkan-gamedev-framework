#pragma once
#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <array>
#include <sstream>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "../Utils/Util.h"

#include "Context.h"

class Context;

/// [tdbe] vertex and fragment shader dynamic uniform properties to bind to per model or per-material.
/// properties need to be copied to <see cerf="DynamicVertexUniformData"/> or <see cerf="dynamicFragmentUniformData"/>
struct DynamicMaterialUniformData
{
    /// [tdbe] per material color
	glm::vec4 colorMultiplier = glm::vec4(1.0f);
    /// [tdbe] allocation for various flags for hacks and triggers sent to the shaders
	glm::vec4 perMaterialVertexFlags = glm::vec4(1.0f);
    /// [tdbe] x: metallic, y: roughness, z: todo: clearcoat, w: procedural color flag & intensity
    glm::vec4 brdfData = glm::vec4(0.5f);
    glm::vec4 ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0f); // [tdbe] gold paint index of refraction
    /// [tdbe] hax
	glm::vec4 perMaterialFragmentFlags = glm::vec4(1.0f);
};

// [tdbe] pipeline configurations for this pipeline / "material"
struct PipelineMaterialPayload
{
    VkBool32 blendEnable = VK_FALSE;
    VkBlendFactor srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	VkBlendFactor dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	VkBlendOp colorBlendOp = VK_BLEND_OP_ADD;
	VkBlendFactor srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	VkBlendFactor dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	VkBlendOp alphaBlendOp = VK_BLEND_OP_ADD;
	VkCullModeFlagBits cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
    VkBool32 depthTestEnable = VK_TRUE;
    VkBool32 depthWriteEnable = VK_TRUE;
    VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
  bool operator==(const PipelineMaterialPayload& other) const
  {
      return 
      (blendEnable == other.blendEnable) 
      &&
      (srcColorBlendFactor == other.srcColorBlendFactor)
      &&
      (dstColorBlendFactor == other.dstColorBlendFactor)
      &&
      (colorBlendOp == other.colorBlendOp)
      &&
      (srcAlphaBlendFactor == other.srcAlphaBlendFactor)
      &&
      (dstAlphaBlendFactor == other.dstAlphaBlendFactor)
      &&
      (alphaBlendOp == other.alphaBlendOp)
      &&
      (cullMode == other.cullMode)
      &&
      (depthTestEnable == other.depthTestEnable)
      &&
      (depthWriteEnable == other.depthWriteEnable)
      &&
      (depthCompareOp == other.depthCompareOp);
  }
};

/*
 * The pipeline class wraps a Vulkan pipeline for convenience. It describes the rendering technique to use, including
 * shaders, culling, scissoring (renderable area, similar to viewport (but changing the scissor rect won't affect coordinates), 
 * and other aspects.
 */
class Pipeline final
{
public:
  Pipeline(const Context* context,
           VkPipelineLayout pipelineLayout,
           VkRenderPass renderPass,
           const std::string& vertexFilename,
           const std::string& fragmentFilename,
           const std::vector<VkVertexInputBindingDescription>& vertexInputBindingDescriptions,
           const std::vector<VkVertexInputAttributeDescription>& vertexInputAttributeDescriptions,
           PipelineMaterialPayload pipelineData
           );
  ~Pipeline();

  void bindPipeline(VkCommandBuffer commandBuffer) const;

  bool IsValid() const;

  const std::string getVertShaderName() const;
  const std::string getFragShaderName() const;
  const PipelineMaterialPayload& getPipelineMaterialData() const;

private:
  std::string vertShaderName;
  std::string fragShaderName;
  bool valid = false;

  const Context* context = nullptr;
  VkPipeline vkPipeline = nullptr;

  PipelineMaterialPayload pipelineData;
};