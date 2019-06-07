#include "softphys/widget/splitview.h"

#include "softphys/viewer/painter.h"

namespace softphys
{
namespace widget
{
Splitview::Splitview(Painter* painter, Split split, std::shared_ptr<Widget> widget1, std::shared_ptr<Widget> widget2, double partition)
  : Widget(painter),
  split_(split), partition_(partition), widget1_(widget1), widget2_(widget2)
{
}

void Splitview::Keyboard(int key, int action, int mods)
{
}

void Splitview::MouseMove(double x, double y)
{
  const auto& mouse = GetPainter()->GetMouse();

  if (mouse_dragging_widget_ == 0)
  {
    widget1_->MouseMove(x, y);
  }
  else if (mouse_dragging_widget_ == 1)
  {
    auto wx = x;
    auto wy = y;

    switch (split_)
    {
    case Split::Horizontal:
      wx -= widget1_->Height();
      break;

    case Split::Vertical:
      wy -= widget1_->Width();
      break;
    }

    widget2_->MouseMove(wx, wy);
  }
}

void Splitview::MouseButton(double x, double y, Mouse::Button button, Mouse::Status action, int mods)
{
  const auto& mouse = GetPainter()->GetMouse();

  UpdateChildrenWidgetSize();

  if (mouse.IsDragging())
  {
    if (mouse_dragging_widget_ == 0)
    {
      widget1_->MouseButton(x, y, button, action, mods);
    }
    else if (mouse_dragging_widget_ == 1)
    {
      auto wx = x;
      auto wy = y;

      switch (split_)
      {
      case Split::Horizontal:
        wx -= widget1_->Height();
        break;

      case Split::Vertical:
        wy -= widget1_->Width();
        break;
      }

      widget2_->MouseButton(wx, wy, button, action, mods);
    }

    if (action == Mouse::Status::Released)
    {
      if (mouse.IsPressed<Mouse::Button::LeftButton>() + mouse.IsPressed<Mouse::Button::RightButton>() + mouse.IsPressed<Mouse::Button::MiddleButton>() == 1)
        mouse_dragging_widget_ = -1;
    }
  }

  else
  {
    auto x = mouse.X();
    auto y = mouse.Y();

    const auto& w1p = widget1_->Position();
    const auto& w1s = widget1_->Size();
    const auto& w2p = widget2_->Position();
    const auto& w2s = widget2_->Size();

    if (w1p(0) <= x && x <= w1p(0) + w1s(0) &&
      w1p(1) <= y && y <= w1p(1) + w1s(1))
    {
      mouse_dragging_widget_ = 0;
      widget1_->MouseButton(x, y, button, action, mods);
    }
    
    else if (w2p(0) <= x && x <= w2p(0) + w2s(0) &&
      w2p(1) <= y && y <= w2p(1) + w2s(1))
    {
      auto wx = x;
      auto wy = y;

      switch (split_)
      {
      case Split::Horizontal:
        wx -= widget1_->Height();
        break;

      case Split::Vertical:
        wy -= widget1_->Width();
        break;
      }

      mouse_dragging_widget_ = 1;
      widget2_->MouseButton(wx, wy, button, action, mods);
    }
  }

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
