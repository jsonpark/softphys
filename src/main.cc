#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"
#include "softphys/physics/physics.h"
#include "softphys/physics/object/rigid_body.h"
#include "softphys/physics/object/simulation_ground.h"
#include "softphys/physics/object/primitive_sphere.h"
#include "softphys/object/sphere.h"
#include "softphys/viewer/light.h"

#include <iostream>

int main()
{
  auto physics = std::make_unique<softphys::Physics>();
  physics->SetEarthGravity();

  Eigen::Affine3d t1 = Eigen::Affine3d::Identity();
  Eigen::Affine3d t2 = Eigen::Affine3d::Identity();
  //t1.translate(Eigen::Vector3d(0., -0.1, 0.));
  //t2.translate(Eigen::Vector3d(0., 0.1, 0.));
  t1.translate(Eigen::Vector3d(0., 0, -0.1));
  t2.translate(Eigen::Vector3d(0., 0, 0.1));

  auto rb = physics->CreateObject<softphys::RigidBody>();
  auto sphere1 = rb->CreatePrimitive<softphys::PrimitiveSphere>(t1, 1., 0.1);
  auto sphere2 = rb->CreatePrimitive<softphys::PrimitiveSphere>(t2, 1., 0.1);
  rb->SetPosition(Eigen::Vector3d(0., 0., 1.));
  
  auto ground = physics->CreateObject<softphys::SimulationGround>(Eigen::Vector3d(0., 0., 1.), Eigen::Vector3d(0., 0., 0.));

  softphys::Engine engine;
  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 1024, 768);
  viewer->DisplayPhysicsScene(std::move(physics));

  // Light
  softphys::Light light0;
  light0.type = softphys::Light::Type::Directional;
  light0.position = Eigen::Vector3f(-1.f, -1.0f, 1.f).normalized();
  light0.ambient = Eigen::Vector3f(0.25f, 0.25f, 0.25f);
  light0.diffuse = Eigen::Vector3f(0.5f, 0.5f, 0.5f);
  light0.specular = Eigen::Vector3f(0.1f, 0.1f, 0.1f);

  softphys::Light light1;
  light1.type = softphys::Light::Type::Directional;
  light1.position = Eigen::Vector3f(-1.f, 1.f, 1.f).normalized();
  light1.ambient = Eigen::Vector3f(0.25f, 0.25f, 0.25f);
  light1.diffuse = Eigen::Vector3f(0.5f, 0.5f, 0.5f);
  light1.specular = Eigen::Vector3f(0.1f, 0.1f, 0.1f);

  softphys::Light light2;
  light2.type = softphys::Light::Type::Directional;
  light2.position = Eigen::Vector3f(1.f, -1.0f, 1.f).normalized();
  light2.ambient = Eigen::Vector3f(0.25f, 0.25f, 0.25f);
  light2.diffuse = Eigen::Vector3f(0.5f, 0.5f, 0.5f);
  light2.specular = Eigen::Vector3f(0.1f, 0.1f, 0.1f);

  softphys::Light light3;
  light3.type = softphys::Light::Type::Directional;
  light3.position = Eigen::Vector3f(1.f, 1.f, 1.f).normalized();
  light3.ambient = Eigen::Vector3f(0.25f, 0.25f, 0.25f);
  light3.diffuse = Eigen::Vector3f(0.5f, 0.5f, 0.5f);
  light3.specular = Eigen::Vector3f(0.1f, 0.1f, 0.1f);

  auto scene = viewer->GetScene();
  scene->AddLight(light0);
  scene->AddLight(light1);
  scene->AddLight(light2);
  scene->AddLight(light3);

  viewer->LoadScene("..\\data\\scene.json");

  engine.Run();

  return 0;
}
