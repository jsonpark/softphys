#ifndef SOFTPHYS_SCENE_SCENE_PRIMITIVE_H_
#define SOFTPHYS_SCENE_SCENE_PRIMITIVE_H_

namespace softphys
{
namespace scene
{
class Primitive
{
public:
  Primitive() = delete;
  Primitive(double density, int material);
  virtual ~Primitive();

  virtual bool IsSphere() const noexcept
  {
    return false;
  }

  virtual bool IsPlane() const noexcept
  {
    return false;
  }

  auto Density() const
  {
    return density_;
  }

  auto Material() const
  {
    return material_;
  }

private:
  double density_;
  int material_;
};
}
}

#endif // SOFTPHYS_SCENE_SCENE_PRIMITIVE_H_
