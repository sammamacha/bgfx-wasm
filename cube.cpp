#include "cube.h"

// Note, it seems render order to counter-clockwise
// 0->1->3 : 0->3->1
// 0->3->2 : 0->2->3
const PosColorVertex cube_vertices[24] = {
    {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0xff0202c0},  // Front face
    {1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0xff0202c0},
    {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0xff0202c0},
    {1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0xff0202c0},

    {-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0xff0202c0},  // Left side
    {-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0xff0202c0},
    {-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0xff0202c0},
    {-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0xff0202c0},

    {1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0xff0202c0},  // Right side
    {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0xff0202c0},
    {1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0xff0202c0},
    {1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0xff0202c0},

    {-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0xff0202c0},  // Back face
    {1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0xff0202c0},
    {-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0xff0202c0},
    {1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0xff0202c0},

    {-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0xff0202c0},  // Top face
    {1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0xff0202c0},
    {-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0xff0202c0},
    {1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0xff0202c0},

    {-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0xff0202c0},  // Bottom face
    {1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0xff0202c0},
    {-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0xff0202c0},
    {1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0xff0202c0}

};

const uint16_t cube_indices[36] = {
    0,  3,  1,  0,  2,  3,  // Front Side

    4,  7,  5,  4,  6,  7,  // Left Side

    8,  9,  11, 8,  11, 10,  // Right Side

    12, 13, 15, 12, 15, 14,  // Back Side

    16, 19, 17, 16, 18, 19,  // Top Side

    20, 21, 23, 20, 23, 22  // Bottom Side

};

void set_color(PosColorVertex *vb, size_t size, uint32_t hex) {
    for (size_t i = 0; i < size; ++i) {
        vb[i].abgr = hex;
    }
}
