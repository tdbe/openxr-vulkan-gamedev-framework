const float PI = 3.1415926;
const float HALFPI = 1.5707963;
const float TWOPI = 6.2831852;
const float DITHER_UV_TEXELSCALE = 1920;
const float MAX_WORLD_HEIGHT = 128.0;

// [tdbe] glsl/vulkan "clamp(val, 0.0, 1.0)" is the devil.
float clamp01(const in float val) { return clamp(val, 0.0, 1.0); }
vec2 clamp01(const in vec2 val) { return clamp(val, 0.0, 1.0); }
vec3 clamp01(const in vec3 val) { return clamp(val, 0.0, 1.0); }
vec4 clamp01(const in vec4 val) { return clamp(val, 0.0, 1.0); }
float saturate(const in float val) { return clamp(val, 0.0, 1.0); }
vec2 saturate(const in vec2 val) { return clamp(val, 0.0, 1.0); }
vec3 saturate(const in vec3 val) { return clamp(val, 0.0, 1.0); }
vec4 saturate(const in vec4 val) { return clamp(val, 0.0, 1.0); }

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// Alexis Naveros https://amindforeverprogramming.blogspot.com/2013/07/random-floats-in-glsl-330.html?showComment=1507064059398#c5427444543794991219
uint hashInt1D( uint x )
{
    x += x >> 11;
    x ^= x << 7;
    x += x >> 15;
    x ^= x << 5;
    x += x >> 12;
    x ^= x << 9;
    return x;
}

// Alexis Naveros https://amindforeverprogramming.blogspot.com/2013/07/random-floats-in-glsl-330.html?showComment=1507064059398#c5427444543794991219
uint hashInt2D( uint x, uint y )
{
    x += x >> 11;
    x ^= x << 7;
    x += y;
    x ^= x << 6;
    x += x >> 15;
    x ^= x << 5;
    x += x >> 12;
    x ^= x << 9;
    return x;
}

// Alexis Naveros https://amindforeverprogramming.blogspot.com/2013/07/random-floats-in-glsl-330.html?showComment=1507064059398#c5427444543794991219
uint hashInt3D( uint x, uint y, uint z )
{
    x += x >> 11;
    x ^= x << 7;
    x += y;
    x ^= x << 3;
    x += z ^ ( x >> 14 );
    x ^= x << 6;
    x += x >> 15;
    x ^= x << 5;
    x += x >> 12;
    x ^= x << 9;
    return x;
}

// https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl/28095165#28095165
float random( float f ) 
{
    if(f < 0.001)
        return 0.0;
    const uint mantissaMask = 0x007FFFFFu;
    const uint one          = 0x3F800000u;
       
    uint h = hashInt1D( floatBitsToUint( f.x ));
    h &= mantissaMask;
    h |= one;
        
    float  r2 = uintBitsToFloat( h );
    return r2 - 1.0;
}

// https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl/28095165#28095165
float random( vec2 f ) 
{   
    if(f.x < 0.001 && f.y < 0.001)
        return 0.0;
    const uint mantissaMask = 0x007FFFFFu;
    const uint one          = 0x3F800000u;
       
    uint h = hashInt2D( floatBitsToUint( f.x ), floatBitsToUint( f.y ) );
    h &= mantissaMask;
    h |= one;
        
    float  r2 = uintBitsToFloat( h );
    return r2 - 1.0;
}

// https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl/28095165#28095165
float random( vec3 f ) 
{
    if(f.x < 0.001 && f.y < 0.001 && f.z < 0.001)
        return 0.0;
    const uint mantissaMask = 0x007FFFFFu;
    const uint one          = 0x3F800000u;
       
    uint h = hashInt3D( floatBitsToUint( f.x ), floatBitsToUint( f.y ), floatBitsToUint( f.z ) );
    h &= mantissaMask;
    h |= one;
        
    float  r2 = uintBitsToFloat( h );
    return r2 - 1.0;
}

float poww(float v, float p) 
{
    return pow(v, p);
}

vec2 poww(vec2 v, float p) 
{
    return vec2(pow(v.x, p), pow(v.y, p));
}

vec3 poww(vec3 v, float p) 
{
    return vec3(pow(v.x, p), pow(v.y, p), pow(v.z, p));
}

float remapInterval(in float val, in float vmin, in float vmax, in float newmin, in float newmax)
{
	if(val<vmin)
		val = vmin;
	return (val - vmin) * (newmax - newmin) / (vmax - vmin) + newmin;
}

vec2 remapInterval(in vec2 val, in float vmin, in float vmax, in float newmin, in float newmax)
{
	return vec2(remapInterval(val.x, vmin, vmax, newmin, newmax), 
                remapInterval(val.y, vmin, vmax, newmin, newmax));
}

vec3 remapInterval(in vec3 val, in float vmin, in float vmax, in float newmin, in float newmax)
{
	return vec3(remapInterval(val.x, vmin, vmax, newmin, newmax), 
                remapInterval(val.y, vmin, vmax, newmin, newmax),
                remapInterval(val.z, vmin, vmax, newmin, newmax));
}

vec3 projectPointOnLine(vec3 pt, vec3 lineStart, vec3 lineStartEnd)
{
    return lineStart + dot(pt - lineStart, lineStartEnd) / dot(lineStartEnd, lineStartEnd) * lineStartEnd;
}

