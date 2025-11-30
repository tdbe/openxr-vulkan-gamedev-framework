const int LIGHT_COUNT = 10;
const int COLOR = 0; const int CENTRAL_VEC = 1; const int SHAPE_VEC_0 = 2; const int SHAPE_VEC_1 = 3;
const int LIGHT_TYPE_DIRECTIONAL = 0; const int LIGHT_TYPE_POINT = 1; const int LIGHT_TYPE_SPHERE = 2; 
const int LIGHT_TYPE_TUBE = 3; const int LIGHT_TYPE_CUBE = 4; const int LIGHT_TYPE_QUAD = 5; const int LIGHT_TYPE_DISC = 6;
const int LIGHT_TYPE_TENTACLE = 103;
const float LIGHT_CULL_INTENSITY = 0.000125; // [tdbe] cull lights that are too weak to be visible
const float FROSTBITE_MIN_ROUGHNESS = 0.045; // [tdbe] reduce specular aliasing, also avoid invisible specular highlights

/// [tdbe] takes the first 3 rows of ambientLight and makes a crude gradient ambient
vec3 sampleAmbient(vec3 surfaceNormal, vec3 up, mat4 ambientLight)
{
	const float lu1d = dot(surfaceNormal, up);
	vec3 outColor = vec3(0,0,0);
	float thresh = 0.175;
	if(lu1d > thresh)
		outColor.rgb = mix(ambientLight[1].rgb, ambientLight[0].rgb, remapInterval(lu1d,thresh, 1.0, 0, 1));
	else if(lu1d > 0.0)
		outColor.rgb = ambientLight[1].rgb;
	else if(lu1d > -thresh)
		outColor.rgb = mix(ambientLight[1].rgb, ambientLight[2].rgb, remapInterval(abs(lu1d), 0.0, thresh, 0, 1));
	else
		outColor.rgb = ambientLight[2].rgb;

	return outColor;

	// [tdbe] some reference colors
	// top: vec3(0.351, 0.422, 0.562);
	// horiz: vec3(0.929, 1.0, 1.0);
	// ground: vec3(0.396, 0.376, 0.353);
	// purple? vec3(0.1, 0.08, 0.12);
	// purpler? vec3(0.2, 0.18, 0.22);
}

/// [tdbe] takes the first 3 rows of ambientLight and makes a crude gradient ambient
vec3 sampleAmbient(vec3 surfaceNormal, vec3 up, mat4 ambientLight, float world_y_pos, float maxHeight)
{
	const float heightNormalized = clamp(world_y_pos / maxHeight, 0.0, 1.0);
	// [tdbe] sample the ground color less the higher we are (ie more atmospheric scattering lowers the shadow under the sun)
	ambientLight[2].rgb = mix(ambientLight[2].rgb, ambientLight[1].rgb, heightNormalized*heightNormalized);

	const float lu1d = dot(surfaceNormal, up);
	vec3 outColor = vec3(0,0,0);
	float thresh = 0.175;
	if(lu1d > thresh)
		outColor.rgb = mix(ambientLight[1].rgb, ambientLight[0].rgb, remapInterval(lu1d,thresh, 1.0, 0, 1));
	else if(lu1d > 0.0)
		outColor.rgb = ambientLight[1].rgb;
	else if(lu1d > -thresh)
		outColor.rgb = mix(ambientLight[1].rgb, ambientLight[2].rgb, remapInterval(abs(lu1d), 0.0, thresh, 0, 1));
	else
		outColor.rgb = ambientLight[2].rgb;

	return outColor;

	// [tdbe] some reference colors
	// top: vec3(0.351, 0.422, 0.562);
	// horiz: vec3(0.929, 1.0, 1.0);
	// ground: vec3(0.396, 0.376, 0.353);
	// purple? vec3(0.1, 0.08, 0.12);
	// purpler? vec3(0.2, 0.18, 0.22);
}

/// [tdbe] takes the first 3 rows of ambientLight and makes a crude gradient ambient
vec3 sampleAmbientSky(vec3 normal, vec3 up, mat4 ambientLight)
{
	const float lu1d = dot(normal, up);
	vec3 outColor = vec3(0,0,0);
	float thresh = 0.125;
	if(lu1d > thresh)
		outColor.rgb = mix(ambientLight[1].rgb, ambientLight[0].rgb, remapInterval(lu1d, thresh, 1.0, 0, 1));
	else if(lu1d > 0.0)
		outColor.rgb = ambientLight[1].rgb;
	else if(lu1d > -thresh)
		outColor.rgb = mix(ambientLight[1].rgb, ambientLight[2].rgb, remapInterval(abs(lu1d), 0.0, thresh, 0, 1));
	else
		outColor.rgb = ambientLight[2].rgb;

	return outColor;
	// [tdbe] some reference colors
	// top: vec3(0.351, 0.422, 0.562);
	// horiz: vec3(0.929, 1.0, 1.0);
	// ground: vec3(0.396, 0.376, 0.353);
	// purple? vec3(0.1, 0.08, 0.12);
	// purpler? vec3(0.2, 0.18, 0.22);
}

// [tdbe] quick fog https://www.ozone3d.net/tutorials/glsl_fog/p04.php?lang=1
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

// [tdbe] quick fog with height changes. 
// I didn't look up ~*science*~ but I'm keeping most fog close to the ground, lgtm. 
vec3 addFog(vec3 finalColor, vec3 fogColor, float density, vec3 topSkyColor, float world_y_pos, float maxHeight)
{
	const float heightNormalized = clamp(world_y_pos / maxHeight, 0.0, 1.0);
	const float heightNormalizedSq = heightNormalized*heightNormalized;
	// [tdbe] change fog to match sky / upper atmosphere color, instead of ground / dust color
	finalColor = mix(finalColor, topSkyColor * topSkyColor, heightNormalizedSq);

	const float LOG2 = 1.442695;
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fogFactor = exp2( -density * density * 
						    z * z * 
						    LOG2 );

	fogFactor = clamp(fogFactor, 0.0, 1.0);
	// [tdbe] lower fog density with height
	fogFactor += clamp01(heightNormalizedSq + heightNormalized * 0.33);

	return mix(fogColor, finalColor, fogFactor);
}

/// [tdbe] normal Distribution function: Isotropic GGX Walter et al. 2007
float D_GGX_W07(in float n_Dot_h, in float roughness, in float shapedAlphaPrime)
{
	// integral hemisphere, normalizeAlpha2
	const float rouSqr = roughness * roughness;
    const float a = n_Dot_h * roughness;
    return rouSqr * shapedAlphaPrime / (PI * (1.0 - n_Dot_h * n_Dot_h + a * a) );
}

