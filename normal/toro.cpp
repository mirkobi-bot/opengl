#include "toro.h"
#include "common.h"
#include "glm/glm.hpp"
#include <vector>
#include <cmath>

const int numMajorSegments = 30; // Numero di segmenti maggiori
const int numMinorSegments = 20; // Numero di segmenti minori
const float majorRadius = 1.0f;  // Raggio maggiore del Toro
const float minorRadius = 0.3f;  // Raggio minore del Toro
const float PI = 3.14159265358979323846;

Toro::Toro() : _initialized(false) {}

void Toro::init(void)
{

    std::vector<Vertex> vertices;

    // Genera i vertici del Toro
    for (int i = 0; i < numMajorSegments; ++i)
    {
        float theta = 2 * PI * i / numMajorSegments;
        float nextTheta = 2 * PI * (i + 1) / numMajorSegments;

        for (int j = 0; j < numMinorSegments; ++j)
        {
            float phi = 2 * PI * j / numMinorSegments;
            float nextPhi = 2 * PI * (j + 1) / numMinorSegments;

            float cosTheta = cos(theta);
            float sinTheta = sin(theta);
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);
            float cosNextTheta = cos(nextTheta);
            float sinNextTheta = sin(nextTheta);
            float cosNextPhi = cos(nextPhi);
            float sinNextPhi = sin(nextPhi);

            // vertici del triangolo
            glm::vec3 p0((majorRadius + minorRadius * cosPhi) * cosTheta,
                         (majorRadius + minorRadius * cosPhi) * sinTheta,
                         minorRadius * sinPhi);

            glm::vec3 p1((majorRadius + minorRadius * cosPhi) * cosNextTheta,
                         (majorRadius + minorRadius * cosPhi) * sinNextTheta,
                         minorRadius * sinPhi);

            glm::vec3 p2((majorRadius + minorRadius * cosNextPhi) * cosTheta,
                         (majorRadius + minorRadius * cosNextPhi) * sinTheta,
                         minorRadius * sinNextPhi);

            glm::vec3 p3((majorRadius + minorRadius * cosNextPhi) * cosNextTheta,
                         (majorRadius + minorRadius * cosNextPhi) * sinNextTheta,
                         minorRadius * sinNextPhi);

            // normali
            glm::vec3 n0 = p0 - glm::vec3(majorRadius * cosTheta, majorRadius * sinTheta, 0.0f);
            glm::vec3 n1 = p1 - glm::vec3(majorRadius * cosNextTheta, majorRadius * sinNextTheta, 0.0f);
            glm::vec3 n2 = p2 - glm::vec3(majorRadius * cosTheta, majorRadius * sinTheta, 0.0f);
            glm::vec3 n3 = p3 - glm::vec3(majorRadius * cosNextTheta, majorRadius * sinNextTheta, 0.0f);

            // coordinate di texture
            glm::vec2 uv0(0, 0);
            glm::vec2 uv1(1, 0);
            glm::vec2 uv2(0, 1);
            glm::vec2 uv3(1, 1);

            // Calcola le tangenti e i bitangenti
            glm::vec3 tangent0, bitangent0;
            calculateTangentAndBitangent(p0, p1, p2, uv0, uv1, uv2, tangent0, bitangent0);

            glm::vec3 tangent1, bitangent1;
            calculateTangentAndBitangent(p2, p1, p3, uv2, uv1, uv3, tangent1, bitangent1);

            // Aggiungi i vertici al vettore
            vertices.push_back(Vertex(p0, n0, uv0, tangent0, bitangent0));
            vertices.push_back(Vertex(p1, n1, uv1, tangent0, bitangent0));
            vertices.push_back(Vertex(p2, n2, uv2, tangent0, bitangent0));

            vertices.push_back(Vertex(p2, n2, uv2, tangent1, bitangent1));
            vertices.push_back(Vertex(p1, n1, uv1, tangent1, bitangent1));
            vertices.push_back(Vertex(p3, n3, uv3, tangent1, bitangent1));
        }
    }

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Specifica il layout degli attributi dei vertici
    glVertexAttribPointer(ATTRIB_POSITIONS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, position)));
    glEnableVertexAttribArray(ATTRIB_POSITIONS);

    glVertexAttribPointer(ATTRIB_NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, normal)));
    glEnableVertexAttribArray(ATTRIB_NORMALS);

    glVertexAttribPointer(ATTRIB_COLOR_TEXTURE_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, textcoord)));
    glEnableVertexAttribArray(ATTRIB_COLOR_TEXTURE_COORDS);

    // Attributo tangente
    glVertexAttribPointer(ATTRIB_TANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(struct Vertex, tangent)));
    glEnableVertexAttribArray(ATTRIB_TANGENTS);
    // Attributo bitangente
    glVertexAttribPointer(ATTRIB_BITANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(struct Vertex, bitangent)));
    glEnableVertexAttribArray(ATTRIB_BITANGENTS);

    _initialized = true;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _color_texture.load("toro_diffuse.png");
    _normalMap.load("toro_normal.png");
}

void Toro::render(void)
{
    if (!_initialized)
        init();
    glBindVertexArray(_VAO);
    // Assicura che la texture del toro sia attiva
    _color_texture.bind(TEXTURE_COLOR);
    _normalMap.bind(NORMAL_MAP);
    // Renderizza il Toro
    glDrawArrays(GL_TRIANGLES, 0, numMajorSegments * numMinorSegments * 6);

    glBindVertexArray(0);
}

void Toro::calculateTangentAndBitangent(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
                                        const glm::vec2 &uv0, const glm::vec2 &uv1, const glm::vec2 &uv2,
                                        glm::vec3 &tangent, glm::vec3 &bitangent)
{
    glm::vec3 edge1 = p1 - p0;
    glm::vec3 edge2 = p2 - p0;

    glm::vec2 deltaUV1 = uv1 - uv0;
    glm::vec2 deltaUV2 = uv2 - uv0;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent = glm::normalize(tangent);

    bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent = glm::normalize(bitangent);
}
