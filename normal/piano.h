#ifndef PIANO_H
#define PIANO_H

#include "GL/glew.h" // prima di freeglut
#include "texture2D.h"
#include "glm/glm.hpp"

class Piano {
public:

  /**
    Costruttore
  */
  Piano();

  /**
    Renderizza l'oggetto. Se necessario, l'oggetto viene prima inizializzato
    chiamando la init().
  */
  void render(void);


  /**
    Inizializzazione degli oggetti OpenGL. E' fatta in un secondo tempo
    poichè è necessario avere inizializzato GLUT prima di qualunque
    uso delle funzioni di OpenGL. La init è chiamata, se necessario,
    dalla render().
  */
  void init(void);

  void calculateTangentAndBitangent(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
                                        const glm::vec2 &uv0, const glm::vec2 &uv1, const glm::vec2 &uv2,
                                        glm::vec3 &tangent, glm::vec3 &bitangent);


private:
  GLuint _VAO;             // Vertex Array Object
  Texture2D _color_texture;  // Color Texture
  Texture2D _normalMap;  // Color Texture
  bool _initialized;       // Oggetto usabile?

  // Blocchiamo le operazioni di copia di una istanza di Piano:
  // non possiamo condividere un VAO
  Piano&operator=(const Piano &other);
  Piano(const Piano &other);
};

#endif 