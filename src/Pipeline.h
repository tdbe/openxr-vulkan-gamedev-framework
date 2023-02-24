#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include <glm/vec4.hpp>

class Context;

// [tdbe] uniform properties to bind to a material's shader.
// properties need to be copied to DynamicVertexUniformData
struct DynamicMaterialUniformData{
	glm::vec4 colorMultiplier = glm::vec4(1.0f);
};

// [tdbe] pipeline configurations for this pipeline / "material"
struct PipelineMaterialPayload{
  VkBlendFactor srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	VkBlendFactor dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	VkBlendOp colorBlendOp = VK_BLEND_OP_ADD;
	VkBlendFactor srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	VkBlendFactor dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	VkBlendOp alphaBlendOp = VK_BLEND_OP_ADD;
	VkCullModeFlagBits cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
  bool operator==(const PipelineMaterialPayload& other) const
  {
      return
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
      (cullMode == other.cullMode);
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

  bool isValid() const;

  const std::string getVertShaderName() const;
  const std::string getFragShaderName() const;
  const PipelineMaterialPayload& getPipelineMaterialData() const;

private:
  std::string vertShaderName;
  std::string fragShaderName;
  bool valid = false;

  const Context* context = nullptr;
  VkPipeline pipeline = nullptr;

  PipelineMaterialPayload pipelineData;
};