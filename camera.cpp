#include "camera.h"

#include <SDL2/SDL.h>

#include "glm/geometric.hpp"

Camera camera;

void camera_init(Camera &cam) {
    cam.pos = glm::vec3(0.0f, 0.0f, 3.0f);
    cam.yaw = -90.0f;
    cam.pitch = 0.0f;
    cam.roll = 0.0f;
}

void camera_update(Camera &cam) {
    const uint8_t *keystate = SDL_GetKeyboardState(NULL);

    const float rot_speed = 0.83f;
    const float mov_speed = 0.10f;

    if (keystate[SDL_SCANCODE_LEFT]) cam.yaw -= rot_speed;
    if (keystate[SDL_SCANCODE_RIGHT]) cam.yaw += rot_speed;
    if (keystate[SDL_SCANCODE_UP]) cam.pitch += rot_speed;
    if (keystate[SDL_SCANCODE_DOWN]) cam.pitch -= rot_speed;

    glm::vec3 direction;
    direction.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    direction.y = sin(glm::radians(cam.pitch));
    direction.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    direction = glm::normalize(direction);

    cam.look = direction;

    const glm::vec3 right =
        glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));

    cam.up = glm::normalize(glm::cross(right, direction));

    if (keystate[SDL_SCANCODE_W]) cam.pos += direction * mov_speed;
    if (keystate[SDL_SCANCODE_S]) cam.pos -= direction * mov_speed;
    if (keystate[SDL_SCANCODE_A]) cam.pos -= right * mov_speed;
    if (keystate[SDL_SCANCODE_D]) cam.pos += right * mov_speed;
}
