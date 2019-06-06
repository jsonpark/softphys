#ifndef SOFTPHYS_PHYSICS_PHYSICS_H_
#define SOFTPHYS_PHYSICS_PHYSICS_H_

#include <memory>
#include <vector>

#include "softphys/physics/object/ground.h"
#include "softphys/physics/object/rigid_body.h"

namespace softphys
{
namespace physics
{
class Physics
{
public:
  Physics();
  ~Physics();

  template<typename ObjectType, typename... Ts>
  std::shared_ptr<ObjectType> CreateObject(Ts&& ... args)
  {
    should_update_solver_ = true;

    auto object = std::make_shared<ObjectType>(std::forward<Ts>(args)...);

    objects_.push_back(object);

    return object;
  }

  void SetTimestep(double timestep) noexcept
  {
    timestep_ = timestep;
  }

  auto GetTime() const noexcept
  {
    return time_;
  }

  void SetGravity(double g);
  void SetGravity(const Eigen::Vector3d& g);
  void SetEarthGravity();

  void Simulate(double time);

  const auto& GetObjects() const
  {
    return objects_;
  }

private:
  void SimulateInternal(double time);

  double time_ = 0.;

  double timestep_ = 0.;

  Eigen::Vector3d gravity_{ 0., 0., 0. };

  std::vector<std::shared_ptr<Object>> objects_;

  // Constraint solver
  void FindContacts(int i, int j, double time);
  void FindContactsGroundRigidBody(int i, int j, double time);
  void FindContactsRigidBodies(int i, int j, double time);

  void UpdateSolver();

  bool should_update_solver_ = false;

  int num_variables_ = 0;
  std::vector<int> object_to_solver_index_;
  MatrixXd mass_inverse_;
  VectorXd external_force_;
  MatrixXd constraints_transpose_;
  VectorXd constraints_bias_;
};
}
}

#endif // SOFTPHYS_PHYSICS_PHYSICS_H_
