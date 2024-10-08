#include "myshaderclass.h"
#include "utilities.h"
#include "common.h"
#include <iostream>

void MyShaderClass::set_model_transform(const glm::mat4 &transform)
{
  glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}

void MyShaderClass::set_camera_transform(const glm::mat4 &transform)
{
  glUniformMatrix4fv(_camera_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}

void MyShaderClass::set_ambient_light(const AmbientLight &al)
{
  glUniform3fv(_ambient_color_location, 1, const_cast<float *>(&al.color()[0]));
  glUniform1f(_ambient_intensity_location, al.intensity());
}

void MyShaderClass::set_specular_light(const SpecularLight &sl)
{
  glUniform1f(_specular_intensity_location, sl.intensity());
  glUniform1f(_specular_shininess_location, sl.shininess());
}

void MyShaderClass::set_spot_light(const SpotLight &sl)
{
  glUniform3fv(_spot_color_location, 1, const_cast<float *>(&sl.color()[0]));
  glUniform3fv(_spot_position_location, 1, const_cast<float *>(&sl.position()[0]));
  glUniform3fv(_spot_direction_location, 1, const_cast<float *>(&sl.direction()[0]));
  glUniform1f(_spot_cutOff_location, sl.cutOff());
  glUniform1f(_spot_outerCutOff_location, sl.outerCutOff());
  glUniform1f(_spot_constant_location, sl.constant());
  glUniform1f(_spot_linear_location, sl.linear());
  glUniform1f(_spot_quadratic_location, sl.quadratic());
}

void MyShaderClass::set_camera_position(const glm::vec3 &pos)
{
  glUniform3fv(_camera_position_location, 1, const_cast<float *>(&pos[0]));
}

void MyShaderClass::set_depthmap(int unit)
{
  glUniform1i(_depthmap_location, unit);
}

void MyShaderClass::set_lightSpaceMatrix_transform(const glm::mat4 &transform)
{
  glUniformMatrix4fv(_lightSpaceMatrix_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}


bool MyShaderClass::load_shaders()
{
  std::cout << "main shader caricato" << std::endl;
  return add_shader(GL_VERTEX_SHADER, "shadow.vert") &&
         add_shader(GL_FRAGMENT_SHADER, "shadow.frag");
}

bool MyShaderClass::load_done()
{
  _model_transform_location = get_uniform_location("Model2World");
  _camera_transform_location = get_uniform_location("World2Camera");

  _lightSpaceMatrix_transform_location = get_uniform_location("lightSpaceMatrix");

   _ambient_color_location = get_uniform_location("AmbientLight.color");
   _ambient_intensity_location = get_uniform_location("AmbientLight.intensity");

   _specular_intensity_location = get_uniform_location("SpecularLight.intensity");
   _specular_shininess_location = get_uniform_location("SpecularLight.shininess");
  _camera_position_location = get_uniform_location("CameraPosition");

   _spot_color_location = get_uniform_location("SpotLight.color");
   _spot_position_location = get_uniform_location("SpotLight.position");

   glUniform1i(get_uniform_location("diffuseMap"), TEXTURE_COLOR);

   _depthmap_location = get_uniform_location("depthmap");

  return (_model_transform_location != INVALID_UNIFORM_LOCATION) &&
         (_camera_transform_location != INVALID_UNIFORM_LOCATION) &&
          (_ambient_color_location != INVALID_UNIFORM_LOCATION) &&
          (_ambient_intensity_location != INVALID_UNIFORM_LOCATION) &&
          (_specular_intensity_location != INVALID_UNIFORM_LOCATION) &&
          (_specular_shininess_location != INVALID_UNIFORM_LOCATION) &&
         (_camera_position_location != INVALID_UNIFORM_LOCATION) &&
         (_depthmap_location != INVALID_UNIFORM_LOCATION) &&
      (_spot_color_location != INVALID_UNIFORM_LOCATION) &&
      (_lightSpaceMatrix_transform_location != INVALID_UNIFORM_LOCATION);
}
