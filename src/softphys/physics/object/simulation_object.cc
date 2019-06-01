#include "softphys/physics/object/simulation_object.h"

namespace softphys
{
SimulationObject::SimulationObject(std::shared_ptr<scene::Object> scene_object)
  : scene_object_(scene_object)
{
}

SimulationObject::~SimulationObject() = default;

void SimulationObject::ApplyImpulse(const Eigen::Vector3d& j)
{
}

void SimulationObject::ApplyForce(const Eigen::Vector3d& f)
{
}

void SimulationObject::ApplyGravity(const Eigen::Vector3d& g)
{
}

void SimulationObject::Simulate(double time)
{
}
}
