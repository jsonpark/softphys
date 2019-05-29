#version 420 core
layout (location = 0) in vec2 aPos;

out vec2 viewport_coord;

void main()
{
  gl_Position = vec4(aPos, 1.f, 1.f);
  viewport_coord = aPos;
}
