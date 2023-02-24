#extension GL_EXT_multiview : enable

layout(binding = 0) uniform DynBufData
{
    mat4 worldMatrix;
    vec4 colorMultiplier;
} dynBufData;

layout(binding = 1) uniform ViewProjection
{
    mat4 matrices[2];
} viewProjection;

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec3 inColor;
//layout(location = 3) in vec3 colorMultiplier;

layout(location = 0) out vec3 position; // In world space
layout(location = 1) out vec3 color;

void main()
{
  vec4 pos = dynBufData.worldMatrix * vec4(inPosition, 1.0);
  gl_Position = viewProjection.matrices[gl_ViewIndex] * pos;
  position = pos.xyz;

  color = inColor
          *dynBufData.colorMultiplier.xyz;
}