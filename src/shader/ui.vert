#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec4 monitor; // (x, y, width, height)

void main()
{
  float x = (aPos[0] - monitor[0]) / monitor[2] * 2.f - 1.f;
  //float y = -(aPos[1] - monitor[1]) / monitor[3] * 2.f + 1.f;
  float y = (aPos[1] - monitor[1]) / monitor[3] * 2.f - 1.f;
  gl_Position = vec4(x, y, 0.f, 1.0f);
}