/// [tdbe] normal Distribution function: Isotropic GGX Trowbridge-Reitz 
/// From Walter et al. 2007, "Microfacet models for refraction through rough surfaces"
float D_GGX_TR(in float n_Dot_h, in float roughness, in float shapedAlphaPrime)
{
	// integral hemisphere, normalizeAlpha2
	const float rouSqr = roughness * roughness;
    const float distr = n_Dot_h * n_Dot_h * (rouSqr - 1.0) + 1.0;
    return rouSqr * shapedAlphaPrime / (PI * distr * distr );
}

/// [tdbe] normal Distribution function: Anisotropic GGX
/// Burley 2012, "Physically-Based Shading at Disney", Disney BRDF ("Disney Principled BRDF")
float D_GGX(in float n_Dot_h, in vec3 halfVector, in vec3 x_tangent_ws, in vec3 y_bitangent_ws, in float x_rougness, in float y_roughness)
{
	const float xr2 = x_rougness * x_rougness;
	const float yr2 = y_roughness * y_roughness;
	const float xt_dot_h = dot( x_tangent_ws, halfVector );
	const float yt_dot_h = dot( y_bitangent_ws, halfVector );
	const float dt = xt_dot_h * xt_dot_h / (xr2 * xr2) + yt_dot_h * yt_dot_h / (yr2 * yr2) + n_Dot_h * n_Dot_h;
	return 1.0 / ( PI * yr2 * yr2 * dt * dt );
}
// [tdbe] more reading: 
// https://google.github.io/filament/Filament.html
// https://mudstack.com/blog/tutorials/physically-based-rendering-study-part-2/

vec3 F_SchlickF(in float l_Dot_h, in vec3 F0)
{
	const float l_Dot_h_5 = pow(1.0 - l_Dot_h, 5.0);
	return F0 + (vec3(1.0) - F0) * l_Dot_h_5;
}

// [tdbe] Smith Geometry half-factor in Schlick approximation
// Unreal / Brian Karis version
float G1V(in float n_Dot_l, in float k)
{
	return 1.0 / (n_Dot_l * (1.0 - k) + k);
}

// [tdbe] mobile optimization by Filament
float V_SmithGGXCorrelatedFast(in float n_Dot_l, in float n_Dot_v, in float roughness) {
    const float a = roughness;
    const float GGXV = n_Dot_l * (n_Dot_v * (1.0 - a) + a);
    const float GGXL = n_Dot_v * (n_Dot_l * (1.0 - a) + a);
    return 0.5 / (GGXV + GGXL);
}

// [tdbe] specular reflection visibility (roughness microfacets shadowing)
float V_GVis_SSBK(in float roughness, in float n_Dot_l, in float n_Dot_v)
{
	// [tdbe] Schlick approximation of Smith's Geometry term
	// [tdbe] Note: we already sanitized n_Dot_l and n_Dot_v to be >= stop
	// (this is the Unreal / Brian Karis version. Instead of r = (roughness + 1.0); k = (r*r) / 8.0;)
	const float k = roughness * roughness;// / 2.0;
	return G1V(n_Dot_l, k) * G1V(n_Dot_v, k);
}

// [tdbe] specular reflection visibility (roughness microfacets shadowing) via Filament
float V_GVis_SmithGGXCorrelated(float n_Dot_l, in float n_Dot_v, float roughness) {
    const float a2 = roughness * roughness;
    const float GGXV = n_Dot_l * sqrt(n_Dot_v * n_Dot_v * (1.0 - a2) + a2);
    const float GGXL = n_Dot_v * sqrt(n_Dot_l * n_Dot_l * (1.0 - a2) + a2);
    return 0.5 / (GGXV + GGXL);
}

vec3 Diffuse_Lambert_Blinn_Phong_Ambient(in vec3 F0, in float n_Dot_l)
{
	return F0 * ( 1.0 - pow(1.0 - n_Dot_l, 5.0));
}

vec3 Diffuse_Lambert_Blinn_Phong(in vec3 F0, in float n_Dot_l)
{
	return F0 * n_Dot_l;
}

/// [tdbe] From Disney BRDF ("Disney Principled BRDF")
vec3 Diffuse_Lambert_Disney_Ambient(in vec3 F0, in float n_Dot_l)
{
	return (F0 + (1.0 - F0) * pow(1.0 - n_Dot_l, 5.0)) / PI; // (1.0 + (F0 - 1.0)
}

/// [tdbe] Burley Disney BRDF: "Physically-Based Shading at Disney" 2012
/// "a novel empirical model for diffuse retroreflection that transitions
/// between a diffuse Fresnel shadow for smooth surfaces and an added highlight for rough surfaces."
vec3 BRDF_Diffuse_Disney_NE(in vec3 F0, in float n_Dot_l, in float v_Dot_h, in float n_Dot_v, in float roughness)
{
	const float Fd90 = 0.5 + 2.0 * v_Dot_h * v_Dot_h * roughness;
    const float FdV = 1.0 + (Fd90 - 1.0) * pow(1.0 - n_Dot_v, 5.0);
    const float FdL = 1.0 + (Fd90 - 1.0) * pow(1.0 - n_Dot_l, 5.0);
	// [tdbe] todo: probably not so good:
    return (F0 + (1.0 - F0) * FdV * FdL) / PI;
}

