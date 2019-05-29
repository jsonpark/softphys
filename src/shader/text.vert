#version 330 core
layout (location = 0) in vec4 aPos;

uniform mat4 projection;

out vec2 frag_tex_coord;

void main()
{
  gl_Position = projection * vec4(aPos.xy, 0.f, 1.0f);
  frag_tex_coord = aPos.zw;
}
