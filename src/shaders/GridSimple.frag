layout(binding = 1) uniform StaFragUniData
{ 
    mat4 ambientMultiplier; 
	vec2 screenSizePixels;
	float ipd;
	float time;
} staFragUniData;

layout(binding = 3) uniform DynFragUniData
{
    vec4 perMaterialFlags;// [tdbe] w: change depth
} dynFragUniData;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) flat in vec4 objPosition; // [tdbe] mesh position, scale
layout(location = 3) flat in vec4 objRot; // [tdbe] mesh rotation

layout(location = 0) out vec4 outColor;

bool isOnGrid(float position, float threshold)
{
  return position < threshold || position > 1.0 - threshold;
}

vec4 conjugateQuat(vec4 quat)
{
    return vec4(-quat.x, -quat.y, -quat.z, quat.w);
}

vec4 multiplyQuat(vec4 quat1, vec4 quat2)
{
    return vec4(
        quat2.xyz * quat1.w + quat1.xyz * quat2.w + cross(quat1.xyz, quat2.xyz),
        quat1.w * quat2.w - dot(quat1.xyz, quat2.xyz)
    );
}

vec3 rotateWithQuat(vec3 pointToRotate, vec4 quat)
{
    return multiplyQuat(quat, 
                        multiplyQuat(
                            vec4(pointToRotate, 0), 
                            conjugateQuat(quat))
                        ).xyz;
}

// quick fog https://www.ozone3d.net/tutorials/glsl_fog/p04.php?lang=1
vec3 addFog(vec3 finalColor, vec3 fogColor, float density)
{
	const float LOG2 = 1.442695;
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fogFactor = exp2( -density * density * 
						    z * z * 
						    LOG2 );
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	return mix(fogColor, finalColor, fogFactor);
}

void main()
{
  //The gl_FragCoord.z component is the depth value that would be used for the fragment's depth if no shader contained any writes to gl_FragDepth. 
  float fragdepth = gl_FragCoord.z;
  vec3 pos = position - objPosition.xyz;
  pos = rotateWithQuat(pos.xyz, objRot);

  const float scale = objPosition.w;
  const float animation = abs(sin(staFragUniData.time + pos.x / 10.0 + pos.z / 10.0));
  const float crossThickness = scale * 0.01 + animation * 0.0025;
  const float crossLength = scale * 0.05 + animation * 0.01;

  const float gx = mod(pos.x, 1.0);
  const float gz = mod(pos.z, 1.0);
  outColor.a = 1.0;
  
  if ((isOnGrid(gx, crossThickness) && isOnGrid(gz, crossLength)) || (isOnGrid(gz, crossThickness) && isOnGrid(gx, crossLength)))
  {
    const float fadeLength = 10.0 * min(1.5, scale);
    const float fade = clamp(1.0 - (length(pos.xz) / fadeLength), 0.0, 1.0);
    const vec3 backgroundColor = vec3(0.1, 0.08, 0.12);
    outColor.rgb = mix(backgroundColor, color.xyz, fade);
    outColor.a = fade;

    if(dynFragUniData.perMaterialFlags.w < 1.0)
    {
        gl_FragDepth = dynFragUniData.perMaterialFlags.w;
    }
  }
  else
  {
    if(dynFragUniData.perMaterialFlags.w < 1.0)
    {
        gl_FragDepth = 1;
    }
    outColor = vec4(0, 0, 0, 0);
  }

  outColor.rgb = addFog(outColor.rgb, vec3(0.5, 0.46, 0.54), 0.02);
  outColor.a *= color.a;
}