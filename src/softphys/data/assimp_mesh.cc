#include "softphys/data/assimp_mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace softphys
{
AssimpMesh::AssimpMesh(const std::string& filename)
{
  Assimp::Importer importer;
  scene_ = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
}

AssimpMesh::~AssimpMesh()
{
}
}
