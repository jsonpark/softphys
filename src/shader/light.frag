#version 330 core

const int NUM_LIGHTS = 8;

struct Light
{
  int type;
  int use;
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 attenuation;
};

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

in vec3 frag_position;
in vec3 frag_normal;

uniform vec3 eye;
uniform Light lights[NUM_LIGHTS];
uniform Material material;
uniform vec2 max_distance;
uniform float alpha;

out vec4 out_color;

vec3 DirectionalLight(Light light, vec3 view_dir, vec3 normal)
{
  vec3 light_dir = light.position;
  float diff = max(dot(normal, light_dir), 0.f);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.f), material.shininess);

  vec3 ambient = light.ambient * material.ambient;
  vec3 diffuse = light.diffuse * diff * material.diffuse;
  vec3 specular = light.specular * spec * material.specular;
  return ambient + diffuse + specular;
}

void main()
{
  vec3 normal = normalize(frag_normal);
  vec3 view_dir = normalize(eye - frag_position);
  vec3 total_color = vec3(0.f, 0.f, 0.f);

  for (int i = 0; i < NUM_LIGHTS; i++)
  {
    if (lights[i].use == 1)
    {
      if (lights[i].type == 0)
        total_color += DirectionalLight(lights[i], view_dir, normal);
    }
  }
  
  float frag_alpha = alpha;
  vec3 d = eye - vec3(frag_position);
  float squared_length = dot(d, d);
  if (squared_length > max_distance[1] * max_distance[1])
    discard;
  else if (squared_length > max_distance[0] * max_distance[0])
    frag_alpha = (1.f - (squared_length - max_distance[0] * max_distance[0]) / (max_distance[1] * max_distance[1] - max_distance[0] * max_distance[0])) * alpha;

  out_color = vec4(total_color, frag_alpha);
}
