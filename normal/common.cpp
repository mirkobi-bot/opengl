#include "common.h"

Vertex::Vertex() : position(0,0,0), normal(0,0,0), textcoord(0,0), tangent(0,0,0), bitangent(0,0,0) {}

Vertex::Vertex(
  float x, float y, float z, 
  float xn, float yn, float zn,
  float s, float t,
  float tx, float ty, float tz,
	float bx, float by, float bz) :position(x,y,z), normal(xn,yn,zn), textcoord(s,t), tangent(tx,ty,tz),bitangent(bx,by,bz) {}


Vertex::Vertex(const glm::vec3 &xyz, const glm::vec3 &norm, const glm::vec2 &txt,const glm::vec3 &tan, const glm::vec3 &bitan) 
  : position(xyz), normal(norm), textcoord(txt),tangent(tan),bitangent(bitan) {}


