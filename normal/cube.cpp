#include "cube.h"
#include "common.h"
#include <iostream>

Cube::Cube() : _initialized(false) {}

void Cube::init(void)
{

  std::vector<Vertex> vertices;

  // Vertici del cubo
  glm::vec3 positions[8] = {
      glm::vec3(-1.0f, -1.0f, 1.0f), // p0
      glm::vec3(1.0f, -1.0f, 1.0f),  // p1
      glm::vec3(-1.0f, 1.0f, 1.0f),  // p2
      glm::vec3(1.0f, 1.0f, 1.0f),   // p3
      glm::vec3(1.0f, -1.0f, -1.0f), // p4
      glm::vec3(1.0f, 1.0f, -1.0f),  // p5
      glm::vec3(-1.0f, 1.0f, -1.0f), // p6
      glm::vec3(-1.0f, -1.0f, -1.0f) // p7
  };

  // Normali per ciascuna faccia del cubo
  glm::vec3 normals[6] = {
      glm::vec3(0, 0, 1),  // Front
      glm::vec3(1, 0, 0),  // Right
      glm::vec3(0, 1, 0),  // Top
      glm::vec3(-1, 0, 0), // Left
      glm::vec3(0, -1, 0), // Bottom
      glm::vec3(0, 0, -1)  // Back
  };

  // Coordinate di texture
  glm::vec2 uvs[4] = {
      glm::vec2(0, 0), // uv0
      glm::vec2(1, 0), // uv1
      glm::vec2(0, 1), // uv2
      glm::vec2(1, 1)  // uv3
  };


  // Calcola le tangenti e i bitangenti
  glm::vec3 tangent0, bitangent0;
  glm::vec3 tangent1, bitangent1;

  calculateTangentAndBitangent(positions[0], positions[1], positions[2], uvs[0], uvs[1], uvs[2], tangent0, bitangent0);
  calculateTangentAndBitangent(positions[1], positions[3], positions[2], uvs[1], uvs[3], uvs[2], tangent1, bitangent1);

  // Faccia davanti

  vertices.push_back(Vertex(positions[0], normals[0], uvs[0], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[1], normals[0], uvs[1], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[2], normals[0], uvs[2], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[1], normals[0], uvs[1], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[3], normals[0], uvs[3], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[2], normals[0], uvs[2], tangent1, bitangent1));

  // Faccia destra

  calculateTangentAndBitangent(positions[1], positions[4], positions[3], uvs[0], uvs[1], uvs[2], tangent0, bitangent0);
  calculateTangentAndBitangent(positions[3], positions[5], positions[4], uvs[1], uvs[3], uvs[2], tangent1, bitangent1);

  vertices.push_back(Vertex(positions[1], normals[1], uvs[0], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[4], normals[1], uvs[1], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[3], normals[1], uvs[2], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[4], normals[1], uvs[1], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[5], normals[1], uvs[3], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[3], normals[1], uvs[2], tangent1, bitangent1));

  // Faccia alto

  calculateTangentAndBitangent(positions[2], positions[3], positions[6], uvs[0], uvs[1], uvs[2], tangent0, bitangent0);
  calculateTangentAndBitangent(positions[3], positions[5], positions[6], uvs[1], uvs[3], uvs[2], tangent1, bitangent1);

  vertices.push_back(Vertex(positions[2], normals[2], uvs[0], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[3], normals[2], uvs[1], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[6], normals[2], uvs[2], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[3], normals[2], uvs[1], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[5], normals[2], uvs[3], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[6], normals[2], uvs[2], tangent1, bitangent1));

  // Faccia sinistra

  calculateTangentAndBitangent(positions[0], positions[2], positions[7], uvs[1], uvs[3], uvs[0], tangent0, bitangent0);
  calculateTangentAndBitangent(positions[7], positions[2], positions[6], uvs[0], uvs[3], uvs[2], tangent1, bitangent1);

  vertices.push_back(Vertex(positions[0], normals[3], uvs[1], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[2], normals[3], uvs[3], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[7], normals[3], uvs[0], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[7], normals[3], uvs[0], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[2], normals[3], uvs[3], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[6], normals[3], uvs[2], tangent1, bitangent1));

  // Faccia basso

  calculateTangentAndBitangent(positions[0], positions[7], positions[1], uvs[1], uvs[3], uvs[0], tangent0, bitangent0);
  calculateTangentAndBitangent(positions[1], positions[7], positions[4], uvs[0], uvs[3], uvs[2], tangent1, bitangent1);

  vertices.push_back(Vertex(positions[0], normals[4], uvs[2], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[7], normals[4], uvs[0], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[1], normals[4], uvs[3], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[1], normals[4], uvs[3], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[7], normals[4], uvs[0], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[4], normals[4], uvs[1], tangent1, bitangent1));

  // Faccia dietro

  calculateTangentAndBitangent(positions[7], positions[6], positions[4], uvs[1], uvs[3], uvs[0], tangent0, bitangent0);
  calculateTangentAndBitangent(positions[4], positions[6], positions[5], uvs[0], uvs[3], uvs[2], tangent1, bitangent1);

  vertices.push_back(Vertex(positions[7], normals[5], uvs[1], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[6], normals[5], uvs[3], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[4], normals[5], uvs[0], tangent0, bitangent0));
  vertices.push_back(Vertex(positions[4], normals[5], uvs[0], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[6], normals[5], uvs[3], tangent1, bitangent1));
  vertices.push_back(Vertex(positions[5], normals[5], uvs[2], tangent1, bitangent1));

  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

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

  _color_texture.load("cubo_diffuse.png");
  _normalMap.load("cubo_normal.png");
}

void Cube::render(void)
{

  if (!_initialized)
    init();

  glBindVertexArray(_VAO);

  _color_texture.bind(TEXTURE_COLOR);
  _normalMap.bind(NORMAL_MAP);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glBindVertexArray(0);
}

void Cube::calculateTangentAndBitangent(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
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
