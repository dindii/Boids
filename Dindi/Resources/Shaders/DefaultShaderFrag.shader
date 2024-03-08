#version 420 core

#define DND_MAX_LIGHTS 1000
#define DND_CSM_LEVELS 3

in vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_Normal;

out vec4 outColor;
in vec4 v_FragPosLightSpace[DND_CSM_LEVELS];
in vec4 v_FragPosViewSpace;

//#TEMPORARY Until we have PBR (=
uniform sampler2D u_Diffuse;
uniform sampler2D u_Specular;
uniform sampler2D u_Normal; //#TODO: Expand to properly accept normal textures other than only attribute normals (usually we will only get those as textures).
uniform sampler2D u_ShadowMap[DND_CSM_LEVELS];

uniform sampler3D u_RandomAngles;

uniform float u_CSMDistances[DND_CSM_LEVELS];

struct PointLight
{
	vec4 m_Position;
	vec4 m_Color;
};

layout(std140, binding = 1) uniform ConstantData
{
	float c_Time;
	float _p1;
	float _p2;
	unsigned int numLights;
	mat4 c_ViewProjection;
	mat4 c_View;
	vec4 c_CameraPos;
	vec4 c_DirLightPos;
	PointLight c_Lights[DND_MAX_LIGHTS];
};


float gamma = 2.2;
//float gShadowMapRandomRadius = 2.5f;
float gShadowMapRandomRadius = 2.2f;

float gShadowMapOffsetTextureSize = 16;
float gShadowMapOffsetFilterSize = 8;


#define NUM_SAMPLES 25  //PCSS sample parameter in step 3
#define BLOCKER_SEARCH_NUM_SAMPLES 25//PCSS sample parameter in step 1


/*******-------------------- PCSS functions --------------------******/

float u_LightSize = 65.0f;


float FilterSizeShadowCalculation(vec4 argfragPosLightSpace, int layer)
{
	vec4 fragPosLightSpace = v_FragPosLightSpace[layer];
	vec3 lightDir = c_DirLightPos.xyz;

	// Handling Perspective Issues
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(u_ShadowMap[layer], projCoords.xy).r;

	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;

	/***--------STEP 1: Blocker search: find the average blocker depth---------***/

	float sampleStride = u_LightSize / 2.5;
	float dBlocker = 0.0;
	float sampleSize = 1.0 / textureSize(u_ShadowMap[layer], 0).x * sampleStride;
	
	int blockerNumSample = BLOCKER_SEARCH_NUM_SAMPLES;

	int count = 0;

	ivec3 OffsetCoord;
	vec2 f = mod(gl_FragCoord.xy, vec2(gShadowMapOffsetFilterSize));
	OffsetCoord.yz = ivec2(f);

	for (int i = 0; i < blockerNumSample; ++i)
	{
		OffsetCoord.x = i;
		vec2 sampleCoord = texelFetch(u_RandomAngles, OffsetCoord, 0).xy * sampleSize + projCoords.xy;
		float closestDepth = texture(u_ShadowMap[layer], sampleCoord).r;
		//Only compute average depth of blocker! not the average of the whole filter's area!
		if (closestDepth < currentDepth) {
			dBlocker += closestDepth;
			count++;
		}
	}

	dBlocker /= count;

	float lightWidth = u_LightSize / 2.5;
	float wPenumbra = (currentDepth - dBlocker) * lightWidth / dBlocker;

	return wPenumbra;
}

float ShadowCalculation(vec4 fragPosLightSpace, int layer)
{
	vec3 projCoords = v_FragPosLightSpace[layer].xyz / v_FragPosLightSpace[layer].w;
	projCoords = projCoords * 0.5f + 0.5f;
	vec3 ShadowCoords = projCoords;

	float radius = clamp(FilterSizeShadowCalculation(fragPosLightSpace, layer), 1.0f, 3.0f);
	//float radius = 1.0f;

	vec4 sc = vec4(ShadowCoords, 1.0f);

	vec3 LightDirection = c_DirLightPos.xyz;
	vec3 Normal = v_Normal;

	ivec3 OffsetCoord;
	vec2 f = mod(gl_FragCoord.xy, vec2(gShadowMapOffsetFilterSize));
	OffsetCoord.yz = ivec2(f);
	float Sum = 0.0;
	int SamplesDiv2 = int(gShadowMapOffsetFilterSize * gShadowMapOffsetFilterSize / 2.0);


	float TexelWidth = 1.0 / textureSize(u_ShadowMap[layer], 0).x;
	float TexelHeight = 1.0 / textureSize(u_ShadowMap[layer], 0).x;

	vec2 TexelSize = vec2(TexelWidth, TexelHeight);

	float DiffuseFactor = dot(Normal, -LightDirection);
	//float bias = mix(0.001, 0.0005f, DiffuseFactor);
	float bias = 0.0005;
	float Depth = 0.0;


	for (int i = 0; i < 4; i++)
	{
		OffsetCoord.x = i;
		vec4 Offsets = texelFetch(u_RandomAngles, OffsetCoord, 0) * gShadowMapRandomRadius * radius;
		sc.xy = ShadowCoords.xy + Offsets.rg * TexelSize;
		Depth = texture(u_ShadowMap[layer], sc.xy).x;
		if (Depth + bias < ShadowCoords.z) {
			Sum += 0.0;
		}
		else {
			Sum += 1.0;
		}

		sc.xy = ShadowCoords.xy + Offsets.ba * TexelSize;
		Depth = texture(u_ShadowMap[layer], sc.xy).x;
		if (Depth + bias < ShadowCoords.z) {
			Sum += 0.0;
		}
		else {
			Sum += 1.0;
		}
	}

	float Shadow = Sum / 8.0;

	if (Shadow != 0.0 && Shadow != 1.0)
	{
		for (int i = 4; i < SamplesDiv2; i++) {
			OffsetCoord.x = i;
			vec4 Offsets = texelFetch(u_RandomAngles, OffsetCoord, 0) * gShadowMapRandomRadius * radius;
			sc.xy = ShadowCoords.xy + Offsets.rg * TexelSize;
			Depth = texture(u_ShadowMap[layer], sc.xy).x;
			if (Depth + bias < ShadowCoords.z) {
				Sum += 0.0;
			}
			else {
				Sum += 1.0;
			}

			sc.xy = ShadowCoords.xy + Offsets.ba * TexelSize;
			Depth = texture(u_ShadowMap[layer], sc.xy).x;
			if (Depth + bias < ShadowCoords.z) {
				Sum += 0.0;
			}
			else {
				Sum += 1.0;
			}
		}

		Shadow = Sum / float(SamplesDiv2 * 2.0f);
	}

	return Shadow;
}


