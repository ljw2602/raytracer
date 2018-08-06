#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable {
  public:
    sphere();
    sphere(vec3 cen, double r, material* m) : center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;

  private:
    vec3 center;
    double radius;
    material *mat_ptr;
};

#endif
