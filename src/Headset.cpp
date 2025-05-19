#include "Headset.h"

#include "Context.h"
#include "ImageBuffer.h"
#include "RenderTarget.h"
#include "Util.h"

#include <glm/mat4x4.hpp>

#include <array>

#if DEBUG
  #include <sstream>
#endif

namespace
{
constexpr XrReferenceSpaceType STAGE_SPACE_TYPE = XR_REFERENCE_SPACE_TYPE_STAGE;
constexpr XrReferenceSpaceType LOCAL_SPACE_TYPE = XR_REFERENCE_SPACE_TYPE_LOCAL;
constexpr XrReferenceSpaceType VIEW_SPACE_TYPE = XR_REFERENCE_SPACE_TYPE_VIEW;
constexpr VkFormat COLOR_FORMAT = VK_FORMAT_R8G8B8A8_SRGB;//_RGBA8UnormSrgb//_RGBA8UnormSrgb
constexpr VkFormat DEPTH_FORMAT = VK_FORMAT_D32_SFLOAT;
} // namespace

Headset::Headset(const Context* context) : context(context)
{
  const VkDevice device = context->getVkDevice();
  const VkSampleCountFlagBits multisampleCount = context->getMultisampleCount();
  xrReferenceSpacePose = util::makeIdentity();

  // Create a render pass
  {
    constexpr uint32_t viewMask = 0b00000011;
    constexpr uint32_t correlationMask = 0b00000011;

    // [tdbe] Single pass / multiview explanation:
    // [tdbe] We feed this multiview create info into the regular vk render pass creation.
    // [tdbe] Vulklan will execute the render pipeline twice (or whatever number is in pViewMasks)
    // [tdbe] To use multiview, in the shader you enable the GL_EXT_multiview extension, and then
    // [tdbe] get a glViewIndex depending on what multiview view you are about to output to. So you
    // [tdbe] can use e.g. an array of transformation matrixes indexed by this.
    VkRenderPassMultiviewCreateInfo renderPassMultiviewCreateInfo{
      VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO
    };
    renderPassMultiviewCreateInfo.subpassCount = 1u;
    renderPassMultiviewCreateInfo.pViewMasks = &viewMask;
    renderPassMultiviewCreateInfo.correlationMaskCount = 1u;
    renderPassMultiviewCreateInfo.pCorrelationMasks = &correlationMask;

    VkAttachmentDescription colorAttachmentDescription{};
    colorAttachmentDescription.format = COLOR_FORMAT;
    colorAttachmentDescription.samples = multisampleCount;
    colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorAttachmentReference;
    colorAttachmentReference.attachment = 0u;
    colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentDescription depthAttachmentDescription{};
    depthAttachmentDescription.format = DEPTH_FORMAT;
    depthAttachmentDescription.samples = multisampleCount;
    depthAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentReference;
    depthAttachmentReference.attachment = 1u;
    depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentDescription resolveAttachmentDescription{};
    resolveAttachmentDescription.format = COLOR_FORMAT;
    resolveAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    resolveAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    resolveAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    resolveAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    resolveAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    resolveAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    resolveAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference resolveAttachmentReference;
    resolveAttachmentReference.attachment = 2u;
    resolveAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // This subpass dependency waits with the transition to the color attachment optimal layout that takes place when
    // calling vkCmdBeginRenderPass() until the draw calls in the render pass are in the appropriate pipeline stages
    VkSubpassDependency subpassDependencyRenderPassBegin;
    subpassDependencyRenderPassBegin.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    subpassDependencyRenderPassBegin.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencyRenderPassBegin.dstSubpass = 0;
    subpassDependencyRenderPassBegin.srcAccessMask = VK_ACCESS_NONE;
    subpassDependencyRenderPassBegin.dstAccessMask =
      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    subpassDependencyRenderPassBegin.srcStageMask =
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    subpassDependencyRenderPassBegin.dstStageMask =
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

    // This subpass dependency ensures that all color and depth/stencil attachment writes in the color attachment output
    // and late fragment tests stages have finished before any draw calls after vkCmdEndRenderPass() begin
    VkSubpassDependency subpassDependencyRenderPassEnd;
    subpassDependencyRenderPassEnd.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    subpassDependencyRenderPassEnd.srcSubpass = 0;
    subpassDependencyRenderPassEnd.dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencyRenderPassEnd.srcAccessMask =
      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    subpassDependencyRenderPassEnd.dstAccessMask = VK_ACCESS_NONE;
    subpassDependencyRenderPassEnd.srcStageMask =
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    subpassDependencyRenderPassEnd.dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

    VkSubpassDescription subpassDescription{};
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.colorAttachmentCount = 1u;
    subpassDescription.pColorAttachments = &colorAttachmentReference;
    subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;
    subpassDescription.pResolveAttachments = &resolveAttachmentReference;

    const std::array attachments = { colorAttachmentDescription, depthAttachmentDescription,
                                     resolveAttachmentDescription };

    const std::array subpassDependencies = { subpassDependencyRenderPassBegin, subpassDependencyRenderPassEnd };

    VkRenderPassCreateInfo renderPassCreateInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
    renderPassCreateInfo.pNext = &renderPassMultiviewCreateInfo;
    renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassCreateInfo.pAttachments = attachments.data();
    renderPassCreateInfo.subpassCount = 1u;
    renderPassCreateInfo.pSubpasses = &subpassDescription;
    renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(subpassDependencies.size());
    renderPassCreateInfo.pDependencies = subpassDependencies.data();
    if (vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
    {
      util::error(Error::GenericVulkan);
      valid = false;
      return;
    }

#ifdef DEBUG
    if (context->setDebugObjectName(reinterpret_cast<uint64_t>(renderPass), VK_OBJECT_TYPE_RENDER_PASS,
                                    "OXR_VK_X Render Pass") != VK_SUCCESS)
    {
      util::error(Error::GenericVulkan);
      valid = false;
      return;
    }
#endif
  }

  const XrInstance xrInstance = context->getXrInstance();
  const XrSystemId xrSystemId = context->getXrSystemId();
  const VkPhysicalDevice vkPhysicalDevice = context->getVkPhysicalDevice();
  const uint32_t vkDrawQueueFamilyIndex = context->getVkDrawQueueFamilyIndex();

  // Create a session with Vulkan graphics binding
  XrGraphicsBindingVulkan2KHR graphicsBinding{ XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR };
  graphicsBinding.device = device;
  graphicsBinding.instance = context->getVkInstance();
  graphicsBinding.physicalDevice = vkPhysicalDevice;
  graphicsBinding.queueFamilyIndex = vkDrawQueueFamilyIndex;
  graphicsBinding.queueIndex = 0u;

  XrSessionCreateInfo sessionCreateInfo{ XR_TYPE_SESSION_CREATE_INFO };
  sessionCreateInfo.next = &graphicsBinding;
  sessionCreateInfo.systemId = xrSystemId;
  XrResult result = xrCreateSession(xrInstance, &sessionCreateInfo, &session);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    valid = false;
    return;
  }
  
  result = createReferenceSpaces(result);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    valid = false;
    return;
  }

  const XrViewConfigurationType viewType = context->getXrViewType();

  // Get the number of eyes
  result = xrEnumerateViewConfigurationViews(xrInstance, xrSystemId, viewType, 0u,
                                             reinterpret_cast<uint32_t*>(&eyeCount), nullptr);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    valid = false;
    return;
  }

  // Get the eye image info per eye
  eyeImageInfos.resize(eyeCount);
  for (XrViewConfigurationView& eyeInfo : eyeImageInfos)
  {
    eyeInfo.type = XR_TYPE_VIEW_CONFIGURATION_VIEW;
    eyeInfo.next = nullptr;
  }

  result =
    xrEnumerateViewConfigurationViews(xrInstance, xrSystemId, viewType, static_cast<uint32_t>(eyeImageInfos.size()),
                                      reinterpret_cast<uint32_t*>(&eyeCount), eyeImageInfos.data());
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    valid = false;
    return;
  }

  // Allocate the eye poses
  eyePoses.resize(eyeCount);
  for (XrView& eyePose : eyePoses)
  {
    eyePose.type = XR_TYPE_VIEW;
    eyePose.next = nullptr;
  }

  // Verify that the desired color format is supported
  {
    uint32_t formatCount = 0u;
    result = xrEnumerateSwapchainFormats(session, 0u, &formatCount, nullptr);
    if (XR_FAILED(result))
    {
      util::error(Error::GenericOpenXR);
      valid = false;
      return;
    }

    std::vector<int64_t> formats(formatCount);
    result = xrEnumerateSwapchainFormats(session, formatCount, &formatCount, formats.data());
    if (XR_FAILED(result))
    {
      util::error(Error::GenericOpenXR);
      valid = false;
      return;
    }

    bool formatFound = false;
    for (const int64_t& format : formats)
    {
      if (format == static_cast<int64_t>(COLOR_FORMAT))
      {
        formatFound = true;
        break;
      }
    }

    if (!formatFound)
    {
      util::error(Error::FeatureNotSupported, "OpenXR swapchain color format");
      valid = false;
      return;
    }
  }

  const VkExtent2D eyeResolution = getEyeResolution(0u);

  // Create a color buffer
  colorBuffer = new ImageBuffer(context, eyeResolution, COLOR_FORMAT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                                context->getMultisampleCount(), VK_IMAGE_ASPECT_COLOR_BIT, 2u);
  if (!colorBuffer->isValid())
  {
    valid = false;
    return;
  }

  // Create a depth buffer
  // [tdbe] Note: the depth buffer is not necessary. I guess it's used for passthrough or other xr depth effects,
  // [tdbe] but it's not required for rendering geometry to the headset color buffer. (It's not "the" depth buffer.)
  depthBuffer = new ImageBuffer(context, eyeResolution, DEPTH_FORMAT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                                context->getMultisampleCount(), VK_IMAGE_ASPECT_DEPTH_BIT, 2u);
  if (!depthBuffer->isValid())
  {
    valid = false;
    return;
  }

  // Create a swapchain and render targets
  // [tdbe] Because we're rendering in singlepass / multiview, we create just one swapchain. But it has 2 images (layers).
  {
    const XrViewConfigurationView& eyeImageInfo = eyeImageInfos.at(0u);

    // Create a swapchain
    XrSwapchainCreateInfo swapchainCreateInfo{ XR_TYPE_SWAPCHAIN_CREATE_INFO };
    swapchainCreateInfo.format = COLOR_FORMAT;
    swapchainCreateInfo.sampleCount = eyeImageInfo.recommendedSwapchainSampleCount;
    swapchainCreateInfo.width = eyeImageInfo.recommendedImageRectWidth;
    swapchainCreateInfo.height = eyeImageInfo.recommendedImageRectHeight;
    swapchainCreateInfo.arraySize = static_cast<uint32_t>(eyeCount);// [tdbe] e.g. swapchain image layer array count: 2
    swapchainCreateInfo.faceCount = 1u;
    swapchainCreateInfo.mipCount = 1u;
    swapchainCreateInfo.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT | XR_SWAPCHAIN_USAGE_TRANSFER_SRC_BIT;

    result = xrCreateSwapchain(session, &swapchainCreateInfo, &swapchain);
    if (XR_FAILED(result))
    {
      util::error(Error::GenericOpenXR);
      valid = false;
      return;
    }

    // Get the number of swapchain images
    // [tdbe] We do have 1 swapchain image, within the just 1 swapchain. 
    // [tdbe] And we also have 1 multiview image, with 2 layers.
    // [tdbe] HOWEVER, we need to use xrEnumerateSwapchainImages. Which creates 2 XR swapchain images.
    // [tdbe] What we do is we bind these 2 openxr swapchain images, to the 2 layers of the multiview image. 🙂
    uint32_t swapchainImageCount;
    result = xrEnumerateSwapchainImages(swapchain, 0u, &swapchainImageCount, nullptr);
    if (XR_FAILED(result))
    {
      util::error(Error::GenericOpenXR);
      valid = false;
      return;
    }

    // Retrieve the swapchain images
    // [tdbe] 1 for every openxr swapchain image / layer.
    std::vector<XrSwapchainImageVulkanKHR> swapchainImages;
    swapchainImages.resize(swapchainImageCount);
    for (XrSwapchainImageVulkan2KHR& swapchainImage : swapchainImages)
    {
      swapchainImage.type = XR_TYPE_SWAPCHAIN_IMAGE_VULKAN2_KHR;
    }

    XrSwapchainImageBaseHeader* data = reinterpret_cast<XrSwapchainImageBaseHeader*>(swapchainImages.data());
    result =
      xrEnumerateSwapchainImages(swapchain, static_cast<uint32_t>(swapchainImages.size()), &swapchainImageCount, data);
    if (XR_FAILED(result))
    {
      util::error(Error::GenericOpenXR);
      valid = false;
      return;
    }

    // Create the render targets
    swapchainRenderTargets.resize(swapchainImages.size());
    // [tdbe] Again, the renderTarget / xr image pairs correspond to the vulkan swapchain layers we created earlier.
    // [tdbe] Multiple redertargets set up this way will use the same render pass.
    for (size_t renderTargetIndex = 0u; renderTargetIndex < swapchainRenderTargets.size(); ++renderTargetIndex)
    {
      RenderTarget*& renderTarget = swapchainRenderTargets.at(renderTargetIndex);

      const VkImage image = swapchainImages.at(renderTargetIndex).image;
      renderTarget = new RenderTarget(device, image, colorBuffer->getImageView(), depthBuffer->getImageView(),
                                      eyeResolution, COLOR_FORMAT, renderPass, 2u);
      if (!renderTarget->isValid())
      {
        valid = false;
        return;
      }

#ifdef DEBUG
      std::stringstream s;
      s << "OXR_VK_X Headset Swapchain Image #" << renderTargetIndex;
      if (context->setDebugObjectName(reinterpret_cast<uint64_t>(image), VK_OBJECT_TYPE_IMAGE, s.str()) != VK_SUCCESS)
      {
        util::error(Error::GenericVulkan);
        valid = false;
        return;
      }
#endif
    }
  }

  // Create the eye render infos
  eyeRenderInfos.resize(eyeCount);
  for (size_t eyeIndex = 0u; eyeIndex < eyeRenderInfos.size(); ++eyeIndex)
  {
    XrCompositionLayerProjectionView& eyeRenderInfo = eyeRenderInfos.at(eyeIndex);
    eyeRenderInfo.type = XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW;
    eyeRenderInfo.next = nullptr;

    // Associate this eye with the swapchain
    const XrViewConfigurationView& eyeImageInfo = eyeImageInfos.at(eyeIndex);
    eyeRenderInfo.subImage.swapchain = swapchain;
    eyeRenderInfo.subImage.imageArrayIndex = static_cast<uint32_t>(eyeIndex);
    eyeRenderInfo.subImage.imageRect.offset = { 0, 0 };
    eyeRenderInfo.subImage.imageRect.extent = { static_cast<int32_t>(eyeImageInfo.recommendedImageRectWidth),
                                                static_cast<int32_t>(eyeImageInfo.recommendedImageRectHeight) };
  }

  // Allocate view and projection Matrixes
  eyeViewMatrixes.resize(eyeCount);
  eyeProjectionMatrixes.resize(eyeCount);
}

