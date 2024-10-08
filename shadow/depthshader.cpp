#include "depthshader.h"
#include "utilities.h"
#include "common.h"
#include <iostream>

void Depthshader::set_model_transform(const glm::mat4 &transform)
{
  glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}

void Depthshader::set_lightSpaceMatrix_transform(const glm::mat4 &transform)
{
  glUniformMatrix4fv(_lightSpaceMatrix_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}


bool Depthshader::load_shaders()
{
  std::cout << "depth shader caricato" << std::endl;
  return add_shader(GL_VERTEX_SHADER, "depth.vert") &&
         add_shader(GL_FRAGMENT_SHADER, "depth.frag");
}


bool Depthshader::load_done()
{
  _model_transform_location = get_uniform_location("Model2World");
  _lightSpaceMatrix_transform_location = get_uniform_location("lightSpaceMatrix");


  return (_model_transform_location != INVALID_UNIFORM_LOCATION) &&
         (_lightSpaceMatrix_transform_location != INVALID_UNIFORM_LOCATION);
}
