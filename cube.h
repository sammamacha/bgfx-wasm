#pragma once
#include <bgfx/bgfx.h>

struct PosColorVertex {
    float x;
    float y;
    float z;
    float n_x;
    float n_y;
    float n_z;
    uint32_t abgr;
};

extern const PosColorVertex cube_vertices[24];
extern const uint16_t cube_indices[36];

void set_color(PosColorVertex *vb, size_t size, uint32_t hex);
