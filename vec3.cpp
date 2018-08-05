#include "vec3.h"

inline vec3& vec3::operator+=(const vec3 &v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
  e[0] *= v.e[0];
  e[1] *= v.e[1];
  e[2] *= v.e[2];
  return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
  e[0] /= v.e[0];
  e[1] /= v.e[1];
  e[2] /= v.e[2];
  return *this;
}
inline vec3& vec3::operator*=(const double t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

inline vec3& vec3::operator/=(const double t) {
  e[0] /= t;
  e[1] /= t;
  e[2] /= t;
  return *this;
}

