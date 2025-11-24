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
layout(location = 5) flat in vec3 lightDir;
layout(location = 6) flat in int lightIndex;

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
	const float roughnessSlider = dynFragUniData.brdfData.y;// [tdbe] clamped to FROSTBITE_MIN_ROUGHNESS
	const float metallicSlider = dynFragUniData.brdfData.x;
	
	const vec3 fixtureColor = inColor.rgb;// * 0.955;

	// [tdbe] TODO: set a perMaterialFlags to know if we're a light fixture for a spherical light or a length based light e.g. tube or quad

	vec3 col = 
				calculateLights( gl_FrontFacing, cameraPos,
							fragWorldPos.xyz, staFragUniData.time,
							normal.xyz, worldspaceNormal.xyz, 
							staFragUniData.allLights, lightIndex,
							inColor.a, 
							staFragUniData.ambientLight,
							fixtureColor.rgb,
							dynFragUniData.ior,
							roughnessSlider,
							metallicSlider);
	col = addFog(col, staFragUniData.ambientLight[3].rgb, staFragUniData.ambientLight[3].w);
	outColor = vec4(col, 1.0);
	
	/*
	mat4 ambMult = staFragUniData.ambientLight;
	//ambMult[2] = mix(ambMult[1], ambMult[2], 0.33);
	ambMult[0] = ambMult[1];
	ambMult[2] = ambMult[1];
	//ambMult[2] = ambMult[0];
	const vec3 surfaceToCameraViewDir = normalize(cameraPos - fragWorldPos);
	const vec3 axis = cross(surfaceToCameraViewDir, lightDir);
	const float angle = -(HALFPI - (acos((dot(surfaceToCameraViewDir, lightDir)))));
	const mat4 rotationUpToPerpendicular = matrAxisAngleClockwise(axis, angle);
	// [tdbe] rotate the normal in a way that negates, how much rotated away, our view direction is, from the perpendicular to the light's forward direction.
	const vec3 rotatedNormalWs = (rotationUpToPerpendicular * vec4(worldspaceNormal, 0.0)).xyz;
	const vec3 rotatedNormal = normalize(rotatedNormalWs);
	vec3 col = 
			   calculateLights( gl_FrontFacing, cameraPos,
								fragWorldPos + normal * 0.33, // [tdbe] "distance" the frag (light fixture) a bit away from the actual light
								staFragUniData.time,
								rotatedNormal, rotatedNormalWs, 
								staFragUniData.allLights, 1,
								inColor.a, 
								ambMult,
								fixtureColor.rgb, true,
								ior,
								roughnessSlider,
								metallicSlider);
	vec3 alteredCol = (poww(col, 4.0));
	const float maxLum = max(col.x, max(col.y, col.z));//length(col);
	vec3 sunCol = 
				  calculateLights( gl_FrontFacing, cameraPos,
								fragWorldPos.xyz, staFragUniData.time,
								-normal.xyz, -worldspaceNormal.xyz, 
								staFragUniData.allLights, 0,
								inColor.a, 
								staFragUniData.ambientLight,
								fixtureColor.rgb, false,
								ior,
								roughnessSlider,
								metallicSlider);
								
	const vec3 lightFixtureBrightestColor = mix(clamp01(col), vec3(1.0), maxLum);
	alteredCol = mix(alteredCol, lightFixtureBrightestColor, clamp01(abs(dot(rotatedNormal, surfaceToCameraViewDir))));
	alteredCol = mix(clamp01(sunCol + col), clamp01(sunCol * 0.5 + alteredCol), maxLum);
	alteredCol = addFog(alteredCol, staFragUniData.ambientLight[3].rgb, staFragUniData.ambientLight[3].w);
	outColor = vec4(alteredCol, 1.0);*/
}