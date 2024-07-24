//------------------------------------------------------------------------------
//  cube-emsc.c
//  Shader uniforms updates.
//------------------------------------------------------------------------------

#include "bgfx/defines.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#define GLM_FORCE_PURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <string>

#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <nlohmann/json.hpp>

#include "camera.h"
#include "cube.h"

using namespace emscripten;
using json = nlohmann::json;

std::vector<glm::mat4> cube_trans;

void parse_input(std::string input) {
  auto obj = json::parse(input.begin(), input.end());
  auto cubes = obj["cubes"];

  for (json::iterator it = cubes.begin(); it != cubes.end(); ++it) {
    auto cube = *it;

    glm::vec3 vec = glm::vec3(cube["x"], cube["y"], cube["z"]);

    glm::mat4 mat(1.0f);
    mat = glm::translate(mat, vec);

    cube_trans.push_back(mat);
  }
}

EMSCRIPTEN_BINDINGS(module) { function("parse_input", &parse_input); }

bgfx::ShaderHandle loadShader(const char *FILENAME) {
  const char *filePath = FILENAME;
  FILE *file = fopen(filePath, "rb");

  printf("Attempting to load file %p at %s\n", file, filePath);

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  printf("It has filesize %ld\n", fileSize);

  const bgfx::Memory *mem = bgfx::alloc(fileSize + 1);
  fread(mem->data, 1, fileSize, file);

  mem->data[mem->size - 1] = '\0';
  fclose(file);

  return bgfx::createShader(mem);
}
bgfx::ProgramHandle program;

bgfx::VertexBufferHandle vbh;
bgfx::VertexBufferHandle vbh_2;
bgfx::VertexBufferHandle vbh_3;

PosColorVertex *cube2, *cube3;

bgfx::IndexBufferHandle ibh;

glm::mat4 proj;
glm::mat4 view;

float t = 0.0f;

void main_loop(void *data) {
  t = t + 0.01f;

  camera_update(camera);

  const glm::mat4 proj_matrix =
      glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 100.0f);
  const glm::mat view_matrix =
      glm::lookAt(camera.pos, camera.pos + camera.look, camera.up);

  bgfx::setViewTransform(0, glm::value_ptr(view_matrix),
                         glm::value_ptr(proj_matrix));
  // bgfx::setViewTransform(0, glm::value_ptr(view), glm::value_ptr(proj));
  glm::mat4 pos = glm::mat4(1.0f);
  // pos = glm::rotate(pos, 5.1f * t, glm::vec3(0.0f, 1.0f, 0.0f));

  bgfx::touch(0);
  bgfx::setState(BGFX_STATE_DEFAULT);
  /*
    bgfx::setTransform(glm::value_ptr(pos));
    bgfx::setVertexBuffer(0, vbh);
    bgfx::setIndexBuffer(ibh);
    bgfx::submit(0, program);

    pos = glm::translate(pos, glm::vec3(3.0f, 0.0f, 0.0f));

    bgfx::setTransform(glm::value_ptr(pos));
    bgfx::setVertexBuffer(0, vbh_2);
    bgfx::setIndexBuffer(ibh);
    bgfx::submit(0, program);

    pos = glm::mat4(1.0f);

    pos = glm::translate(pos, glm::vec3(-3.0f, 0.0f, 0.0f));
    pos = glm::rotate(pos, t, {0.0f, 1.0f, 0.0f});

    bgfx::setTransform(glm::value_ptr(pos));
    bgfx::setVertexBuffer(0, vbh_3);
    bgfx::setIndexBuffer(ibh);
    bgfx::submit(0, program);
  */

  for (const auto &cube : cube_trans) {
    bgfx::setTransform(glm::value_ptr(cube));
    bgfx::setVertexBuffer(0, vbh);
    bgfx::setIndexBuffer(ibh);
    bgfx::submit(0, program);
  }

  bgfx::frame();
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window; // Declare a pointer to an SDL_Window

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
      "bgfx and SDL2 on XCode Testing",    //    window title
      SDL_WINDOWPOS_UNDEFINED,             //    initial x position
      SDL_WINDOWPOS_UNDEFINED,             //    initial y position
      640,                                 //    width, in pixels
      480,                                 //    height, in pixels
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL //    flags - see below
  );

  // Check that th window was successfully made
  if (window == NULL) {
    // In the event that the window could not be made...

    return 1;
  }
  bgfx::PlatformData pd;

  printf("Test123\n");
  pd.ndt = NULL;
  pd.nwh = (void *)"#canvas";
  pd.context = NULL;
  pd.backBuffer = NULL;
  pd.backBufferDS = NULL;

  bgfx::renderFrame();

  bgfx::Init bgfxInit;
  bgfxInit.type = bgfx::RendererType::Count;
  bgfxInit.resolution.width = 640;
  bgfxInit.resolution.height = 480;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  bgfxInit.platformData = pd;
  bool v = bgfx::init(bgfxInit);

  printf("Init Status: %d\n", v);

  camera_init(camera);

  bgfx::reset(640, 480, BGFX_RESET_VSYNC);

  // Enable debug text.
  bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

  // Set view 0 clear state.
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303090ff, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, 640, 480);

  // FILE *f = fopen("shaders/v_simple.bin", "rb");

  // printf("Foobar %p\n", f);

  bgfx::ShaderHandle vsh = loadShader("shaders/v_simple.bin");
  bgfx::ShaderHandle fsh = loadShader("shaders/f_simple.bin");
  program = bgfx::createProgram(vsh, fsh, true);

  bgfx::VertexLayout pcvDecl;
  pcvDecl.begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  cube2 = new PosColorVertex[24];
  cube3 = new PosColorVertex[24];

  memcpy(cube2, cube_vertices, 24 * sizeof(PosColorVertex));
  memcpy(cube3, cube_vertices, 24 * sizeof(PosColorVertex));

  set_color(cube2, 24, 0x309030ff);

  vbh = bgfx::createVertexBuffer(
      bgfx::makeRef(cube_vertices, sizeof(cube_vertices)), pcvDecl);

  vbh_2 = bgfx::createVertexBuffer(bgfx::makeRef(cube2, sizeof(cube_vertices)),
                                   pcvDecl);

  vbh_3 = bgfx::createVertexBuffer(bgfx::makeRef(cube3, sizeof(cube_vertices)),
                                   pcvDecl);

  ibh = bgfx::createIndexBuffer(
      bgfx::makeRef(cube_indices, sizeof(cube_indices)));

  emscripten_set_main_loop_arg(main_loop, 0, -1, 1);
  bgfx::shutdown();

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();
  return 0;
}