// [tdbe] I use Cook-Torrance BRDF: Specular = D*F*G
// D: GGX Distribution, F: Schlick-Fresnel, G/V: Schlick approximation of Smith solved with GGX
//Survey on various BRDFs, and general documentation:
// https://www.ea.com/frostbite/news/moving-frostbite-to-pb
// https://google.github.io/filament/Filament.html
// http://www.codinglabs.net/article_physically_based_rendering_cook_torrance.aspx
// http://graphicrants.blogspot.de/2013/08/specular-brdf-reference.html
// https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Shaders/BRDF.usf
// https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf
// http://simonstechblog.blogspot.de/2011/12/microfacet-brdf.html
//+ various shadertoys
//	 for ex this one has realistic material values: https://www.shadertoy.com/view/XssGzf
vec3 calcBRDF(
	in int lightType,
	in vec3 lightDir_spec,// [tdbe] the direction from surface to light
	in vec3 lightDir_diff,// can be identical to ^
	in vec3 viewDir,// the direction from surface to eye
	in vec3 surfaceNormal,
	in vec3 albedo,
	in vec3 lightColor,
	in float n_Dot_v,
	in float lightIntensity,
	in float matRoughness,
	in float matRoughnessSq,
	in float matMetallic,
	in vec3 F0,// specReflectance,
	in float occlusion, 
	in float shaped_n_Dot_l,
	in float aPrime_Karis_spec
)
{
	const float stop = LIGHT_CULL_INTENSITY;

	// [tdbe] half way vector between surface to light and surface to view
	const vec3 halfVector_spec = normalize(viewDir + lightDir_spec);
	const vec3 halfVector_diff = normalize(viewDir + lightDir_diff);
	// dots
	float n_Dot_l_spec = clamp(dot(surfaceNormal, lightDir_spec), stop, 1.0);
	float n_Dot_l_diff = clamp(dot(surfaceNormal, lightDir_diff), stop, 1.0);
	const float l_Dot_h_spec = clamp(dot(lightDir_spec, halfVector_spec), stop, 1.0);
	const float v_Dot_h_diff = clamp(dot(viewDir, halfVector_diff), stop, 1.0);
	const float n_Dot_h_spec = clamp(dot(surfaceNormal, halfVector_spec), stop, 1.0);
	//const float n_Dot_v = comes in from outside the lights loop;
	
	float roughnessGaussianDistributionAlpha = matRoughnessSq;
		
	// [tdbe] (An)isotropic microfacets normal Distribution Function.
	//const float Distribution = D_GGX_W07(n_Dot_h, roughnessGaussianDistributionAlpha);
	const float Distribution = D_GGX_TR(n_Dot_h_spec, roughnessGaussianDistributionAlpha, aPrime_Karis_spec);
	
	const vec3 Fresnel = F_SchlickF(l_Dot_h_spec, F0);

	float v_vis_n_Dot_l = n_Dot_l_spec;
	if(shaped_n_Dot_l != 1.0)
		v_vis_n_Dot_l = shaped_n_Dot_l;
	//const float GVis = V_GVis_SSBK(roughnessGaussianDistributionAlpha, v_vis_n_Dot_l, n_Dot_v);
	const float GVis = V_GVis_SmithGGXCorrelated(v_vis_n_Dot_l, n_Dot_v, roughnessGaussianDistributionAlpha);

	//const vec3 kSpec = n_Dot_l_spec * vec3((l_Dot_h_spec));
	//const vec3 kSpec = mix(vec3(1.0), albedo, matMetallic) * n_Dot_l_spec * Fresnel * Distribution * GVis / (4.0 * n_Dot_l * n_Dot_v);
	//const vec3 kSpec = mix(vec3(1.0), albedo, matMetallic) * n_Dot_l_spec * Fresnel * (Distribution * GVis);// / (4.0);
	const vec3 kSpec = mix(vec3(1.0), albedo, matMetallic) * n_Dot_l_spec * Fresnel * (Distribution * GVis);

	//const vec3 kLambDiff = n_Dot_l_diff * albedo / PI;
	// [tdbe] How to do diffuse component of area lights with disney's diffuse term: 
	// e.g. page 54-55 and 117-118 frostbyte: https://media.contentapi.ea.com/content/dam/eacom/frostbite/files/course-notes-moving-frostbite-to-pbr-v32.pdf
	// (aka course notes from here https://www.ea.com/frostbite/news/moving-frostbite-to-pb)
	// MRP (most representative point) is still inaccurate for diffuse, but there aren't any better solutions besides raytracing.
	// Added a 'better' MRP for the diffuse, like the paper, and like here: https://www.shadertoy.com/view/tl2GD3.
	const vec3 kLambDiff = (1.0 - matMetallic) * albedo * n_Dot_l_diff * 
						  BRDF_Diffuse_Disney_NE(F0, n_Dot_l_diff, v_Dot_h_diff, n_Dot_v, roughnessGaussianDistributionAlpha);

	// [tdbe] Note: smth smth law of conservation of energy, the K's, aka in orbitals talk the energy absorption coefficients 
	// of the energy conductor, aka the diffuse and specular components of your pixel, should sum to 1.0.

	//return (kSpec) * occlusion * lightColor * lightIntensity;
	//return (kLambDiff) * occlusion * lightColor * lightIntensity;
	return (kLambDiff + kSpec) * occlusion * lightColor * lightIntensity;
	
	// [tdbe] Todo: add clearcoat ie: Clearcoat property is an additional specular layer that is applied on top of a material. 
	// An example of this in effect is when a car is painted, and the paint acts as the additional layer. 
	// Another example is a pair of shoes after they have been polished or waxed.
	// e.g.: https://github.com/GarrettGunnell/Disney-PBR/blob/main/Assets/Shaders/DisneyBRDF.shader
}

