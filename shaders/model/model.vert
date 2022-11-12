#version 460

layout(location = 0) in vec3 position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main()
{
    vec3 worldPos = vec3(model_matrix * vec4(position, 1.0));

    gl_Position = proj_matrix * view_matrix * vec4(worldPos, 1.0);
}