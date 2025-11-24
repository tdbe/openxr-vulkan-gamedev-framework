#include "_Utils.glsl"

/// [tdbe] trick for chaperone: push vertices away from you 
/// so you don't get things "poking you in the eye" or otherwise dizzying during locomotion.
void dislocateForChaperone(int inLocomotion, float sphereMultiplier, mat4 camWorldMatrix, inout vec3 worldPosition, inout vec3 normalWs, inout vec3 color, inout float alpha)
{
    if(inLocomotion > 0)
    {
        // NOTE: the viewProjection space has 0.0 at the centre of the screen (for each eye).
        
        const float distCamToVertex = distance(worldPosition, camWorldMatrix[3].xyz);
        const float distCamToPortal = sphereMultiplier * 2.35;//2.30//2.225;
        
        const vec3 cameraForwardNN = -(camWorldMatrix[2].xyz);
        const vec3 camToVert = normalize(worldPosition - camWorldMatrix[3].xyz);
        const float camToVert_Dot_camFwd = dot(camToVert, normalize(cameraForwardNN));
        //const float yDiff = worldPosition.y - camWorldMatrix[3].y;
        const float distVertToPortal = distCamToPortal - distCamToVertex;

        //worldPosition += camToVert * distCamToPortal * PI / max(1.0, dist * dist); 
        
        if(distCamToVertex < distCamToPortal)
        {
            const vec3 cameraRight = normalize(camWorldMatrix[0].xyz);
            const vec3 cameraUp = normalize(camWorldMatrix[1].xyz);

            if(camToVert_Dot_camFwd >= 0.0 && distCamToVertex > 0.5)
            {
                // [tdbe] move things that are in a cone in front of you, up to where the portal is.
                const float moveAmount = clamp(camToVert_Dot_camFwd, 0.0, 1.0) * (distVertToPortal);
                worldPosition += camToVert * moveAmount * 1.125 * (clamp01(distVertToPortal));//1.325
                //alpha = 1-clamp((moveAmount * 0.75 - 0.25), 0.0, 1.0);
                alpha *= 1-remapInterval(clamp(moveAmount, 0.785, 1.0), 0.785, 1.0, 0.0, 1.0);

                // [tdbe] camera forward as normals, just for visual effect
                normalWs = mix(-cameraForwardNN, normalWs, (clamp01(remapInterval(distCamToVertex, 1.85, 2.0, 0.33, 1.0))));

                // [tdbe] make the intersection point with the portal look like the ring colors
                const vec3 color0 = mix(color.rgb, vec3(1.0, 1.0, -0.5), remapInterval(clamp(moveAmount, 0.63, 1.0), 0.63, 1.0, 0.0, 1.0));
                const vec3 color1 = mix(color0, vec3(-1.0, 1.0, 0.5), remapInterval(clamp(moveAmount, 0.68, 1.0), 0.68, 1.0, 0.0, 1.0));
		        const vec3 color2 = mix(vec3(1.0, 0.0, 1.0), color1, alpha);
                color.rgb = color2;
            }
            else //if(0.0 > yDiff && yDiff > -0.5)// [tdbe] be more lax vs what is probably the ground beneath you, unless our ground is on a different shader
            {
                // [tdbe] if things are behind you, we could still be intersecting some undesirable long wall (but we could also be e.g. inside a house).
                alpha = 0.0;
            }
        }
        // [tdbe] in case we have very long walls etc. coming from behind us.
        else if (camToVert_Dot_camFwd < 0.0 && sphereMultiplier > 0.5)
            alpha = 0.0;            
    }
}

vec3 projectPointOnLine_vert(vec3 pt, vec3 lineStart, vec3 lineStartEnd)
{
    return lineStart + dot(pt - lineStart, lineStartEnd) / dot(lineStartEnd, lineStartEnd) * lineStartEnd;
}

vec3 projectPointOnLineNoOvershoot_vert(vec3 pt, vec3 lineStart, vec3 lineStartEnd, vec3 lineEnd)
{
	vec3 projected = projectPointOnLine(pt, lineStart, lineStartEnd);
	float t = dot(projected - lineStart, normalize(lineStartEnd)) / length(lineStartEnd);
	if (t < 0.0) 
		return lineStart;
	if (t > 1.0) 
		return lineEnd;
	return projected;

}

mat3 matrAxisAngleClockwiseX3_vert(vec3 axisNormalized, float angle)
{
    vec3 axis = axisNormalized;
    float s = sin(angle);
    float c = cos(angle);
    float ic = 1.0 - c;
    return mat3(ic * axis.x * axis.x + c,           ic * axis.x * axis.y - axis.z * s,  ic * axis.z * axis.x + axis.y * s,
                ic * axis.x * axis.y + axis.z * s,  ic * axis.y * axis.y + c,           ic * axis.y * axis.z - axis.x * s,
                ic * axis.z * axis.x - axis.y * s,  ic * axis.y * axis.z + axis.x * s,  ic * axis.z * axis.z + c);
}

vec3 rotateZ_vert(vec3 vec, float angle) 
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

vec3 tentacleMovement_vert(float index, vec3 point, vec3 origin, float distToBase, float lightLengthWs,  float time, vec3 directionNormalized, float speed /*= 0.5*/)
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
	point *= matrAxisAngleClockwiseX3_vert(dirH, lowFreqOctave * highFreqOctave * amplitude);

    // [tdbe] left-right
    float highFreqOctave2 = cos(time * 2.25);
    float lowFreqOctave2 = cos(distToBase * 3.0 + time * 1.25);
    point *= matrAxisAngleClockwiseX3_vert(dirUp, lowFreqOctave2 * highFreqOctave2 * amplitude);

    point += origin;
    return point;
}