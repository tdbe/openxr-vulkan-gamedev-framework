#extension GL_EXT_multiview : enable

layout(binding = 2) uniform DynVertBufData
{
    mat4 worldMatrix;
    vec4 colorMultiplier;
    vec4 perMaterialFlags;
} dynVertBufData;

layout(binding = 0) uniform StaVertBufData
{
    mat4 handsWorldMatrixes[2];
    mat4 cameraWorldMatrixes[2];
    mat4 viewMatrixes[2];
    mat4 viewProjectonMatrixes[2];
} staVertBufData;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
//layout(location = 3) in vec3 colorMultiplier;

layout(location = 0) out vec3 normal; // In world space
layout(location = 1) out vec4 color;
layout(location = 2) flat out int glViewIndex;


void main()
{
    const vec4 pos = dynVertBufData.worldMatrix * vec4(inPosition, 1.0);
    gl_Position = staVertBufData.viewProjectonMatrixes[gl_ViewIndex] * pos;
    glViewIndex = gl_ViewIndex;

    normal = normalize(vec3(dynVertBufData.worldMatrix * vec4(inNormal, 0.0)));
    color.rgb = inColor.rgb * dynVertBufData.colorMultiplier.rgb;
    color.w = dynVertBufData.colorMultiplier.w;
}