// [tdbe] Getting the most-representative-point / closest-point-on-line and
// custom light direction, n dot l, and alpha prime, for both specular and diffuse components,
// to then feed into any existing Cook-Torrence BRDF.
// The Brian Karis technique of finding the closest point on segment to ray, is an alternative to Picott's smallest angle method.
// From / Todo: implement more of: 
// The more accurate frostbyte version has a tube light that is actually a quad light, it's heavier but lower maintenance / easier to get to look good.
// It's honestly probably more efficient given the dumb hacks I had to do to Karis' method to eliminate dealbreaking artifacts.
// https://www.ea.com/frostbite/news/moving-frostbite-to-pb,
// https://alextardif.com/arealights.html, 
// https://www.shadertoy.com/view/3dsBD4,
// https://www.elopezr.com/rendering-line-lights/,
// https://github.com/Unity-Technologies/VolumetricLighting/blob/master/Assets/TubeLight/Shaders/TubeLight.cginc,
// https://hal.science/hal-02155101/document,
// https://www.realtimerendering.com/intersections.html -- neat collection of intersections math
// -------------
// TL;DR overview of current method (line/tube light): https://blog.deferredreality.com/mrp-volumetric-lights-are-broken/
// - Get the line between light ends. 
// - Check for horizon (surface) intersection and move submerged light end point to the surface. 
// - If the light('s reflection) is pointing dead-on the same as the surface normal, then there is no line to calculate on, so we substitute it with the closest light end to the surface. 
// - Diffuse: pick the MRP diffuse distribution (unless it's the dead-on issue above). 
// - Specular: pick a specular MRP distribution (unless it's the dead-on issue above).
// - Also distort the n dot l, and aPrime roughness/radius.
void MRPointOnTubeLight(vec3 lightStartWS, vec3 centerAndRadiusWS, vec3 lightEndWS, 
					float lightType, float lightRadius, float lightLength,
					float roughness, float roughnessSq, inout float intensity, inout vec3 lightColor, inout vec3 fragPosWS, 
					float time, float lightIndex,
					vec3 normalReflectedView, vec3 normalReflectedViewWS, vec3 normal, vec3 normalWS,
					out vec3 lightDir_spec, out float lightDist_spec, out float tspec,
					out vec3 lightDir_diff, out float lightDist_diff, out float tdiff,
					out float tubeNdotL_spec, out float aPrime_spec)
{
	vec3 litend0WS = lightStartWS.xyz;
	vec3 litend1WS = lightEndWS.xyz;
	vec3 fpWsL0Ws = litend0WS - fragPosWS;
	vec3 fpWsL1Ws = litend1WS - fragPosWS;

	vec3 ldWS = fpWsL1Ws - fpWsL0Ws;
	vec3 ld = normalize(ldWS);
	lightLength = distance(litend0WS, litend1WS) - lightRadius;
	//roughness = mix(1.0, roughness, remapInterval(clamp01(intensity*2.0), 0.0, 1.0, 0.85, 1.0));
	
	{	// [tdbe] handling the case where the light intersects with a horizon or surface, see frostbite paper, although I have a simpler tube light so I try a simpler approach:
		// if one (but not both) ends of the light are not visible normal-wise to the surface, then we try to find the closest point on the line that is visible.
		// also based on https://www.elopezr.com/rendering-line-lights/

		const float fpWsL0Ws_Dot_normal = dot(fpWsL0Ws, normal);
		const float fpWsL1Ws_Dot_normal = dot(fpWsL1Ws, normal);

		if(fpWsL0Ws_Dot_normal > 0.0 && fpWsL1Ws_Dot_normal < 0.0)
		{
			float ldWS_Dot_normal = (dot((ldWS), normal));
			// [tdbe] move l1 closer to l0, onto the point on the line where the fpWsL1Ws_Dot_normal wouldWS not be < 0
			const float thoriz = -fpWsL0Ws_Dot_normal / ldWS_Dot_normal;// - 
			const vec3 intersectionPoint = litend0WS + ldWS * thoriz;// no clamp01 needed
			
			litend1WS = intersectionPoint;
			//litend1WS -= lightRadius * ld;
			fpWsL1Ws = litend1WS - fragPosWS;
			lightLength = distance(litend0WS, litend1WS) - lightRadius;
		}
		else
		if(fpWsL0Ws_Dot_normal < 0.0 && fpWsL1Ws_Dot_normal > 0.0)
		{
			//vec3 ldWS10 = fpWsL0Ws - fpWsL1Ws;
			//float ldWS10_Dot_normal = (dot((ldWS10), normal));
			//const float thoriz = (fpWsL1Ws_Dot_normal) / (ldWS10_Dot_normal);
			//const vec3 intersectionPoint = litend1WS + ldWS * (thoriz);
			//litend0WS = intersectionPoint;
			//fpWsL0Ws = litend0WS - fragPosWS;

			float ldWS_Dot_normal = (dot((ldWS), normal));
			// [tdbe] move l0 closer to l1, onto the point on the line where the fpWsL0Ws_Dot_normal wouldWS not be < 0
			const float thoriz = -fpWsL0Ws_Dot_normal / ldWS_Dot_normal;// + 
			const vec3 intersectionPoint = litend0WS + ldWS * thoriz;// no clamp01 needed

			litend0WS = intersectionPoint;
			//litend0WS += lightRadius * ld;
			fpWsL0Ws = litend0WS - fragPosWS;
			lightLength = distance(litend0WS, litend1WS) - lightRadius;
		}

		// [tdbe] debug view the intersection point only
		//fpWsL0Ws = fpWsL1Ws*1.0001;
		ldWS = fpWsL1Ws - fpWsL0Ws;
		ld = normalize(ldWS);
	}
	

	// ---

	/*const*/ float len_fpWsL0Ws = length(fpWsL0Ws);
	/*const*/ float len_fpWsL1Ws = length(fpWsL1Ws);
	/*const*/ float normal_dot_fpWsL0Ws = dot(normal, fpWsL0Ws);
	/*const*/ float normal_dot_fpWsL1Ws = dot(normal, fpWsL1Ws);
    /*const*/ float n_Dot_fpWsL0Ws = normal_dot_fpWsL0Ws / (2.0 * len_fpWsL0Ws);
    /*const*/ float n_Dot_fpWsL1Ws = normal_dot_fpWsL1Ws / (2.0 * len_fpWsL1Ws);
	// [tdbe] similar to NdotL but only used for specular correction
	// also makes the specular fatter with distance
    tubeNdotL_spec = (2.0 * clamp01(n_Dot_fpWsL0Ws + n_Dot_fpWsL1Ws)) / (len_fpWsL0Ws * len_fpWsL1Ws + dot(fpWsL0Ws, fpWsL1Ws) + 2.0);

	// ---

	// [tdbe] (these are not const because of the animation trick I do further down)
	/*const*/ float r_Dot_fpWsL0Ws = dot(normalReflectedView, fpWsL0Ws);
    /*const*/ float r_Dot_ldWS = dot(normalReflectedView, ldWS);
    /*const*/ float fpWsL0Ws_Dot_ldWS = dot(fpWsL0Ws, ldWS);
    /*const*/ float ldWS_sqrMag = dot(ldWS, ldWS);// aka length roundtrip pow(length(ldWS), 2.0);
	float norm_dot_ld = dot(normal, ld);

	vec3 mrp_on_segment_diff = vec3(1.0);
	float closestLightAB = 0.0;
	float closestLightABPercent = 0.0;
	float tentacleSpeed = 0.35;
	vec3 fragPosWS_diffuse = fragPosWS;

	// [tdbe] redorav & Guerrilla Games' Decima Engine's diffuse MRP point:
	// (point where the half vector (of fragPosWS to litend0WS and fragPosWS to litend1WS), touches the ldWS vector)
	/*
	[tdbe] unoptimized, easier to understand the point:
	{
		vec3 half_l0l1 = normalize(fpWsL0Ws) + normalize(fpWsL1Ws);
		vec3 crossVector = cross(half_l0l1, ldWS); // Find vector perpendicular to both half_l0l1 and ldWS (would intersect both lines)
		mat3 m = mat3(fpWsL0Ws, ldWS, crossVector);
		// Find intersection between half vector and line vector. There is a guaranteed intersection by construction.
		float tdiff = determinant(m) / dot(crossVector, crossVector);
		vec3 mrp_on_segment_diff = fragPosWS + half_l0l1 * clamp01(tdiff);
	}
	*/
	// [tdbe] optimized bisector of angle theorem version:
	tdiff = clamp01(len_fpWsL0Ws / (len_fpWsL1Ws + len_fpWsL0Ws));
	float tdiff2 = clamp01(len_fpWsL1Ws / (len_fpWsL0Ws + len_fpWsL1Ws));
	//vec3 mrp_on_segment_diff = litend0WS + ldWS * tdiff;
	// [tdbe] Patching a dealbreaking issue with this technique: if one of the directions from the fragment to one end of the light tube is pointing dead-on the same as the surface normal, there will be a "hole" in the middle of the radial light gradient.
	closestLightAB = dot(normalReflectedView, ld);
	closestLightABPercent = (clamp(closestLightAB, -1.0, 1.0)+1.0)*0.5;// [tdbe] to know if l0 is closer to the frag pos than l1, or vice versa.
	//float closestLightABPercentStep = mix(0.0, 1.0, (1.0*sign(closestLightAB)+1.0)/2.0);// [tdbe] to know if l0 is closer to the frag pos than l1, or vice versa.
	closestLightAB = clamp01(abs(closestLightAB));
	mrp_on_segment_diff = mix(litend0WS + ldWS * tdiff * (1.0 - clamp01(0.8 * pow(normal_dot_fpWsL1Ws, 1.5))), // 0.8, 1.5
							  litend1WS - ldWS * tdiff2 * (1.0 - clamp01(0.8 * pow(normal_dot_fpWsL0Ws, 1.5))), 
							  closestLightABPercent);

	// [tdbe] scripting for fun tentacle lights diffuse. If you're new here, ignore this. If you worry about performance, also look away lol.
	if(lightType == LIGHT_TYPE_TENTACLE)
	{
		float percentFromL = clamp01(distance(mrp_on_segment_diff, litend1WS) / lightLength);
		// [tdbe] bend the tentacle light by moving the fragment point up and down with time in a wiggle animation.
		// (we need to bend, as in rotate, the vertex, not just displace up and down)
		fragPosWS_diffuse = tentacleMovement(lightIndex, fragPosWS_diffuse, vec3(3.62, 2.5, -9.95), percentFromL, lightLength, time, ld, tentacleSpeed);

		vec3 fpWsL0Ws_TD = litend0WS - fragPosWS_diffuse;
		vec3 fpWsL1Ws_TD = litend1WS - fragPosWS_diffuse;
		vec3 ldWS_TD = fpWsL1Ws_TD - fpWsL0Ws_TD;
		vec3 litend0WS_TD = litend0WS;
		vec3 litend1WS_TD = litend1WS;
		{	
			const float fpWsL0Ws_Dot_normal = dot(fpWsL0Ws_TD, normal);
			const float fpWsL1Ws_Dot_normal = dot(fpWsL1Ws_TD, normal);

			if(fpWsL0Ws_Dot_normal > 0.0 && fpWsL1Ws_Dot_normal < 0.0)
			{
				float ldWS_Dot_normal = (dot((ldWS_TD), normal));
				const float thoriz = -fpWsL0Ws_Dot_normal / ldWS_Dot_normal;
				const vec3 intersectionPoint = litend0WS_TD + ldWS_TD * thoriz;
			
				litend1WS_TD = intersectionPoint;
				fpWsL1Ws_TD = litend1WS_TD - fragPosWS;
			}
			else
			if(fpWsL0Ws_Dot_normal < 0.0 && fpWsL1Ws_Dot_normal > 0.0)
			{
				float ldWS_Dot_normal = (dot((ldWS_TD), normal));
				const float thoriz = -fpWsL0Ws_Dot_normal / ldWS_Dot_normal;
				const vec3 intersectionPoint = litend0WS_TD + ldWS_TD * thoriz;
				litend0WS_TD = intersectionPoint;
				fpWsL0Ws_TD = litend0WS_TD - fragPosWS;
			}
		}

		ldWS_TD = fpWsL1Ws_TD - fpWsL0Ws_TD;
		const float len_fpWsL0Ws_TD = length(fpWsL0Ws_TD);
		const float len_fpWsL1Ws_TD = length(fpWsL1Ws_TD);

		tdiff = clamp01(len_fpWsL0Ws_TD / (len_fpWsL1Ws_TD + len_fpWsL0Ws_TD));
		mrp_on_segment_diff = litend0WS_TD + ldWS_TD * tdiff;
	}
	
	// index of most representative point (MRP) on the segment
	// [tdbe] original math, if normalReflectedView vector is not normalized
	/*{
		const float refl_sqrMag = dot(normalReflectedViewWS, normalReflectedViewWS);
		const float tspec_num	= dot(normalReflectedViewWS, litend0WS) * r_Dot_ldWS 
								+ dot(fragPosWS, ldWS) * refl_sqrMag 
								- dot(fragPosWS, normalReflectedViewWS) * r_Dot_ldWS 
								- dot(litend0WS, ldWS) * refl_sqrMag;
		const float tspec_den = (ldWS_sqrMag * refl_sqrMag - r_Dot_ldWS * r_Dot_ldWS);
	}*/
	// [tdbe] Note: The triangle math in this lighting method is optimized by corresponding dot products.
	// So be careful if something needs normalized or unnormalized vectors in the dots.
	// [tdbe] optimized if normalReflectedView vector is normalized:
	/*const*/ float tspec_num = (r_Dot_fpWsL0Ws * r_Dot_ldWS - fpWsL0Ws_Dot_ldWS);
	/*const*/ float tspec_den = (ldWS_sqrMag - r_Dot_ldWS * r_Dot_ldWS);
	// [tdbe] this "line" is "oriented" correctly but becomes infinite so just clamping as the method does, makes it tricky to accuately cap in a non hard-falloff way.
    tspec =	clamp01(tspec_num / tspec_den);
	// [tdbe] MRP on the light.
    vec3 mrp_on_segment_spec = vec3(0.0);
	//vec3 mrp_on_segment_spec = litend0WS + ldWS * tspec; 
	// [tdbe] instead of the ^above line:
	// [tdbe] I patch 3 dealbreaking errors that nobody's implementations addresses.
	// (Everyone just hides it by cherrypicking value & angle ranges. Can be independently observed by tweaking the roughness/intensity/positions settings of every single shadertoy/blog/github on this method to date (2025)).
	// The tspec term causes a hard cutoff at the ends of the line/segment, and we can't pick points when the line is dead-on facing the reflection. Introduces 3 problems:
	// Fix 1: deadeye: an "empty center hole" artifact when the reflected view dir is facing (almost) the same direction as the line light's dir.
	// Fix 2: sharp end: at >45 degree angles there's a sharp "cylindrical edge" artifact in the reflection on the side of the line light that's furthest away from the fragment point (which should be the blurriest side not the sharpest!).
	// Fix 3: horizon skew: when the reflected line is ~parallel to the surface (ground), and the light is big/long and far away, the reflection's end of the line that's closest to you, appears to have a downward sharp slope at the very end. And the opposite end gets a upward sharp end.
	// ..I should have tried the frostbyte quad tube version lol nobody admitted how shit all the MRP techniques are.
	float deadeyeABNarrowBand = abs(closestLightAB * mix(abs(norm_dot_ld), 1.0, closestLightAB));
	float roughnessLerp = pow((1.0-roughness), 5.0);
	float deadeyeDot = clamp01(pow(deadeyeABNarrowBand, max(50.0 * roughnessLerp, 1.0)));// 50.0 // [tdbe] the higher this ridiculous percent the more accurate the light length is at low roughnesses.
	float smoothTerm123 = mix(tspec, tdiff, deadeyeDot);
	// This now nicely rounds the ends across all roughnesses, but shortens the caboose/furthest reflection a tiny amount. Hey it's not more inaccurate than the aberrating original. 
	mrp_on_segment_spec = litend0WS + ldWS * smoothTerm123;
	// [tdbe] TODO: I still haven't fixed point 3; easiest way is to get the distance between light centre and the mrp, and the closer the mrp is to the end of the tube, the more you replace it with light0 or light1.
	// Or fade the intensity of the light towards its ends in some exponential curve way so it muffles the ends only.
	
	// ---

	// [tdbe] scripting for fun tentacle lights specular. If you're new here, ignore this. If you worry about performance, also look away lol.
	if(lightType == LIGHT_TYPE_TENTACLE)
	{
		float percentFromL = clamp01(distance(mrp_on_segment_spec, litend1WS) / lightLength);
		// [tdbe] bend the tentacle light by moving the fragment point up and down with time in a wiggle animation.
		// (we need to bend, as in rotate, the vertex, not just displace up and down)
		fragPosWS = tentacleMovement(lightIndex, fragPosWS, vec3(3.62, 2.5, -9.95), percentFromL, lightLength, time, ld, tentacleSpeed);

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		fpWsL0Ws = litend0WS - fragPosWS;
		fpWsL1Ws = litend1WS - fragPosWS;
		ldWS = fpWsL1Ws - fpWsL0Ws;
		vec3 litend0WSBak = litend0WS;
		{	
			const float fpWsL0Ws_Dot_normal = dot(fpWsL0Ws, normal);
			const float fpWsL1Ws_Dot_normal = dot(fpWsL1Ws, normal);

			if(fpWsL0Ws_Dot_normal > 0.0 && fpWsL1Ws_Dot_normal < 0.0)
			{
				float ldWS_Dot_normal = (dot((ldWS), normal));
				const float thoriz = -fpWsL0Ws_Dot_normal / ldWS_Dot_normal;
				const vec3 intersectionPoint = litend0WS + ldWS * thoriz;
			
				litend1WS = intersectionPoint;
				fpWsL1Ws = litend1WS - fragPosWS;
			}
			else
			if(fpWsL0Ws_Dot_normal < 0.0 && fpWsL1Ws_Dot_normal > 0.0)
			{
				float ldWS_Dot_normal = (dot((ldWS), normal));
				const float thoriz = -fpWsL0Ws_Dot_normal / ldWS_Dot_normal;
				const vec3 intersectionPoint = litend0WS + ldWS * thoriz;
				litend0WS = intersectionPoint;
				fpWsL0Ws = litend0WS - fragPosWS;
			}
		}

		/*
		percentFromL = clamp01(distance(mrp_on_segment_spec, litend0WSBak) / lightLength);
		// todo: * 10.0 is a hack for lack of extra parameters
		lightLength = distance(litend0WS, litend1WS) - mix(lightRadius, lightRadius * 10.0, pow(percentFromL, 2.0));
		*/

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ldWS = fpWsL1Ws - fpWsL0Ws;
		ld = normalize(ldWS);
		len_fpWsL0Ws = length(fpWsL0Ws);
		len_fpWsL1Ws = length(fpWsL1Ws);
		normal_dot_fpWsL0Ws = dot(normal, fpWsL0Ws);
		normal_dot_fpWsL1Ws = dot(normal, fpWsL1Ws);
		n_Dot_fpWsL0Ws = normal_dot_fpWsL0Ws / (2.0 * len_fpWsL0Ws);
		n_Dot_fpWsL1Ws = normal_dot_fpWsL1Ws / (2.0 * len_fpWsL1Ws);
		tubeNdotL_spec = (2.0 * clamp01(n_Dot_fpWsL0Ws + n_Dot_fpWsL1Ws)) / (len_fpWsL0Ws * len_fpWsL1Ws + dot(fpWsL0Ws, fpWsL1Ws) + 2.0);

		// ---

		r_Dot_fpWsL0Ws = dot(normalReflectedView, fpWsL0Ws);
		r_Dot_ldWS = dot(normalReflectedView, ldWS);
		fpWsL0Ws_Dot_ldWS = dot(fpWsL0Ws, ldWS);
		ldWS_sqrMag = dot(ldWS, ldWS);
		tspec_num = (r_Dot_fpWsL0Ws * r_Dot_ldWS - fpWsL0Ws_Dot_ldWS);
		tspec_den = (ldWS_sqrMag - r_Dot_ldWS * r_Dot_ldWS);
		tspec =	clamp01(tspec_num / tspec_den);
		closestLightAB = dot(normalReflectedView, ld);
		closestLightAB = clamp01(abs(closestLightAB));
		deadeyeABNarrowBand = abs(closestLightAB * mix(abs(dot(normal, ld)), 1.0, closestLightAB));
		deadeyeDot = clamp01(pow(deadeyeABNarrowBand, max(50.0 * roughnessLerp, 1.0)));
		smoothTerm123 = mix(tspec, tdiff, deadeyeDot);
		mrp_on_segment_spec = litend0WS + ldWS * smoothTerm123;
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		percentFromL = clamp01(distance(mrp_on_segment_spec, litend0WSBak) / lightLength);
		float percentFromLPow = pow(percentFromL, 2.0);
		lightColor = mix(lightColor, vec3(1.0), percentFromLPow);// [tdbe] scripting tentacle to be white at base
		// [tdbe] scripting the tentacle: thickest at l1 and mesh scale regular thickness at l0.
		// todo: * 10.0 is a hack for lack of extra parameters
		lightRadius = mix(lightRadius, lightRadius * 10.0, percentFromLPow);
		//float starfishHax = ((1.0-roughness) * lightRadius * percentFromL * deadeyeABNarrowBand * 10.0);// * 5.0);
		//roughnessSq += pow(starfishHax, 2.0);
		intensity *= clamp01(2.0*(1.0-pow((1.0-percentFromLPow), 10.0)));
		intensity += deadeyeABNarrowBand * lightRadius;
	}

	// ---

	// [tdbe] kokokara code you can reuse for other kinds of radius & MRP based lights:
	// Note: The triangle math in this lighting method is optimized by corresponding dot products.
	// So be careful if something needs normalized or unnormalized vectors in the dots.

	// [tdbe] we can mostly get away without adding radius because of the `Specular D Modification`
	//const vec3 mrp_grow_dir_spec = dot(mrp_on_segment_spec, normalReflectedViewWS) * normalReflectedView - mrp_on_segment_spec;
	//const vec3 mrp_on_tube_spec = mrp_on_segment_spec + mrp_grow_dir_spec * clamp01(lightRadius / length(mrp_grow_dir_spec));
	
	// [tdbe] should not be needed for diffuse.
	//const vec3 mrp_grow_dir_diff = dot(mrp_on_segment_diff, normalReflectedViewWS) * normalReflectedView;
	//mrp_on_tube_diff += mrp_on_segment_diff + mrp_grow_dir_diff * clamp01(lightRadius / (length(mrp_grow_dir_diff)));
	
	lightDist_spec = distance(mrp_on_segment_spec, fragPosWS);
	lightDir_spec = normalize(mrp_on_segment_spec - fragPosWS);
	//lightDistnormal = 0.5 * (len_fpWsL0Ws * len_fpWsL1Ws + dot(fpWsL0Ws, fpWsL1Ws));

	lightDist_diff = distance(mrp_on_segment_diff, fragPosWS_diffuse);
	lightDir_diff = normalize(mrp_on_segment_diff - fragPosWS_diffuse);

	// ---

	// Karis' volume Specular D Modification
	// [tdbe] helps adjust the scale with shape/radius of the tube or other radius lights.
    //aPrime_spec = (clamp01(roughnessSq + lightRadius / (2.0 * lightDist_spec)));
    aPrime_spec = (max(0.0, roughnessSq + lightRadius / (lightDist_spec * lightDist_spec)));
}