Headset::~Headset()
{
  // Clean up OpenXR
  if (session)
  {
    xrEndSession(session);
  }

  if (swapchain)
  {
    xrDestroySwapchain(swapchain);
  }

  for (const RenderTarget* renderTarget : swapchainRenderTargets)
  {
    delete renderTarget;
  }

  if (game_world_stage_space != NULL)
  {
    xrDestroySpace(game_world_stage_space);
  }

  if (session)
  {
    xrDestroySession(session);
  }

  // Clean up Vulkan
  if (depthBuffer)
  {
    delete depthBuffer;
  }

  if (colorBuffer)
  {
    delete colorBuffer;
  }

  const VkDevice vkDevice = context->getVkDevice();
  if (vkDevice && renderPass)
  {
    vkDestroyRenderPass(vkDevice, renderPass, nullptr);
  }
}

/// <summary>
/// <see cref="createReferenceSpaces"/>
/// </summary>
void Headset::reCreateReferenceSpaces()
{
  if (game_world_stage_space != NULL)
    xrDestroySpace(game_world_stage_space);
  createReferenceSpaces(XR_SUCCESS);
}

/// <summary>
/// [tdbe] Create a play space
/// [tdbe] This is a reference space. There are multiple XrReferenceSpaceType's
/// [tdbe] e.g. XR_REFERENCE_SPACE_TYPE_VIEW, XR_REFERENCE_SPACE_TYPE_LOCAL, XR_REFERENCE_SPACE_TYPE_STAGE
/// [tdbe] and they're used for positional information.
/// [tdbe] "stage_space" means worldspace but it's meant to represent your IRL walkable area e.g. floor rectangle.
/// </summary>
XrResult Headset::createReferenceSpaces(XrResult result)
{
  XrReferenceSpaceCreateInfo referenceSpaceCreateInfo{ XR_TYPE_REFERENCE_SPACE_CREATE_INFO };
  referenceSpaceCreateInfo.referenceSpaceType = STAGE_SPACE_TYPE;
  referenceSpaceCreateInfo.poseInReferenceSpace = xrReferenceSpacePose;
  result = xrCreateReferenceSpace(session, &referenceSpaceCreateInfo, &game_world_stage_space);
  if (XR_FAILED(result))
  {
    return result;
  }
  // [tdbe] can also (re)create other (stage/local/view) spaces here.
  
  return result;
}

