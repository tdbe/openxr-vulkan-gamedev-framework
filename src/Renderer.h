#pragma once

#include <glm/fwd.hpp>

#include <vulkan/vulkan.h>

#include <vector>

#include "GameData.h"
#include "InputData.h"

class Context;
class DataBuffer;
class Headset;
class MeshData;
struct Model;
struct Material;
class Pipeline;
class RenderProcess;

/*
 * The renderer class facilitates rendering with Vulkan. It is initialized with a constant list of models to render and
 * holds the vertex/index buffer, the pipelines that define the rendering techniques to use, as well as a number of
 * render processes. Note that all resources that need to be duplicated in order to be able to render several frames in
 * parallel are held by this number of render processes.
 */
/*
* [tdbe] Look for "// [tdbe]" comments in Renderer.cpp, and in GameData.h/Material. I have explained some of the confusing 
* vulkan bits for you and I modified it for a Material style workflow, with per-material pipeline support, and/or descriptor sets.
*/
class Renderer final
{
public:
  Renderer(const Context* context, const Headset* headset, const MeshData* meshData, const std::vector<Material*>& materials, const std::vector<GameObject*>& gameObjects);
  ~Renderer();

  void render(const glm::mat4& cameraMatrix, size_t swapchainImageIndex, float time, const Inputspace::InputData& inputData);
  void submit(bool useSemaphores) const;

  bool isValid() const;
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
  std::vector<RenderProcess*> renderProcesses;
  VkPipelineLayout pipelineLayout = nullptr;
  std::vector<Pipeline *> pipelines;
  DataBuffer* vertexIndexBuffer = nullptr;
  std::vector<Material*> materials;
  std::vector<GameObject*> gameObjects;
  size_t indexOffset = 0u;
  size_t currentRenderProcessIndex = 0u;

  const int findExistingPipeline(const std::string& vertShader, const std::string& fragShader, const PipelineMaterialPayload& pipelineData) const;
};