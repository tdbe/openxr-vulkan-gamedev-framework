#pragma once
#include <array>
#include <stdio.h>

#include "../Utils/Util.h"
#include "Renderer.h"
#include "../OpenXrInput/InputData.h"
#include "Context.h"
#include "Headset.h"
#include "../GameData/MeshData.h"
#include "Pipeline.h"
#include "RenderProcess.h"
#include "RenderTarget.h"

#include "../GameData/GameData.h"
#include "../GameData/Components/Transform.h"
#include "../GameData/Components/Material.h"
#include "../GameData/Components/Light.h"
#include "../GameData/Entities/GameEntityObject.h"
#include "../OpenXrAndVulkan/DataBuffer.h"

using namespace Game;

Renderer::Renderer(const Context* context,
                   const Headset* headset)
: context(context), headset(headset)
{
    const VkDevice device = context->getVkDevice();

    // Create a command pool
    VkCommandPoolCreateInfo commandPoolCreateInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolCreateInfo.queueFamilyIndex = context->getVkDrawQueueFamilyIndex();
    if (vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        util::DebugError("[Renderer] can't vkCreateCommandPool!");
        util::LogError(Error::GenericVulkan);
        valid = false;
        return;
    }

    // Create a descriptor pool
    // [tdbe] we need something like a circular buffer of descriptorset data, to cover more than 1 frame in flight,
    // so the gpu can read one while the cpu is writing another
    std::array<VkDescriptorPoolSize, 2u> descriptorPoolSizes;

    descriptorPoolSizes.at(0u).type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    descriptorPoolSizes.at(0u).descriptorCount = static_cast<uint32_t>(framesInFlight);

    descriptorPoolSizes.at(1u).type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorPoolSizes.at(1u).descriptorCount = static_cast<uint32_t>(framesInFlight * 2u);

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
    descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
    descriptorPoolCreateInfo.pPoolSizes = descriptorPoolSizes.data();
    descriptorPoolCreateInfo.maxSets = static_cast<uint32_t>(framesInFlight);
    if (vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool) != VK_SUCCESS)
    {
        util::DebugError("[Renderer] can't vkCreateDescriptorPool!");
        valid = false;
        return;
    }

    // [tdbe] Pipelines in Vulkan:
    // [tdbe] Uness you are using some kind of large "Standard Shader" / "Uber Shader", you want to make one
    //        pipeline for each type of shader E.g. BRDF Opaque, Simple Transparent, etc. and describe:
    //        - the kind of data that goes into it. (descriptor set data)
    //        - the kind of vertex, index, vertex color etc input data
    //        - the way this shader is rendered (e.g. depth test, culling, blending, etc.)
    //        Make a pipeline for a shader (for one kind of vertex-fragment or render stage / subpass).
    //        A "Material" would belong to a pipeline (subscribe to a format of uniform buffers) and source 
    //        different data for the descriptor sets (ie properties (DynamicFragmentUniformData, 
    //        DynamicMaterialUniformData)). 
    //        
    //        If your material doesn't change the vertex or pipeline payload (e.g. blending), you can reuse an existing pipeline.
    //        My Material components can & do share pipelines, but I don't batch the drawcalls by pipeline, I batch by material. 
    //        (Which can be less efficient if you have many materials with the same pipeline but not next to each other in the 
    //        material data pool. But I do create them next to each other and their pipeline doesn't change across their lifetime.
    //        (To batch materials with out of order pipelines, in the material buffer, we'd need a way to sort them, e.g. a new 
    //        buffer just for pipelines, with Material children with game Entity owners... not worth it.))
    // 
    //        (Or you can also just raw-dog it and change pipelines and properties here and there while making your drawcalls 
    //        and not have any materials.)

    // Create a descriptor set layout
    std::array<VkDescriptorSetLayoutBinding, 4u> descriptorSetLayoutBindings;

    // [tdbe] NOTE: TODO: We also need a descriptor set layout that supports textures,
    // and a descriptor set per-material, (or descriptor set data per-materal),
    // to bind textures to each material.

    // [tdbe] TODO: create a per-material buffer for e.g. brdf, colors, textures etc

    // [tdbe] cross-shader global (pipeline/descriptorset wide) vertex static
    descriptorSetLayoutBindings.at(0u).binding = 0u;
    descriptorSetLayoutBindings.at(0u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetLayoutBindings.at(0u).descriptorCount = 1u;
    descriptorSetLayoutBindings.at(0u).stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetLayoutBindings.at(0u).pImmutableSamplers = nullptr;

    // [tdbe] cross-shader global (pipeline/descriptorset wide) fragment static
    descriptorSetLayoutBindings.at(1u).binding = 1u;
    descriptorSetLayoutBindings.at(1u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetLayoutBindings.at(1u).descriptorCount = 1u;
    descriptorSetLayoutBindings.at(1u).stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    descriptorSetLayoutBindings.at(1u).pImmutableSamplers = nullptr;

    // [tdbe] per model/mesh data, vertex dynamic;
    descriptorSetLayoutBindings.at(2u).binding = 2u;
    descriptorSetLayoutBindings.at(2u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    descriptorSetLayoutBindings.at(2u).descriptorCount = 1u;
    descriptorSetLayoutBindings.at(2u).stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetLayoutBindings.at(2u).pImmutableSamplers = nullptr;

    // [tdbe] per model/mesh data, fragment dynamic;
    descriptorSetLayoutBindings.at(3u).binding = 3u;
    descriptorSetLayoutBindings.at(3u).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    descriptorSetLayoutBindings.at(3u).descriptorCount = 1u;
    descriptorSetLayoutBindings.at(3u).stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    descriptorSetLayoutBindings.at(3u).pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO
    };
    descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(descriptorSetLayoutBindings.size());
    descriptorSetLayoutCreateInfo.pBindings = descriptorSetLayoutBindings.data();
    if (vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout) !=
        VK_SUCCESS)
    {
        util::DebugError("[Renderer] can't vkCreateDescriptorSetLayout!");
        valid = false;
        return;
    }

    // Create a pipeline layout
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
    pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutCreateInfo.setLayoutCount = 1u;
    if (vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
    {
        util::DebugError("[Renderer] can't vkCreatePipelineLayout!");
        valid = false;
        return;
    }

    /// Create a render process for each frame in flight.
    renderProcessesCircularBuffer.resize(framesInFlight);
    for (RenderProcess*& renderProcess : renderProcessesCircularBuffer)
    {
        renderProcess =
            new RenderProcess(context, commandPool, descriptorPool, descriptorSetLayout);
        if (!renderProcess->IsValid())
        {
            util::DebugError("[Renderer] can't create renderProcess!");
            valid = false;
            return;
        }
    }
}

/// [tdbe] we need a circular buffer of descriptorset data, to cover more than 1 frame in flight,
/// so the gpu can read one while the cpu is writing another.
/// The aim should always be to set up gpu bufferas once, with the max number of items you'll use in this game
/// world, the same idea as with the <see cref="GameDataPool"/>. (It doesn't cost gpu power to just have it there.)
void Renderer::SetUpRenderProcesses(const Game::MeshData* meshData,
                                     const GameDataPool<Material>* materials,
                                     const GameDataPool<GameEntityObject>* gameEntityObjects,
                                     const GameDataPool<GameEntityObject>* gameVFXObjects,
                                     const GameDataPool<Light>* gameLights)
{
    for (RenderProcess* renderProcess : renderProcessesCircularBuffer)
    {
        renderProcess->AllocateDescriptorSetsUniformBuffers(gameEntityObjects->MaxSize() + gameVFXObjects->MaxSize(), materials->MaxSize());
        if (!renderProcess->IsValid())
        {
            util::DebugError("[Renderer] can't AllocateDescriptorSetsUniformBuffers! entities: " +
                             util::ToString(gameEntityObjects->MaxSize() + gameVFXObjects->MaxSize()) +
                             "; materials: " + util::ToString(materials->MaxSize()));
            valid = false;
            return;
        }
    }

    // Create the pipeline
    VkVertexInputBindingDescription vertexInputBindingDescription;
    vertexInputBindingDescription.binding = 0u;
    vertexInputBindingDescription.stride = sizeof(Vertex);
    vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // [tdbe] This is where you bind mesh vertex uniform data for shader input
    // (e.g. vertex pos, vertex normal, vertex color, vertex texcoord/uv), and assign per-pipeline.
    // (for mesh vertices, not related to the properties uniform descriptor set layout above)
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

    VkVertexInputAttributeDescription vertexInputAttributeUv;
    vertexInputAttributeUv.binding = 0u;
    vertexInputAttributeUv.location = 3u;
    vertexInputAttributeUv.format = VK_FORMAT_R32G32_SFLOAT;
    vertexInputAttributeUv.offset = offsetof(Vertex, uv);

    PipelineMaterialPayload pipelineMaterialPayload = {};

    ClearPipelines();// [tdbe] it would be very weird to call this function more than once
    pipelines.resize(0);
    /* Manual creation:
    pipelines[0] = new Pipeline(context, pipelineLayout, headset->getVkRenderPass(), "shaders/Diffuse.vert.spv",
    "shaders/Diffuse.frag.spv", { vertexInputBindingDescription }, { vertexInputAttributePosition,
    vertexInputAttributeColor }, pipelineMaterialPayload);
    */
    for (int i = 0; i < materials->Size(); i++)
    {
        Material* mat = materials->items[i];
        if (mat->id.IsCleared())
            continue;
        // [tdbe] inefficient checking, but there aren't (ever) that many materials
        int pipelineExistsAt = findExistingPipeline(mat->vertShaderName, mat->fragShaderName, mat->pipelineData);
        // std::printf("[Renderer][log] pipelining materials: index: {%d}, shader.name: {%s}, exists: {%d}\n", i,
        // materials[i]->fragShaderName.c_str(), pipelineExistsAt );

        // [tdbe] specific pipeline:
        // if(i == 0){
        //  materials[i]->pipeline = pipelines[0];
        //} else

        if (pipelineExistsAt > -1)
        {
            mat->pipeline = pipelines[pipelineExistsAt];
        } // [tdbe] create a new pipeline from material shader name, with default parameters
        else
        {
            pipelines.emplace_back(
                new Pipeline(context, pipelineLayout, headset->getVkRenderPass(), 
                            mat->vertShaderName,
                            mat->fragShaderName, 
                            { vertexInputBindingDescription },
                            {   vertexInputAttributePosition, 
                                vertexInputAttributeNormal, 
                                vertexInputAttributeColor, 
                                vertexInputAttributeUv },                             
                            mat->pipelineData));
                            mat->pipeline = pipelines[pipelines.size() - 1];
        }

        if (!mat->pipeline->IsValid())
        {
            util::DebugError("[Renderer] can't create vk pipeline for material! pipelines.size(): " +
                             util::ToString(pipelines.size()) + "; mat->id: " + mat->id.PrintGlobalUID());
            valid = false;
            return;
        }
    }

    // Create a vertex index buffer
    {
        // Create a staging buffer
        size_t meshDataTotalSize = meshData->GetSize();
        util::DebugLog("[Renderer] meshDataTotalSize: " + util::ToString(meshDataTotalSize));
        const VkDeviceSize bufferSize = static_cast<VkDeviceSize>(meshDataTotalSize);
        DataBuffer* stagingBuffer =
            new DataBuffer(context, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, bufferSize);
        if (!stagingBuffer->IsValid())
        {
            util::DebugError("[Renderer] can't create staging buffer! bufferSize" + util::ToString(bufferSize));
            valid = false;
            return;
        }

        // Fill the staging buffer with vertex and index data
        char* bufferData = static_cast<char*>(stagingBuffer->map());
        if (!bufferData)
        {
            util::DebugError("[Renderer] can't map staging vertex & index data!");
            valid = false;
            return;
        }

        meshData->WriteTo(bufferData);
        stagingBuffer->unmap();
        // Create an empty target buffer
        delete vertexIndexBuffer;// [tdbe] it would be very weird to call this function more than once.
        vertexIndexBuffer = new DataBuffer(context,
                                           VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                               VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                           VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferSize);
        if (!vertexIndexBuffer->IsValid())
        {
            util::DebugError("[Renderer] could not create vertexIndexBuffer; bufferSize: " + util::ToString(bufferSize));
            valid = false;
            return;
        }
        // Copy from the staging to the target buffer
        if (!stagingBuffer->copyTo(*vertexIndexBuffer, renderProcessesCircularBuffer.at(0u)->GetCommandBuffer(),
                                   context->getVkDrawQueue()))
        {
            valid = false;
            return;
        }

        // Clean up the staging buffer
        delete stagingBuffer;
    }

    indexOffset = meshData->GetIndexOffset();
}

// returns i of pipeline vectors, or -1 if a pipeline for these shaders hasn't been created yet.
const int Renderer::findExistingPipeline(const std::string& vertShader,
                                         const std::string& fragShader,
                                         const PipelineMaterialPayload& pipelineData) const
{
    for (size_t i = 0; i < pipelines.size(); i++)
    {
        if (pipelines[i]->getVertShaderName() == vertShader && pipelines[i]->getFragShaderName() == fragShader)
        {
            if (pipelineData == pipelines[i]->getPipelineMaterialData())
            {
                return (int)i;
            }
        }
    }
    return -1;
}

/// [tdbe] Render. (The ideal is indirect rendering, and)
/// Prefer less drawcalls, less cpu-gpu communication:
/// - one draw call per material "instanced geometry" style,
/// - or one draw call per mesh but grouped by material.
void Renderer::Render(const glm::mat4& cameraMatrix,
                      size_t swapchainImageIndex,
                      float time,
                      const Inputspace::InputData& inputData,
                      const bool playerIsInChaperone,
                      const GameDataPool<Material>* materials,
                      const GameDataPool<GameEntityObject>* gameEntityObjects,
                      const GameDataPool<GameEntityObject>* gameVFXObjects,
                      const GameDataPool<Light>* gameLights)
{
    currentRenderProcessIndex = (currentRenderProcessIndex + 1u) % renderProcessesCircularBuffer.size();

    RenderProcess* renderProcess = renderProcessesCircularBuffer.at(currentRenderProcessIndex);

    const VkDevice device = context->getVkDevice();
    const VkFence busyFence = renderProcess->GetBusyFence();

    // Wait until the render process is free to use again
    // [tdbe] VKFences are like the vulkan semaphores but for GPU -> CPU synchronization instead of GPU-GPU
    // Similarly, use a fence to wait for the current frame to pass before e.g. updating its (uniform) buffer.
    if (vkWaitForFences(device, 1u, &busyFence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
    {
        return;
    }

    if (vkResetFences(device, 1u, &busyFence) != VK_SUCCESS)
    {
        return;
    }

    const VkCommandBuffer commandBuffer = renderProcess->GetCommandBuffer();
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
        for (size_t i = 0; i < gameEntityObjects->Size() + gameVFXObjects->Size(); i++)
        {
            size_t usedIdx = i;
            const GameEntityObject* gameObject;
            if (usedIdx < gameEntityObjects->Size())
            {
                gameObject = gameEntityObjects->items[usedIdx];
            }
            else
            {
                gameObject = gameVFXObjects->items[usedIdx - gameEntityObjects->Size()];
            }

            if (gameObject->id.IsCleared() || !gameObject->IsEnabled())
                continue;
            
            auto mats = gameObject->GetComponentsByTypeIndex<Material>();
            if (mats.size() == 0)
                continue;
            // [tdbe] Note: / future todo: although we don't want to multiple materials on the same entity, there's
            // an exception on the transparent materials (we render all the backfaces of all transparents
            // first, and then all the frontfaces). And the sky also has 2 materials.

            // [tdbe] We only save the non-pipeline data of the first available & visible material.
            // (as in we only push to the gpu, one slot per material-component-vector of the owner-entity).
            for(auto mat : mats)
            {
                // [tdbe] some entities might not (yet) have a material component.
                if (mat == nullptr) 
                    continue;
                if (!mat->IsVisible()) 
                    continue;
                // [tdbe] broadly speaking it's okay to skip^ pool elements, it's also the best average case performance.

                Transform* trans = gameObject->GetComponentByTypeIndex<Transform>();
                renderProcess->dynamicVertexUniformData[usedIdx].worldMatrix = trans->GetWorldMatrix();
                renderProcess->dynamicVertexUniformData[usedIdx].colorMultiplier =
                    mat->dynamicUniformData.colorMultiplier;
                renderProcess->dynamicVertexUniformData[usedIdx].instanceCount = (int)mat->instanceCount;
                renderProcess->dynamicVertexUniformData[usedIdx].perMaterialFlags =
                    mat->dynamicUniformData.perMaterialVertexFlags;
                // [tdbe] TODO: create a per-material buffer for e.g. brdf, colors, textures etc
                mat->dynamicUniformData.brdfData.y =
                    glm::clamp(mat->dynamicUniformData.brdfData.y, FROSTBITE_MIN_ROUGHNESS, 1.0f);
                renderProcess->dynamicFragmentUniformData[usedIdx].brdfData = mat->dynamicUniformData.brdfData;
                renderProcess->dynamicFragmentUniformData[usedIdx].ior = mat->dynamicUniformData.ior;
                renderProcess->dynamicFragmentUniformData[usedIdx].perMaterialFlags =
                    mat->dynamicUniformData.perMaterialFragmentFlags;
                break;
            }
        }

        float ipd = glm::distance(glm::vec3(renderProcess->staticVertexUniformData.viewMatrixes.at(0)[3]),
                      glm::vec3(renderProcess->staticVertexUniformData.viewMatrixes.at(
                          1)[3])); // [tdbe] TODO: is this the right way to get ipd? khronos forum trolls out there
                                   // gaslighting that there's no ipd in the api because "ipd isn't a thing any more";
                                   // but hu-mans still have 2 eyes, and in shaders I still want to know
                                   // how far away the other eye is.

        renderProcess->staticVertexUniformData.ipd = ipd;
        renderProcess->staticVertexUniformData.time = time;
        renderProcess->staticVertexUniformData.inLocomotion = (int)playerIsInChaperone;
        renderProcess->staticVertexUniformData.handsWorldMatrixes.at((int)Inputspace::ControllerEnum::LEFT) =
            cameraMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::LEFT];
        renderProcess->staticVertexUniformData.handsWorldMatrixes.at((int)Inputspace::ControllerEnum::RIGHT) =
            cameraMatrix * inputData.controllerAimPoseMatrixes[(int)Inputspace::ControllerEnum::RIGHT];
        auto eyePoses = headset->getEyePoses();
        glm::mat4 invCameraMatrix = glm::inverse(cameraMatrix);
        for (size_t eyeIndex = 0u; eyeIndex < headset->getEyeCount(); ++eyeIndex)
        {
            renderProcess->staticVertexUniformData.viewMatrixes.at(eyeIndex) =
                headset->getEyeViewMatrix(eyeIndex) * invCameraMatrix;
            glm::mat4 cam = cameraMatrix * inputData.eyePoseMatrixes[eyeIndex];
            renderProcess->staticVertexUniformData.cameraWorldMatrixes.at(eyeIndex) = cam;
            renderProcess->staticVertexUniformData.viewProjectionMatrixes.at(eyeIndex) =
                headset->getEyeProjectionMatrix(eyeIndex) * headset->getEyeViewMatrix(eyeIndex) * invCameraMatrix;
        }

        for (size_t i = 0; i < gameLights->Size(); i++)
        {
            Light* light = gameLights->items[i];
            if (light->id.IsCleared()) 
                continue;
            glm::mat4 matr = light->GetShaderMatrix();
            if (!light->IsVisible() || !light->GetOwner()->IsEnabled())
                matr[0].w = 0.0f;
            renderProcess->staticFragmentUniformData.lights[i] = matr;
        }

        renderProcess->staticFragmentUniformData.screenSizePixels =
            glm::vec2(headset->getEyeResolution(0).width, headset->getEyeResolution(0).height);
        renderProcess->staticFragmentUniformData.ipd = ipd;
        renderProcess->staticFragmentUniformData.time = time;

        renderProcess->UpdateUniformBufferData();
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

    // [tdbe] A refresher from 
    // https://stackoverflow.com/questions/42501912/can-someone-help-me-understand-viewport-scissor-renderarea-framebuffer-size
    /*
        Viewport: specifies how the normalized device coordinates are transformed into the 
        pixel coordinates of the framebuffer. The render commands will render within the 
        viewport. The other way around (render area smaller than the viewport) will result 
        in undefined values in the framebuffer.

        Scissor: is the area where you can render, this is similar to viewport in that regard 
        but changing the scissor rectangle doesn't affect the coordinates.

        RenderArea: is the area of the framebuffer that will be changed by the renderpass. 
        This lets the implementation know that not the entire frame buffer will be changed 
        and gives it opportunity to optimize by for example not including some tiles in 
        a tile based architecture. It is the application's responsibility that no rendering 
        happens outside that area, for example by making sure the scissor rects are always 
        fully contained within the renderArea.

        You can use multiple draw calls with different render areas and have things like 
        split screen or picture in picture.
    */

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

    // [tdbe] Drawcalls grouped per pipeline & material, then per model.
    // Indirect Rendering, anyone? 🙃 https://vkguide.dev/docs/gpudriven/gpu_driven_engines/
    const VkDescriptorSet descriptorSet = renderProcess->GetDescriptorSet();
    Pipeline* lastpip = nullptr;
    for (size_t i = 0; i < materials->Size(); i++)
    {
        Material* mat = materials->items[i];
        if (mat->id.IsCleared() || !mat->IsVisible())
            continue;

        Pipeline* pip = mat->pipeline;
        if (lastpip != pip)
        {
            // khronos: "Once bound, a pipeline binding affects subsequent commands that interact with the given
            // pipeline type in the command buffer until a different pipeline of the same type is bound to the bind
            // point, or until the pipeline bind point is disturbed by binding a shader object"
            mat->pipeline->bindPipeline(commandBuffer);
        }
        lastpip = pip;

        // [tdbe] TODO: create a per-material buffer for e.g. brdf, colors, textures etc.

        // [tdbe] now per entity object & model:
        auto entityOwnersOfMat = mat->GetOwners();
        for (int j = 0; j < entityOwnersOfMat.size(); j++)
        {
            GameEntity* ent = entityOwnersOfMat[j];
            if (ent->id.IsCleared() || !ent->IsEnabled())
                continue;

            // [tdbe] this index needs to match a gpu-friendly global entity index of all entity
            // buffers concatenated as we did when we updated the uniform buffer data above.
            // (todo: which is a bit annoying? we need to be aware of all (game)entity buffers)
            size_t usedIdx = ent->id.index;
            if (ent->id.globalUIDSeed == GameData::GlobalUIDSeeds.GAME_VFX_OBJECTS)
            {
                usedIdx = gameEntityObjects->Size() + ent->id.index;
            }

            // Bind the uniform buffer for per model/mesh dynamic, vertex
            // [tdbe] count for multiple dynamic buffers and offsets,
            // because we made e.g. a dynamic buffer for vertex * objects, and one for fragment * objects
            const uint32_t dynamicOffsetsCount = 2u;
            uint32_t uniformBufferDynamicOffsets[2];
            uniformBufferDynamicOffsets[0] = static_cast<uint32_t>(
                util::align(static_cast<VkDeviceSize>(sizeof(RenderProcess::DynamicVertexUniformData)),
                            context->getUniformBufferOffsetAlignment()) *
                static_cast<VkDeviceSize>(usedIdx));
            uniformBufferDynamicOffsets[1] = static_cast<uint32_t>(
                util::align(static_cast<VkDeviceSize>(sizeof(RenderProcess::DynamicFragmentUniformData)),
                            context->getUniformBufferOffsetAlignment()) *
                static_cast<VkDeviceSize>(usedIdx));
            // [tdbe] khronos: "Once bound, a descriptor set affects rendering of subsequent commands that interact
            // with the given pipeline type in the command buffer until either a different set is bound to the same set
            // number, or the set is disturbed"
            // TODO: Shouldn't the descriptorSet be optimized / split so we bind only the actual per-object dynamic descriptor/offsets 
            // here, and the more global ones further up e.g. per material?
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0u, 1u,
                                    &descriptorSet, dynamicOffsetsCount, uniformBufferDynamicOffsets);

            Model* model = ent->GetComponentByTypeIndex<Game::Model>();
            // [tdbe] the instance ID of the first instance to draw. (fed into gl_InstanceIndex in the vertex shader)
            uint32_t firstInstance;
            if (mat->instanceCount > 1)
                firstInstance = mat->firstInstance;
            else
                firstInstance = (uint32_t)j;// [tdbe] a nice hack to know in the shader the #'th mesh rendered with this material.

            // [tdbe] drawcall
            vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(model->indexCount), mat->instanceCount,
                             static_cast<uint32_t>(model->firstIndex), 0u, firstInstance);
        }
    }
    for (size_t i = 0; i < gameEntityObjects->Size() + gameVFXObjects->Size(); i++)
    {
        size_t usedIdx = i;
        const GameEntityObject* gameObject;
        if (usedIdx < gameEntityObjects->Size())
        {
            gameObject = gameEntityObjects->items[usedIdx];
        }
        else
        {
            usedIdx = usedIdx - gameEntityObjects->Size();
            gameObject = gameVFXObjects->items[usedIdx];
        }
        if (gameObject->id.IsCleared() || !gameObject->IsEnabled())
            continue;


        
    }

    vkCmdEndRenderPass(commandBuffer);
}