Headset::BeginFrameResult Headset::beginFrame(uint32_t& swapchainImageIndex) 
{
  const XrInstance instance = context->getXrInstance();

  // Poll OpenXR events
  XrEventDataBuffer buffer{ XR_TYPE_EVENT_DATA_BUFFER };
  while (xrPollEvent(instance, &buffer) == XR_SUCCESS)
  {
    switch (buffer.type)
    {
    case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
      exitRequested = true;
      return BeginFrameResult::SkipFully;
    case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED:
    {
      XrEventDataSessionStateChanged* event = reinterpret_cast<XrEventDataSessionStateChanged*>(&buffer);
      sessionState = event->state;

      if (event->state == XR_SESSION_STATE_READY)
      {
        if (!beginSession())
        {
          return BeginFrameResult::Error;
        }
      }
      else if (event->state == XR_SESSION_STATE_STOPPING)
      {
        if (!endSession())
        {
          return BeginFrameResult::Error;
        }
      }
      else if (event->state == XR_SESSION_STATE_LOSS_PENDING || event->state == XR_SESSION_STATE_EXITING)
      {
        exitRequested = true;
        return BeginFrameResult::SkipFully;
      }

      break;
    }
    }

    buffer.type = XR_TYPE_EVENT_DATA_BUFFER;
  }

  if (sessionState != XR_SESSION_STATE_READY && sessionState != XR_SESSION_STATE_SYNCHRONIZED &&
      sessionState != XR_SESSION_STATE_VISIBLE && sessionState != XR_SESSION_STATE_FOCUSED)
  {
    // If we are not ready, synchronized, visible or focused, we skip all processing of this frame
    // This means no waiting, no beginning or ending of the frame at all
    return BeginFrameResult::SkipFully;
  }

  // Wait for the new frame
  frameState.type = XR_TYPE_FRAME_STATE;
  XrFrameWaitInfo frameWaitInfo{ XR_TYPE_FRAME_WAIT_INFO };
  // [tdbe] xrWaitFrame gets the predictedDisplayTime to sync spaces and poses
  XrResult result = xrWaitFrame(session, &frameWaitInfo, &frameState);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  // Begin the new frame
  XrFrameBeginInfo frameBeginInfo{ XR_TYPE_FRAME_BEGIN_INFO };
  result = xrBeginFrame(session, &frameBeginInfo);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  // Update the eye poses
  viewState.type = XR_TYPE_VIEW_STATE;
  uint32_t viewCount;
  XrViewLocateInfo viewLocateInfo{ XR_TYPE_VIEW_LOCATE_INFO };
  viewLocateInfo.viewConfigurationType = context->getXrViewType();
  viewLocateInfo.displayTime = frameState.predictedDisplayTime;
  viewLocateInfo.space = game_world_stage_space;
  result = xrLocateViews(session, &viewLocateInfo, &viewState, static_cast<uint32_t>(eyePoses.size()), &viewCount,
                         eyePoses.data());
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  if (viewCount != eyeCount)
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  if ((viewState.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) == 0)
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  if ((viewState.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) == 0)
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  // Update the eye render infos, view and projection Matrixes
  for (size_t eyeIndex = 0u; eyeIndex < eyeCount; ++eyeIndex)
  {
    // Copy the eye poses into the eye render infos
    XrCompositionLayerProjectionView& eyeRenderInfo = eyeRenderInfos.at(eyeIndex);
    const XrView& eyePose = eyePoses.at(eyeIndex);
    eyeRenderInfo.pose = eyePose.pose;
    eyeRenderInfo.fov = eyePose.fov;

    // Update the view and projection Matrixes
    const XrPosef& pose = eyeRenderInfo.pose;
    eyeViewMatrixes.at(eyeIndex) = glm::inverse(util::poseToMatrix(pose));
    eyeProjectionMatrixes.at(eyeIndex) = util::createProjectionMatrix(eyeRenderInfo.fov, 0.01f, 250.0f);
  }

  // Acquire the swapchain image
  XrSwapchainImageAcquireInfo swapchainImageAcquireInfo{ XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO };
  result = xrAcquireSwapchainImage(swapchain, &swapchainImageAcquireInfo, &swapchainImageIndex);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  // Wait for the swapchain image
  XrSwapchainImageWaitInfo swapchainImageWaitInfo{ XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO };
  swapchainImageWaitInfo.timeout = XR_INFINITE_DURATION;
  result = xrWaitSwapchainImage(swapchain, &swapchainImageWaitInfo);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return BeginFrameResult::Error;
  }

  if (!frameState.shouldRender)
  {
    return BeginFrameResult::SkipRender;
  }

  return BeginFrameResult::RenderFully;
}