vec3 projectPointOnLineNoOvershoot(vec3 pt, vec3 lineStart, vec3 lineStartEnd, vec3 lineEnd)
{
	vec3 projected = projectPointOnLine(pt, lineStart, lineStartEnd);
	float t = dot(projected - lineStart, normalize(lineStartEnd)) / length(lineStartEnd);
	if (t < 0.0) 
		return lineStart;
	if (t > 1.0) 
		return lineEnd;
	return projected;

}

vec3 projectVectors(vec3 v0, vec3 v1)
{
    float v1_dot_v1_sqr_magnitude = dot(v1, v1);
    if (v1_dot_v1_sqr_magnitude == 0.0) 
        return vec3(0.0);
    return (dot(v0, v1) / v1_dot_v1_sqr_magnitude) * v1;
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

mat4 matrAxisAngleClockwise(vec3 axisNormalized, float angle)
{
    vec3 axis = axisNormalized;
    float s = sin(angle);
    float c = cos(angle);
    float ic = 1.0 - c;
    return mat4(ic * axis.x * axis.x + c,           ic * axis.x * axis.y - axis.z * s,  ic * axis.z * axis.x + axis.y * s,  0.0,
                ic * axis.x * axis.y + axis.z * s,  ic * axis.y * axis.y + c,           ic * axis.y * axis.z - axis.x * s,  0.0,
                ic * axis.z * axis.x - axis.y * s,  ic * axis.y * axis.z + axis.x * s,  ic * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}


mat3 matrAxisAngleClockwiseX3(vec3 axisNormalized, float angle)
{
    vec3 axis = axisNormalized;
    float s = sin(angle);
    float c = cos(angle);
    float ic = 1.0 - c;
    return mat3(ic * axis.x * axis.x + c,           ic * axis.x * axis.y - axis.z * s,  ic * axis.z * axis.x + axis.y * s,
                ic * axis.x * axis.y + axis.z * s,  ic * axis.y * axis.y + c,           ic * axis.y * axis.z - axis.x * s,
                ic * axis.z * axis.x - axis.y * s,  ic * axis.y * axis.z + axis.x * s,  ic * axis.z * axis.z + c);
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

vec3 rotateZ(vec3 vec, float angle) 
{
    if(angle < 0.001)
        return vec;
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    return vec3(
        vec.x * cosAngle - vec.y * sinAngle,
        vec.x * sinAngle + vec.y * cosAngle,
        vec.z
    );
}

vec2 rotateZ(vec2 vec, float angle) 
{
    if(angle < 0.001)
        return vec;
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    return vec2(
        vec.x * cosAngle - vec.y * sinAngle,
        vec.x * sinAngle + vec.y * cosAngle
    );
}

vec3 rotateY(vec3 vec, float angle) 
{
    if(angle < 0.001)
        return vec;
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    return vec3(
        vec.x * cosAngle - vec.z * sinAngle,
        vec.y,
        vec.x * sinAngle + vec.z * cosAngle
    );
}

vec3 scaleAlongVector(vec3 vector, vec3 scalingDirNormalized, float scale) 
{
    vec3 projection = dot(vector, scalingDirNormalized) * scalingDirNormalized;
    vec3 scaledProjection = projection * scale;
    vec3 perpendicularComponent = vector - projection;
    return scaledProjection + perpendicularComponent;
}

// https://gist.github.com/mairod/a75e7b44f68110e1576d77419d608786
vec3 hue_shift(vec3 color, float dhue) 
{
	float s = sin(dhue);
	float c = cos(dhue);
	return (color * c) + (color * s) * mat3(
		vec3(0.167444, 0.329213, -0.496657),
		vec3(-0.327948, 0.035669, 0.292279),
		vec3(1.250268, -1.047561, -0.202707)
	) + dot(vec3(0.299, 0.587, 0.114), color) * (1.0 - c);
}

// From https://github.com/gkjohnson/unity-dithered-transparency-shader/tree/master
// Returns > 0 if not clipped, < 0 if clipped based on the dither
// For use with the "clip" function
// [tdbe] pos is the fragment position in screen pixels space e.g. [1920,1080]
// if the result is < 0.0, it is transparent / dithered / you should "discard"
// (the clip function (not available in vulkan) can receive this float as a param
// and discards on its own if it's negative)
float isDithered(vec2 pos, float alpha) 
{
    // Define a dither threshold matrix which can
    // be used to define how a 4x4 set of pixels
    // will be dithered
    const float DITHER_THRESHOLDS[16] =
    {
        1.0 / 17.0,  9.0 / 17.0,  3.0 / 17.0, 11.0 / 17.0,
        13.0 / 17.0,  5.0 / 17.0, 15.0 / 17.0,  7.0 / 17.0,
        4.0 / 17.0, 12.0 / 17.0,  2.0 / 17.0, 10.0 / 17.0,
        16.0 / 17.0,  8.0 / 17.0, 14.0 / 17.0,  6.0 / 17.0
    };

    const int index = (int(pos.x) % 4) * 4 + int(pos.y) % 4;
    return (alpha - DITHER_THRESHOLDS[index]);
}