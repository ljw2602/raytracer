#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
  public:
    camera(vec3 origin_,
	   vec3 lower_left_corner_,
	   vec3 horizontal_,
	   vec3 vertical_) :
      origin(origin_),
      lower_left_corner(lower_left_corner_),
      horizontal(horizontal_),
      vertical(vertical_) {}
    ray get_ray(double u, double v);

  private:
    vec3 origin, lower_left_corner, horizontal, vertical;
};

#endif
