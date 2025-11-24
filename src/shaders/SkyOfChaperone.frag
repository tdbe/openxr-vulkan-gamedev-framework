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
layout(location = 5) flat in int glViewIndex;
layout(location = 6) in vec3 cyclopsNoiseSeed;

layout(location = 0) out vec4 outColor;

void main()
{
	if(color.a == 0.0)
	{
		//if(isDithered(gl_FragCoord.xy, inColor.a) <= 0.0)
		//if(isDithered(uv.xy*DITHER_UV_TEXELSCALE*0.5, inColor.a) <= 0.0)
		//if(mix(isDithered(gl_FragCoord.xy, inColor.a), isDithered(uv.xy*DITHER_UV_TEXELSCALE*0.5, inColor.a), 0.5) <= 0.0)
			discard;// [tdbe] maybe still write to fragdepth if you need.
	}

	const vec3 normal = normalize(worldspaceNormal);
    //The gl_FragCoord.z component is the depth value that would be used for the fragment's depth if no shader contained any writes to gl_FragDepth. 
    float fragdepth = max(dynFragUniData.perMaterialFlags.w, gl_FragCoord.z);

	// [tdbe] TODO: make an actual sky shader, not a brdf shader :)
	const vec3 surfaceToCameraViewDir = normalize(cameraPos - fragWorldPos);

	float roughnessSlider = dynFragUniData.brdfData.y;// [tdbe] clamped to FROSTBITE_MIN_ROUGHNESS
	float metallicSlider = dynFragUniData.brdfData.x;
	const vec3 ior = dynFragUniData.ior.xyz;

	vec3 F0 = abs ((1.0 - ior) / (1.0 + ior));
	F0 = F0 * F0;
	const vec3 ambientGradient = sampleAmbientSky(normal, vec3(0,1,0), staFragUniData.ambientLight);
	const vec3 ambientLight = ambientGradient * ambientGradient;

	metallicSlider = 0.5;
	//F0 = mix(F0, color.rgb, metallicSlider);
	roughnessSlider = clamp(0.06758975, FROSTBITE_MIN_ROUGHNESS, 1.0);
	const int mainDirectionalLight = 0;
	vec3 lightColor = staFragUniData.allLights[mainDirectionalLight][COLOR].rgb;
	float lightIntensity = staFragUniData.allLights[mainDirectionalLight][COLOR].w;
	lightColor = mix(ambientLight, lightColor, 0.66);
	const vec3 surfaceToLightDir = staFragUniData.allLights[mainDirectionalLight][CENTRAL_VEC].xyz;
	const float n_Dot_v = clamp(abs(dot(-normal, surfaceToCameraViewDir)), LIGHT_CULL_INTENSITY, 1.0);
	vec3 col = calcBRDF(LIGHT_TYPE_DIRECTIONAL,
						-surfaceToLightDir, -surfaceToLightDir, surfaceToCameraViewDir, -normal, color.rgb,
						lightColor, n_Dot_v, lightIntensity, roughnessSlider, roughnessSlider*roughnessSlider, metallicSlider, F0, 
						1.0, 1.0, 1.0);
	const vec3 halfVector = normalize(-surfaceToLightDir + vec3(0.0,-1.0,0.0));
	const float v_Dot_h = clamp(dot(surfaceToCameraViewDir, halfVector), LIGHT_CULL_INTENSITY, 1.0);
	const float n_Dot_l = clamp(dot(-normal, vec3(0.0,-1.0,0.0)), LIGHT_CULL_INTENSITY, 1.0);
	vec3 lambDiff = 0.66 * (1-Diffuse_Lambert_Blinn_Phong_Ambient(F0, n_Dot_l));
	col += lambDiff*lambDiff;
	col = clamp(ambientLight + col, 0.0, 1.0);
	outColor = vec4(col, color.w);

	// [tdbe] Chaperone:
	if( dynFragUniData.perMaterialFlags.w < 1.0)
	{
		vec2 screenspacePos01 = gl_FragCoord.xy / staFragUniData.screenSizePixels;
		// [tdbe] this curl noise is not necessary, it's just to look cool :) 
		// piyushslayer for flame
		//const vec3 curlWorleyFbm = fbmCurlWorley(screenspacePos01, 8.0, staFragUniData.time);
		//float curl = curlWorleyFbm.r * 0.625 + curlWorleyFbm.g * 0.25 + curlWorleyFbm.b * 0.125;//625
		// magician0809
		const float time = staFragUniData.time*0.33;
		// [tdbe] we need identical position for both eyes when we sample the noise else it will be different noise seeds per eye (so we can't use e.g. screenspace)
		vec2 coords4Noise = (cyclopsNoiseSeed.xy/cyclopsNoiseSeed.z);
		coords4Noise = remapInterval(rotateZ(coords4Noise, staFragUniData.time), 0.0, 1.0, 1.0, 1.2);
		const vec3 curl3 = (curl_noise_m0(coords4Noise, 8.0, time));

		//float curl = curl3.r * 0.5 + curl3.g * 0.25 + curl3.b * 0.125;//625
		float curl = (curl3.r * 1.85 + curl3.g * 1.25 + curl3.b * 0.55);
		screenspacePos01 = mix(screenspacePos01, screenspacePos01 * curl, mix(curl * 0.225, curl * 0.0125, dynFragUniData.perMaterialFlags.y));

		const float tunnelDF = getChaperoneTunnelDist(screenspacePos01, staFragUniData.ipd, glViewIndex);
		const float animationRing = abs(sin(staFragUniData.time));
		const float thicknessRing = 0.9875 + animationRing * 0.0125;
		const float ringDF = pow(getRingDF(tunnelDF, dynFragUniData.perMaterialFlags.x) * thicknessRing, 14);//12
		// [tdbe] the middle part of the ring
		const float ringDF_innerHalf = clamp(remapInterval(ringDF, 0.5, 1.0, 0.0, 1.0), 0.0, 1.0);
		// [tdbe] the outer glow part of the ring (both on the inside and the outside of the portal)
		const float ringDf_outerHalf = pow(clamp(remapInterval(ringDF, 0.0, 0.5, 0.0, 1.0), 0.0, 1.0), 4.0);
		const vec3 ringCentreColor1 = vec3(0.0, 1.0, 0.0);
		const vec3 ringOuterColor1 = vec3(1.0, 0.0, 1.0);
		const vec3 ringColor1 = mix(ringOuterColor1, ringCentreColor1, clamp(ringDF_innerHalf + 0.33, 0.0, 1.0));
		const vec3 ringCentreColor2 = vec3(-1.0, 1.0, 0.5);
		const vec3 ringOuterColor2 = vec3(1.0, 0.0, 1.0);
		const vec3 ringColor2 = mix(ringOuterColor2, ringCentreColor2, clamp(ringDF_innerHalf + 0.33, 0.0, 1.0));
		// [tdbe] now we're thinking with portals! Note: / todo: I had to copy this to GridGround.frag as well because of the current layering setup.
		//outColor.rgb = mix(outColor.rgb, ringColor, ringDf_outerHalf);
		//outColor.rgb = mix(outColor.rgb, ringColor, mix(ringDf_outerHalf, ringDf_outerHalf * curl, curl * 1.3));
		outColor.rgb = mix(outColor.rgb, mix(ringColor1, ringColor2, curl * 1.25), ringDf_outerHalf);

		if(tunnelDF > dynFragUniData.perMaterialFlags.x)
		{
			gl_FragDepth = dynFragUniData.perMaterialFlags.w;
		}
		else
		{
			const float stronk = pow(ringDF, 3.0);
            outColor.a *=stronk;
			/*
			if(dynFragUniData.perMaterialFlags.w < fragdepth)
            {
				// [tdbe] Note: this is just an optional depth trick to alter how the ring glow appears to intersect with objects at different depths.
                gl_FragDepth = mix(fragdepth, dynFragUniData.perMaterialFlags.w, stronk);
                outColor.rgb = mix(outColor.rgb, ringCentreColor1, gl_FragDepth * stronk);
            }
            else */
                gl_FragDepth = fragdepth;
		}

		outColor.rgb = mix(outColor.rgb, vec3(0.025, 0.025, 0.025), dynFragUniData.perMaterialFlags.z * ringDF);
	}
    else
	{
		gl_FragDepth = fragdepth;
	}
}