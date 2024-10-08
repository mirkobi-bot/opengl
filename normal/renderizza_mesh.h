#ifndef renderizza_mesh_H
#define renderizza_mesh_H

#include "GL/glew.h" // prima di freeglut
#include "texture2D.h"
#include "common.h"
#include <vector>
#include "glm/glm.hpp"
#include <iostream>
#include <fstream>
#include "mesh.h"

class RenderizzaMesh {
public:
    RenderizzaMesh();
    RenderizzaMesh(const std::string &filename);
    RenderizzaMesh(const std::vector <Vertex> &vertices):_vertices(vertices),_initialized(false){};

    /**
    Renderizza l'oggetto. Se necessario, l'oggetto viene prima inizializzato
    chiamando la init().
    */
    void render(void);
    void renderFromFile(void);

     /**
    Inizializzazione degli oggetti OpenGL. E' fatta in un secondo tempo
    poichè è necessario avere inizializzato GLUT prima di qualunque
    uso delle funzioni di OpenGL. La init è chiamata, se necessario,
    dalla render().
  */
  void init(void);
  void initFromFile(void);

private:
    GLuint _VAO;             // Vertex Array ObjectTexture2D 
    Texture2D _color_texture;  // Color Texture
    bool _initialized;       // Oggetto usabile?
    std::vector <Vertex> _vertices;
    std::string _filename; //il percorso del file contenente la mesh
    Mesh _model;
    

  // Blocchiamo le operazioni di copia di una istanza di RenderizzaMeshes:
  // non possiamo condividere un VAO
  RenderizzaMesh&operator=(const RenderizzaMesh &other);
  RenderizzaMesh(const RenderizzaMesh &other);
};
#endif 