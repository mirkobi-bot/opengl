#include <iostream>
#include <sstream>
#include "GL/glew.h" // prima di freeglut
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <vector>
#include "transform.h"
#include "camera.h"
#include "myshaderclass.h"
#include "cube.h"
#include "piano.h"
#include "common.h"
#include "depthshader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "debug.h"

Cube cubo;
Piano piano;

GLint MODE = GL_FILL;

/**
  Struttura di comodo dove sono memorizzate tutte le variabili globali
*/
struct global_struct
{

  int WINDOW_WIDTH = 1024; // Larghezza della finestra
  int WINDOW_HEIGHT = 768; // Altezza della finestra

  Camera camera;
  Camera spotlight_camera;

  AmbientLight ambient_light;
  SpotLight spot_light;
  SpecularLight specular_light;

  glm::mat4 lightSpaceMatrix;

  MyShaderClass mainshader;
  Depthshader depthshader;
  Debug debugshader;

  unsigned int depthMapFBO;
  unsigned int depthMap;

  bool firstpass = true;

  const float SPEED = 1;
  float angolo = 0.0f;        // Angolo di rotazione
  float velRotazione = 45.0f; // Velocità di rotazione espressa in gradi al secondo
  float gradX;
  float gradY;

  global_struct() : gradX(0.0f), gradY(0.0f) {}

} global;

/**
funzione che ruota il cubo
*/
void update(int value)
{
  global.angolo += global.velRotazione / 30.0f; // Aggiorna l'angolo in base alla velocità di rotazione (30fps)
  if (global.angolo > 360)
  {
    global.angolo -= 360; // Per evitare overflow dell'angolo
  }
  glutPostRedisplay();
  glutTimerFunc(1000 / 30, update, 0); // Richiama se stesso dopo 1/30 di secondo
}

/**
Prototipi della nostre funzioni di callback.
Sono definite più avanti nel codice.
*/
void MyRenderScene(void);
void MyIdle(void);
void MyKeyboard(unsigned char key, int x, int y);
void MyClose(void);
void MySpecialKeyboard(int Key, int x, int y);
void MyMouse(int x, int y);
bool setframebuffer(void);

bool setframebuffer()
{

  glGenFramebuffers(1, &global.depthMapFBO);

  glGenTextures(1, &global.depthMap);
  glBindTexture(GL_TEXTURE_2D, global.depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, global.WINDOW_WIDTH, global.WINDOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // Cambia GL_REPEAT con GL_CLAMP_TO_BORDER
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  // Set a border color
  GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, global.depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, global.depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Always check that our framebuffer is ok
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return false;
  return true;
}

void init(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Progetto Esame IG");

  /*
    // Imposta la modalità a schemo intero e nasconde il cursore
    std::stringstream game_mode;
    game_mode << global.WINDOW_WIDTH << "x" << global.WINDOW_HEIGHT << ":32";
    glutGameModeString(game_mode.str().c_str());
    glutEnterGameMode();
  */
  glutSetCursor(GLUT_CURSOR_NONE);

  global.camera.set_mouse_init_position(global.WINDOW_WIDTH / 2, global.WINDOW_HEIGHT / 2);
  global.camera.lock_mouse_position(true);
  glutWarpPointer(global.WINDOW_WIDTH / 2, global.WINDOW_HEIGHT / 2);

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    std::cerr << "Error : " << glewGetErrorString(res) << std::endl;
    exit(1);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glutDisplayFunc(MyRenderScene);

  glutKeyboardFunc(MyKeyboard);

  glutCloseFunc(MyClose);

  glutSpecialFunc(MySpecialKeyboard);

  glutPassiveMotionFunc(MyMouse);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);
}

void create_scene()
{
  if (!setframebuffer)
  {
    std::cout << "FRAMEBUFFER ERROR" << std::endl;
    exit(EXIT_FAILURE);
  }

  global.camera.set_camera(
      glm::vec3(0, 5, 20),
      glm::vec3(0, 0, 0),
      glm::vec3(0, 1, 0));

  global.camera.set_perspective(
      30.0f,
      global.WINDOW_WIDTH,
      global.WINDOW_HEIGHT,
      0.1,
      100);

  global.ambient_light = AmbientLight(glm::vec3(1, 1, 0), 0.2);
  global.specular_light = SpecularLight(0.5, 30);
  global.spot_light = SpotLight(glm::vec3(1, 1, 0), glm::vec3(-5, 2, 2), glm::vec3(0, 1, 0), 30.0f, 45.0f, 1.0f, 0.09f, 0.032f);

  glm::mat4 lightProjection, lightView;
  glm::mat4 lightSpaceMatrix;
  /* float near_plane = 1.0f, far_plane = 7.5f;
  lightProjection = glm::perspective(glm::radians(global.spot_light.cutOff()), 1.0f, near_plane, far_plane);
  lightView = glm::lookAt(global.spot_light.position(), global.spot_light.position() + global.spot_light.direction(), glm::vec3(0.0f, 1.0f, 0.0f));
  lightSpaceMatrix = lightProjection * lightView; */

  float near_plane = 1.0f, far_plane = 7.5f; // Estendi il far plane per catturare più scena
  // lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);  // Per luce direzionale
  lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)global.WINDOW_WIDTH / (GLfloat)global.WINDOW_HEIGHT, near_plane, far_plane);
  // note that if you use a perspective projection matrix
  // you'll have to change the light position as the current light position isn't enough to reflect the whole scene
  lightView = glm::lookAt(global.spot_light.position(), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
  global.lightSpaceMatrix = lightProjection * lightView;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  global.depthshader.set_lightSpaceMatrix_transform(global.lightSpaceMatrix);

  global.depthshader.init();

  global.mainshader.init();
}

