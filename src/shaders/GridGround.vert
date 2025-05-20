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
layout(location = 2) in vec3 inColor;
//layout(location = 3) in vec3 colorMultiplier;

layout(location = 0) out vec3 position; // [tdbe] vertex position in world space
layout(location = 1) out vec4 color;
layout(location = 2) flat out vec4 objPosition; // [tdbe] mesh position
layout(location = 3) flat out vec4 objRot; // [tdbe] mesh rotation
layout(location = 4) flat out int glViewIndex;

void main()
{
    const vec4 pos = dynVertBufData.worldMatrix * vec4(inPosition, 1.0);
    gl_Position = staVertBufData.viewProjectonMatrixes[gl_ViewIndex] * pos;
    objPosition = vec4(dynVertBufData.worldMatrix[3].x, dynVertBufData.worldMatrix[3].y, dynVertBufData.worldMatrix[3].z, 1);
    position = pos.xyz;
    glViewIndex = gl_ViewIndex;

    // [tdbe] this will only work for 180 degrees (e.g. -90 to 90):
    //objRot.x = acos(( normalize(dynVertBufData.worldMatrix[0]).x + normalize(dynVertBufData.worldMatrix[1]).y + normalize(dynVertBufData.worldMatrix[2]).z - 1)/2);
    mat4 rotMat = dynVertBufData.worldMatrix;
    rotMat[0] = normalize(rotMat[0]);// [tdbe] normalize to get rid of the object scale
    rotMat[1] = normalize(rotMat[1]);
    rotMat[2] = normalize(rotMat[2]);
    rotMat[3] = vec4(0,0,0,1);// [tdbe] get rid of translation
    vec4 quatFromMat = vec4(0);
    quatFromMat.w = sqrt(1 + rotMat[0].x + rotMat[1].y + rotMat[2].z) / 2;
    quatFromMat.x = (rotMat[2].y - rotMat[1].z)/( 4 * quatFromMat.w);
    quatFromMat.y = (rotMat[0].z - rotMat[2].x)/( 4 * quatFromMat.w);
    quatFromMat.z = (rotMat[1].x - rotMat[0].y)/( 4 * quatFromMat.w);
    objRot = quatFromMat;

    objPosition.w = length(dynVertBufData.worldMatrix[0].xyz);// [tdbe] scale; we assume scale is the same on all axies
    objPosition.w /= 128; // [tdbe] hack: the default scale is 128 in main.cpp

    color.rgb = inColor * dynVertBufData.colorMultiplier.xyz;
    color.w = dynVertBufData.colorMultiplier.w;
}