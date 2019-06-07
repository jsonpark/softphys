#include "softphys/widget/splitview.h"

namespace softphys
{
namespace widget
{
Splitview::Splitview(Split split, std::shared_ptr<Widget> widget1, std::shared_ptr<Widget> widget2, double partition)
  : Widget(),
  split_(split), partition_(partition), widget1_(widget1), widget2_(widget2)
{
}

void Splitview::Resize(double width, double height)
{
  Widget::Resize(width, height);
  UpdateChildrenWidgetSize();
}

void Splitview::SetPartition(double partition)
{
  partition_ = partition;
  UpdateChildrenWidgetSize();
}

void Splitview::UpdateChildrenWidgetSize()
{
  switch (split_)
  {
  case Split::Horizontal:
    widget1_->Move(0., 0.);
    widget1_->Resize(Width(), Height() * partition_);
    widget2_->Move(0., Height() * partition_);
    widget2_->Resize(Width(), Height() * (1. - partition_));
    break;

  case Split::Vertical:
    widget1_->Move(0., 0.);
    widget1_->Resize(Width() * partition_, Height());
    widget2_->Move(Width() * partition_, 0.);
    widget2_->Resize(Width() * (1. - partition_), Height());
    break;
  }
}

void Splitview::Draw()
{
  widget1_->SetScreenPosition(ScreenPosition() + widget1_->Position());
  widget1_->Draw();

  widget2_->SetScreenPosition(ScreenPosition() + widget2_->Position());
  widget2_->Draw();
}
}
}
