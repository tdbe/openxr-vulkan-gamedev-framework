#include "Renderer.h"

#include "Context.h"
#include "DataBuffer.h"
#include "Headset.h"
#include "MeshData.h"
#include "GameData.h"
#include "Pipeline.h"
#include "RenderProcess.h"
#include "RenderTarget.h"
#include "Util.h"

#include <array>
#include <stdio.h>


namespace
{
constexpr size_t framesInFlightCount = 2u;
} // namespace

Renderer::Renderer(const Context* context,
                   const Headset* headset,
                   const MeshData* meshData,
                   const std::vector<Material*>& materials,
                   const std::vector<GameObject*>& gameObjects
                   )
: context(context), headset(headset), materials(materials), gameObjects(gameObjects)
{
  const VkDevice device = context->getVkDevice();

  // Create a command pool
  VkCommandPoolCreateInfo commandPoolCreateInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
  commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  commandPoolCreateInfo.queueFamilyIndex = context->getVkDrawQueueFamilyIndex();
  if (vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &commandPool) != VK_SUCCESS)
  {
    util::error(Error::GenericVulkan);
    valid = false;
    return;
  }

  // Create a descriptor pool
  std::array<VkDescriptorPoolSize, 2u> descriptorPoolSizes;

  descriptorPoolSizes.at(0u).type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
  descriptorPoolSizes.at(0u).descriptorCount = static_cast<uint32_t>(framesInFlightCount);

  descriptorPoolSizes.at(1u).type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptorPoolSizes.at(1u).descriptorCount = static_cast<uint32_t>(framesInFlightCount * 2u);

  VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
  descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
  descriptorPoolCreateInfo.pPoolSizes = descriptorPoolSizes.data();
  descriptorPoolCreateInfo.maxSets = static_cast<uint32_t>(framesInFlightCount);
  if (vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool) != VK_SUCCESS)
  {
    util::error(Error::GenericVulkan);
    valid = false;
    return;
  }

  // [tdbe] Pipelines in Vulkan:
  // [tdbe] Uness you are using some kind of large "Standard Shader" / "Uber Shader", you want to make one 
  //        pipeline per type of shader. E.g. BRDF Opaque, Simple Transparent, etc. Every time you have a
  //        new shader, if it takes very different inputs, the vukan way to do it is to have a new pipeline.
  //        "Pipeline" can be a confusing term.
  //        You can have one pipeline for one shader for one vertex-fragment or render stage / subpass. 
  //        But also you can bind different uniforms to the same shader. Ie, the "material" workflow we are
  //        are all familiar with.
  //        Each GameData/`Material` -can- run a unique pipeline if you need. Set it up in here. One pipeline per shader.
  //        Also, each Material can hold different descriptor set data (ie properties (DynamicMaterialUniformData)), 
  //        such that if it fits the main pipeline's layout's descriptor set layout (🙂), you don't need to make 
  //        a new pipeline or a new descriptor.

  // [tdbe] NOTE: TODO: We also need a descriptor set layout that supports textures, 
  // and a descriptor set per-material, (or descriptor set data per-materal), 
  // to bind textures to each material.
  // Rn we have one universal descriptor set for all our materials, and can only push floats, arrays etc.

  // Create a descriptor set layout
  std::array<VkDescriptorSetLayoutBinding, 3u> descriptorSetLayoutBindings;

  // [tdbe] per model/mesh data, vertex dynamic; 
  //        and also per-material data go here.
  descriptorSetLayoutBindings.at(0u).binding = 0u;
  descriptorSetLayoutBindings.at(0u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
  descriptorSetLayoutBindings.at(0u).descriptorCount = 1u;
  descriptorSetLayoutBindings.at(0u).stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  descriptorSetLayoutBindings.at(0u).pImmutableSamplers = nullptr;

  // [tdbe] cross-shader global (pipeline/descriptorset wide) vertex static
  descriptorSetLayoutBindings.at(1u).binding = 1u;
  descriptorSetLayoutBindings.at(1u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptorSetLayoutBindings.at(1u).descriptorCount = 1u;
  descriptorSetLayoutBindings.at(1u).stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  descriptorSetLayoutBindings.at(1u).pImmutableSamplers = nullptr;

  // [tdbe] cross-shader global (pipeline/descriptorset wide) fragment static
  descriptorSetLayoutBindings.at(2u).binding = 2u;
  descriptorSetLayoutBindings.at(2u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptorSetLayoutBindings.at(2u).descriptorCount = 1u;
  descriptorSetLayoutBindings.at(2u).stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  descriptorSetLayoutBindings.at(2u).pImmutableSamplers = nullptr;

  VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
  descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(descriptorSetLayoutBindings.size());
  descriptorSetLayoutCreateInfo.pBindings = descriptorSetLayoutBindings.data();
  if (vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
  {
    util::error(Error::GenericVulkan);
    valid = false;
    return;
  }

  // Create a pipeline layout
  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
  pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
  pipelineLayoutCreateInfo.setLayoutCount = 1u;
  if (vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
  {
    util::error(Error::GenericVulkan);
    valid = false;
    return;
  }

  // Create a render process for each frame in flight
  renderProcesses.resize(framesInFlightCount);
  for (RenderProcess*& renderProcess : renderProcesses)
  {
    renderProcess = new RenderProcess(context, commandPool, descriptorPool, descriptorSetLayout, gameObjects.size(), materials.size());
    if (!renderProcess->isValid())
    {
      valid = false;
      return;
    }
  }

  // Create the pipeline
  VkVertexInputBindingDescription vertexInputBindingDescription;
  vertexInputBindingDescription.binding = 0u;
  vertexInputBindingDescription.stride = sizeof(Vertex);
  vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  // [tdbe] This is where you bind vertex uniform data for shader input 
  // (e.g. vertex pos, vertex normal, vertex color), and assign per-pipeline.
  // (not related to the descriptor set layout above)
  VkVertexInputAttributeDescription vertexInputAttributePosition;
  vertexInputAttributePosition.binding = 0u;
  vertexInputAttributePosition.location = 0u;
  vertexInputAttributePosition.format = VK_FORMAT_R32G32B32_SFLOAT;
  vertexInputAttributePosition.offset = offsetof(Vertex, position);

  VkVertexInputAttributeDescription vertexInputAttributeNormal;
  vertexInputAttributeNormal.binding = 0u;
  vertexInputAttributeNormal.location = 1u;
  vertexInputAttributeNormal.format = VK_FORMAT_R32G32B32_SFLOAT;
  vertexInputAttributeNormal.offset = offsetof(Vertex, normal);

  VkVertexInputAttributeDescription vertexInputAttributeColor;
  vertexInputAttributeColor.binding = 0u;
  vertexInputAttributeColor.location = 2u;
  vertexInputAttributeColor.format = VK_FORMAT_R32G32B32_SFLOAT;
  vertexInputAttributeColor.offset = offsetof(Vertex, color);
  
  PipelineMaterialPayload pipelineMaterialPayload = {};
  pipelines.resize(2);
  pipelines[0] = new Pipeline(context, pipelineLayout, headset->getVkRenderPass(), "shaders/Grid.vert.spv", "shaders/Grid.frag.spv",
                    { vertexInputBindingDescription }, 
                    { vertexInputAttributePosition, vertexInputAttributeColor
                    },
                    pipelineMaterialPayload);
  pipelines[1] = new Pipeline(context, pipelineLayout, headset->getVkRenderPass(), "shaders/Diffuse.vert.spv", "shaders/Diffuse.frag.spv",
                    { vertexInputBindingDescription }, 
                    { vertexInputAttributePosition, vertexInputAttributeNormal, vertexInputAttributeColor
                    },
                    pipelineMaterialPayload);

  for(size_t i=0; i<materials.size(); i++){
    int pipelineExistsAt = findExistingPipeline(materials[i]->vertShaderName, materials[i]->fragShaderName, materials[i]->pipelineData);
    //std::printf("\n[Renderer][log] pipelining materials: index: {%d}, shader.name: {%s}, exists: {%d}", i, materials[i]->fragShaderName.c_str(), pipelineExistsAt );
    // [tdbe] default grid pipeline
    if(i==0){   
      materials[0]->pipeline = pipelines[0];
        
    }// [tdbe] default diffuse pipeline
    else if (pipelineExistsAt > -1)
    {
      materials[i]->pipeline = pipelines[pipelineExistsAt];
    }// [tdbe] create a new pipeline from material shader name, with default parameters
    else{
      pipelines.emplace_back(new Pipeline(context, pipelineLayout, headset->getVkRenderPass(), 
                    materials[i]->vertShaderName, materials[i]->fragShaderName,
                    { vertexInputBindingDescription }, 
                    { vertexInputAttributePosition, vertexInputAttributeNormal, vertexInputAttributeColor
                    },
                    materials[i]->pipelineData));
      materials[i]->pipeline = pipelines[pipelines.size()-1];
    }
    
    if (!materials[i]->pipeline->isValid())
    {
      valid = false;
      return; 
    }
  }
  
  // Create a vertex index buffer
  {
    // Create a staging buffer
    const VkDeviceSize bufferSize = static_cast<VkDeviceSize>(meshData->getSize());
    DataBuffer* stagingBuffer =
      new DataBuffer(context, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, bufferSize);
    if (!stagingBuffer->isValid())
    {
      valid = false;
      return;
    }

    // Fill the staging buffer with vertex and index data
    char* bufferData = static_cast<char*>(stagingBuffer->map());
    if (!bufferData)
    {
      valid = false;
      return;
    }

    meshData->writeTo(bufferData);
    stagingBuffer->unmap();

    // Create an empty target buffer
    vertexIndexBuffer = new DataBuffer(context,
                                       VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                         VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferSize);
    if (!vertexIndexBuffer->isValid())
    {
      valid = false;
      return;
    }

    // Copy from the staging to the target buffer
    if (!stagingBuffer->copyTo(*vertexIndexBuffer, renderProcesses.at(0u)->getCommandBuffer(),
                               context->getVkDrawQueue()))
    {
      valid = false;
      return;
    }

    // Clean up the staging buffer
    delete stagingBuffer;
  }

  indexOffset = meshData->getIndexOffset();
}

Renderer::~Renderer()
{
  delete vertexIndexBuffer;
  
  for (size_t i = 0; i<pipelines.size(); i++) {
    //vkDestroyPipeline(device, materials[i]->pipeline, nullptr);
    delete pipelines[i];
  }

  const VkDevice device = context->getVkDevice();
  if (device)
  {

    if (pipelineLayout)
    {
      vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    }

    if (descriptorSetLayout)
    {
      vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    }

    if (descriptorPool)
    {
      vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    }
  }

  for (const RenderProcess* renderProcess : renderProcesses)
  {
    delete renderProcess;
  }

  if (device && commandPool)
  {
    vkDestroyCommandPool(device, commandPool, nullptr);
  }
}

// returns i of pipeline vectors, or -1 if a pipeline for these shaders hasn't been created yet.
const int Renderer::findExistingPipeline(const std::string& vertShader, const std::string& fragShader, const PipelineMaterialPayload& pipelineData) const{
  for(size_t i = 0; i< pipelines.size(); i++){
    if(pipelines[i]->getVertShaderName() == vertShader &&
      pipelines[i]->getFragShaderName() == fragShader
      ){
        if(pipelineData == pipelines[i]->getPipelineMaterialData()){
          return (int)i;
        }
        
    }
  }
  return -1;
}

void Renderer::render(const glm::mat4& cameraMatrix, size_t swapchainImageIndex, float time)
{
  currentRenderProcessIndex = (currentRenderProcessIndex + 1u) % renderProcesses.size();

  RenderProcess* renderProcess = renderProcesses.at(currentRenderProcessIndex);

  const VkDevice device = context->getVkDevice();
  const VkFence busyFence = renderProcess->getBusyFence();

  // Wait until the render process is free to use again
  if (vkWaitForFences(device, 1u, &busyFence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
  {
    return;
  }

  if (vkResetFences(device, 1u, &busyFence) != VK_SUCCESS)
  {
    return;
  }

  const VkCommandBuffer commandBuffer = renderProcess->getCommandBuffer();
  if (vkResetCommandBuffer(commandBuffer, 0u) != VK_SUCCESS)
  {
    return;
  }

  VkCommandBufferBeginInfo commandBufferBeginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
  if (vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
  {
    return;
  }

  // Update the uniform buffer data
  {
    for (size_t goIndex = 0u; goIndex < gameObjects.size(); ++goIndex)
    {
      renderProcess->dynamicVertexUniformData[goIndex].worldMatrix = gameObjects.at(goIndex)->worldMatrix;
      renderProcess->dynamicVertexUniformData[goIndex].colorMultiplier = gameObjects.at(goIndex)->material->dynamicUniformData.colorMultiplier;
    }

    for (size_t eyeIndex = 0u; eyeIndex < headset->getEyeCount(); ++eyeIndex)
    {
      renderProcess->staticVertexUniformData.viewProjectionMatrices.at(eyeIndex) =
        headset->getEyeProjectionMatrix(eyeIndex) * headset->getEyeViewMatrix(eyeIndex) * cameraMatrix;
    }

    renderProcess->staticFragmentUniformData.time = time;

    renderProcess->updateUniformBufferData();
  }

  const std::array clearValues = { VkClearValue({ 0.01f, 0.01f, 0.01f, 1.0f }), VkClearValue({ 1.0f, 0u }) };

  VkRenderPassBeginInfo renderPassBeginInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
  renderPassBeginInfo.renderPass = headset->getVkRenderPass();
  renderPassBeginInfo.framebuffer = headset->getRenderTarget(swapchainImageIndex)->getFramebuffer();
  renderPassBeginInfo.renderArea.offset = { 0, 0 };
  renderPassBeginInfo.renderArea.extent = headset->getEyeResolution(0u);
  renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassBeginInfo.pClearValues = clearValues.data();

  vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

  // Set the viewport
  VkViewport viewport;
  viewport.x = static_cast<float>(renderPassBeginInfo.renderArea.offset.x);
  viewport.y = static_cast<float>(renderPassBeginInfo.renderArea.offset.y);
  viewport.width = static_cast<float>(renderPassBeginInfo.renderArea.extent.width);
  viewport.height = static_cast<float>(renderPassBeginInfo.renderArea.extent.height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(commandBuffer, 0u, 1u, &viewport);

  // Set the scissor
  VkRect2D scissor;
  scissor.offset = renderPassBeginInfo.renderArea.offset;
  scissor.extent = renderPassBeginInfo.renderArea.extent;
  vkCmdSetScissor(commandBuffer, 0u, 1u, &scissor);

  // Bind the vertex section of the geometry buffer
  VkDeviceSize vertexOffset = 0u;
  const VkBuffer buffer = vertexIndexBuffer->getBuffer();
  vkCmdBindVertexBuffers(commandBuffer, 0u, 1u, &buffer, &vertexOffset);

  // Bind the index section of the geometry buffer
  vkCmdBindIndexBuffer(commandBuffer, buffer, indexOffset, VK_INDEX_TYPE_UINT32);

  // Draw each model
  const VkDescriptorSet descriptorSet = renderProcess->getDescriptorSet();
  for (size_t goIndex = 0u; goIndex < gameObjects.size(); ++goIndex)
  {
    const GameObject* gameObject = gameObjects.at(goIndex);
    //std::printf("\n[Renderer][log] render() goIndex: {%d}, go.name: {%s}", goIndex, gameObject->name.c_str());
    if(!gameObject->isVisible)
      continue;

    // Bind the uniform buffer for per model/mesh dynamic, vertex
    const uint32_t uniformBufferOffset =
      static_cast<uint32_t>(util::align(static_cast<VkDeviceSize>(sizeof(RenderProcess::DynamicVertexUniformData)),
                                        context->getUniformBufferOffsetAlignment()) *
                            static_cast<VkDeviceSize>(goIndex)); 
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0u, 1u, &descriptorSet, 1u,
                            &uniformBufferOffset);

    // TODO: bind the DynamicMaterialxUniformData somehow... "per pipeline" uniform data...

    // [tdbe] fetch the material for this GO and bind its "pipeline" to the command buffer.
    gameObject->material->pipeline->bindPipeline(commandBuffer);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(gameObject->model->indexCount), 1u,
                     static_cast<uint32_t>(gameObject->model->firstIndex), 0u, 0u);
  }

  vkCmdEndRenderPass(commandBuffer);
}

void Renderer::submit(bool useSemaphores) const
{
  const RenderProcess* renderProcess = renderProcesses.at(currentRenderProcessIndex);
  const VkCommandBuffer commandBuffer = renderProcess->getCommandBuffer();

  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
  {
    return;
  }

  constexpr VkPipelineStageFlags waitStages = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
  const VkSemaphore drawableSemaphore = renderProcess->getDrawableSemaphore();
  const VkSemaphore presentableSemaphore = renderProcess->getPresentableSemaphore();

  VkSubmitInfo submitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };
  submitInfo.pWaitDstStageMask = &waitStages;
  submitInfo.commandBufferCount = 1u;
  submitInfo.pCommandBuffers = &commandBuffer;

  if (useSemaphores)
  {
    submitInfo.waitSemaphoreCount = 1u;
    submitInfo.pWaitSemaphores = &drawableSemaphore;
    submitInfo.signalSemaphoreCount = 1u;
    submitInfo.pSignalSemaphores = &presentableSemaphore;
  }

  const VkFence busyFence = renderProcess->getBusyFence();
  if (vkQueueSubmit(context->getVkDrawQueue(), 1u, &submitInfo, busyFence) != VK_SUCCESS)
  {
    return;
  }
}

bool Renderer::isValid() const
{
  return valid;
}

VkCommandBuffer Renderer::getCurrentCommandBuffer() const
{
  return renderProcesses.at(currentRenderProcessIndex)->getCommandBuffer();
}

VkSemaphore Renderer::getCurrentDrawableSemaphore() const
{
  return renderProcesses.at(currentRenderProcessIndex)->getDrawableSemaphore();
}

VkSemaphore Renderer::getCurrentPresentableSemaphore() const
{
  return renderProcesses.at(currentRenderProcessIndex)->getPresentableSemaphore();
}