#include "softphys/engine.h"
#include "softphys/viewer/viewer.h"
#include "softphys/physics/physics.h"
#include "softphys/physics/object/rigid_body.h"
#include "softphys/physics/object/ground.h"
#include "softphys/shape/sphere.h"

#include <memory>

int main()
{
  auto physics = std::make_unique<softphys::Physics>();
  physics->SetEarthGravity();

  // Sphere
  auto sphere_shape = std::make_shared<softphys::Sphere>(0.1);
  auto sphere = physics->CreateObject<softphys::RigidBody>(0.1, sphere_shape);
  sphere->SetCom(Eigen::Vector3d(0., 0., 1.));
  sphere->ApplyImpulse(Eigen::Vector3d(1., 0., 1.));

  // Ground
  auto ground = physics->CreateObject<softphys::Ground>(Eigen::Vector3d(0., 0., 1.), Eigen::Vector3d(0., 0., 0.));

  softphys::Engine engine;
  auto viewer = engine.CreateEngineWindow<softphys::Viewer>(200, 200, 1024, 768);
  viewer->DisplayPhysicsScene(std::move(physics));
  engine.Run();

  return 0;
}
