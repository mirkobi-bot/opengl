#include "debug.h"
#include "utilities.h"
#include "common.h"
#include <iostream>


void Debug::set_depthmap(int unit)
{
  glUniform1i(_depthmap_location, unit);
}


bool Debug::load_shaders()
{
  std::cout << "main shader caricato" << std::endl;
  return add_shader(GL_VERTEX_SHADER, "debug.vert") &&
         add_shader(GL_FRAGMENT_SHADER, "debug.frag");
}

bool Debug::load_done()
{
   _depthmap_location = get_uniform_location("depthmap");

  return (_depthmap_location != INVALID_UNIFORM_LOCATION);
  }
