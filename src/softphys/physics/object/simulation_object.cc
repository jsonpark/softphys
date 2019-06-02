#include "softphys/physics/object/simulation_object.h"

namespace softphys
{
SimulationObject::SimulationObject(const std::string& model_name)
  : model_name_(model_name)
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

void SimulationObject::ApplyContactConstraint(const Eigen::Vector3d& n)
{
}

void SimulationObject::Simulate(double time)
{
}
}
