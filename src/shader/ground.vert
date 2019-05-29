#version 420 core
layout (location = 0) in vec2 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 tex_coord;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 0.f, 1.f);
  tex_coord = aPos;
}
