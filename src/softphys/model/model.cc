#include "softphys/model/model.h"

namespace softphys
{
namespace model
{
Model::Model(const std::string& name)
  : name_(name)
{
}

Model::~Model() = default;
}
}
