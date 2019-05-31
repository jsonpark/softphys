#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"
#include "softphys/physics/physics.h"
#include "softphys/physics/object/rigid_body.h"
#include "softphys/physics/object/ground.h"
#include "softphys/physics/object/primitive_sphere.h"
#include "softphys/shape/sphere.h"

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
  
  auto ground = physics->CreateObject<softphys::Ground>(Eigen::Vector3d(0., 0., 1.), Eigen::Vector3d(0., 0., 0.));

  softphys::Engine engine;
  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 1024, 768);
  viewer->DisplayPhysicsScene(std::move(physics));
  engine.Run();

  return 0;
}
