#version 330

// Il vertex shader riceve in input gli attributi dei vertici
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;    
layout (location = 2) in vec2 textcoord;  

uniform mat4 Model2World;
uniform mat4 World2Camera;
uniform mat4 lightSpaceMatrix;

// Passiamo al fragment shader le informazioni sulle normali dei vertici  
out vec3 fragment_normal;

// Passiamo al fragment shader le coordinate mondo dei vertici
out vec3 fragment_position;

// Passiamo al fragment shader le coordinate mondo dei vertici
out vec2 fragment_textcoord;

out vec4 FragPosLightSpace;


void main()
{
     // Calcolo della posizione del vertice nello spazio del mondo
    vec4 worldPosition = Model2World * vec4(position, 1.0);
    
    // Posizione nel clip space (proiezione) dello spazio della telecamera
    gl_Position = World2Camera * worldPosition;

    // Trasformazione delle normali con la matrice trasposta inversa del modello
    fragment_normal = mat3(transpose(inverse(Model2World))) * normal;

    // Passaggio delle coordinate texture
    fragment_textcoord = textcoord;

    // Calcolo della posizione nello spazio della luce
    FragPosLightSpace = lightSpaceMatrix * worldPosition;

    // Passiamo la posizione del frammento nello spazio del mondo
    fragment_position = worldPosition.xyz;
    
}