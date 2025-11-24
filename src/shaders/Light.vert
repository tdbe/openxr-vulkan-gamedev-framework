#extension GL_EXT_multiview : enable
#include "_VertexProcessing.glsl"

layout(binding = 2) uniform DynVertBufData
{
    mat4 worldMatrix;
    vec4 colorMultiplier;
    vec4 perMaterialFlags;
    int instanceCount;
} dynVertBufData;

layout(binding = 0) uniform StaVertBufData
{
    mat4 handsWorldMatrixes[2];
    mat4 cameraWorldMatrixes[2];
    mat4 viewMatrixes[2];
    mat4 viewProjectonMatrixes[2];
    float ipd; 
    float time;
    int inLocomotion;
} staVertBufData;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 uv;

layout(location = 0) out vec3 normal; // In world space
layout(location = 1) out vec4 color;
layout(location = 2) out vec2 uvCoords;
layout(location = 3) out vec3 fragWorldPos;
layout(location = 4) flat out vec3 cameraPos;
layout(location = 5) flat out vec3 lightDir;
layout(location = 6) flat out int lightIndex;

void main()
{
    vec4 wpos = dynVertBufData.worldMatrix * vec4(inPosition, 1.0);
    normal = (dynVertBufData.worldMatrix * vec4(inNormal, 0.0)).xyz;
    uvCoords = uv;
    cameraPos = staVertBufData.cameraWorldMatrixes[gl_ViewIndex][3].xyz;
    color.rgb = inColor * dynVertBufData.colorMultiplier.xyz;
    color.a = dynVertBufData.colorMultiplier.a;
    dislocateForChaperone(  staVertBufData.inLocomotion,
                            1.0,
                            staVertBufData.cameraWorldMatrixes[gl_ViewIndex],
                            wpos.xyz, 
                            normal,
                            color.rgb,
                            color.a
                            );

    gl_Position = staVertBufData.viewProjectonMatrixes[gl_ViewIndex] * wpos;
    fragWorldPos = wpos.xyz;
    lightDir = dynVertBufData.worldMatrix[2].xyz;// [tdbe] mesh forward is tube light forward in case it's a tube light or some length focused area light
    // [tdbe] todo: quick demoscene data connection; improve.
    // 1. this assumes the first light is the directional light, the next ones are tube lights, and anything else follows, and any light that doesn't have a Light mesh (light fixture (this shader)) is at the very end regardless of type.
    // 2. And gl_InstanceIndex is hijacked to know in the shader the #'th mesh rendered with this material. So it's nth mesh rendered with a specific material, and it has a light component.
    // For 1. and 2. to align, you must assume all light entities with a light fixture mesh have a single material with this shader.
    lightIndex = 1 + 6 + int(gl_InstanceIndex); 
}