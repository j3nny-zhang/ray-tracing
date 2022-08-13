#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

//  is a pointer to some allocated type, with reference-counting semantics. New pointer incremements counter
//  when pointer goes out of scope, the counter is decremented
//  object is deleted when counter goes to 0
using std::shared_ptr;
//  allocates a new instance and returns a shared pointer 
// ex: shared_ptr<sphere> sphere_ptr = make_shared<sphere>(point3(0,0,0), 1.0);
// or express it more simply with auto: auto sphere_ptr = make_shared<sphere>(point3(0,0,0), 1.0);
using std::make_shared;

class hittable_list : public hittable {
    public:
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif