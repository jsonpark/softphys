#ifndef SOFTPHYS_WIDGET_TREEVIEW_ENTRY_H_
#define SOFTPHYS_WIDGET_TREEVIEW_ENTRY_H_

#include <memory>
#include <vector>
#include <string>

namespace softphys
{
namespace widget
{
class Entry
{
public:
  Entry() = delete;
  explicit Entry(const std::string& name);
  virtual ~Entry();

  virtual bool HasValue() const noexcept
  {
    return false;
  }

  bool IsCollapsed() const noexcept
  {
    return is_collapsed_;
  }

  bool HasChildren() const
  {
    return !children_.empty();
  }

  const auto& Name() const noexcept
  {
    return name_;
  }

  const auto& Children() const noexcept
  {
    return children_;
  }

private:
  std::string name_;

  std::weak_ptr<Entry> parent_;
  std::vector<std::shared_ptr<Entry>> children_;

  bool is_collapsed_ = false;
};
}
}

#endif // SOFTPHYS_WIDGET_TREEVIEW_ENTRY_H_