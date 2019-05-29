#include "softphys/engine/gl_vertex_array.h"

namespace softphys
{
GlVertexArray::GlVertexArray()
{
  glGenVertexArrays(1, &id_);
}

GlVertexArray::~GlVertexArray()
{
  glDeleteVertexArrays(1, &id_);
}

void GlVertexArray::Bind()
{
  glBindVertexArray(id_);
}

void GlVertexArray::Unbind()
{
  glBindVertexArray(0);
}
}
