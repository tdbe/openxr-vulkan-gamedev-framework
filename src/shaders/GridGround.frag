#include "_Utils.glsl"
#include "_LoudNoises.glsl"
#include "_ProceduralGeometry.glsl"
#include "_Lighting.glsl"

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

layout(location = 0) in vec3 fragWorldPos;
layout(location = 1) flat in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) flat in vec4 objPosition; // [tdbe] mesh position, grid scale
layout(location = 4) flat in vec4 objRot; // [tdbe] mesh rotation
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
    float fragdepth = max(dynFragUniData.perMaterialFlags.w, gl_FragCoord.z);

    if(dynFragUniData.perMaterialFlags.w < 1.0)
    {
        //The gl_FragCoord.z component is the depth value that would be used for the fragment's depth if no shader contained any writes to gl_FragDepth. 
        vec3 pos = fragWorldPos - objPosition.xyz;
        pos = rotateWithQuat(pos.xyz, objRot);

        const float scale = objPosition.w;
        const float animation = abs(sin(staFragUniData.time + pos.x / 10.0 + pos.z / 10.0));
        const float crossThickness = scale * 0.01125 + animation * 0.0025;
        const float crossThickness2 = crossThickness * 2.125;
        const float crossLength = scale * 0.05625 + animation * 0.01;
        const float crossLength2 = crossLength * 1.25;

        //const vec3 backgroundColor = vec3(0.1, 0.08, 0.12);
        const vec3 backgroundColor = vec3(0.05, 0.04, 0.06);
        outColor.a = 1;

        const float gx = mod(pos.x, 1.0);
        const float gz = mod(pos.z, 1.0);
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

        const float fadeLength = 30.0 * min(1.5, scale);
        const float fadeLengthCross = 14.0 * min(1.5, scale);
        const float len = length(pos.xz);
        const float auraFade = clamp(1.0 - len / fadeLength, 0.0, 1.0);
        const float fadeCrosses = clamp(1.0 - len / fadeLengthCross, 0.0, 1.0);
        const float fadeCrosses2 = fadeCrosses*fadeCrosses;

        const vec3 floorCharacterAuraLightColor = vec3(0.2, 0.18, 0.22);
        outColor.rgb = mix(backgroundColor, floorCharacterAuraLightColor, auraFade);
        //outColor.rgb = mix(outColor.rgb, ringColor, ringDF);
        //outColor.rgb = mix(outColor.rgb, ringColor, mix(ringDF, ringDF * curl, curl * 1.3));
        outColor.rgb = mix(outColor.rgb, mix(ringColor1, ringColor2, curl * 1.25), ringDf_outerHalf);

        outColor.a = max(outColor.a * color.a, ringDF);

        if(tunnelDF > dynFragUniData.perMaterialFlags.x)
        {
            gl_FragDepth = dynFragUniData.perMaterialFlags.w;
        }
        else // [tdbe] inside tunnel // [tdbe] TODO: a tunnel copy is no longer necessary in the ground grid (see txt) take it out
        {
            outColor.a *= max(fadeCrosses2, ringDF);
            const float stronk = pow(ringDF, 3.0);
            outColor.a *= max(stronk, auraFade-ringDF);
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

        // [tdbe] draw the grid on top
        if ((isOnGrid(gx, crossThickness) && isOnGrid(gz, crossLength)) || 
            (isOnGrid(gz, crossThickness) && isOnGrid(gx, crossLength)))
        {
            outColor.rgb = mix(outColor.rgb, color.xyz, fadeCrosses2);
            gl_FragDepth = dynFragUniData.perMaterialFlags.w;
        }
        else if ((isOnGrid(gx, crossThickness2) && isOnGrid(gz, crossLength2)) || 
                (isOnGrid(gz, crossThickness2) && isOnGrid(gx, crossLength2)))
        {
            outColor.rgb = mix(outColor.rgb, mix(outColor.rgb, -color.xyz, 0.5), fadeCrosses2);
            gl_FragDepth = dynFragUniData.perMaterialFlags.w;
        }

        outColor.rgb = mix(outColor.rgb, vec3(0.025, 0.025, 0.025), dynFragUniData.perMaterialFlags.z * ringDF);
        //outColor.rgb = mix(addFog(outColor.rgb, vec3(0.5, 0.46, 0.54), 0.02), outColor.rgb, ringDF * 1.05);  
        outColor.rgb = mix(addFog(outColor.rgb, vec3(0.45, 0.41, 0.49), 0.024), outColor.rgb, ringDF * 1.05);  
        //outColor.rgb = mix(addFog(outColor.rgb, vec3(0.43, 0.39, 0.47), 0.033), outColor.rgb, ringDF * 1.05);  
        //gl_FragDepth -= 0.0001;// [tdbe] don't z-fight 
    }
    else
    {
        gl_FragDepth = fragdepth;
    }

}