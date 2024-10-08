#version 330 core

struct AmbientLightStruct {
    vec3 color;
    float intensity;
};

struct SpecularLightStruct {
    float intensity;
    float shininess;
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

in vec3 fragment_color;
in vec3 fragment_normal;
in vec3 fragment_position;
in vec2 fragment_textcoord;
in vec4 FragPosLightSpace;

uniform AmbientLightStruct AmbientLight;
uniform SpecularLightStruct SpecularLight;
uniform SpotLightStruct SpotLight;

uniform vec3 CameraPosition;
uniform sampler2D diffuseMap;
uniform sampler2D depthmap;

out vec4 out_color;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // trasforma le coordinate da clip space a coordinate schermo, dividendo ogni componente xyz per il componente w
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Le coordinate NDC sono nel range [-1,1]. Questo passaggio le trasforma nel range [0,1], che è il range delle texture.
    projCoords = projCoords * 0.5 + 0.5;
    // Viene campionata la shadow map utilizzando le coordinate xy trasformate. Questo restituisce la depth più vicina vista dalla luce, memorizzata nella shadow map.
    float closestDepth = texture(depthmap, projCoords.xy).r; 
    // Si ottiene la depth del frammento attuale dal punto di vista della luce.
    float currentDepth = projCoords.z;
    /* Il bias è utilizzato per prevenire il fenomeno dell'auto-ombreggiatura (shadow acne). 
    Il bias è calcolato in base all'angolo tra la normale del frammento e la direzione della luce. 
    Questo fa sì che frammenti che sono quasi paralleli alla luce abbiano un bias maggiore. */
    vec3 normal = normalize(fragment_normal);
    vec3 lightDir = normalize(SpotLight.position - fragment_position);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    /* La shadow map viene campionata in un'area 3x3 attorno al frammento attuale. Se la depth del frammento attuale, con il bias applicato,
    è maggiore della depth in uno qualsiasi dei campioni, il frammento è considerato in ombra per quel campione.
    Il valore finale dell'ombra è la media dei risultati dei campioni, producendo ombre più morbide. */
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(depthmap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(depthmap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Se le coordinate z del frammento sono al di fuori del range del frustum della luce, l'ombra viene impostata a 0.0, 
    // indicando che il frammento non è in ombra.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}


void main()
{
    vec3 color = texture(diffuseMap, fragment_textcoord).rgb;
    vec3 normal = normalize(fragment_normal);
    vec3 lightColor = SpotLight.color;

    vec3 ambient = AmbientLight.color * AmbientLight.intensity;
    
    vec3 lightDir = normalize(SpotLight.position - fragment_position);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 viewDir = normalize(CameraPosition - fragment_position);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SpecularLight.shininess);
    vec3 specular = spec * SpecularLight.intensity * lightColor;

    float shadow = ShadowCalculation(FragPosLightSpace);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    out_color = vec4(lighting, 1.0);
}
