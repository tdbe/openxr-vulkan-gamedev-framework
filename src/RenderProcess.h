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

  // [tdbe] TODO: create a per-material buffer for e.g. the colorMultiplier, texture etc

  /// [tdbe] vertex shader dynamic uniform properties to bind to per model / gameObject.
  /// (in case you don't know: this struct is bound to a memory span slot on the gpu (one that you can name 
  /// whatever you want on the gpu e.g. DynVertBufData in vert shaders), so that's why you can't find a 
  /// direct reference between them)
  struct DynamicVertexUniformData
  {
    /// [tdbe] per model/mesh
    glm::mat4 worldMatrix = glm::mat4(1.0f);
    /// [tdbe]"per material" (ie it doesn't -need- to be unique per model/mesh)
    glm::vec4 colorMultiplier = glm::vec4(1.0f);
    /// [tdbe] allocation for various flags for hacks and triggers sent to the vertex shaders
    glm::vec4 perMaterialFlags = glm::vec4(1.0f);
  };
  std::vector<DynamicVertexUniformData> dynamicVertexUniformData;

  /// [tdbe] vertex shader  global uniform properties
  /// (in case you don't know: this struct is bound to a memory span slot on the gpu (one that you can name
  /// whatever you want on the gpu e.g. StaVertBufData in vert shaders), so that's why you can't find a
  /// direct reference between them)
  struct StaticVertexUniformData
  {
    std::array<glm::mat4, 2u> cameraWorldMatrixes; // 0 = left eye, 1 = right eye
    std::array<glm::mat4, 2u> viewMatrixes; // 0 = left eye, 1 = right eye
    std::array<glm::mat4, 2u> viewProjectionMatrixes; // 0 = left eye, 1 = right eye
  } staticVertexUniformData;
  
  /// [tdbe] fragment shader dynamic uniform properties
  struct DynamicFragmentUniformData
  {
    /// [tdbe] allocation for various flags for hacks and triggers sent to the fragment shaders
    glm::vec4 perMaterialFlags = glm::vec4(1.0f);
  };
  std::vector<DynamicFragmentUniformData> dynamicFragmentUniformData;

  /// [tdbe] fragment shader global uniform properties
  struct StaticFragmentUniformData
  {
    /// [tdbe] used as a set of colors (and other flags) to simulate ambience until we do better sampling features
    glm::mat4 ambientMultiplier = glm::mat4(0.351f, 0.422f, 0.562f, 1.0f,
                                            0.5929f, 0.61f, 0.71f, 1.0f,
                                            //0.396f, 0.376f, 0.353f, 1.0f,
                                            0.1f, 0.08f, 0.12f, 1.0f,
                                            0.5f, 0.46f, 0.54f, 0.01f);// [tdbe] fog color and density
    glm::vec2 screenSizePixels;
    float ipd; // [tdbe] Interpupillary distance, the headset's setting for the distance between your eyes.
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