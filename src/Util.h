#pragma once
#include <vulkan/vulkan.h>
#include <openxr/openxr.h>
#include <string>
#include <vector>

//#include <glm/glm.hpp>
#include <glm/vec3.hpp>
//#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> // tdbe gtx = "experimental"
//#include <glm/trigonometric.hpp>  // tdbe radians
//#include <glm/fwd.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/mat4x4.hpp>


// All the things that can go wrong
enum class Error
{
  FeatureNotSupported,
  FileMissing,
  GenericGLFW,
  GenericOpenXR,
  GenericVulkan,
  HeadsetNotConnected,
  ModelLoadingFailure,
  OutOfMemory,
  VulkanNotSupported,
  WindowFailure
};


/// [tdbe] Data structure utils for XR, input, gamedev, logging. 
/// Also some common gamedev math functions you can easily see & use. (on top of glm)
/// Todo: a bit of a mess, maybe have a separate proper glm extension util and a xr util etc.
  
namespace util
{
    typedef struct posef {
        glm::quat orientation;
        glm::vec3 position;
    } posef;


    std::string ToString(const bool& boolean, bool clean = false);
    //template <typename T, int size> std::string ToString(const glm::vec<size, T>& vec);
    // template <typename T, int rows, int cols> std::string ToString(const glm::mat<rows, cols, T>& mat);
    std::string ToString(const glm::mat4& mat);
    std::string ToString(const glm::vec4& vec);
    std::string ToString(const glm::vec3& vec);
    std::string ToString(const glm::vec2& vec);
    std::string ToString(const int16_t& number, bool clean = false);
    std::string ToString(const int& number, bool clean = false);
    std::string ToString(const size_t& number, bool clean = false);
    std::string ToString(const uint16_t& number, bool clean = false);
    std::string ToString(const uint32_t& number, bool clean = false);
    std::string ToString(const float& number, bool clean = false);
    std::string ToString(const double& number, bool clean = false);

    void DebugError(const std::string& details = "");

    void DebugLog(const std::string& details = "");

    // Reports an error with optional details through a system-native message box
    void LogError(Error error, const std::string& details = "");

    // Loads an OpenXR extension function by 'name' into 'function', returns false on error
    bool loadXrExtensionFunction(XrInstance instance, const std::string& name, PFN_xrVoidFunction* function);

    // Loads a Vulkan extension function by 'name', returns nullptr on error
    PFN_vkVoidFunction loadVkExtensionFunction(VkInstance instance, const std::string& name);

    // Unpacks a Vulkan or OpenXR extension list in a single string into a vector of c-style strings
    std::vector<const char*> unpackExtensionString(const std::string& string);

    // Loads a Vulkan shader from 'file' into 'shaderModule', returns false on error
    bool loadShaderFromFile(VkDevice device, const std::string& filename, VkShaderModule& shaderModule);

    // Finds a suitable Vulkan memory type index for given requirements and properties, returns false on error
    bool findSuitableMemoryTypeIndex(VkPhysicalDevice physicalDevice,
                                     VkMemoryRequirements requirements,
                                     VkMemoryPropertyFlags properties,
                                     uint32_t& typeIndex);
    // Aligns a value to an alignment
    VkDeviceSize align(VkDeviceSize value, VkDeviceSize alignment);

    // Creates an OpenXR path from a name string
    XrPath stringToPath(XrInstance instance, const std::string& string);

    // Creates an OpenXR action with a given names, returns false on error
    bool createAction(XrActionSet actionSet,
                      const std::vector<XrPath>& paths,
                      const std::string& actionName,
                      const std::string& localizedActionName,
                      XrActionType type,
                      XrAction& action);

    /// Creates an OpenXR identity pose
    XrPosef makeIdentity();

    /// Converts a transformation matrix to an OpenXR pose
    XrPosef matrixToPose(const glm::mat4 matrix);

    /// Converts an OpenXR pose to a transformation matrix
    glm::mat4 poseToMatrix(const XrPosef& pose);

    glm::mat4 poseToMatrix(const util::posef& pose);

    util::posef xrPosefToGlmPosef(const XrPosef& xrPosef);

    /// Creates an OpenXR projection matrix
    glm::mat4 createProjectionMatrix(XrFovf fov, float nearClip, float farClip);

    glm::quat xrQuaternionfToGlmQuat(const XrQuaternionf& src);

    XrQuaternionf glmQuatToXrQuaternionf(const glm::quat& src);

    glm::vec3 xrVector3fToGlmVec3(const XrVector3f& src);

    XrVector3f glmVec3ToXrVector3f(const glm::vec3& src);

    float dot(const glm::quat& a, const glm::quat& b);

    glm::quat lerpMix(const glm::quat& from, const glm::quat& to, float t);

    glm::vec3 lerpMix(const glm::vec3& a, const glm::vec3& b, float w);

    float lerpMix(float a, float b, float w);

    float dot(const glm::vec3& a, const glm::vec3& b);

    glm::vec3 crossProductVector3(const glm::vec3& vector_a, const glm::vec3& vector_b);

    float clampf(float num, float left, float right);

    float clampf01(float num);

    float lengthSquared(const glm::vec3& vec);

    float length(const glm::vec3& vec);

    glm::vec3 normalize(const glm::vec3& vec);

    float distanceSquared(const glm::vec3& vec1, const glm::vec3& vec2);

    float distance(const glm::vec3& vec1, const glm::vec3& vec2);

    glm::quat slerp(const glm::quat& start, const glm::quat& end, float percent);

    glm::vec3 slerp(const glm::vec3& start, const glm::vec3& end, float percent);

    float vectorAngleAroundNormal(const glm::vec3& vec1, const glm::vec3& vec2, const glm::vec3& norm);

    glm::mat4 rotationAroundPoint(glm::vec3 point, glm::mat4 rotationMatrix);

    void quaternionToAngleAxis(const glm::quat& quat, float& angle, glm::vec3& axis);

    glm::quat quaternionFromAngleAxis(const float& angle, const glm::vec3& axis);

    float remapInterval(float val, const float vmin, const float vmax, const float newmin, const float newmax);
    } // namespace util