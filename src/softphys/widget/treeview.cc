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

  indent_ = 0;

  for (auto entry : entries_)
  {
    DrawEntries(entry);
  }
}

void Treeview::DrawEntries(std::shared_ptr<Entry> entry)
{
  if (entry->HasChildren())
  {
    if (entry->IsCollapsed())
    {
    }
    else
    {
      for (auto child_entry : entry->Children())
      {
      }
    }
  }
  else
  {
    if (entry->HasValue())
    {
    }
  }
}

void Treeview::AddEntry(std::shared_ptr<Entry> entry)
{
  entries_.push_back(entry);
}
}
}
