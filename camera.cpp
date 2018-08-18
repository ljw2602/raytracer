#include "camera.h"

vec3 random_in_unit_disk() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), 0.0) - vec3(1.0, 1.0, 0.0);
  } while(dot(p,p) >= 1.0);
  return p;
}

ray camera::get_ray(double s, double t) {
  vec3 rd = lens_radius * random_in_unit_disk();
  vec3 offset = u * rd.x() + v * rd.y();
  double time = time0 + drand48() * (time1 - time0);
  return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
}
