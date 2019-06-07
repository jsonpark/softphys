#ifndef SOFTPHYS_WIDGET_SPLITVIEW_H_
#define SOFTPHYS_WIDGET_SPLITVIEW_H_

#include "softphys/widget/widget.h"

#include <memory>

namespace softphys
{
namespace widget
{
class Splitview : public Widget
{
public:
  enum class Split
  {
    Horizontal,
    Vertical
  };

public:
  Splitview() = delete;
  Splitview(Split split, std::shared_ptr<Widget> widget1, std::shared_ptr<Widget> widget2, double portion = 0.5);

private:
  Split split_;
  double portion_;
  std::shared_ptr<Widget> widget1_;
  std::shared_ptr<Widget> widget2_;
};
}
}

#endif // SOFTPHYS_WIDGET_SPLITVIEW_H_
