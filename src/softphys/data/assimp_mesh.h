#ifndef SOFTPHYS_DATA_ASSIMP_MESH_H_
#define SOFTPHYS_DATA_ASSIMP_MESH_H_

#include <string>

#include <assimp/scene.h>

namespace softphys
{
class AssimpMesh
{
public:
  AssimpMesh() = delete;
  AssimpMesh(const std::string& filename);
  ~AssimpMesh();

private:
  const aiScene* scene_ = nullptr;
};
}

#endif // SOFTPHYS_DATA_ASSIMP_MESH_H_
