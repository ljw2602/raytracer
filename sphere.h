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

class moving_sphere : public hitable {
  public:
    moving_sphere();
    moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, material *m) : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;
    vec3 center(double time) const;
    
  private:
    vec3 center0, center1;
    double time0, time1;
    double radius;
    material *mat_ptr;
};

#endif
