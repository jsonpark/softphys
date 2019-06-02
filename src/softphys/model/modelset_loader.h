#ifndef SOFTPHYS_MODEL_MODEL_LOADER_H_
#define SOFTPHYS_MODEL_MODEL_LOADER_H_

#include <memory>
#include <string>

#include "softphys/model/modelset.h"

namespace softphys
{
namespace model
{
class ModelsetLoader
{
public:
  ModelsetLoader();
  ~ModelsetLoader();

  std::shared_ptr<Modelset> LoadFromJson(const std::string& filename);

private:
};
}
}

#endif // SOFTPHYS_MODEL_MODEL_LOADER_H_
