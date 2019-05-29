#version 420 core

in vec2 tex_coord;

uniform sampler2D texture_image;

out vec4 out_color;

void main()
{
  out_color = vec4(texture(texture_image, tex_coord).rgb, 1.f);
}
