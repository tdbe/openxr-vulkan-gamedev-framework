#include "_Utils.glsl"
#include "_ProceduralGeometry.glsl"
#include "_Lighting.glsl"

layout(binding = 1) uniform StaFragUniData
{ 
	mat4[LIGHT_COUNT] allLights;// [tdbe] each matrix row is: const int COLOR = 0 (.w means disabled if 0.0); const int CENTRAL_VEC = 1 (and .w is radius); const int SHAPE_VEC_0 = 2; const int SHAPE_VEC_1 = 3;
	mat4 ambientLight;// [tdbe] set of ambient / global illumination fake gradient colors
	vec2 screenSizePixels;
	float ipd;
	float time;
} staFragUniData;

layout(binding = 3) uniform DynFragUniData
{
	vec4 brdfData;// [tdbe] x: metallic, y: roughness, z: todo: clearcoat, w: procedural color flag & intensity
	vec4 ior;// [tdbe] .w: overrides minimum brightness of the ambientLight (ie the ground side is usually the dark part you want to tweak)
    vec4 perMaterialFlags;// [tdbe] x: tunnelvision radius, w: change depth
} dynFragUniData;

layout(location = 0) in vec3 worldspaceNormal;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 fragWorldPos;
layout(location = 4) flat in vec3 cameraPos;
layout(location = 5) flat in float time;

layout(location = 0) out vec4 outColor;

void main()
{
	vec4 inColor = color;
	if(inColor.a < 0.999)
	{
		//if(isDithered(gl_FragCoord.xy, inColor.a) <= 0.0)
		//if(isDithered(uv.xy*DITHER_UV_TEXELSCALE*0.5, inColor.a) <= 0.0)
		if(mix(isDithered(gl_FragCoord.xy, inColor.a), isDithered(uv.xy*DITHER_UV_TEXELSCALE*0.5, inColor.a), 0.5) <= 0.0)
			discard;// [tdbe] maybe still write to fragdepth if you need.
	}
	// [tdbe] for ground at least we can make a 3x3 conveyor belt 
	// with a worldspace height displacement function that can be reproduced on the CPU for locomotion

	const vec3 normal = normalize(worldspaceNormal);
	const float roughnessSlider = dynFragUniData.brdfData.y;// [tdbe] clamped to FROSTBITE_MIN_ROUGHNESS
	const float metallicSlider = dynFragUniData.brdfData.x;
	vec3 col = calculateLights( gl_FrontFacing, cameraPos,
								fragWorldPos, time,
								normal, worldspaceNormal, 
								staFragUniData.allLights, -1,
								inColor.a, 
								staFragUniData.ambientLight,
								inColor.rgb,
								dynFragUniData.ior,
								roughnessSlider,
								metallicSlider);
	col = addFog(col, staFragUniData.ambientLight[3].rgb, staFragUniData.ambientLight[3].w);
	outColor = vec4(col, 1.0);
}