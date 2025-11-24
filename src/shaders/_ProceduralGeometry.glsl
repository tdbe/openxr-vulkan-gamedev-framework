bool isOnGrid(float position, float threshold)
{
  return position < threshold || position > 1.0 - threshold;
}

bool isOnGrid(vec2 position, float threshold)
{
  return position.x < threshold && position.y < threshold || position.x > 1.0 - threshold && position.y > 1.0 - threshold;
}

float sdfCircle(vec2 uv, float rad, vec2 offset) 
{
	float x = uv.x - offset.x;
	float y = uv.y - offset.y;
	return length(vec2(x, y)) - rad;
}

vec2 opRepeatUv(vec2 point, float rad, vec2 cen)
{
	return mod(point + 0.5 * cen, cen) - 0.5 * cen;
}

float opRepeat(vec2 point, float rad, vec2 cen)
{
	vec2 uv = mod(point + 0.5 * cen, cen) - 0.5 * cen;
	return sdfCircle(uv, rad, vec2(0));
}

// IQ
vec3 smoothMin( in vec3 a, in vec3 b, in float k )
{
    k *= 4.0;
    float h = max(k-abs(a.x-b.x),0.0);
    float m = 0.25*h*h/k;
    float n = 0.50*  h/k;
    return vec3( min(a.x,  b.x) - m, 
                 mix(a.yz, b.yz, (a.x<b.x)?n:1.0-n) );
}

vec2 smoothMin( in vec2 a, in vec2 b, in float k )
{
    k *= 4.0;
    float h = max(k-abs(a.x-b.x),0.0);
    float m = 0.25*h*h/k;
    float n = 0.50*  h/k;
    return vec2( min(a.x,  b.x) - m, 
                 mix(a.y, b.y, (a.x<b.x)?n:1.0-n) );
}

float smoothMin( in float a, in float b, in float k )
{
    k *= 4.0;
    float h = max(k-abs(a-b),0.0);
    float m = 0.25*h*h/k;
    return min(a,  b) - m;
}

float getChaperoneTunnelDist(vec2 screenspacePos01, float ipd, int glViewIndex)
{
	// [tdbe] annoying that all we get screenspace-wise by default in vulkan is gl_FragCoord (which is in pixels), and we don't at least also get the view size in pixels with it
	// https://www.khronos.org/opengl/wiki/Fragment_Shader
	//const vec2 screenspacePos01 = gl_FragCoord.xy / staFragUniData.screenSizePixels;
	
	// [tdbe] for screen recording so it's less boring, less small:
	//screenspacePos01+= vec2(0.6, 0.6);
	//screenspacePos01*=0.45;

	const float customDepth = 1.25;//1.3;
	float cipd = -ipd * customDepth;
    if(glViewIndex == 0)
        cipd *=-1;

	// [tdbe] split the space to make a main portal and 3 extra ones around it.
	const float distCenter =	 distance(screenspacePos01, vec2(0.50 + cipd, 0.50));
	float distCorner =										// (y = 0.0 bottom, 1.0 top)
								 distance(screenspacePos01, vec2(0.5 + cipd, 0.375)) - 0.025;
								 //distance(screenspacePos01, vec2(0.635 + cipd, 0.635));
	//distCorner = min(distCorner, distance(screenspacePos01, vec2(0.365 + cipd, 0.635)));
	distCorner = min(distCorner, distance(screenspacePos01, vec2(0.635 + cipd, 0.45)));
	distCorner = min(distCorner, distance(screenspacePos01, vec2(0.365 + cipd, 0.45)));
	const float smoothness = 0.01085;// [tdbe] less means stronger contrast, less smoothness
	const float cornersInvScale = 0.1;// [tdbe] less means bigger disc
    return 0.1205 + remapInterval(
			clamp(smoothMin(distCenter, cornersInvScale + distCorner, smoothness), 0.0, 0.5),
			0.0, 0.5, 0.0, 1.0);

	/*
	const vec2 absScaledViewspacePos = abs(viewspacePos.xy * 0.01);
	const float dist = distance(vec2(0, 0), absScaledViewspacePos.xy);
	return pow(dist, 9);
	*/
}

float getRingDF(float tunnelDF, float thresh)
{
	float clampedDist = 0;
	const float diff = abs(tunnelDF - thresh);

	if(diff > thresh)
		clampedDist = thresh;

	clampedDist = remapInterval(diff, 0, thresh, 1, 0);
	return clamp(clampedDist, 0, 1);
}

vec3 tentacleMovement(float index, vec3 point, vec3 origin, float distToBase, float lightLengthWs, float time, vec3 directionNormalized, float speed /*= 0.5*/)
{
	point -= origin;
	// [tdbe] the problem is not how much I bend here, but how much I bend here + the angle the flimsy mrp distribution light was already at before making it a tentacle.
	// needs more research, but I'd rather use a different area light approach altogether. Or just give up for non-raytraced lights.
	float how_much_I_can_get_away_with_it = 0.025 * min(4.0, lightLengthWs);
    float amplitude = how_much_I_can_get_away_with_it * distToBase;
    time = time * speed + index * 15;

	vec3 dirUp = vec3(-0.15, 1.0, 0.15);
	vec3 dirH = -cross(directionNormalized, dirUp);
	
	// [tdbe] up-down
	float highFreqOctave = sin(time * 2.5);
	float lowFreqOctave = sin(distToBase * 3.0 + time * 1.5);
	point *= matrAxisAngleClockwiseX3(dirH, lowFreqOctave * highFreqOctave * amplitude);
    
	// [tdbe] left-right. This one needs to be the mirror of the vertex version of `tentacleMovement`
    float highFreqOctave2 = cos(time * 2.25);
    float lowFreqOctave2 = cos(distToBase * 3.0 + time * 1.25);
    point *= matrAxisAngleClockwiseX3(dirUp, -lowFreqOctave2 * highFreqOctave2 * amplitude);

	point += origin;
    return point;
}