#include "common/all_you_need.h"
#include "common/stats.h"
#include "acceleration/bvh.h"
#include "core/camera.h"
#include "geometry/hittable.h"
#include "geometry/hittable_list.h"
#include "material/material.h"
#include "geometry/sphere.h"

uint64_t thread_local ray_object_tests = 0;
uint64_t thread_local bvh_node_tests = 0;

int main() {
    hittable_list world;

    // Materials
    auto ocean_floor = make_shared<metal>(color(0.03, 0.04, 0.07), 0.50);
    auto moon_glass = make_shared<dielectric>(1.45);
    auto silver_mirror = make_shared<metal>(color(0.90, 0.92, 0.95), 0.00);
    auto silver_rough = make_shared<metal>(color(0.78, 0.82, 0.88), 0.08);
    auto rock_mat = make_shared<lambertian>(color(0.10, 0.10, 0.13));
    auto foam_mat = make_shared<lambertian>(color(0.88, 0.90, 0.94));

    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ocean_floor));

    // The Moon - r=11
    double moon_radius = 11.0;
    world.add(make_shared<sphere>(
        point3(0.0, moon_radius + 1.2, -55.0),
        moon_radius,
        moon_glass
    ));

    // Silver Sea - inner ring
    {
        double spacing = 0.52;
        double r = 0.26;
        int nx = 90;
        int nz = 110;

        for (int ix = -nx / 2; ix < nx / 2; ix++) {
            for (int iz = 0; iz < nz; iz++) {
                double cx = ix * spacing + random_double(-0.04, 0.04);
                double cz = -2.0 - iz * spacing + random_double(-0.04, 0.04);

                double wave =
                    0.06 * std::sin(cx * 1.8) * std::cos(cz * 1.3) +
                    0.04 * std::sin(cx * 3.1 + cz * 2.0);

                double cy = r + wave;

                auto mat = ((ix + iz) % 3 == 0) ? silver_rough : silver_mirror;

                world.add(make_shared<sphere>(point3(cx, cy, cz), r, mat));
            }
        }
    }

    // Silver Sea — outer ring
    {
        double r = 0.38;
        double spacing = 0.72;
        int nx = 60;
        int nz = 40;

        for (int ix = -nx / 2; ix < nx / 2; ix++) {
            for (int iz = 0; iz < nz; iz++) {
                double cx = ix * spacing + random_double(-0.08, 0.08);
                double cz = -2.0 - 110 * 0.52 - iz * spacing + random_double(-0.08, 0.08);
                double cy = r + 0.05 * std::sin(cx * 1.2 + cz * 0.9);
                world.add(make_shared<sphere>(point3(cx, cy, cz), r, silver_mirror));
            }
        }
    }

    // Foam crests
    for (int i = 0; i < 280; i++) {
        double cx = random_double(-22.0, 22.0);
        double cz = random_double(-5.0, -52.0);
        double r = random_double(0.06, 0.16);
        double cy = 0.30 + r + random_double(0.0, 0.18);

        world.add(make_shared<sphere>(point3(cx, cy, cz), r, foam_mat));
    }

    // Horizon rocks
    struct Rock {
        double x, z, r;
    };

    Rock rocks[] = {
        {-28.0, -72.0, 4.5},
        {-18.0, -78.0, 3.2},
        {-10.0, -68.0, 2.0},
        {5.0, -74.0, 3.8},
        {16.0, -70.0, 2.5},
        {26.0, -76.0, 5.0},
        {-36.0, -66.0, 6.0},
        {34.0, -68.0, 5.5},
    };

    for (auto& rock : rocks)
        world.add(make_shared<sphere>(
            point3(rock.x, rock.r * 0.6, rock.z),
            rock.r,
            rock_mat
        ));


    // 5 mirror spheres - spread across the sea
    struct MirrorSphere {
        double x, y, z, r;
    };

    MirrorSphere mirrors[] = {
        {-10.5, 2.8, -26.0, 1.8},
        {-5.0, 2.2, -22.0, 2.2},
        {0.0, 2.8, -32.0, 2.5},
        {5.5, 2.0, -21.0, 2.0},
        {11.0, 2.5, -27.0, 1.7},
    };

    for (auto& m : mirrors)
        world.add(make_shared<sphere>(
            point3(m.x, m.y, m.z),
            m.r,
            silver_mirror
        ));

    // Foreground sea extension - fill the black strip
    {
        double spacing = 0.48;
        double r = 0.24;
        int nx = 50;
        int nz = 20;

        for (int ix = -nx / 2; ix < nx / 2; ix++) {
            for (int iz = 0; iz < nz; iz++) {
                double cx = ix * spacing + random_double(-0.03, 0.03);
                double cz = 6.0 - iz * spacing + random_double(-0.03, 0.03);
                double wave = 0.05 * std::sin(cx * 2.0) * std::cos(cz * 1.5);
                double cy = r + wave;
                auto mat = ((ix + iz) % 3 == 0) ? silver_rough : silver_mirror;
                world.add(make_shared<sphere>(point3(cx, cy, cz), r, mat));
            }
        }
    }

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 600;
    cam.max_depth = 60;
    cam.vfov = 28;

    cam.lookfrom = point3(0.0, 1.4, 14.0);
    cam.lookat = point3(0.0, 2.0, -55.0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.25;
    cam.focus_dist = 40.0;

    cam.render(world);
}