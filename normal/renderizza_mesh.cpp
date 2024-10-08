#include "renderizza_mesh.h"
#include "common.h"

RenderizzaMesh::RenderizzaMesh():_initialized(false) {}

RenderizzaMesh::RenderizzaMesh(const std::string &filename){
    _filename = filename;
    std::cerr << "Dentro costruttore" << std::endl;
}

void RenderizzaMesh::init()
{
    glGenVertexArrays(1, &(_VAO));
    glBindVertexArray(_VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

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

    _color_texture.load("texture-cubo.png");
}

void RenderizzaMesh::initFromFile(void) {
  _model.load_mesh(_filename);
  _initialized = true;
}

void RenderizzaMesh::render(void)
{
    if (!_initialized)
        init();

    glBindVertexArray(_VAO);

    _color_texture.bind(TEXTURE_COLOR);

    glDrawArrays(GL_TRIANGLES, 0, _vertices.size() * sizeof(Vertex));

    glBindVertexArray(0);
}



void RenderizzaMesh::renderFromFile(void)
{
     if (!_initialized)
        initFromFile();
  _model.render();
   std::cerr << "Oggetto renderizzato" << std::endl;
}
