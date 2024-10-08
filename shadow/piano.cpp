#include "piano.h"
#include "common.h"
#include "glm/glm.hpp"

#include <iostream>

Piano::Piano() : _initialized(false) {}

void Piano::init(void)
{

  // inizio costruzione coordinate dei vertici incluse tangent e bitangent

  // positions
  glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
  glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
  glm::vec3 pos3(1.0f, -1.0f, 0.0f);
  glm::vec3 pos4(1.0f, 1.0f, 0.0f);
  // texture coordinates
  glm::vec2 uv1(0.0f, 1.0f);
  glm::vec2 uv2(0.0f, 0.0f);
  glm::vec2 uv3(1.0f, 0.0f);
  glm::vec2 uv4(1.0f, 1.0f);
  // normal vector
  glm::vec3 nm(0.0f, 0.0f, 1.0f);


  Vertex Vertices[] = {
      // positions            // normal         // texcoords  // tangent                          // bitangent
      Vertex(pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y),
      Vertex(pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y),
      Vertex(pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y),

      Vertex(pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y),
      Vertex(pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y),
      Vertex(pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y)};

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

  _initialized = true;

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  _color_texture.load("piano_diffuse.png");

  
  
}

void Piano::render(void)
{

  if (!_initialized)
    init();

  glBindVertexArray(_VAO);

  _color_texture.bind(TEXTURE_COLOR);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glBindVertexArray(0);
}
