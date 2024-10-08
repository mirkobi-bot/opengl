#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textcoord;
layout (location = 3) in vec3 tangent;    // Attributo per la tangente
layout (location = 4) in vec3 bitangent;  // Attributo per la bitangente

uniform mat4 Model2World;
uniform mat4 World2Camera;

out vec3 frag_position;  // Passa la posizione del frammento al fragment shader
out vec3 frag_normal;    // Passa la normale del frammento al fragment shader
out vec2 frag_textcoord; // Passa le coordinate di texture al fragment shader
out vec3 frag_tangent;   // Passa la tangente al fragment shader
out vec3 frag_bitangent; // Passa la bitangente al fragment shader

out mat3 TBN;

void main()
{
 // Calcola la posizione del vertice nello spazio della camera
    gl_Position = World2Camera * Model2World * vec4(position, 1.0);

    // Calcola la matrice trasposta inversa del modello
    mat3 normalMatrix = transpose(inverse(mat3(Model2World)));

    // Trasforma normale, tangente e bitangente nello spazio del mondo
    frag_normal = normalize(normalMatrix * normal);
    frag_tangent = normalize(normalMatrix * tangent);
    frag_bitangent = normalize(normalMatrix * bitangent);

    // Costruisci la matrice TBN
    TBN = mat3(frag_tangent, frag_bitangent, frag_normal);

    // Passa le coordinate di texture
    frag_textcoord = textcoord;

    // Passa la posizione del frammento nello spazio del mondo
    frag_position = vec3(Model2World * vec4(position, 1.0));   
}

