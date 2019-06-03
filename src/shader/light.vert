#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model_inv_transpose;

out vec3 frag_position;
out vec3 frag_normal;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
  frag_position = vec3(model * vec4(aPos, 1.f));
  frag_normal = vec3(model_inv_transpose * vec4(aNormal, 0.f));
}
