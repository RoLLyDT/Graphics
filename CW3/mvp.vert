#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aTex;
layout(location = 2) in vec3 aNor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex;
out vec3 col;
out vec3 nor;
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    tex = aTex.xy;
    FragPos = vec3(model * vec4(aPos, 1.0f));
    col = vec3(0.0);  // Assuming you have a default color, modify as needed
    nor = mat3(transpose(inverse(model))) * aNor;
}
