#ifndef SOFTPHYS_WIDGET_TREEVIEW_H_
#define SOFTPHYS_WIDGET_TREEVIEW_H_

#include "softphys/widget/widget.h"

#include "softphys/widget/treeview/entry.h"

namespace softphys
{
namespace widget
{
class Treeview : public Widget
{
public:
  Treeview() = delete;
  Treeview(Painter* painter);
  ~Treeview();

  void Draw() override;

  void AddEntry(std::shared_ptr<Entry> entry);

private:
  std::vector<std::shared_ptr<Entry>> entries_;
  double scroll_ = 0.;

  // Drawing
  void DrawEntries(std::shared_ptr<Entry> entry);
  int indent_ = 0;
};
}
}

#endif // SOFTPHYS_WIDGET_TREEVIEW_H_
