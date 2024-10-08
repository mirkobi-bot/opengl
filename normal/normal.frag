#version 330 core

struct AmbientLightStruct {
    vec3 color;
    float intensity;
};

struct DirectionalLightStruct {
    vec3 color;
    vec3 direction;
};

struct SpecularLightStruct {
    float intensity;
    float shininess;
};

struct PointLightStruct {
    vec3 color;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLightStruct {
    vec3 color;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_textcoord;
in mat3 TBN;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform AmbientLightStruct AmbientLight;
uniform DirectionalLightStruct DirectionalLight;
uniform SpecularLightStruct SpecularLight;
uniform PointLightStruct PointLight;
uniform SpotLightStruct SpotLight;
uniform vec3 CameraPosition;

out vec4 out_color;

vec3 calculateSpecular(vec3 lightColor, vec3 lightDir, vec3 normal, vec3 viewDir) {
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SpecularLight.shininess);
    return lightColor * spec * SpecularLight.intensity;
}

vec3 calculatePointLight(PointLightStruct light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient = AmbientLight.color * AmbientLight.intensity;
    vec3 diffuse = texture(diffuseMap, frag_textcoord).rgb;
    vec3 specular = calculateSpecular(light.color, lightDir, normal, viewDir);
    return (ambient + (diffuse + specular) * attenuation);
}

vec3 calculateSpotLight(SpotLightStruct light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient = AmbientLight.color * AmbientLight.intensity;
    vec3 diffuse = texture(diffuseMap, frag_textcoord).rgb;
    vec3 specular = calculateSpecular(light.color, lightDir, normal, viewDir);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    return (ambient + (diffuse + specular) * attenuation * intensity);
}

vec3 calculateDirectionalLight(DirectionalLightStruct light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 ambient = AmbientLight.color * AmbientLight.intensity;
    vec3 diffuse = texture(diffuseMap, frag_textcoord).rgb;
    vec3 specular = calculateSpecular(light.color, lightDir, normal, viewDir);
    return (ambient + (diffuse + specular));
}

void main() {
    vec3 normal = texture(normalMap, frag_textcoord).rgb * 2.0 - 1.0;
    normal = normalize(TBN * normal);

    vec3 viewDir = normalize(CameraPosition - frag_position);
    
    vec3 pointLightColor = calculatePointLight(PointLight, normal, frag_position, viewDir);
    vec3 spotLightColor = calculateSpotLight(SpotLight, normal, frag_position, viewDir);
    vec3 directionalLightColor = calculateDirectionalLight(DirectionalLight, normal, viewDir);

    vec3 finalColor = pointLightColor + spotLightColor + directionalLightColor;
    out_color = vec4(finalColor, 1.0);
}