void Headset::endFrame() const
{
  // Release the swapchain image
  XrSwapchainImageReleaseInfo swapchainImageReleaseInfo{ XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO };
  XrResult result = xrReleaseSwapchainImage(swapchain, &swapchainImageReleaseInfo);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return;
  }

  // End the frame
  XrCompositionLayerProjection compositionLayerProjection{ XR_TYPE_COMPOSITION_LAYER_PROJECTION };
  compositionLayerProjection.space = game_world_stage_space;
  compositionLayerProjection.viewCount = static_cast<uint32_t>(eyeRenderInfos.size());
  compositionLayerProjection.views = eyeRenderInfos.data();

  std::vector<XrCompositionLayerBaseHeader*> layers;
  if (frameState.shouldRender)
  {
    layers.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>(&compositionLayerProjection));
  }

  XrFrameEndInfo frameEndInfo{ XR_TYPE_FRAME_END_INFO };
  frameEndInfo.displayTime = frameState.predictedDisplayTime;
  frameEndInfo.layerCount = static_cast<uint32_t>(layers.size());
  frameEndInfo.layers = layers.data();
  frameEndInfo.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
  result = xrEndFrame(session, &frameEndInfo);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return;
  }
}

bool Headset::isValid() const
{
  return valid;
}

bool Headset::isExitRequested() const
{
  return exitRequested;
}

