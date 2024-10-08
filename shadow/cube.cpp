#include "cube.h"
#include "common.h"
#include "glm/glm.hpp"

#include <iostream>

Cube::Cube() : _initialized(false) {}

void Cube::init(void)
{

  Vertex Vertices[36] = {
      Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
      Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(1, 0)),
      Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(0, 1)),
      Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(1, 0)),
      Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(1, 1)),
      Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(0, 1)),

      // Destra
      Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1, 0, 0), glm::vec2(0, 0)),
      Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1, 0, 0), glm::vec2(1, 0)),
      Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 0, 0), glm::vec2(0, 1)),
      Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1, 0, 0), glm::vec2(1, 0)),
      Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1, 0, 0), glm::vec2(1, 1)),
      Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 0, 0), glm::vec2(0, 1)),

      // Alto
      Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0), glm::vec2(0, 0)),
      Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0), glm::vec2(1, 0)),
      Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 1, 0), glm::vec2(0, 1)),
      Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0), glm::vec2(1, 0)),
      Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
      Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 1, 0), glm::vec2(0, 1)),

      // Sinistra
      Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1, 0, 0), glm::vec2(1, 0)),
      Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
      Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1, 0, 0), glm::vec2(0, 0)),
      Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1, 0, 0), glm::vec2(0, 0)),
      Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
      Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1, 0, 0), glm::vec2(0, 1)),

      // Basso
      Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0, -1, 0), glm::vec2(0, 1)),
      Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, -1, 0), glm::vec2(0, 0)),
      Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, -1, 0), glm::vec2(1, 1)),
      Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, -1, 0), glm::vec2(1, 1)),
      Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, -1, 0), glm::vec2(0, 0)),
      Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, -1, 0), glm::vec2(1, 0)),

      // Dietro
      Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(1, 0)),
      Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(1, 1)),
      Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(0, 0)),
      Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(0, 0)),
      Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(1, 1)),
      Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(0, 1))};

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

  _color_texture.load("cubo_diffuse.png");
}

void Cube::render(void)
{

  if (!_initialized)
    init();

  glBindVertexArray(_VAO);

  _color_texture.bind(TEXTURE_COLOR);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glBindVertexArray(0);
}
