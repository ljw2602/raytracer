#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
  public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup,
	   double vfov, double aspect,  // vfov is top to bottom in degrees
	   double aperture, double focus_dist) {
      lens_radius = aperture/2.0;

      double theta       = vfov * M_PI / 180.0;
      double half_height = tan(theta / 2.0);
      double half_width  = aspect * half_height;

      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      origin             = lookfrom;
      lower_left_corner  = origin - half_width * u * focus_dist - half_height * v * focus_dist - w * focus_dist;
      horizontal         = 2.0 * half_width  * u * focus_dist;
      vertical           = 2.0 * half_height * v * focus_dist;
    }
    ray get_ray(double s, double t);

  private:
    vec3 origin, lower_left_corner, horizontal, vertical;
    vec3 u, v, w;
    double lens_radius;
};

#endif
