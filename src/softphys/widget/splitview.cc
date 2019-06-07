#include "softphys/widget/splitview.h"

namespace softphys
{
namespace widget
{
Splitview::Splitview(Split split, std::shared_ptr<Widget> widget1, std::shared_ptr<Widget> widget2, double portion)
  : Widget(),
  split_(split), portion_(portion)
{
}
}
}
