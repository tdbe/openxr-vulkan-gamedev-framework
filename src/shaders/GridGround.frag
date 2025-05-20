layout(binding = 1) uniform StaFragUniData
{ 
    mat4 ambientMultiplier; 
	vec2 screenSizePixels;
	float ipd;
	float time;
} staFragUniData;

layout(binding = 3) uniform DynFragUniData
{
    vec4 perMaterialFlags;// [tdbe] x: tunnelvision radius; y: ring wobble stability (1 = stable, 0 = wild); z: ring & chaperone fade (0 is not faded, 1 is faded); w: change the sky's own depth
} dynFragUniData;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) flat in vec4 objPosition; // [tdbe] mesh position, scale
layout(location = 3) flat in vec4 objRot; // [tdbe] mesh rotation
layout(location = 4) flat in int glViewIndex;

layout(location = 0) out vec4 outColor;

bool isOnGrid(float position, float threshold)
{
  return position < threshold || position > 1.0 - threshold;
}

vec4 mulQuat(vec4 quat1, vec4 quat2)
{
    return vec4(
        quat2.xyz * quat1.w + quat1.xyz * quat2.w + cross(quat1.xyz, quat2.xyz),
        quat1.w * quat2.w - dot(quat1.xyz, quat2.xyz)
    );
}

vec4 conjugateQuat(vec4 quat)
{
    return vec4(-quat.x, -quat.y, -quat.z, quat.w);
}

