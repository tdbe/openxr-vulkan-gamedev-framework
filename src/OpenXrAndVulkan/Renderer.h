#pragma once
#include <glm/fwd.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "Pipeline.h"
#include "../GameData/GameDataPool.h"

// [tdbe] newb-friendly-note: predeclaring here so we can use pointers here and avoid circular dependency, we reference the real headers inside the .cpp
namespace Game
{
    struct MeshData;
    struct Model;
    struct Material;
    struct Light;
    struct GameEntityObject;
}
using namespace Game;

namespace Inputspace
{
    struct InputData;
}
using namespace Inputspace;

class Context;
class DataBuffer;
class Headset;
class Pipeline;
class RenderProcess;

/*
 * The renderer class facilitates rendering with Vulkan. It is initialized with a constant list of models to render and
 * holds the vertex/index buffer, the pipelines that define the rendering techniques to use, as well as a number of
 * render processes. Note that all resources that need to be duplicated in order to be able to render several frames in
 * parallel are held by this number of render processes.
 */

class Renderer final
{
public:
    /// [tdbe] how many render processes we have. You don't want the CPU to write to a frame that the GPU is in the middle of reading from.
    static constexpr size_t framesInFlight = 2u; 
    static constexpr float NEAR_CLIP_PLANE = 0.09f;
    static constexpr float FAR_CLIP_PLANE = 512.0f;
    static constexpr  float FROSTBITE_MIN_ROUGHNESS = 0.045f; // [tdbe] reduce specular aliasing, also avoid invisible specular highlights
    /// [tdbe] we need a circular buffer of descriptorset data, to cover more than 1 frame in flight,
    /// so the gpu can read one while the cpu is writing another.
    /// The aim should always be to set up gpu bufferas once, with the max number of items you'll use in this game
    /// world, the same idea as with the <see cref="GameDataPool"/>. (It doesn't cost gpu power to just have it there.)
    void SetUpRenderProcesses(const Game::MeshData* meshData,
                               const GameDataPool<Material>* materials,
                               const GameDataPool<GameEntityObject>* gameEntityObjects,
                               const GameDataPool<GameEntityObject>* gameVFXObjects,
                               const GameDataPool<Light>* gameLights);
    /// [tdbe] Render. (The ideal is indirect rendering, and)
    /// Prefer less drawcalls, less cpu-gpu communication:
    /// - one draw call per material "instanced geometry" style,
    /// - or one draw call per mesh but grouped by material.
    Renderer(const Context* context,
             const Headset* headset);
    ~Renderer();

    void Render(const glm::mat4& cameraMatrix,
                size_t swapchainImageIndex,
                float time,
                const Inputspace::InputData& inputData,
                const bool playerIsInChaperone,
                const GameDataPool<Material>* materials,
                const GameDataPool<GameEntityObject>* gameEntityObjects,
                const GameDataPool<GameEntityObject>* gameVFXObjects,
                const GameDataPool<Light>* gameLights);
    void submit(bool useSemaphores) const;

    bool IsValid() const;
    VkCommandBuffer getCurrentCommandBuffer() const;
    VkSemaphore getCurrentDrawableSemaphore() const;
    VkSemaphore getCurrentPresentableSemaphore() const;

private:
    bool valid = true;

    const Context* context = nullptr;
    const Headset* headset = nullptr;

    VkCommandPool commandPool = nullptr;
    VkDescriptorPool descriptorPool = nullptr;
    VkDescriptorSetLayout descriptorSetLayout = nullptr;
    std::vector<RenderProcess*> renderProcessesCircularBuffer;
    VkPipelineLayout pipelineLayout = nullptr;
    std::vector<Pipeline *> pipelines;
    DataBuffer* vertexIndexBuffer = nullptr;
    size_t indexOffset = 0u;
    size_t currentRenderProcessIndex = 0u;

    void ClearPipelines();

    const int findExistingPipeline(const std::string& vertShader, 
        const std::string& fragShader, const PipelineMaterialPayload& pipelineData) const;
};