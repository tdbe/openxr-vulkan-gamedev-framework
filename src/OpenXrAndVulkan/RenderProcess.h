#pragma once
#include <vulkan/vulkan.h>

#include <array>
#include <cstring>
#include <glm/mat4x4.hpp>
#include <vector>

#include "../Utils/Util.h"
#include "Context.h"
#include "DataBuffer.h"

#include "../GameData/GameData.h"

class Context;
class DataBuffer;

/*
 * The render process class consolidates all the resources that needs to be duplicated for each frame that can be
 * rendered to in parallel. The renderer owns a render process for each frame that can be processed at the same time,
 * and each render process holds their own uniform buffer, command buffer, semaphores and memory fence. With this
 * duplication, the application can be sure that one frame does not modify a resource that is still in use by another
 * simultaneous frame.
 
 [tdbe] Some context: <see cref="Renderer::framesInFlight"/> we need a circular buffer of multiple frames in flight 
 (typically 2 (not to be confused with 2 eyes in vr)) and pool of descriptorset data, so the gpu can safely read from one
 set while the cpu writes to the other.

 [tdbe] TODO: create a per-material buffer for e.g. brdf, colors, textures etc
 ie create descriptor sets (the main way of connecting CPU data to the GPU), per-material,
 to also be able to push different (texture) data per gameobject/mat. (vkCmdPushConstants is a limited alternative.)
 */
class RenderProcess final
{
  public:
    // [tdbe] TODO: create a per-material buffer for e.g. brdf, colors, textures etc

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
        int instanceCount = 1;
    };
    std::vector<DynamicVertexUniformData> dynamicVertexUniformData;

    /// [tdbe] vertex shader  global uniform properties
    /// (in case you don't know: this struct is bound to a memory span slot on the gpu (one that you can name
    /// whatever you want on the gpu e.g. StaVertBufData in vert shaders), so that's why you can't find a
    /// direct reference between them)
    struct StaticVertexUniformData
    {
        std::array<glm::mat4, 2u> handsWorldMatrixes;     // [tdbe] 0 = left hand, 1 = right hand
        std::array<glm::mat4, 2u> cameraWorldMatrixes;    // [tdbe] 0 = left eye, 1 = right eye
        std::array<glm::mat4, 2u> viewMatrixes;           // [tdbe] 0 = left eye, 1 = right eye
        std::array<glm::mat4, 2u> viewProjectionMatrixes; // [tdbe] 0 = left eye, 1 = right eye
        float ipd; // [tdbe] Interpupillary distance, the headset's setting for the distance between your eyes.
        float time;
        int inLocomotion;// [tdbe] for some globally applied tricks to avoid motion sickness
    } staticVertexUniformData;

    /// [tdbe] fragment shader dynamic uniform properties
    struct DynamicFragmentUniformData
    {
        // [tdbe] TODO: create a per-material buffer for e.g. brdf, colors, textures etc
        /// [tdbe] x: metallic, y: roughness, z: todo: clearcoat, w: procedural color flag & intensity
        glm::vec4 brdfData = glm::vec4(0.5f);
        glm::vec4 ior = glm::vec4(9.16095e-12f, 1.81225e-12f, 0.0024589f, 1.0); // [tdbe] gold paint index of refraction
        /// [tdbe] allocation for various flags for hacks and triggers sent to the fragment shaders
        glm::vec4 perMaterialFlags = glm::vec4(1.0f);
    };
    std::vector<DynamicFragmentUniformData> dynamicFragmentUniformData;

    /// [tdbe] fragment shader global uniform properties
    struct StaticFragmentUniformData
    {
        /// [tdbe] each matrix row is: const int COLOR = 0 (.w means disabled if 0.0); const int CENTRAL_VEC = 1 (and .w
        /// is radius); const int SHAPE_VEC_0 = 2; const int SHAPE_VEC_1 = 3;
        std::array<glm::mat4, Game::GameData::AllocationMagicNumbers::LIGHTS_COUNT> lights;
        /// [tdbe] used as a set of colors to simulate ambience until we do better sampling features
        glm::mat4 ambientLight = glm::mat4( //0.351f, 0.422f, 0.562f, 1.0f,
                                            0.325f, 0.41, 0.689f, 1.0f,// zenith
                                            //0.5929f, 0.61f, 0.71f, 1.0f,// horizon
                                            0.595f, 0.685f, 0.805f, 1.0f,// horizon
                                            // 0.396f, 0.376f, 0.353f, 1.0f,
                                            0.1f, 0.08f, 0.12f, 1.0f,// ground
                                            0.5f, 0.46f, 0.54f, 0.01f); // [tdbe] <- fog color and density
        glm::vec2 screenSizePixels;
        float ipd; // [tdbe] Interpupillary distance, the headset's setting for the distance between your eyes.
        float time;
    } staticFragmentUniformData;

    /// [tdbe] this is for mapping memory buffers to the gpu, so the strategy is similar to our <see cref="GameDataPool"/>
    /// in the sense that we allocate for e.g. max possible renderable object count in our game, and we'll do actual 
    /// draw calls in the renderer, only for the game objects we actually have available.
    void AllocateDescriptorSetsUniformBuffers(size_t gameObjectCount, size_t materialsCount);

    bool IsValid() const;
    VkCommandBuffer GetCommandBuffer() const;
    VkSemaphore GetDrawableSemaphore() const;
    VkSemaphore GetPresentableSemaphore() const;
    VkFence GetBusyFence() const;
    VkDescriptorSet GetDescriptorSet() const;

    void UpdateUniformBufferData() const;

    RenderProcess(const Context* context,
                  VkCommandPool commandPool,
                  VkDescriptorPool descriptorPool,
                  VkDescriptorSetLayout descriptorSetLayout);
    ~RenderProcess();

  private:
    bool valid = true;

    const Context* context = nullptr;
    VkCommandPool commandPool;
    VkDescriptorPool descriptorPool;
    VkDescriptorSetLayout descriptorSetLayout;
    VkCommandBuffer commandBuffer = nullptr;
    VkSemaphore drawableSemaphore = nullptr, presentableSemaphore = nullptr;
    VkFence busyFence = nullptr;
    DataBuffer* uniformBuffer = nullptr;
    void* uniformBufferMemory = nullptr;
    VkDescriptorSet descriptorSet = nullptr;

    void ClearUniformBuffer();
};