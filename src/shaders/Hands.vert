#extension GL_EXT_multiview : enable

layout(binding = 2) uniform DynVertBufData
{
    mat4 worldMatrix;
    vec4 colorMultiplier;
    vec4 perMaterialFlags;// [tdbe] w: make the object very close to our face, as far as the projected depth position is concerned
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
layout(location = 1) flat out vec4 color;
layout(location = 2) out vec2 uvCoords;
layout(location = 3) out vec3 fragWorldPos;
layout(location = 4) flat out vec3 cameraPos;

void main()
{
    const vec4 wpos = dynVertBufData.worldMatrix * vec4(inPosition, 1.0);
    gl_Position = staVertBufData.viewProjectonMatrixes[gl_ViewIndex] * dynVertBufData.worldMatrix * vec4(inPosition, 1.0);
    if(dynVertBufData.perMaterialFlags.w < 1.0)
        gl_Position.z *= dynVertBufData.perMaterialFlags.w; // [tdbe] make the object very close to our face, as far as the projected depth position is concerned
    fragWorldPos = wpos.xyz;
    cameraPos = staVertBufData.cameraWorldMatrixes[gl_ViewIndex][3].xyz;
  
    normal = (dynVertBufData.worldMatrix * vec4(inNormal, 0.0)).xyz;
    uvCoords = uv;
    // [tdbe] remove the "flat out" and "flat in" from color definitions if you're actually using vertex colors etc.
    color.rgb = inColor * dynVertBufData.colorMultiplier.rgb;
    color.a *= dynVertBufData.colorMultiplier.a;
}