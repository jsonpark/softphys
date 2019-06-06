#version 420 core

in vec2 tex_coord;
in vec4 frag_coord;

uniform sampler2D texture_image;
uniform vec3 eye;
uniform vec2 max_distance;

out vec4 out_color;

void main()
{
  float alpha = 1.f;

  vec3 d = eye - vec3(frag_coord);
  float squared_length = dot(d, d);
  if (squared_length > max_distance[1] * max_distance[1])
    discard;
  else if (squared_length > max_distance[0] * max_distance[0])
    alpha = 1.f - (squared_length - max_distance[0] * max_distance[0]) / (max_distance[1] * max_distance[1] - max_distance[0] * max_distance[0]);

  out_color = vec4(texture(texture_image, tex_coord).rgb, alpha * 0.5f);
}
