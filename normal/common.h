#ifndef common_H 
#define common_H

#include "glm/glm.hpp"


/**
Struttura dati che contiene gli attributi di un vertice.
*/
struct Vertex {
	glm::vec3 position; ///< Coordinate spaziali
	glm::vec3 normal;   ///< Normale
	glm::vec2 textcoord;///< Coordinate di texture
	glm::vec3 tangent;      ///< Tangente
    glm::vec3 bitangent;    ///< Bitangente

	Vertex();

	Vertex(
  		float x, float y, float z, 
  		float xn, float yn, float zn,
  		float s, float t,
		float tx, float ty, float tz,
		float bx, float by, float bz);

	Vertex(const glm::vec3 &xyz, const glm::vec3 &norm, const glm::vec2 &txt, const glm::vec3 &tan, const glm::vec3 &bitan);

};


enum ATTRIB_ID {ATTRIB_POSITIONS=0, ATTRIB_NORMALS=1, ATTRIB_COLOR_TEXTURE_COORDS=2, ATTRIB_TANGENTS=3,ATTRIB_BITANGENTS=4};

enum TEXTURE_UNIT_ID {TEXTURE_COLOR = 0, NORMAL_MAP = 1, GLOSS_MAP = 2};


#endif