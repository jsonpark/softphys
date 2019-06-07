#ifndef SOFTPHYS_WIDGET_TREEVIEW_H_
#define SOFTPHYS_WIDGET_TREEVIEW_H_

#include "softphys/widget/widget.h"

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

private:
};
}
}

#endif // SOFTPHYS_WIDGET_TREEVIEW_H_