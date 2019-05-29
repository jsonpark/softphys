#version 420 core

in vec2 viewport_coord;

uniform mat4 camera;
uniform vec4 monitor; // (1 / tan(fovy/2), 1 / tan(fovy/2) / aspect, near, far)
uniform mat4 plane;

uniform sampler2D texture_image;

out vec4 out_color;
out float gl_FragDepth;

const float threshold = 0.01;

void main()
{
  gl_FragDepth = 1.f;
  vec4 dir = camera * vec4(monitor.xy * viewport_coord, -1.f, 0.f);

  vec3 plane_normal = vec3(plane[2]);
  vec4 plane_equation = vec4(plane_normal, -dot(plane_normal, vec3(plane[3])));

  float dp = dot(dir, plane_equation);
  if (abs(dp) < threshold) discard;

  float ep = dot(camera[3], plane_equation);
  float t = - ep / dp;
  float l = length(dir.xyz);
  if (t * l < monitor[2] || t * l > monitor[3]) discard;

  vec4 x = camera[3] + t * dir;

  // Depth
  float z = - dot(camera[2], t * dir);
  float d = (z - monitor[2]) / (monitor[3] - monitor[2]);
  gl_FragDepth = 0.f;

  // Texture
  vec2 tex_coord = vec2(dot(plane[0], x - plane[3]), dot(plane[1], x - plane[3]));
  out_color = vec4(texture(texture_image, tex_coord).rgb, 1.f);
}
