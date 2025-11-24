#include "_Utils.glsl"
#include "_ProceduralGeometry.glsl"
#include "_Lighting.glsl"
#include "_LoudNoises.glsl"

layout(binding = 1) uniform StaFragUniData
{ 
	mat4[LIGHT_COUNT] allLights;
	mat4 ambientLight; 
	vec2 screenSizePixels;
	float ipd;
	float time;
} staFragUniData;

layout(binding = 3) uniform DynFragUniData
{
    vec4 brdfData;// [tdbe] x: metallic, y: roughness, z: todo: clearcoat, w: procedural color flag & intensity
	vec4 ior;// [tdbe] .w: overrides minimum brightness of the ambientLight (ie the ground side is usually the dark part you want to tweak)
    vec4 perMaterialFlags;// [tdbe] x: tunnelvision radius; y: ring wobble stability (1 = stable, 0 = wild); z: ring & chaperone fade (0 is not faded, 1 is faded); w: change the sky's own depth
} dynFragUniData;

layout(location = 0) in vec3 worldspaceNormal;
layout(location = 1) flat in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 fragWorldPos;
layout(location = 4) flat in vec3 cameraPos;

layout(location = 0) out vec4 outColor;

void main()
{
	if(color.a == 0.0)
	{
		//if(isDithered(gl_FragCoord.xy, inColor.a) <= 0.0)
		//if(isDithered(uv.xy*DITHER_UV_TEXELSCALE*0.5, inColor.a) <= 0.0)
		//if(mix(isDithered(gl_FragCoord.xy, inColor.a), isDithered(uv.xy*DITHER_UV_TEXELSCALE*0.5, inColor.a), 0.5) <= 0.0)
			discard;
	}

	const vec3 normal = normalize(worldspaceNormal);

	// [tdbe] TODO: make an actual sky shader, not a brdf shader :)
	const vec3 surfaceToCameraViewDir = normalize(cameraPos - fragWorldPos);

	float roughnessSlider = dynFragUniData.brdfData.y;// [tdbe] clamped to FROSTBITE_MIN_ROUGHNESS
	float metallicSlider = dynFragUniData.brdfData.x;
	const vec3 ior = dynFragUniData.ior.xyz;

	vec3 F0 = abs ((1.0 - ior) / (1.0 + ior));
	F0 = F0 * F0;
	const vec3 ambientGradient = sampleAmbientSky(normal, vec3(0,1,0), staFragUniData.ambientLight);
	const vec3 ambientLight = ambientGradient * ambientGradient;

	metallicSlider = 1.0;
	//F0 = mix(F0, color.rgb, metallicSlider);
	roughnessSlider = clamp(0.0668975, FROSTBITE_MIN_ROUGHNESS, 1.0);
	const int mainDirectionalLight = 0;
	vec3 lightColor = staFragUniData.allLights[mainDirectionalLight][COLOR].rgb;
	float lightIntensity = staFragUniData.allLights[mainDirectionalLight][COLOR].w;
	//lightColor = mix(ambientLight, lightColor, 0.66);
	
	const vec3 surfaceToLightDir = staFragUniData.allLights[mainDirectionalLight][CENTRAL_VEC].xyz;
	const float n_Dot_v = clamp(abs(dot(-normal, surfaceToCameraViewDir)), LIGHT_CULL_INTENSITY, 1.0);
	vec3 col = calcBRDF(LIGHT_TYPE_DIRECTIONAL,
						-surfaceToLightDir, -surfaceToLightDir, surfaceToCameraViewDir, -normal, color.rgb,
						lightColor, n_Dot_v, lightIntensity, roughnessSlider, roughnessSlider*roughnessSlider, metallicSlider, F0, 
						1.0, 1.0, 1.0);
	const vec3 halfVector = normalize(-surfaceToLightDir + vec3(0.0,-1.0,0.0));
	const float v_Dot_h = clamp(dot(surfaceToCameraViewDir, halfVector), LIGHT_CULL_INTENSITY, 1.0);
	const float n_Dot_l = clamp(dot(-normal, vec3(0.0,-1.0,0.0)), LIGHT_CULL_INTENSITY, 1.0);
	vec3 lambDiff = 0.45 * (1-Diffuse_Lambert_Blinn_Phong_Ambient(F0, n_Dot_l));
	col += lightColor * lambDiff;//*lambDiff;
	col = clamp(ambientLight + col, 0.0, 1.0);
	outColor = vec4(col, color.w);

}