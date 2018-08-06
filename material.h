#ifndef MATERIALH
#define MATERIALH

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 reflect(const vec3 &v, const vec3 &n) {
  return v - 2*dot(v,n)*n;
}

bool refract(const vec3 &v, const vec3 &n, double ni_over_nt, vec3 &refracted) {
  vec3 uv = unit_vector(v);
  double dt = dot(uv, n);
  double discriminant = 1 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
  if (discriminant > 0.0) {
    refracted = ni_over_nt * (uv - n*dt) - n * sqrt(discriminant);
    return true;
  } else {
    return false;
  }
}

double schlick(double cosine, double ref_idx) {
  double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

class material {
  public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

/* diffuse materials that randomly scatter light */
class lambertian : public material {
  public:
    lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
      vec3 target = rec.p + rec.normal + random_in_unit_sphere();
      scattered = ray(rec.p, target - rec.p);
      attenuation = albedo;
      return true;
    }
  private:
    vec3 albedo;    
};

class metal : public material {
  public:
    metal(const vec3 &a, double f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
      vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
      scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
      attenuation = albedo;
      return (dot(scattered.direction(), rec.normal) > 0.0);
    }
  private:
    vec3 albedo;
    double fuzz;
};

class dielectric : public material {
  public:
    dielectric(double ri) : ref_idx(ri) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
      vec3 outward_normal, refracted;
      vec3 reflected = reflect(r_in.direction(), rec.normal);
      double ni_over_nt, reflect_prob, cosine;
      attenuation = vec3(1.0, 1.0, 1.0);
      if (dot(r_in.direction(), rec.normal) > 0.0) {
	outward_normal = -rec.normal;
	ni_over_nt = ref_idx;
	cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
      } else {
	outward_normal = rec.normal;
	ni_over_nt = 1.0 / ref_idx;
	cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
      }

      if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
	reflect_prob = schlick(cosine, ref_idx);
      } else {
	scattered = ray(rec.p, refracted);
	reflect_prob = 1.0;
      }

      if (drand48() < reflect_prob) {
	scattered = ray(rec.p, reflected);
      } else {
	scattered = ray(rec.p, refracted);
      }
      return true;
    }
  private:
    double ref_idx;
};

#endif