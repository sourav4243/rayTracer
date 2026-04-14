#include "common/all_you_need.h"
#include "common/stats.h"
#include "acceleration/bvh.h"
#include "core/camera.h"
#include "geometry/hittable.h"
#include "geometry/hittable_list.h"
#include "material/material.h"
#include "geometry/sphere.h"

thread_local uint64_t ray_object_tests = 0;
thread_local uint64_t bvh_node_tests  = 0;

int main() {
    hittable_list world;

    auto surface = make_shared<metal>(color(0.988, 0.663, 0.541), 0.05);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, surface));

    auto chrome_mirror  = make_shared<metal>(color(0.92, 0.92, 0.94), 0.00);
    auto chrome_diffuse = make_shared<metal>(color(0.80, 0.80, 0.83), 0.28);
    auto chrome_semi    = make_shared<metal>(color(0.86, 0.86, 0.89), 0.10);

    auto gold_mirror    = make_shared<metal>(color(0.95, 0.80, 0.28), 0.00);
    auto gold_diffuse   = make_shared<metal>(color(0.88, 0.72, 0.22), 0.30);
    auto gold_semi      = make_shared<metal>(color(0.92, 0.76, 0.25), 0.10);

    auto rose_mirror    = make_shared<metal>(color(0.92, 0.72, 0.62), 0.00);
    auto rose_diffuse   = make_shared<metal>(color(0.85, 0.65, 0.56), 0.25);

    struct Ball { double x, z, R; shared_ptr<material> mat; };

    Ball heroes[] = {
        {  0.0,   0.0,  1.20,  chrome_mirror  },
        { -2.8,   0.3,  1.10,  gold_mirror    },
        {  2.6,  -0.2,  1.00,  gold_diffuse   },
        { -1.5,   2.5,  1.05,  chrome_diffuse },
        {  2.0,   2.8,  0.95,  rose_mirror    },
    };

    for (auto& b : heroes) {
        double cy = b.R; 
        world.add(make_shared<sphere>(point3(b.x, cy, b.z), b.R, b.mat));
    }

    Ball mediums[] = {
        {  1.2,   1.2,  0.60,  chrome_mirror  },
        { -1.4,   1.0,  0.55,  gold_semi      },
        {  3.8,   1.0,  0.62,  chrome_semi    },
        { -3.8,   1.2,  0.58,  gold_mirror    },
        {  0.5,  -1.5,  0.52,  rose_diffuse   },
        { -0.8,  -1.3,  0.48,  chrome_diffuse },
        {  4.2,  -0.5,  0.50,  gold_diffuse   },
        { -4.0,  -0.3,  0.54,  chrome_mirror  },
    };

    for (auto& b : mediums) {
        double cy = b.R;
        world.add(make_shared<sphere>(point3(b.x, cy, b.z), b.R, b.mat));
    }

    Ball smalls[] = {
        {  1.6,  -0.6,  0.28,  gold_mirror    },
        { -1.8,  -0.5,  0.24,  chrome_mirror  },
        {  3.2,   0.2,  0.30,  rose_mirror    },
        { -3.0,   0.0,  0.26,  gold_diffuse   },
        {  0.8,   1.8,  0.22,  chrome_semi    },
        { -0.6,   1.6,  0.26,  gold_semi      },
        {  2.8,   2.0,  0.24,  chrome_mirror  },
        { -2.5,   2.2,  0.28,  rose_diffuse   },
        {  4.8,   0.5,  0.22,  gold_mirror    },
        { -4.6,   0.8,  0.26,  chrome_diffuse },
        {  1.0,   3.0,  0.20,  gold_mirror    },
        { -1.2,   3.2,  0.24,  chrome_mirror  },
    };

    for (auto& b : smalls) {
        double cy = b.R;
        world.add(make_shared<sphere>(point3(b.x, cy, b.z), b.R, b.mat));
    }

    for (int i = 0; i < 80; i++) {
        double angle = random_double(0, 2 * pi);
        double dist  = random_double(0.5, 6.5);
        double tx    = dist * std::cos(angle);
        double tz    = dist * std::sin(angle);
        double r     = random_double(0.06, 0.14);

        shared_ptr<material> mat;
        double pick = random_double();
        if      (pick < 0.30) mat = chrome_mirror;
        else if (pick < 0.50) mat = chrome_diffuse;
        else if (pick < 0.70) mat = gold_mirror;
        else if (pick < 0.85) mat = gold_diffuse;
        else                  mat = rose_mirror;

        world.add(make_shared<sphere>(point3(tx, r, tz), r, mat));
    }

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;

    cam.vfov     = 45;
    cam.lookfrom = point3(0.0, 6.0, 12.0);
    cam.lookat   = point3(0.0, 0.8,  1.0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0.0; 
    cam.focus_dist    = 12.0;

    cam.render(world);
}