#pragma once
#include <base/matrix.h>

namespace ge {
namespace impl {

template <typename T>
BasicMatrix<T> RotateImpl(T angle, uint32_t x, uint32_t y)
{
  const T sina = sin(angle);
  const T cosa = cos(angle);
  BasicMatrix<T> result = BasicIdentity<T>();
  result(x, x) = +cosa;
  result(x, y) = -sina;
  result(y, x) = +sina;
  result(y, y) = +cosa;
  return result;
}

}  // namespace impl

template <typename T>
struct BasicTransformation {
  static BasicMatrix<T> Translate(T dx, T dy, T dz)
  {
    BasicMatrix<T> result = BasicIdentity<T>();
    result(3, 0) = dx;
    result(3, 1) = dy;
    result(3, 2) = dz;
    return result;
  }

  static BasicMatrix<T> Scale(T f)
  {
    BasicMatrix<T> result = BasicZeroes<T>();
    result(0, 0) = f;
    result(1, 1) = f;
    result(2, 2) = f;
    result(3, 3) = static_cast<T>(1);
    return result;
  }

  static BasicMatrix<T> RotateAboutX(T angle)
  { return impl::RotateImpl(angle, 1, 2); }

  static BasicMatrix<T> RotateAboutY(T angle)
  { return impl::RotateImpl(angle, 2, 0); }

  static BasicMatrix<T> RotateAboutZ(T angle)
  { return impl::RotateImpl(angle, 0, 1); }
};

using Transformation = BasicTransformation<float>;

}  // namespace ge