vec4 inverseQuat(vec4 quat)
{
    return conjugateQuat(quat) / 
        (quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);
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

mat4 matAxisAngleClockwise(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

vec4 quatFromAngleAxis(float angle, vec3 axis)
{
  return vec4(
      axis.x * sin(angle/2),
      axis.y * sin(angle/2),
      axis.z * sin(angle/2),
      cos(angle/2)
  );
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

float remapInterval(in float val, in float vmin, in float vmax, in float newmin, in float newmax)
{
	if(val<vmin)
		val = vmin;
	return (val - vmin) * (newmax - newmin) / (vmax - vmin) + newmin;
}

float getChaperoneTunnelDist(vec2 screenspacePos01)
{
	// [tdbe] annoying that all we get screenspace-wise by default in vulkan is gl_FragCoord (which is in pixels), and we don't at least also get the view size in pixels with it
	// https://www.khronos.org/opengl/wiki/Fragment_Shader
    //const vec2 screenspacePos01 = gl_FragCoord.xy / staFragUniData.screenSizePixels;

	const float customDepth = 1.3;
	float ipd = -staFragUniData.ipd * customDepth;
    if(glViewIndex == 0)
        ipd *=-1;
    return remapInterval(
			distance(screenspacePos01, vec2(0.5 + ipd, 0.5)),
			0.0, 0.5, 0.0, 1.0);
}

float getRingDF(float tunnelDF)
{
	float clampedDist = 0;
	const float diff = abs(tunnelDF - dynFragUniData.perMaterialFlags.x);

	if(diff > dynFragUniData.perMaterialFlags.x)
		clampedDist = dynFragUniData.perMaterialFlags.x;

	clampedDist = remapInterval(diff, 0, dynFragUniData.perMaterialFlags.x, 1, 0);
	return clamp(clampedDist, 0, 1);
}

// kinonik https://www.shadertoy.com/view/tlcBRl
//mini
float noise1(float seed1,float seed2){
return(
fract(seed1+12.34567*
fract(100.*(abs(seed1*0.91)+seed2+94.68)*
fract((abs(seed2*0.41)+45.46)*
fract((abs(seed2)+757.21)*
fract(seed1*0.0171))))))
* 1.0038 - 0.00185;
}

// kinonik https://www.shadertoy.com/view/tlcBRl
//2 seeds
float noise2(float seed1,float seed2){
float buff1 = abs(seed1+100.94) + 1000.;
float buff2 = abs(seed2+100.73) + 1000.;
buff1 = (buff1*fract(buff2*fract(buff1*fract(buff2*0.63))));
buff2 = (buff2*fract(buff2*fract(buff1+buff2*fract(seed1*0.79))));
buff1 = noise1(buff1, buff2);
return(buff1 * 1.0038 - 0.00185);
}

// kinonik https://www.shadertoy.com/view/tlcBRl
//3 seeds
float noise2(float seed1,float seed2,float seed3){
float buff1 = abs(seed1+100.81) + 1000.3;
float buff2 = abs(seed2+100.45) + 1000.2;
float buff3 = abs(noise1(seed1, seed2)+seed3) + 1000.1;
buff1 = (buff3*fract(buff2*fract(buff1*fract(buff2*0.146))));
buff2 = (buff2*fract(buff2*fract(buff1+buff2*fract(buff3*0.52))));
buff1 = noise1(buff1, buff2);
return(buff1);
}

// kinonik https://www.shadertoy.com/view/tlcBRl
//3 seeds hard
float noise3(float seed1,float seed2,float seed3)
{
	float buff1 = abs(seed1+100.813) + 1000.314;
	float buff2 = abs(seed2+100.453) + 1000.213;
	float buff3 = abs(noise1(buff2, buff1)+seed3) + 1000.17;
	buff1 = (buff3*fract(buff2*fract(buff1*fract(buff2*0.14619))));
	buff2 = (buff2*fract(buff2*fract(buff1+buff2*fract(buff3*0.5215))));
	buff1 = noise2(noise1(seed2,buff1), noise1(seed1,buff2), noise1(seed3,buff3));
	return(buff1);
}

/*  magician0809 https://www.shadertoy.com/view/wstGDN  */
float hash21_m0(vec2 p)
{
    p = fract(p * vec2(234.34, 435.345));
    p += dot(p, p + 34.23);
	return fract(p.x * p.y);
}

// noise function from https://www.shadertoy.com/view/Msf3WH
vec2 hash_m0( vec2 p ) // replace this by something better
{
	p = vec2( dot(p,vec2(127.1,311.7)), dot(p,vec2(269.5,183.3)) );
	return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}
float simplex_noise_m0( in vec2 p )
{
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;

	vec2  i = floor( p + (p.x+p.y)*K1 );
    vec2  a = p - i + (i.x+i.y)*K2;
    float m = step(a.y,a.x); 
    vec2  o = vec2(m,1.0-m);
    vec2  b = a - o + K2;
	vec2  c = a - 1.0 + 2.0*K2;
    vec3  h = max( 0.5-vec3(dot(a,a), dot(b,b), dot(c,c) ), 0.0 );
	vec3  n = h*h*h*h*vec3( dot(a,hash_m0(i+0.0)), dot(b,hash_m0(i+o)), dot(c,hash_m0(i+1.0)));
    return dot( n, vec3(70.0) );
}

vec3 curl_noise_m0(vec2 p, float freq, float t)
{
	p *= freq;
	p += t;

	const float NSIZE = 1.25;
	const float NSPEED = 0.12;

    const float dt = 1e-4;
    vec2 ds = vec2(dt, 0.0);
    
    p /= NSIZE;
    float n0 = simplex_noise_m0(p);
    float n1 = simplex_noise_m0(p + ds.xy);
    float n2 = simplex_noise_m0(p + ds.yx);
    
    vec2 grad = vec2(n1 - n0, n2 - n0) / ds.x;
    vec2 curl = vec2(grad.y, -grad.x);
    return vec3(curl, n0) * NSIZE * NSPEED;
}
/*  /magician0809 https://www.shadertoy.com/view/wstGDN  */

/*  piyushslayer https://www.shadertoy.com/view/tdcXDf */
// Hash functions by Dave_Hoskins
float hash12(vec2 p)
{
	uvec2 q = uvec2(ivec2(p)) * uvec2(1597334673U, 3812015801U);
	uint n = (q.x ^ q.y) * 1597334673U;
	return float(n) * (1.0 / float(0xffffffffU));
}

vec2 hash22(vec2 p)
{
	uvec2 q = uvec2(ivec2(p))*uvec2(1597334673U, 3812015801U);
	q = (q.x ^ q.y) * uvec2(1597334673U, 3812015801U);
	return vec2(q) * (1.0 / float(0xffffffffU));
}

float perlin (vec2 uv) {
    vec2 id = floor(uv);
    vec2 gv = fract(uv);

    // Four corners in 2D of a tile
    float a = hash12(id);
    float b = hash12(id + vec2(1.0, 0.0));
    float c = hash12(id + vec2(0.0, 1.0));
    float d = hash12(id + vec2(1.0, 1.0));

    vec2 u = gv * gv * (3.0 - 2.0 * gv);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

vec2 curl (vec2 uv)
{
    vec2 eps = vec2(0., 1.);
    
    float n1, n2, a, b;
    n1 = perlin(uv+eps);
    n2 = perlin(uv-eps);
    a = (n1-n2)/(2.*eps.y); // _x1/_y
    
    n1 = perlin(uv+eps.yx);
    n2 = perlin(uv-eps.yx);
    b = (n1-n2)/(2.*eps.y); // _y1/_x
    
    return vec2(a, -b);
}

float worley(vec2 uv, float freq, float t)
{
    uv *= freq;
    uv += t;
    
    vec2 id = floor(uv);
    vec2 gv = fract(uv);
    
    float minDist = 100.;
    for (float y = -1.; y <= 1.; ++y)
    {
        for(float x = -1.; x <= 1.; ++x)
        {
            vec2 offset = vec2(x, y);
            vec2 h = hash22(id + offset) * .8 + .1; // .1 - .9
    		h += offset;
            vec2 d = gv - h;
           	minDist = min(minDist, dot(d, d));
        }
    }
    
    return minDist + .4;
}

// Worley noise fbm using uvs offset by curl noise
vec3 fbmCurlWorley(vec2 uv, float freq, float t)
{
    float worley1 = 1. - worley(uv, freq * 2., t * 2.);
    float worley2 = 1. - worley(uv, freq * 4., t * 4.);
    float worley3 = 1. - worley(uv, freq * 8., t * 8.);
    float worley4 = 1. - worley(uv, freq * 16., t * 16.);
    
    float fbm1 = worley1 * .625 + worley2 * .25 + worley3 * .125;
    float fbm2 = worley2 * .625 + worley3 * .25 + worley4 * .125;
    float fbm3 = worley3 * .75 + worley4 * .25;
    return vec3(fbm1, fbm2, fbm3);
}
/*  /piyushslayer https://www.shadertoy.com/view/tdcXDf */

void main()
{
    float fragdepth = gl_FragCoord.z;
    if(dynFragUniData.perMaterialFlags.w < 1.0)
    {
        //The gl_FragCoord.z component is the depth value that would be used for the fragment's depth if no shader contained any writes to gl_FragDepth. 
        vec3 pos = position - objPosition.xyz;
        pos = rotateWithQuat(pos.xyz, objRot);

        const float scale = objPosition.w;
        const float animation = abs(sin(staFragUniData.time + pos.x / 10.0 + pos.z / 10.0));
        const float crossThickness = scale * 0.01 + animation * 0.0025;
        const float crossLength = scale * 0.05 + animation * 0.01;

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
	    const vec3 curl3 = curl_noise_m0(screenspacePos01, 8.0, staFragUniData.time);
	    float curl = curl3.r * 0.5 + curl3.g * 0.25 + curl3.b * 0.125;//625
	    screenspacePos01 = mix(screenspacePos01, screenspacePos01 * curl, mix(curl * 0.225, curl * 0.0125, dynFragUniData.perMaterialFlags.y));
        const float tunnelDF = getChaperoneTunnelDist(screenspacePos01);

        const float animationRing = abs(sin(staFragUniData.time));
        const float thicknessRing = 0.9875 + animationRing * 0.0125;
	    const float ringDF = pow(getRingDF(tunnelDF) * thicknessRing, 14);//12
        const float ringDF_innerHalf = clamp(remapInterval(ringDF, 0.5, 1.0, 0.0, 1.0), 0.0, 1.0);
	    const float ringDf_outerHalf = clamp(remapInterval(ringDF, 0.0, 0.5, 0.0, 1.0), 0.0, 1.0);
        const vec3 ringCentreColor1 = vec3(0.0, 1.0, 0.0);
		const vec3 ringOuterColor1 = vec3(1.0, 0.0, 1.0);
		const vec3 ringColor1 = mix(ringOuterColor1, ringCentreColor1, clamp(ringDF_innerHalf + 0.33, 0.0, 1.0));
		const vec3 ringCentreColor2 = vec3(0.0, 1.0, 0.5);
		const vec3 ringOuterColor2 = vec3(0.5, 0.0, 1.0);
		const vec3 ringColor2 = mix(ringOuterColor2, ringCentreColor2, clamp(ringDF_innerHalf + 0.33, 0.0, 1.0));

        const float fadeLength = 15.0;
        const float len = length(pos.xz);
        const float fade = clamp(1.0 - len / fadeLength, 0.0, 1.0);

        const vec3 floorCharacterAuraColor = vec3(0.2, 0.18, 0.22);
        outColor.rgb = mix(backgroundColor, floorCharacterAuraColor, fade);
        //outColor.rgb = mix(outColor.rgb, ringColor, ringDF);
        //outColor.rgb = mix(outColor.rgb, ringColor, mix(ringDF, ringDF * curl, curl * 1.3));
        outColor.rgb = mix(outColor.rgb, mix(ringColor1, ringColor2, curl * 1.25), ringDF);

        outColor.a = max(outColor.a * color.a, ringDF);

        if(tunnelDF > dynFragUniData.perMaterialFlags.x)
        {
            gl_FragDepth = dynFragUniData.perMaterialFlags.w;
        }
        else // [tdbe] inside tunnel
        {
            outColor.a *= max(fade, ringDF);
            
            if(dynFragUniData.perMaterialFlags.w < fragdepth)
            {
                // [tdbe] Note: this is not necessary, it's just cool. Also, we could just add a fullscreen quad under the sky to avoid the "need" for this.
			    const float stronk = pow(ringDF, 6);
                gl_FragDepth = mix(fragdepth, dynFragUniData.perMaterialFlags.w, stronk);
                outColor.rgb = mix(outColor.rgb, ringCentreColor1, gl_FragDepth * stronk);
            }
            else 
            {
                gl_FragDepth = fragdepth;
            }
        }

        // [tdbe] draw the grid on top
        if ((isOnGrid(gx, crossThickness) && isOnGrid(gz, crossLength)) || (isOnGrid(gz, crossThickness) && isOnGrid(gx, crossLength)))
        {
            const float fadeLengthCross = 10.0 * min(1.5, scale);
            const float fadeCrosses = clamp(1.0 - len / fadeLengthCross, 0.0, 1.0);
        
            outColor.rgb = mix(outColor.rgb, color.xyz, fadeCrosses);

            gl_FragDepth = dynFragUniData.perMaterialFlags.w;
        }

        outColor.rgb = mix(outColor.rgb, vec3(0.025, 0.025, 0.025), dynFragUniData.perMaterialFlags.z * ringDF);
        outColor.rgb = mix(addFog(outColor.rgb, vec3(0.5, 0.46, 0.54), 0.02), outColor.rgb, ringDF * 1.05);  

        gl_FragDepth -= 0.00005;// [tdbe] don't z-fight with any flat ground
    }
    else
    {
        gl_FragDepth = fragdepth;
        discard;
    }
}