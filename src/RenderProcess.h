#pragma once

#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>

#include <array>
#include <vector>

#include "GameData.h"

class Context;
class DataBuffer;

/*
 * The render process class consolidates all the resources that needs to be duplicated for each frame that can be
 * rendered to in parallel. The renderer owns a render process for each frame that can be processed at the same time,
 * and each render process holds their own uniform buffer, command buffer, semaphores and memory fence. With this
 * duplication, the application can be sure that one frame does not modify a resource that is still in use by another
 * simultaneous frame.
 * 
 * [tdbe] TODO: We should create descriptor sets (the main way of connecting CPU data to the GPU), per-material, 
 * to also be able to push different (texture) data per gameobject/mat. (vkCmdPushConstants is a limited alternative.)
 */
class RenderProcess final
{
public:
  RenderProcess(const Context* context,
                VkCommandPool commandPool,
                VkDescriptorPool descriptorPool,
                VkDescriptorSetLayout descriptorSetLayout,
                size_t gameObjectCount,
                size_t materialsCount
                );
  ~RenderProcess();

  // [tdbe] uniform properties to bind to per model.
  // Also the per-material properties get sent here.
  struct DynamicVertexUniformData{
    // per model/mesh
    glm::mat4 worldMatrix = glm::mat4(1.0f);
    // "per material" (ie it doesn't -need- to be unique per model/mesh)
    glm::vec4 colorMultiplier = glm::vec4(1.0f);
  };
  std::vector<DynamicVertexUniformData> dynamicVertexUniformData;

  // [tdbe] uniform properties available globally
  struct StaticVertexUniformData
  {
    std::array<glm::mat4, 2u> viewProjectionMatrices; // 0 = left eye, 1 = right eye
  } staticVertexUniformData;
  
  // [tdbe] uniform properties available globally
  struct StaticFragmentUniformData
  {
    float time;
  } staticFragmentUniformData;

  bool isValid() const;
  VkCommandBuffer getCommandBuffer() const;
  VkSemaphore getDrawableSemaphore() const;
  VkSemaphore getPresentableSemaphore() const;
  VkFence getBusyFence() const;
  VkDescriptorSet getDescriptorSet() const;

  void updateUniformBufferData() const;

private:
  bool valid = true;

  const Context* context = nullptr;
  VkCommandBuffer commandBuffer = nullptr;
  VkSemaphore drawableSemaphore = nullptr, presentableSemaphore = nullptr;
  VkFence busyFence = nullptr;
  DataBuffer* uniformBuffer = nullptr;
  void* uniformBufferMemory = nullptr;
  VkDescriptorSet descriptorSet = nullptr;
};