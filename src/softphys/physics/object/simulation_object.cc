#include "softphys/physics/object/simulation_object.h"

namespace softphys
{
SimulationObject::SimulationObject() = default;

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
