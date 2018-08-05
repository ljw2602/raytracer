#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list : public hitable {
  public:
    hitable_list() {}
    hitable_list(hitable **l, int n) : list(l), list_size(n) {}
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;
  private:
    hitable **list;
    int list_size;
};

#endif
