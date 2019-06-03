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
  samplerCube diffuse_texture;
  vec3 specular;
  float shininess;
};

in vec3 frag_position;
in vec3 frag_normal;
in vec3 frag_tex_coord;

uniform vec3 eye;
uniform Light lights[NUM_LIGHTS];
uniform Material material;
uniform vec2 max_distance;

out vec4 out_color;

vec3 DirectionalLight(Light light, vec3 view_dir, vec3 normal)
{
  vec3 light_dir = light.position;
  float diff = max(dot(normal, light_dir), 0.f);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.f), material.shininess);

  vec3 ambient = light.ambient * material.ambient;
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture, frag_tex_coord));
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
  
  float alpha = 1.f;
  vec3 d = eye - vec3(frag_position);
  float squared_length = dot(d, d);
  if (squared_length > max_distance[1] * max_distance[1])
    alpha = 0.f;
  else if (squared_length > max_distance[0] * max_distance[0])
    alpha = 1.f - (squared_length - max_distance[0] * max_distance[0]) / (max_distance[1] * max_distance[1] - max_distance[0] * max_distance[0]);

  out_color = vec4(total_color, alpha);
}
