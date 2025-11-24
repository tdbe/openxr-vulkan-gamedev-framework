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
layout(location = 5) flat in int glInstanceIndex;
layout(location = 6) flat in int instanceCount;

layout(location = 0) out vec4 outColor;

void main()
{
	vec4 inColor = color;
	if(inColor.a == 0.0)
		discard;// [tdbe] maybe still write to fragdepth if you need.
	float roughnessSlider = dynFragUniData.brdfData.y;// [tdbe] clamped to FROSTBITE_MIN_ROUGHNESS
	float metallicSlider = dynFragUniData.brdfData.x;
	const vec3 normal = normalize(worldspaceNormal);

	float randPerInstance = 0.0;
	// [tdbe] this is very basic optional instancing, so it just bakes-in a demo to cycle through metallic and roughness ranges in a 5x5 grid
	if(instanceCount > 1)
    {
		int index = glInstanceIndex;
        int depth = int(floor(index / 25));
        index = index - (depth * 25);

		float row = floor(index / 5);
		float column = (index % 5);
        metallicSlider = 1.0 - ((column) * 0.25);
        roughnessSlider = clamp(row * 0.25, FROSTBITE_MIN_ROUGHNESS, 1.0);
		//float tim = remapInterval(sin(staFragUniData.time*0.5) + 1.0, 0.0, 2.0, 0.5, 1.0);
		//inColor.a *= tim;
		inColor.a *= 1.0 - depth * 0.333;
		inColor.rgb = mix(vec3(1.0, 0.64, 0.16), vec3(0.16, 0.64, 1.0), column * 0.25);
		randPerInstance = random(glInstanceIndex);
    }

	// [tdbe] adding some rainbow irridescence waves
	if(dynFragUniData.brdfData.w > 0.001)
	{
		float stripScale = 45.35;

		// [tdbe] irridescence
		//vec3 worldOffset = clamp01((fragWorldPos)/128);
		//const float mul = dot(normal, worldOffset);
		const float mul = dot(normal, vec3(0.0, 0.1, 0.0)) / 3;
		//const float mul = dot(rotateY(normal, randPerInstance*TWOPI), worldOffset);

		const float piOffset = 2.0*PI/3.0;
		const float time = 0.025*(staFragUniData.time);//0.0185
		vec3 magic = vec3((sin(			      stripScale*(time + mul))), 
						  (sin(piOffset +	  stripScale*(time + mul))), 
						  (sin(2.0*piOffset + stripScale*(time + mul))));
		
		//magic = hue_shift(magic, staFragUniData.time);
		const float rotv = 0.76*staFragUniData.time * randPerInstance;
		magic = rotateZ(magic.xyz, rotv);
		magic = rotateZ(magic.zxy, rotv);
		magic = rotateZ(magic.yzx, rotv);
		magic = (1.0 + magic) * 0.5;

		inColor.xyz = mix(inColor.rgb, magic, dynFragUniData.brdfData.w);
	}

	/*
	hologram strips on red
	{
		vec3 magic = gl_FragCoord.xyz + staFragUniData.time;
		float pimath = 2.0*PI/3.0;
		magic.x = sin(magic.y+pimath);
		magic.y = sin(magic.x+2.0*pimath);
		magic.z = sin(magic.z);
		inColor.rgb = mix(magic * inColor.rgb, inColor.rgb, clamp01(inColor.a*1.9));
	}*/

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
	col = addFog(col, staFragUniData.ambientLight[3].rgb, staFragUniData.ambientLight[3].w);
	outColor = vec4(col, inColor.w);
}