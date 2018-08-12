#include "sphere.h"

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
  vec3 oc = r.origin() - center;
  double a = dot(r.direction(), r.direction());
  double b = dot(oc, r.direction());
  double c = dot(oc, oc) - radius * radius;
  double discriminant = b * b - a * c;
  if (discriminant > 0.0) {
    double t1 = (-b - sqrt(discriminant)) / a;
    double t2 = (-b + sqrt(discriminant)) / a;
    double t;
    if (t1 > t_min && t1 < t_max) {
      t = t1;
    } else if (t2 > t_min && t2 < t_max) {
      t = t2;
    } else {
      return false;
    }
    rec.t = t;
    rec.p = r.point_at_parameter(t);
    rec.normal = (r.point_at_parameter(t) - center) / radius;  // unit vector
    rec.mat_ptr = mat_ptr;
    return true;
  } else {
    return false;
  }
}
