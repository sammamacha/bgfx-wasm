$input v_color0, v_normal, v_pos

#include <bgfx_shader.sh>

void main() {
    //gl_FragColor = v_color0;

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(vec3(1.2f, 2.2f, 2.0f) - v_pos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    vec3 result = v_color0.xyz * (diffuse + vec3(0.4, 0.4, 0.4));
    gl_FragColor = vec4(result, 1.0);
    // gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
