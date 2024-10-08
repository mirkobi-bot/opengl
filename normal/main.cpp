/**
  Questo codice mostra come sfruttare la libreria esterna assimp per impofrtare dei
  modelli 3D e renderizzarli nella scena.
  Al momento, il codice è in grado di renderizzare modelli costituiti da una
  singola mesh e con una singola Texture associata.

  I modelli 3D sono memorizzato nella cartella models (nella root di questo codice).
  Il formato dei file è Wavefront (https://en.wikipedia.org/wiki/Wavefront_.obj_file),
  un semplice file di testo con la lista delle coordinate dei vertici, facce e
  normali dei triangoli, e la/le texture associata/e.

  E' stata creata una classe Mesh che gestisce il caricamento e il rendering dei
  modelli. Gli oggetti in scena sono incapsulati in classi che permettono
  l'inizializzazione del modello e il suo rendering.

  Per comodità, sono state istanziate delle variabili globali che
  contengono diversi modelli 3D:

  Modelli singoli:
  'teapot': Una teiera (visualizzabile premendo 't')
  'skull' : Una teschio (visualizzabile premendo 'k')
  'dragon': Una drago (visualizzabile premendo 'g')
  'boot'  : Uno scarpone (visualizzabile premendo 'b')
  'flower': Un fiore (visualizzabile premendo 'f')

  Modello composto
  'marius': Un volto (visualizzabile premendo 'm').
  Questo modello è composto da diverse mesh (6) ciascuna definita in un suo
  file separato. Una volta caricate le singole mesh, queste sono renderizzate
  di seguito all'interno dello stesso ciclo di rendering per avere il volto
  completo. Inoltre, per questo modello, alcune texture hanno delle trasparenze
  Per poterle usare in modo corretto è necessario impostare in modo appropriato
  OpenGL. Vedere la funzione marius.render().
*/

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
#include "toro.h"
// #include "renderizza_mesh.h"
#include "piano.h"
#include "common.h"

Cube cubo;
Toro toro;

Piano piano;

/*

Cubo CORRETTO NORMALI, TEXTURE, ECC..
Vertex Vertices[36] = {
    // Faccia davanti
    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(0,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 1), glm::vec2(0,1), glm::vec3(), glm::vec3()),

    // Faccia destra
    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1, 0, 0), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1, 0, 0), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 0, 0), glm::vec2(0,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1, 0, 0), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1, 0, 0), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 0, 0), glm::vec2(0,1), glm::vec3(), glm::vec3()),

    // Faccia alto
    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 1, 0), glm::vec2(0,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 1, 0), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0, 1, 0), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 1, 0), glm::vec2(0,1), glm::vec3(), glm::vec3()),

    // Faccia sinistra
    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1, 0, 0), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1, 0, 0), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1, 0, 0), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1, 0, 0), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1, 0, 0), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1, 0, 0), glm::vec2(0,1), glm::vec3(), glm::vec3()),

    // Faccia basso
    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0, -1, 0), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, -1, 0), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, -1, 0), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, -1, 0), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, -1, 0), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, -1, 0), glm::vec2(0,1), glm::vec3(), glm::vec3()),

    // Faccia dietro
    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(1,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(0,0), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(1,1), glm::vec3(), glm::vec3()),
    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0, 0, -1), glm::vec2(0,1), glm::vec3(), glm::vec3())
  };

RenderizzaMesh mesh(vertices);

*/

// RenderizzaMesh mesh("models/dragon.obj");

unsigned char MODEL_TO_RENDER = 'p';
GLint MODE = GL_FILL;

/**
  Struttura di comodo dove sono memorizzate tutte le variabili globali
*/
struct global_struct
{

  int WINDOW_WIDTH = 1024; // Larghezza della finestra
  int WINDOW_HEIGHT = 768; // Altezza della finestra

  Camera camera;

  AmbientLight ambient_light;
  DirectionalLight directional_light;
  DiffusiveLight diffusive_light;
  SpecularLight specular_light;
  PointLight point_light;
  SpotLight spot_light;

  MyShaderClass myshaders;

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
  global.camera.set_camera(
      glm::vec3(0, 0, 0),
      glm::vec3(0, 0, -1),
      glm::vec3(0, 1, 0));

