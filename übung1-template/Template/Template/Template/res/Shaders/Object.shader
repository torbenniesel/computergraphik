#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

//out vec3 ourColor;
out vec3 ourFragPos;
out vec3 ourNormal;
out vec2 ourTexCoord;

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	ourFragPos = vec3(model * vec4(aPos, 1.0f));
	ourNormal = normalize(transpose(inverse(mat3(model))) * aNormal);
	//gl_Position = transform * vec4(aPos, 1.0f);
	gl_Position = projection * view * vec4(ourFragPos, 1.0f);

	//ourColor = aColor;
	ourTexCoord = aTexCoord;
}

////////////////////////////////////////////////
// fragment shader
////////////////////////////////////////////////
#shader fragment
#version 330 core

struct Material {
	vec4 ambient;	
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

uniform vec4 ambientLight;

#define MAX_DIR_LIGHTS 8
struct DirLight {
	int enabled;

	vec3 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform int numberDirLights;

#define MAX_POINT_LIGHTS 8
struct PointLight {
	int enabled;

	vec3 position;

	float k0;
	float k1;
	float k2;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numberPointLights;

#define MAX_SPOT_LIGHTS 8
struct SpotLight {
	int enabled;

	vec3 position;
	vec3 direction;

	float k0;
	float k1;
	float k2;

	float cutOff;
	float outerCutOff;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int numberSpotLights;

out vec4 FragColor;

//in vec3 ourColor;
in vec3 ourFragPos;
in vec3 ourNormal;
in vec2 ourTexCoord;

uniform Material material;
uniform int useTex;
uniform int hasDiffMap;
uniform int hasSpecMap;

uniform vec3 viewPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

vec4 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 ambMap, vec4 diffMap, vec4 specMap);
vec4 calcDirLight(int idx, vec3 norm, vec3 viewDir, vec4 ambMap, vec4 diffMap, vec4 specMap);
vec4 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec4 ambMap, vec4 diffMap, vec4 specMap);

void main(){
	vec3 norm = normalize(ourNormal);
	vec3 viewDir = normalize(viewPos - ourFragPos);
	vec4 ambientMap = material.ambient;
	vec4 diffuseMap = material.diffuse;
	vec4 specularMap = material.specular;

	if (useTex == 1)
	{
		if (hasDiffMap == 1) {
			ambientMap = texture(diffuse0, ourTexCoord);
			diffuseMap = material.diffuse * texture(diffuse0, ourTexCoord);
		}
		if (hasSpecMap == 1) {
			specularMap = material.specular * texture(specular0, ourTexCoord);
		}
	}

	vec4 result = ambientLight * ambientMap;

	//direction light
	if (numberDirLights > 0) {
		int nd = numberDirLights; 
		if (nd > MAX_DIR_LIGHTS)
			nd = MAX_DIR_LIGHTS;
		for (int i = 0; i < nd; i++) {
			if (0 < dirLights[i].enabled)
				result += calcDirLight(i, norm, viewDir, ambientMap, diffuseMap, specularMap);
		}
	}

	//point light
	if (numberPointLights > 0) {
		int np = numberPointLights;
		if ( np > MAX_POINT_LIGHTS)
			np = MAX_POINT_LIGHTS;
		for (int i = 0; i < np; i++) {
			if (0 < pointLights[i].enabled)
				result += calcPointLight(i, norm, viewDir, ambientMap, diffuseMap, specularMap);
		}
	}

	//spot light
	if (numberSpotLights > 0) {
		int ns = numberSpotLights;
		if ( ns > MAX_SPOT_LIGHTS)
			ns = MAX_SPOT_LIGHTS;
		for (int i = 0; i < ns; i++) {
			if (0 < spotLights[i].enabled)
				result += calcSpotLight(i, norm, viewDir, ambientMap, diffuseMap, specularMap);
		}
	}

	FragColor = max(result, material.emission);

	// only the DIFFUSE colour's alpha value actually determines the transparency
	//if (useTex == 0){
		FragColor[3] = diffuseMap[3];
	//}

	//FragColor = vec4(1.0f, 0.2f, 0.6f, 1.0f);
	//FragColor = vec4(ourColor, 1.0f);
	//FragColor = vec4(ourColor, 1.0f) * texture(texture1, ourTexCoord);
	//FragColor = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), mixVal);
}

vec4 calcDirLight(int idx, vec3 norm, vec3 viewDir, vec4 ambMap, vec4 diffMap, vec4 specMap){
	//ambient
	vec4 ambient = dirLights[idx].ambient * ambMap;

	//diffuse
	vec3 lightDir = normalize(-dirLights[idx].direction); // direction toward the light
	float diff = max(dot(norm, lightDir), 0.0f); 
	vec4 diffuse = dirLights[idx].diffuse * (diff * diffMap);

	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir), 0.0f), material.shininess * 128);
	vec4 specular = dirLights[idx].specular * (spec * specMap);

	return vec4(ambient + diffuse + specular);
}

vec4 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 ambMap, vec4 diffMap, vec4 specMap){
	//ambient
	vec4 ambient = pointLights[idx].ambient * ambMap;

	//diffuse
	vec3 lightDir = normalize(pointLights[idx].position - ourFragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec4 diffuse = pointLights[idx].diffuse * (diff * diffMap);

	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir), 0.0f), material.shininess * 128);
	vec4 specular = pointLights[idx].specular * (spec * specMap);

	float dist = length(pointLights[idx].position - ourFragPos);
	float attenuation = 1.0f / (pointLights[idx].k0 + pointLights[idx].k1 * dist + pointLights[idx].k2 * (dist * dist));

	return vec4(ambient + diffuse + specular) * attenuation;
}


vec4 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec4 ambMap, vec4 diffMap, vec4 specMap){
	vec3 lightDir = normalize(spotLights[idx].position - ourFragPos);
	float theta = dot(lightDir, normalize(-spotLights[idx].direction));

	//ambient
	vec4 ambient = spotLights[idx].ambient * ambMap;

	if(theta > spotLights[idx].outerCutOff){
		//diffuse
		float diff = max(dot(norm, lightDir), 0.0f);
		vec4 diffuse = spotLights[idx].diffuse * (diff * diffMap);
		//specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir,reflectDir), 0.0f), material.shininess * 128);
		vec4 specular = spotLights[idx].specular * (spec * specMap);

		float intensity = (theta - spotLights[idx].outerCutOff) / (spotLights[idx].cutOff - spotLights[idx].outerCutOff);
		intensity = clamp(intensity, 0.0f, 1.0f);
		diffuse *= intensity;
		specular *= intensity;

		float dist = length(spotLights[idx].position - ourFragPos);
		float attenuation = 1.0f / (spotLights[idx].k0 + spotLights[idx].k1 * dist + spotLights[idx].k2 * (dist * dist));

		return vec4(ambient + diffuse + specular) * attenuation;
	}
	else{
		return ambient;
	}
}