struct PackLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

PackLight CalculateLight(vec3 argLightColor, vec3 argLightPos, bool isDirLighting)
{
	vec4 diffuseAll = texture(u_Diffuse, v_TexCoord);

	if (diffuseAll.a < 1.0f)
		discard;

	vec3 color = diffuseAll.rgb * argLightColor;
	vec3 specularColor = texture(u_Specular, v_TexCoord).rgb * argLightColor;

	//ambient
	vec3 ambient = 0.05f * color;

	//diffuse calc
	vec3 lightPos = argLightPos;

	vec3 lightDir = normalize(lightPos - v_FragPos) * float(!isDirLighting);
	lightDir += normalize(lightPos) * float(isDirLighting);

	vec3 normal = normalize(v_Normal);

	float diffuseRate = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diffuseRate * color;

	//specular calc
	vec3 cameraPos = c_CameraPos.xyz;
	vec3 viewDir = normalize(cameraPos - v_FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float specularRate = 0.0f;
	specularRate = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);

	vec3 specular = vec3(0.3f) * specularRate;

	return PackLight(ambient, diffuse, specular);
}

void main()
{
	vec3 temporaryResult = vec3(0.0f, 0.0f, 0.0f);

	//I will not waste too much time setting uniforms for those tweaks or even setting properties in the light class because we are not going to
	//use blinn-phong for much time. So, that's why it is extremely hardcoded.
	for (unsigned int x = 0; x < numLights; x++)
	{
		PackLight temp = CalculateLight(c_Lights[x].m_Color.rgb, c_Lights[x].m_Position.rgb, false);

		float distance = length(c_Lights[x].m_Position.xyz - v_FragPos);
		//float attenuation = 1.0f / (distance * distance);
		float attenuation = 2.0f / (distance * (distance / 2));

		vec3 ambientWithAttenuation = temp.ambient * attenuation;
		vec3 diffuseWithAttenuation = temp.diffuse * attenuation;
		vec3 specularWithAttenuation = temp.specular * attenuation;

		temporaryResult += vec3(ambientWithAttenuation + diffuseWithAttenuation) + vec3(temp.specular * specularWithAttenuation);
	}

	//#TODO: colocar a cor do dir light no cbuffer
	PackLight dirLight = CalculateLight(vec3(1.0f, 1.0f, 1.0f), c_DirLightPos.xyz, true);

	int layer = 2;

	float closer = u_CSMDistances[0];// -12.0f;
	float mid = u_CSMDistances[1];


	//
	if (abs(v_FragPosViewSpace.z) < closer)
	{
		outColor.rgb *= vec3(1.0f, 0.1f, 0.1f);
		layer = 0;
	}
	else if (abs(v_FragPosViewSpace.z) < mid)
	{
		outColor.rgb *= vec3(0.1f, 1.1f, 0.1f);
		layer = 1;
	}

	//float shadow = ShadowCalculation(v_FragPosLightSpace[layer], layer);
	float shadow = ShadowCalculation(v_FragPosLightSpace[layer], layer);
	//
	//vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;	


//	temporaryResult += vec3(dirLight.ambient + (1.0 - shadow) * (dirLight.diffuse + dirLight.specular));
	temporaryResult += vec3(dirLight.ambient + (/*1.0 -*/ shadow) * (dirLight.diffuse + dirLight.specular));
	outColor = vec4(temporaryResult.xyz, 1.0f);

	outColor.rgb = pow(outColor.rgb, vec3(1.0f / gamma));

	//
	if (abs(v_FragPosViewSpace.z) < closer)
	{
	//		outColor.rgb *= vec3(1.0f, 0.1f, 0.1f);
		layer = 0;
	}
	else if (abs(v_FragPosViewSpace.z) < mid)
	{
	//		outColor.rgb *= vec3(0.1f, 1.1f, 0.1f);
		layer = 1;
	}
}