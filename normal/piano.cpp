#include "piano.h"
#include "common.h"

#include <iostream>

Piano::Piano() : _initialized(false) {}

void Piano::init(void)
{

  // inizio costruzione coordinate dei vertici incluse tangent e bitangent

  // positions
  glm::vec3 p0(-1.0f, 1.0f, 0.0f);
  glm::vec3 p1(-1.0f, -1.0f, 0.0f);
  glm::vec3 p2(1.0f, -1.0f, 0.0f);
  glm::vec3 p3(1.0f, 1.0f, 0.0f);
  // texture coordinates
  glm::vec2 uv0(0.0f, 1.0f);
  glm::vec2 uv1(0.0f, 0.0f);
  glm::vec2 uv2(1.0f, 0.0f);
  glm::vec2 uv3(1.0f, 1.0f);
  // normal vector
  glm::vec3 nm(0.0f, 0.0f, 1.0f);

  // calculate tangent/bitangent vectors of both triangles
  glm::vec3 tangent0, bitangent0;
  calculateTangentAndBitangent(p0, p1, p2, uv0, uv1, uv2, tangent0, bitangent0);
  glm::vec3 tangent1, bitangent1;
  calculateTangentAndBitangent(p0, p1, p2, uv0, uv1, uv2, tangent1, bitangent1);
  Vertex Vertices[] = {
      // positions // normal // texcoords  // tangent // bitangent
      Vertex(p0, nm, uv0, tangent0, bitangent0),
      Vertex(p1, nm, uv1, tangent0, bitangent0),
      Vertex(p2, nm, uv2, tangent0, bitangent0),

      Vertex(p0, nm, uv0, tangent1, bitangent1),
      Vertex(p2, nm, uv2, tangent1, bitangent1),
      Vertex(p3, nm, uv3, tangent1, bitangent1)};

  glGenVertexArrays(1, &(_VAO));
  glBindVertexArray(_VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(ATTRIB_POSITIONS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<GLvoid *>(offsetof(struct Vertex, position)));
  glEnableVertexAttribArray(ATTRIB_POSITIONS);

  glVertexAttribPointer(ATTRIB_NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<GLvoid *>(offsetof(struct Vertex, normal)));
  glEnableVertexAttribArray(ATTRIB_NORMALS);

  glVertexAttribPointer(ATTRIB_COLOR_TEXTURE_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<GLvoid *>(offsetof(struct Vertex, textcoord)));
  glEnableVertexAttribArray(ATTRIB_COLOR_TEXTURE_COORDS);

  // Specifica gli attributi per le tangenti e le bitangenti
  glVertexAttribPointer(ATTRIB_TANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<GLvoid *>(offsetof(struct Vertex, tangent)));
  glEnableVertexAttribArray(ATTRIB_TANGENTS);

  glVertexAttribPointer(ATTRIB_BITANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<GLvoid *>(offsetof(struct Vertex, bitangent)));
  glEnableVertexAttribArray(ATTRIB_BITANGENTS);

  _initialized = true;

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  _color_texture.load("piano_diffuse.png");
  _normalMap.load("piano_normal.png");
}

void Piano::render(void)
{

  if (!_initialized)
    init();

  glBindVertexArray(_VAO);

  _color_texture.bind(TEXTURE_COLOR);
  _normalMap.bind(NORMAL_MAP); // Normal map binding

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glBindVertexArray(0);
}

void Piano::calculateTangentAndBitangent(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
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
