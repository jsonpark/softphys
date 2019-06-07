#include "softphys/widget/treeview.h"

#include "softphys/viewer/painter.h"

namespace softphys
{
namespace widget
{
Treeview::Treeview(Painter* painter)
  : Widget(painter)
{
}

Treeview::~Treeview() = default;

void Treeview::Draw()
{
  const auto painter = GetPainter();
  const auto& position = Position();
  painter->DrawRect(position(0), position(1), Width(), Height(), Vector4f(1.f, 1.f, 1.f, 1.f));
}
}
}
