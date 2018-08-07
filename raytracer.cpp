#include <iostream>
#include <cfloat>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "hitable_list.h"

const vec3 color (const ray& r, hitable *world, unsigned depth) {
  hit_record rec;
  if (world->hit(r, 0.001, DBL_MAX, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth+1);
    } else {
      return vec3(0.0, 0.0, 0.0);
    }
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int nx = 400, ny = 200, ns = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  vec3 lookfrom(3.0, 3.0, 2.0);
  vec3 lookat(0.0, 0.0, -1.0);
  double dist_to_focus = (lookfrom - lookat).length();
  double aperture = 0.0;
  camera cam(lookfrom, lookat, vec3(0.0,1.0,0.0), 20, double(nx)/double(ny),
             aperture, dist_to_focus);

  hitable *list[4];
  list[0] = new sphere(vec3( 0.0,    0.0, -1.0),   0.5, new lambertian(vec3(0.1, 0.2, 0.5)     ));
  list[1] = new sphere(vec3( 0.0, -100.5, -1.0), 100.0, new lambertian(vec3(0.8, 0.8, 0.0)     ));
  list[2] = new sphere(vec3( 1.0,    0.0, -1.0),   0.5, new      metal(vec3(0.8, 0.6, 0.2), 0.0));
  list[3] = new sphere(vec3(-1.0,    0.0, -1.0),   0.5, new dielectric(1.5                     ));
  hitable *world = new hitable_list(list, 4);

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0.0, 0.0, 0.0);

      for (int s = 0; s < ns; s++) {
	double u = double(i + drand48()) / double(nx);  // antialiasing (smooth edge)
        double v = double(j + drand48()) / double(ny);  // drand48() = random number generater [0,1)
        ray r = cam.get_ray(u, v);
        col += color(r, world, 0);
      }
      col /= double(ns);
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

      int ir = int(255.9 * col[0]);
      int ig = int(255.9 * col[1]);
      int ib = int(255.9 * col[2]);

      std::cout << ir << " " << ig << " " << ib << std::endl;
    }
  }
  return(0);
}