void render_cubo()
{
  LocalTransform modelT;
  // imposto la rotazione attorno all'asse y
  // modelT.rotate(0.0f, global.angolo ,0.0f);
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(0, 1, 0);
  if (global.firstpass)
  {
    global.depthshader.set_model_transform(modelT.T());
  }
  else
  {
    global.mainshader.set_model_transform(modelT.T());
  }

  cubo.render();
  // std::cerr << "render del cubo" << std::endl;
}

void render_cubino()
{
  LocalTransform modelT;
  // imposto la rotazione attorno all'asse y
  // modelT.rotate(0.0f, global.angolo ,0.0f);
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.scale(0.5);
  modelT.translate(5, 0.5, 0);

  if (global.firstpass)
  {
    global.depthshader.set_model_transform(modelT.T());
  }
  else
  {
    global.mainshader.set_model_transform(modelT.T());
  }

  cubo.render();
  // std::cerr << "render del cubo" << std::endl;
}

void render_piano()
{
  LocalTransform modelT;
  // imposto la rotazione attorno all'asse y
  // modelT.rotate(0.0f, global.angolo ,0.0f);
  modelT.rotate(-90.0f, global.gradY, 0.0f);
  modelT.translate(0, 0, 0);
  modelT.scale(10.0);

  if (global.firstpass)
  {
    global.depthshader.set_model_transform(modelT.T());
  }
  else
  {
    global.mainshader.set_model_transform(modelT.T());
  }

  piano.render();
  // std::cerr << "render del cubo" << std::endl;
}

void render_depth()
{
  glCullFace(GL_FRONT);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  global.depthshader.enable();
  glViewport(0, 0, global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
  glBindFramebuffer(GL_FRAMEBUFFER, global.depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);

  global.depthshader.set_lightSpaceMatrix_transform(global.lightSpaceMatrix);

  render_piano();
  render_cubino();
  render_cubo();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
   
}

void render_scena()
{
  glCullFace(GL_BACK);
  global.firstpass = false;
  // reset viewport
  glViewport(0, 0, global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  global.mainshader.enable();

  global.mainshader.set_depthmap(1);
  global.mainshader.set_lightSpaceMatrix_transform(global.lightSpaceMatrix);
  global.mainshader.set_camera_transform(global.camera.CP());
  global.mainshader.set_ambient_light(global.ambient_light);
  global.mainshader.set_specular_light(global.specular_light);
  global.mainshader.set_camera_position(global.camera.position());
  global.mainshader.set_spot_light(global.spot_light);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, global.depthMap);

  render_piano();
  render_cubino();
  render_cubo();
}

void MyRenderScene()
{
  render_depth();
  render_scena();

  glutSwapBuffers();
}

// Funzione globale che si occupa di gestire l'input da tastiera.
void MyKeyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // Escape key
    glutDestroyWindow(glutGetWindow());
    return;
    break;

  // Variamo l'intensità di luce ambientale
  case '1':
    global.ambient_light.dec(0.01);
    break;

  case '2':
    global.ambient_light.inc(0.01);
    break;

  // Variamo l'intensità di luce speculare
  case '5':
    global.specular_light.dec(0.01);
    break;

  // Variamo l'intensità di luce speculare
  case '6':
    global.specular_light.inc(0.01);
    break;

  // Variamo l'esponente della luce speculare
  case '7':
    global.specular_light.dec_shine(1);
    break;

  // Variamo l'esponente della luce speculare
  case '8':
    global.specular_light.inc_shine(1);
    break;

  case ' ': // Reimpostiamo la camera
    global.camera.set_camera(
        glm::vec3(0, 5, 20),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0));
    global.gradX = 0;
    global.gradY = 0;

    break;

  case 'z':
    if (MODE == GL_FILL)
      MODE = GL_LINE;
    else
      MODE = GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, MODE);
    break;
  }

  glutPostRedisplay();
}

void MySpecialKeyboard(int Key, int x, int y)
{
  global.camera.onSpecialKeyboard(Key);
  glutPostRedisplay();
}

void MyMouse(int x, int y)
{
  if (global.camera.onMouse(x, y))
  {
    // Risposto il mouse al centro della finestra
    glutWarpPointer(global.WINDOW_WIDTH / 2, global.WINDOW_HEIGHT / 2);
  }
  glutPostRedisplay();
}

// Funzione globale che si occupa di gestire la chiusura della finestra.
void MyClose(void)
{
  std::cout << "Tearing down the system..." << std::endl;
  // Clean up here

  // A schermo intero dobbiamo uccidere l'applicazione.
  exit(0);
}

int main(int argc, char *argv[])
{
  init(argc, argv);

  create_scene();

  glutMainLoop();

  return 0;
}