#version 330 core

in vec3 frag_color;
in vec2 tex_coord;

uniform sampler2D texture_image1;
uniform sampler2D texture_image2;

out vec4 out_color;

void main()
{
  out_color = mix(texture(texture_image1, tex_coord), texture(texture_image2, tex_coord), 0.2) * vec4(frag_color, 1.0);
}
