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
layout(location = 3) in vec3 cyclopsNoiseSeed;
layout(location = 4) in vec3 fragWorldPos;
layout(location = 5) flat in vec3 cameraPos;
layout(location = 6) flat in int glInstanceIndex;

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

	const vec3 normal = normalize(worldspaceNormal);
    {
		//float distCamToFrag = max(1.0, distance(cameraPos, fragWorldPos));
		//float mul = cyclopsNoiseSeed.x*cyclopsNoiseSeed.y*cyclopsNoiseSeed.z / distCamToFrag;
		vec3 worldOffset = clamp((fragWorldPos)/256, 0.125, 1.0);
		float stripScale = 45.35;
		const float randPerInstance = random(glInstanceIndex*TWOPI) * 0.25 + 0.75;
		const float time = 0.025*(staFragUniData.time);//0.0185
		float mul = 1.0;
		if(glInstanceIndex == 0)
		{
			mul = dot(normal, worldOffset);
			stripScale *= 0.25;
		}
		else if(glInstanceIndex == 1)
		{
			// [tdbe] symmetrical trippy frog quadrants
			mul = normal.x * normal.y * normal.z + (worldOffset.x + worldOffset.y + worldOffset.z)/3;
		}
		else if(glInstanceIndex == 2)
		{
			// [tdbe] irridescence
			//mul = dot(normal, worldOffset);
			mul = dot(normal, vec3(0.1, 0.85, -1.0)) * 0.085;
		}
		else if(glInstanceIndex == 3)
		{
			// [tdbe] trippy iris
			//mul = normal.x + normal.y + normal.z;
			vec3 fragToCam = normalize(cameraPos - fragWorldPos) * 0.75;
			mul = dot(fragToCam, normal);
		}
		else
		{
			// [tdbe] irridescence more angle variation
			mul = dot(rotateY(normal, randPerInstance*TWOPI*time), worldOffset) * 0.433;
			stripScale *= 0.25;
		}

		const float piOffset = 2.0*PI/3.0;
		vec3 magic = vec3((sin(			      stripScale*(time + mul))), 
						  (sin(piOffset +	  stripScale*(time + mul))), 
						  (sin(2.0*piOffset + stripScale*(time + mul))));
		
		//magic = hue_shift(magic, staFragUniData.time);
		const float rotv = 0.76*staFragUniData.time * randPerInstance;
		magic = rotateZ(magic.xyz, rotv);
		magic = rotateZ(magic.zxy, rotv);
		magic = rotateZ(magic.yzx, rotv);
		
		if(glInstanceIndex == 0)
		{
			magic = (1.0 + magic) * 0.5 * dynFragUniData.brdfData.w;
			inColor.xyz = mix(inColor.xyz, magic, dynFragUniData.brdfData.w);
		}
		else if(glInstanceIndex == 1)
		{
			//magic = (0.75 + magic) * 0.7514;
			magic = (0.5 + magic) * 0.666;
			inColor.xyz = mix(inColor.xyz, magic, dynFragUniData.brdfData.w);
		}
		else if(glInstanceIndex == 2)
		{
			magic = (1.0 + magic) * 0.5;
			inColor.xyz = mix(inColor.xyz, magic, dynFragUniData.brdfData.w);
		}
		else if(glInstanceIndex == 3)
		{
			magic = (0.5 + magic) * 0.666;
			inColor.xyz = mix(inColor.xyz, magic, dynFragUniData.brdfData.w);
		}
		else if(glInstanceIndex == 4)
		{
			magic = (0.5 + magic) * 0.666;
			inColor.xyz = inColor.xyz;
		}
		else
		{
			magic = (1.0 + magic) * 0.5 * dynFragUniData.brdfData.w;
			inColor.xyz = mix(inColor.xyz, magic, dynFragUniData.brdfData.w);
		}
	}

	const float roughnessSlider = dynFragUniData.brdfData.y;// [tdbe] clamped to FROSTBITE_MIN_ROUGHNESS
	const float metallicSlider = dynFragUniData.brdfData.x;
	vec3 col = calculateLights( gl_FrontFacing, cameraPos,
								fragWorldPos, staFragUniData.time,
								normal, worldspaceNormal, 
								staFragUniData.allLights, -1,
								inColor.a, 
								staFragUniData.ambientLight,
								inColor.rgb,
								dynFragUniData.ior,
								roughnessSlider,
								metallicSlider);
	col = addFog(col, staFragUniData.ambientLight[3].rgb, staFragUniData.ambientLight[3].w, staFragUniData.ambientLight[0].xyz, fragWorldPos.y, MAX_WORLD_HEIGHT);
	outColor = vec4(col, 1.0);
}