// [tdbe] in Vulkan, semaphores synchronize pending work queues on the GPU side only, GPU-GPU.
// Used to wait and sync the access to the gpu memory (uniform) buffer
void Renderer::submit(bool useSemaphores) const
{
    const RenderProcess* renderProcess = renderProcessesCircularBuffer.at(currentRenderProcessIndex);
    const VkCommandBuffer commandBuffer = renderProcess->GetCommandBuffer();

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        return;
    }

    constexpr VkPipelineStageFlags waitStages = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    const VkSemaphore drawableSemaphore = renderProcess->GetDrawableSemaphore();
    const VkSemaphore presentableSemaphore = renderProcess->GetPresentableSemaphore();

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

    const VkFence busyFence = renderProcess->GetBusyFence();
    if (vkQueueSubmit(context->getVkDrawQueue(), 1u, &submitInfo, busyFence) != VK_SUCCESS)
    {
        return;
    }
}

bool Renderer::IsValid() const
{
    return valid;
}

VkCommandBuffer Renderer::getCurrentCommandBuffer() const
{
    return renderProcessesCircularBuffer.at(currentRenderProcessIndex)->GetCommandBuffer();
}

VkSemaphore Renderer::getCurrentDrawableSemaphore() const
{
    return renderProcessesCircularBuffer.at(currentRenderProcessIndex)->GetDrawableSemaphore();
}

VkSemaphore Renderer::getCurrentPresentableSemaphore() const
{
    return renderProcessesCircularBuffer.at(currentRenderProcessIndex)->GetPresentableSemaphore();
}

void Renderer::ClearPipelines()
{
    for (size_t i = 0; i < pipelines.size(); i++)
    {
        // vkDestroyPipeline(device, materials[i]->pipeline, nullptr);
        delete pipelines[i];
    }
}

Renderer::~Renderer()
{
    delete vertexIndexBuffer;

    ClearPipelines();

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

    for (const RenderProcess* renderProcess : renderProcessesCircularBuffer)
    {
        delete renderProcess;
    }

    if (device && commandPool)
    {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }
}