
// kinonik https://www.shadertoy.com/view/tlcBRl
//mini
float noise1(float seed1,float seed2)
{
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
float noise2(float seed1, float seed2)
{
    float buff1 = abs(seed1+100.94) + 1000.;
    float buff2 = abs(seed2+100.73) + 1000.;
    buff1 = (buff1*fract(buff2*fract(buff1*fract(buff2*0.63))));
    buff2 = (buff2*fract(buff2*fract(buff1+buff2*fract(seed1*0.79))));
    buff1 = noise1(buff1, buff2);
    return(buff1 * 1.0038 - 0.00185);
}

// kinonik https://www.shadertoy.com/view/tlcBRl
//3 seeds
float noise2(float seed1, float seed2, float seed3)
{
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

vec3 curl_noise_m0(vec2 p, float freq, float time)
{
	p *= freq;
	p += time;

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
