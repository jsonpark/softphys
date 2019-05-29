#version 330 core

in vec2 frag_tex_coord;

const float threshold = 0.1f;
uniform sampler2D glyph;
uniform vec3 text_color;

out vec4 out_color;

void main()
{
  float a = texture(glyph, frag_tex_coord).r;
  out_color = vec4(text_color, a);
}
