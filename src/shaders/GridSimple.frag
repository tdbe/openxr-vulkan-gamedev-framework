#include "_Utils.glsl"
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
    vec4 perMaterialFlags;// [tdbe] w: change depth
} dynFragUniData;

layout(location = 0) in vec3 fragWorldPos;
layout(location = 1) flat in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) flat in vec4 objPosition; // [tdbe] mesh position, grid scale
layout(location = 4) flat in vec4 objRot; // [tdbe] mesh rotation

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

    //The gl_FragCoord.z component is the depth value that would be used for the fragment's depth if no shader contained any writes to gl_FragDepth. 
    float fragdepth = gl_FragCoord.z;
    vec3 pos = fragWorldPos - objPosition.xyz;
    pos = rotateWithQuat(pos.xyz, objRot);

    const float scale = objPosition.w;
    const float animation = abs(sin(staFragUniData.time + pos.x / 10.0 + pos.z / 10.0));
    const float crossThickness = scale * 0.01125 + animation * 0.0025;
    const float crossThickness2 = crossThickness * 2.125;
    const float crossLength = scale * 0.05625 + animation * 0.01;
    const float crossLength2 = crossLength * 1.25;

    const float gx = mod(pos.x, 1.0);
    const float gz = mod(pos.z, 1.0);
    outColor.a = 1.0;
    const vec3 backgroundColor = vec3(0.1, 0.08, 0.12);
  
    if ((isOnGrid(gx, crossThickness) && isOnGrid(gz, crossLength)) || 
        (isOnGrid(gz, crossThickness) && isOnGrid(gx, crossLength)))
    {
        const float fadeLength = 14.0 * min(1.5, scale);
        const float fade = clamp(1.0 - (length(pos.xz) / fadeLength), 0.0, 1.0);
        outColor.rgb = mix(backgroundColor, color.xyz, fade * fade);
        outColor.a = fade;

        if(dynFragUniData.perMaterialFlags.w < 1.0)
        {
            gl_FragDepth = dynFragUniData.perMaterialFlags.w;
        }
    }
    else if ((isOnGrid(gx, crossThickness2) && isOnGrid(gz, crossLength2)) || 
             (isOnGrid(gz, crossThickness2) && isOnGrid(gx, crossLength2)))
    {
        const float fadeLength = 14.0 * min(1.5, scale);
        const float fade = clamp(1.0 - (length(pos.xz) / fadeLength), 0.0, 1.0);
        outColor.rgb = mix(backgroundColor, mix(backgroundColor, -color.xyz, 0.5), fade * fade);
        outColor.a = fade;
        gl_FragDepth = dynFragUniData.perMaterialFlags.w;
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