vec3 calculateLights(bool glFrontFacing,
					 vec3 cameraPos, vec3 fragWorldPos, float time,
					 vec3 surfaceNormal, vec3 surfaceNormalWS, 
					 mat4[LIGHT_COUNT] allLights, int lightIndex,
					 float transparency, mat4 ambientLight, vec3 albedo,
					 vec4 ior, float roughnessSlider, float metallicSlider)
{
	if(!glFrontFacing)
		surfaceNormal *= -1.0;

	// [tdbe] the ambient part here is my temporary improvisation to simulate 
	// some rich light convergence bounce "from all directions"
	vec3 ambientGradient = vec3(0.0);
	if(ambientLight[1][1] != 0.0)
	{
		ambientGradient = sampleAmbient(surfaceNormal, vec3(0,1,0), ambientLight, fragWorldPos.y, MAX_WORLD_HEIGHT);
		float groundAmbientTweak = ior.w - 1.0;
		ambientGradient.x = max(groundAmbientTweak, ambientGradient.x);
		ambientGradient.y = max(groundAmbientTweak, ambientGradient.y);
		ambientGradient.z = max(groundAmbientTweak, ambientGradient.z);
	}

	//const vec3 lightDir = vec3(0.5, -1.0, -0.85);
	//const float diffuse = clamp(dot(surfaceNormal, -lightDir), 0.0, 1.0);
	//vec3 col = color * clamp(ambient * 0.5 + (diffuse * 0.5 + diffuse * ambient * 0.5), 0.0, 1.0);

	// ----------------

	// [tdbe] F0 is the % of reflected light when you're looking (perpendicularly) at the surface.
	vec3 F0 = abs ((1.0 - ior.xyz) / (1.0 + ior.xyz));
	F0 = F0 * F0;
	// [tdbe] for dielectric materials (non-conductors (non-metallic)), the specular isn't affected 
	// by albedo (material color).
	// But for conductors (metals), the specular is tinted by the albedo and we have 0 ior aka 1.0 reflection.
	F0 = mix(F0, albedo, metallicSlider);

	float occlusion = 1.0;
	// [tdbe] since this is the light coming from everywhere (and a hack), it counds as all 3: diffuse and specular and reflection.
	// add albedo even though metallic should not have diffuse color (only specular color coming from the actual lighting calculations).
	vec3 ambientLightContribution = albedo*ambientGradient;// * ambient scale * ambient occlusion

	// ----------------

	const float roughnessSliderSq = roughnessSlider*roughnessSlider;
	const vec3 surfaceToCameraViewDirWS = cameraPos - fragWorldPos;
	const vec3 surfaceToCameraViewDir = normalize(surfaceToCameraViewDirWS);
	float n_Dot_v = dot(surfaceNormal, surfaceToCameraViewDir);

	// ----------------

	vec3 dynamicLights = vec3(0.0);
	int totalLights = allLights.length();
	int startingLight = 0;
	for(int i = startingLight; i < totalLights; i++)
	{
		if(allLights[i][COLOR].w == 0.0)// [tdbe] "disabled" -- will also become 0 if you have set any light dimensions <= 0.0 from c++
		{
			continue;
		}

		vec3 lightColor = allLights[i][COLOR].rgb;
		int lightType = int(allLights[i][SHAPE_VEC_0].w);
		vec3 lightPos = allLights[i][CENTRAL_VEC].xyz;
		float attenuation = 1.0;
		float lightIntensity = allLights[i][COLOR].w;
		const float roughness = roughnessSlider;
		const float roughnessSq = roughnessSliderSq;
		const float metallic = metallicSlider;
		vec3 surfCol = albedo;
		vec3 fragWs = fragWorldPos;
		vec3 normal = surfaceNormal;
		vec3 normalWS = surfaceNormalWS;	

		vec3 surfaceToLightDir_spec = vec3(0.0);
		vec3 surfaceToLightDir_diff = vec3(0.0);
		float aPrime_Karis_spec = 1.0;
		float shaped_n_Dot_l = 1.0;
		if(lightType == LIGHT_TYPE_DIRECTIONAL)
		{
			// [tdbe] a hack to make the lights sorta look like they are part of the ambient convergence
			lightColor = mix(ambientGradient, lightColor, 0.66);

			// [tdbe] TODO: turn the directional light into a directional disc light / frostbite.
			surfaceToLightDir_spec = surfaceToLightDir_diff = allLights[i][CENTRAL_VEC].xyz;
		}
		else if(lightType == LIGHT_TYPE_TUBE || lightType == LIGHT_TYPE_TENTACLE)
		{
			/*// [tdbe] early imprecise cull?
			float lightDist = distance(fragWs, lightPos);
			attenuation = 1.0/pow(max(0.0, lightDist - allLights[i][SHAPE_VEC_1].w - allLights[i][CENTRAL_VEC].w), 2.0);
			if(attenuation < LIGHT_CULL_INTENSITY)
				continue; */
			float lightRadius = allLights[i][CENTRAL_VEC].w;// [tdbe] CENTRAL_VEC].w means radius if exists, otherwise 0.0
			float lightLength = allLights[i][SHAPE_VEC_1].w;

			vec3 lightDirWS = allLights[i][SHAPE_VEC_1].xyz - allLights[i][SHAPE_VEC_0].xyz;

			// [tdbe] these modifications are to light a "light fixture mesh" the actual light of which is at index i == `lightIndex`
			if(lightIndex == i)
			{
				normalWS = -normalWS;
				normal = -normal;
				n_Dot_v = -n_Dot_v;
				fragWs -= normal * 0.1 + normal * lightRadius;// [tdbe] CENTRAL_VEC].w means radius if exists, otherwise 0.0
				vec3 lightDir = normalize(lightDirWS);
				float compensateLightAngle = pow(clamp01(abs(dot(surfaceToCameraViewDir, lightDir))), 12.0);
				float viewmod = clamp01(dot(surfaceToCameraViewDir, -normal)*0.5);
				vec3 lightColMod = mix(lightColor, vec3(1.0), compensateLightAngle * 0.5);
				surfCol = mix(surfCol, lightColMod, 0.75);
				surfCol = mix(surfCol, vec3(1.0), viewmod);
				ambientLightContribution = mix(ambientLightContribution, lightColMod, 0.5);//0.75
				ambientLightContribution = mix(ambientLightContribution, vec3(1.0), viewmod);
				ambientGradient = mix(ambientGradient, lightColMod, 0.9);//0.99//0.75
				ambientGradient = mix(ambientGradient, vec3(1.0), viewmod);
			}

			// [tdbe] hack to make the lights sorta look like they are part of the ambient convergence
			lightColor = mix(ambientGradient, lightColor, 0.66);

			float lightDist_spec = 0.0;
			float lightDist_diff = 0.0;
			float tspec = 0.0;
			float tdiff = 0.0;
			const vec3 normalReflectedView = reflect(surfaceToCameraViewDir, normal);
			const vec3 normalReflectedViewWS = reflect(surfaceToCameraViewDirWS, normalWS);
			// [tdbe] get (relative) position and specular n_dot_l's as if the light was a tube.
			MRPointOnTubeLight( 
								allLights[i][SHAPE_VEC_0].xyz, 
								allLights[i][CENTRAL_VEC].xyz, 
								allLights[i][SHAPE_VEC_1].xyz, 
								lightType, lightRadius, lightLength,
								roughness, roughnessSq,
								lightIntensity, lightColor,
								fragWs, time, i,
								normalReflectedView, normalReflectedViewWS, 
								normal, normalWS,
								surfaceToLightDir_spec, lightDist_spec, tspec,
								surfaceToLightDir_diff, lightDist_diff, tdiff,
								shaped_n_Dot_l, 
								aPrime_Karis_spec);
			
			// [tdbe] this "Epic's inverse square formula for the lighting falloff" from here https://alextardif.com/arealights.html seems wrong: 
			//attenuation = pow(clamp(1.0 - pow(lightDist/allLights[i][CENTRAL_VEC].w, 4.0), 0.0, 1.0), 2.0) / ((lightDist * lightDist) + 1.0);	
			
			// [tdbe] Proper attenuation (but how for tube edge cases? Just MRP?): 
			// read 4.7.3 Five times rule here: https://media.contentapi.ea.com/content/dam/eacom/frostbite/files/course-notes-moving-frostbite-to-pbr-v32.pdf
			// (aka course notes from here https://www.ea.com/frostbite/news/moving-frostbite-to-pb)
			// "the distance to a light source should be greater than five times the largest dimension of the sources" for
			// the inverse square law to be correct

			//attenuation /= pow(distance(fragWs, lightPos), 2.0);
			//float largestDimension = allLights[i][SHAPE_VEC_1].w;// [tdbe] SHAPE_VEC_1].w is the length dimension, CENTRAL_VEC].w is the radius
			//lightDist = lightDist_spec / largestDimension;
			float lightDist = min(lightDist_spec, lightDist_diff);
			attenuation = 1.0/(lightDist * lightDist);
			
			// [tdbe] cull lights that are too far from us.
			if(attenuation < LIGHT_CULL_INTENSITY)
				continue; 

			//surfaceToLightDir_spec = surfaceToLightDir_diff = normalize(lightPos - fragWs);
		}
		else if(lightType == LIGHT_TYPE_POINT)
		{
			const float lightDist = distance(fragWs, lightPos);

			attenuation = 1.0/pow(lightDist, 2.0);
			// [tdbe] cull lights that are too far from us.
			if(attenuation < LIGHT_CULL_INTENSITY)
				continue;

			// [tdbe] a hack to make the lights sorta look like they are part of the ambient convergence
			lightColor = mix(ambientGradient, lightColor, 0.66);

			surfaceToLightDir_spec = surfaceToLightDir_diff = normalize(lightPos - fragWs);
		}

		float shadow = 1.0;
		// [tdbe] todo: something something shinethrough, refraction... but probably when adding raytraced light (shadows)
		/*
		if(transparency < 0.999)
		{
			float density = 1.0 - transparency;
		}*/
		n_Dot_v = clamp(abs(n_Dot_v), LIGHT_CULL_INTENSITY, 1.0);
		dynamicLights += attenuation * shadow * calcBRDF(
													lightType,
													surfaceToLightDir_spec, surfaceToLightDir_diff,
													surfaceToCameraViewDir, normal, 
													surfCol, lightColor, n_Dot_v, lightIntensity,
													roughness, roughnessSq, metallic,
													F0, occlusion, shaped_n_Dot_l, aPrime_Karis_spec);
	}

	vec3 col = clamp01(ambientLightContribution + dynamicLights);
	return col;
}