XrSession Headset::getXrSession() const
{
  return session;
}

XrSpace Headset::getXrSpace() const
{
  return game_world_stage_space;
}

XrFrameState Headset::getXrFrameState() const
{
  return frameState;
}

VkRenderPass Headset::getVkRenderPass() const
{
  return renderPass;
}

size_t Headset::getEyeCount() const
{
  return eyeCount;
}

VkExtent2D Headset::getEyeResolution(size_t eyeIndex) const
{
  const XrViewConfigurationView& eyeInfo = eyeImageInfos.at(eyeIndex);
  return { eyeInfo.recommendedImageRectWidth, eyeInfo.recommendedImageRectHeight };
}

glm::mat4 Headset::getEyeViewMatrix(size_t eyeIndex) const
{
  return eyeViewMatrixes.at(eyeIndex);
}

glm::mat4 Headset::getEyeProjectionMatrix(size_t eyeIndex) const
{
  return eyeProjectionMatrixes.at(eyeIndex);
}

std::vector<XrView> Headset::getEyePoses() const
{
  return eyePoses;
}

XrPosef Headset::getXrReferenceSpacePose() const
{
  return xrReferenceSpacePose;
}

/// <summary>
/// [tdbe] Use this to recreate the (stage) space at runtime to move the stage.
/// </summary>
/// <param name="newPose">Typically the value of <see cref="getXrReferenceSpacePose"/> plus some offset you
/// add.</param>
void Headset::setXrReferenceSpacePose(glm::mat4 newWorldPoseMatrix)
{
  xrReferenceSpacePose = util::matrixToPose(newWorldPoseMatrix);
  reCreateReferenceSpaces();
}

XrSessionState Headset::getSessionState() const
{
  return sessionState;
}

RenderTarget* Headset::getRenderTarget(size_t swapchainImageIndex) const
{
  return swapchainRenderTargets.at(swapchainImageIndex);
}

bool Headset::beginSession() const
{
  // Start the session
  XrSessionBeginInfo sessionBeginInfo{ XR_TYPE_SESSION_BEGIN_INFO };
  sessionBeginInfo.primaryViewConfigurationType = context->getXrViewType();
  const XrResult result = xrBeginSession(session, &sessionBeginInfo);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return false;
  }

  return true;
}

bool Headset::endSession() const
{
  // End the session
  const XrResult result = xrEndSession(session);
  if (XR_FAILED(result))
  {
    util::error(Error::GenericOpenXR);
    return false;
  }

  return true;
}