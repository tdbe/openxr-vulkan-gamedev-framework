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
layout(location = 3) out vec3 cyclopsNoiseSeed;
layout(location = 4) out vec3 fragWorldPos;
layout(location = 5) flat out vec3 cameraPos;
layout(location = 6) flat out int glInstanceIndex;

void main()
{
    mat4 wmatr = dynVertBufData.worldMatrix;
    glInstanceIndex = 0;
    // [tdbe] this is very basic optional instancing for demo purposes
    if(dynVertBufData.instanceCount > 1)
    {
        glInstanceIndex = gl_InstanceIndex;
    }
    vec4 wpos = wmatr * vec4(inPosition, 1.0);
    normal = (dynVertBufData.worldMatrix * vec4(inNormal, 0.0)).xyz;
    uvCoords = uv;

    cameraPos = staVertBufData.cameraWorldMatrixes[gl_ViewIndex][3].xyz;
    color.rgb = inColor * dynVertBufData.colorMultiplier.rgb;
    color.a = dynVertBufData.colorMultiplier.a;
    dislocateForChaperone(  staVertBufData.inLocomotion,
                            1.0,
                            staVertBufData.cameraWorldMatrixes[gl_ViewIndex],
                            wpos.xyz, 
                            normal,
                            color.rgb,
                            color.a);
    gl_Position = staVertBufData.viewProjectonMatrixes[gl_ViewIndex] * wpos;
    fragWorldPos = wpos.xyz;

    mat4 vpc = staVertBufData.viewProjectonMatrixes[0];
    cyclopsNoiseSeed = (vpc * wpos).xyz;
    //cyclopsNoiseSeed.x -= 0.4;
    //cyclopsNoiseSeed.y += 0.2;
}