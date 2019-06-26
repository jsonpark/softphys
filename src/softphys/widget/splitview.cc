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

  UpdateChildrenWidgetSize();

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
  else if (mouse_dragging_widget_ == 2)
  {
    double new_partition;
    switch (split_)
    {
    case Split::Horizontal:
      new_partition = y / Height();
      break;

    case Split::Vertical:
      new_partition = x / Width();
      break;
    }

    constexpr double clip = 0.01;
    if (new_partition < clip)
      new_partition = clip;
    if (new_partition > 1. - clip)
      new_partition = 1. - clip;

    SetPartition(new_partition);
  }
  else
  {
    const auto& w1p = widget1_->Position();
    const auto& w1s = widget1_->Size();
    const auto& w2p = widget2_->Position();
    const auto& w2s = widget2_->Size();

    if (w1p(0) <= x && x <= w1p(0) + w1s(0) &&
      w1p(1) <= y && y <= w1p(1) + w1s(1))
    {
      mouse_dragging_widget_ = 0;
      widget1_->MouseMove(x, y);
    }

    else if (w2p(0) <= x && x <= w2p(0) + w2s(0) &&
      w2p(1) <= y && y <= w2p(1) + w2s(1))
    {
      auto wx = x;
      auto wy = y;

      switch (split_)
      {
      case Split::Horizontal:
        wy -= widget1_->Height();
        break;

      case Split::Vertical:
        wx -= widget1_->Width();
        break;
      }

      mouse_dragging_widget_ = 1;
      widget2_->MouseMove(wx, wy);
    }
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
      if (mouse.IsPressed(Mouse::Button::LeftButton) + mouse.IsPressed(Mouse::Button::RightButton) + mouse.IsPressed(Mouse::Button::MiddleButton) == 1)
        mouse_dragging_widget_ = -1;
    }
  }

  else
  {
    mouse_dragging_widget_ = -1;
    switch (split_)
    {
    case Split::Horizontal:
      if (widget1_->Height() <= y && y <= widget2_->Y())
        mouse_dragging_widget_ = 2;
      break;

    case Split::Vertical:
      if (widget1_->Width() <= x && x <= widget2_->X())
        mouse_dragging_widget_ = 2;
      break;
    }

    if (mouse_dragging_widget_ == -1)
    {
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
    widget1_->Resize(Width(), Height() * partition_ - border_halfsize_);
    widget2_->Move(0., Height() * partition_ + border_halfsize_);
    widget2_->Resize(Width(), Height() * (1. - partition_) - border_halfsize_);
    break;

  case Split::Vertical:
    widget1_->Move(0., 0.);
    widget1_->Resize(Width() * partition_ - border_halfsize_, Height());
    widget2_->Move(Width() * partition_ + border_halfsize_, 0.);
    widget2_->Resize(Width() * (1. - partition_) - border_halfsize_, Height());
    break;
  }
}

void Splitview::Draw()
{
  widget1_->SetScreenPosition(ScreenPosition() + widget1_->Position());
  widget1_->Draw();

  widget2_->SetScreenPosition(ScreenPosition() + widget2_->Position());
  widget2_->Draw();

  const auto painter = GetPainter();
  const Vector4f color(0.35f, 0.42f, 0.6f, 1.f);
  switch (split_)
  {
  case Split::Horizontal:
    painter->DrawRect(0.f, widget1_->Height(), Width(), widget1_->Height() + border_halfsize_ * 2, color);
    break;

  case Split::Vertical:
    painter->DrawRect(widget1_->Width(), 0.f, widget1_->Width() + border_halfsize_ * 2, Height(), color);
    break;
  }
}
}
}
