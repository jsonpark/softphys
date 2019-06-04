#include "softphys/model/visual/visual.h"

namespace softphys
{
namespace model
{
Visual::Visual(const std::string& material_name)
  : material_name_(material_name)
{
}

Visual::~Visual() = default;
}
}
