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

void MyShaderClass::set_diffusive_light(const DiffusiveLight &dl)
{
  glUniform1f(_diffusive_intensity_location, dl.intensity());
}

void MyShaderClass::set_directional_light(const DirectionalLight &dl)
{
  glm::vec3 direction_normalized = glm::normalize(dl.direction());
  glUniform3fv(_directional_color_location, 1, const_cast<float *>(&dl.color()[0]));
  glUniform3fv(_directional_direction_location, 1, const_cast<float *>(&direction_normalized[0]));
}

void MyShaderClass::set_specular_light(const SpecularLight &sl)
{
  glUniform1f(_specular_intensity_location, sl.intensity());
  glUniform1f(_specular_shininess_location, sl.shininess());
}

// gestione di spot light e point light

void MyShaderClass::set_point_light(const PointLight &pl)
{
  glUniform3fv(_point_color_location, 1, const_cast<float *>(&pl.color()[0]));
  glUniform3fv(_point_position_location, 1, const_cast<float *>(&pl.position()[0]));
  glUniform1f(_point_constant_location, pl.constant());
  glUniform1f(_point_linear_location, pl.linear());
  glUniform1f(_point_quadratic_location, pl.quadratic());
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


bool MyShaderClass::load_shaders()
{
  std::cout << "dentro load_shaders" << std::endl;
  return add_shader(GL_VERTEX_SHADER, "normal.vert") &&
         add_shader(GL_FRAGMENT_SHADER, "normal.frag");
}


bool MyShaderClass::load_done()
{
  _model_transform_location = get_uniform_location("Model2World");
  _camera_transform_location = get_uniform_location("World2Camera");

  _ambient_color_location = get_uniform_location("AmbientLight.color");
  _ambient_intensity_location = get_uniform_location("AmbientLight.intensity");

  _directional_color_location = get_uniform_location("DirectionalLight.color");
  _directional_direction_location = get_uniform_location("DirectionalLight.direction");

  //_diffusive_intensity_location = get_uniform_location("DiffusiveLight.intensity");

  _specular_intensity_location = get_uniform_location("SpecularLight.intensity");
  _specular_shininess_location = get_uniform_location("SpecularLight.shininess");
  _camera_position_location = get_uniform_location("CameraPosition");

  // gestione di spot light e point light

  _point_color_location = get_uniform_location("PointLight.color");
  _point_position_location = get_uniform_location("PointLight.position");
  _point_constant_location = get_uniform_location("PointLight.constant");
  _point_linear_location = get_uniform_location("PointLight.linear");
  _point_quadratic_location = get_uniform_location("PointLight.quadratic");

  _spot_color_location = get_uniform_location("SpotLight.color");
  _spot_position_location = get_uniform_location("SpotLight.position");
  _spot_direction_location = get_uniform_location("SpotLight.direction");
  _spot_cutOff_location = get_uniform_location("SpotLight.cutOff");
  _spot_outerCutOff_location = get_uniform_location("SpotLight.outerCutOff");
  _spot_constant_location = get_uniform_location("SpotLight.constant");
  _spot_linear_location = get_uniform_location("SpotLight.linear");
  _spot_quadratic_location = get_uniform_location("SpotLight.quadratic");

  glUniform1i(get_uniform_location("diffuseMap"), TEXTURE_COLOR);

  glUniform1i(get_uniform_location("normalMap"), NORMAL_MAP);

  //glUniform1i(get_uniform_location("glossMap"), GLOSS_MAP);

  return (_model_transform_location != INVALID_UNIFORM_LOCATION) &&
         (_camera_transform_location != INVALID_UNIFORM_LOCATION) &&
         (_ambient_color_location != INVALID_UNIFORM_LOCATION) &&
         (_ambient_intensity_location != INVALID_UNIFORM_LOCATION) &&
         (_directional_color_location != INVALID_UNIFORM_LOCATION) &&
         (_directional_direction_location != INVALID_UNIFORM_LOCATION) &&
         //(_diffusive_intensity_location != INVALID_UNIFORM_LOCATION) &&
         (_specular_intensity_location != INVALID_UNIFORM_LOCATION) &&
         (_specular_shininess_location != INVALID_UNIFORM_LOCATION) &&
         (_camera_position_location != INVALID_UNIFORM_LOCATION) &&
         (_point_color_location != INVALID_UNIFORM_LOCATION) &&
         (_point_position_location != INVALID_UNIFORM_LOCATION) &&
         (_point_constant_location != INVALID_UNIFORM_LOCATION) &&
         (_point_linear_location != INVALID_UNIFORM_LOCATION) &&
         (_point_quadratic_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_color_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_position_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_direction_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_cutOff_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_outerCutOff_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_constant_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_linear_location != INVALID_UNIFORM_LOCATION) &&
         (_spot_quadratic_location != INVALID_UNIFORM_LOCATION);
}