  global.camera.set_perspective(
      30.0f,
      global.WINDOW_WIDTH,
      global.WINDOW_HEIGHT,
      0.1,
      100);

  global.ambient_light = AmbientLight(glm::vec3(1, 1, 1), 0.2);
  // global.directional_light = DirectionalLight(glm::vec3(1,1,1),glm::vec3(0,0,-10)); // 0.5
  // global.diffusive_light = DiffusiveLight(0.5); // 0.5
  global.specular_light = SpecularLight(0.5, 30);
  // global.point_light = PointLight(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1.0f, 0.09f, 0.032f); //luce bianca nell'origine
  global.point_light = PointLight(glm::vec3(1, 0, 0), glm::vec3(0, 0, -10), 1.0f, 0.09f, 0.032f); // luce rossa spostata
  // global.spot_light = SpotLight(glm::vec3(1, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), 45.0f, 30.0f, 1.0f, 0.09f, 0.032f);///luce gialla
  global.spot_light = SpotLight(glm::vec3(1, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), 10.0f, 5.0f, 1.0f, 0.09f, 0.032f);

  global.myshaders.init();
  global.myshaders.enable();
}

void render_cubo()
{
  LocalTransform modelT;
  // imposto la rotazione attorno all'asse y
  // modelT.rotate(0.0f, global.angolo ,0.0f);
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(0, 0, -10);

  global.myshaders.set_model_transform(modelT.T());

  cubo.render();
  // std::cerr << "render del cubo" << std::endl;
}

void render_toro()
{
  LocalTransform modelT;
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(0, 0, -10);

  global.myshaders.set_model_transform(modelT.T());

  toro.render();

  // std::cerr << "render del toro" << std::endl;
}
/*
void render_mesh(){
  LocalTransform modelT;
  modelT.rotate(global.gradX, global.gradY ,0.0f);
  modelT.translate(0,-1.6,-10);

  global.myshaders.set_model_transform(modelT.T());

  mesh.renderFromFile();
  //std::cerr << "render della mesh" << std::endl;
}
*/

void render_piano()
{
  LocalTransform modelT;
  // imposto la rotazione attorno all'asse y
  // modelT.rotate(0.0f, global.angolo ,0.0f);
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(0, 0, -10);

  global.myshaders.set_model_transform(modelT.T());

  piano.render();
  // std::cerr << "render del cubo" << std::endl;
}

void MyRenderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  global.myshaders.set_camera_transform(global.camera.CP());
  global.myshaders.set_ambient_light(global.ambient_light);
  global.myshaders.set_directional_light(global.directional_light);
  global.myshaders.set_diffusive_light(global.diffusive_light);
  global.myshaders.set_specular_light(global.specular_light);
  global.myshaders.set_camera_position(global.camera.position());
  global.myshaders.set_spot_light(global.spot_light);
  global.myshaders.set_point_light(global.point_light);

  switch (MODEL_TO_RENDER)
  {
  // case 'm': render_mesh(); break;
  case 'p':
    render_piano();
    break;
  case 'c':
    render_cubo();
    break;
  case 't':
    render_toro();
    break;
  }

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
  case 'a':
    global.gradY -= global.SPEED;
    break;
  case 'd':
    global.gradY += global.SPEED;
    break;
  case 'w':
    global.gradX -= global.SPEED;
    break;
  case 's':
    global.gradX += global.SPEED;
    break;

  // Variamo l'intensità di luce ambientale
  case '1':
    global.ambient_light.dec(0.01);
    break;

  case '2':
    global.ambient_light.inc(0.01);
    break;

  // Variamo l'intensità di luce diffusiva
  case '3':
    global.diffusive_light.dec(0.01);
    break;

  // Variamo l'intensità di luce diffusiva
  case '4':
    global.diffusive_light.inc(0.01);
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

  // spostiamo la point light
  case '9':
    global.point_light.incZ(1.0);
    break;

  case '0':
    global.point_light.decZ(1.0);
    break;

  case ' ': // Reimpostiamo la camera
    global.camera.set_camera(
        glm::vec3(0, 0, 0),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 1, 0));
    global.gradX = 0;
    global.gradY = 0;

    break;

  case 'r':
    // Avvia la funzione di aggiornamento
    glutTimerFunc(25, update, 0);
    break;

  case 'p':
  case 'c':
  case 't':
    MODEL_TO_RENDER = key;
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