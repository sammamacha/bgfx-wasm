$input a_position, a_normal, a_color0
$output v_color0, v_normal, v_pos 

#include <bgfx_shader.sh>

void main() {
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
    v_color0 = a_color0;
    v_normal = a_normal;
    
    v_pos = mul(u_model[0], vec4(a_position, 1.0)).xyz;
}
