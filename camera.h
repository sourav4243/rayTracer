#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 1.0;  // Ratio of image width over height
        int image_width = 100;      // Rendered image width in pixel count
        int samples_per_pixel = 10; // Count of ranodm samples for each pixel
        int max_depth = 10;         // Maximum number of ray bounces into scene


        void render(const hittable& world){
            initialize();   // call initialize before working of render

            std::cout<< "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int j=0; j<image_height; j++){
                std::clog<<"\rScanlines remaining: "<< (image_height-j) << ' ' << std::flush; // progress bar
                for(int i=0; i<image_width; i++){
                    color pixel_color(0, 0, 0);
                    for(int sample=0; sample<samples_per_pixel; sample++){
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                }
            }

            std::clog << "\rDone.                \n";    // progress bar
        }

    private:
        int image_height;       // Rendered image height
        double pixel_samples_scale;     // Color scale factor for a sum of pixel samples
        point3 center;          // Camera center
        point3 pixel00_loc;     // Location of pixel 0, 0
        vec3 pixel_delta_u;     // Offset to pixel to the right
        vec3 pixel_delta_v;     // Offset to pixel below
        
        void initialize(){
            // Calculate the image height, and ensure that it's at leat 1.
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height<1)? 1: image_height;
            
            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = point3(0, 0, 0);

            // Determine viewport dimensions
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * ( pixel_delta_u + pixel_delta_v);
        }

        ray get_ray(int i, int j) const {
            // Construct a camera ray originating from the origin and directed at randomly sampled point
            // around the pixel location i, j

            auto offset = sample_square();
            // gives ray around the center for (i, j)th pixel wrt top-left pixel (pixel00_loc)
            auto pixel_sample = pixel00_loc + ( (i + offset.x()) * pixel_delta_u ) + ( (j + offset.y())* pixel_delta_v );
            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            // Returns the vector to a random point in the [-0.5, -0.5] - [+0.5, +0.5] unit square
            return vec3(random_double()-0.5, random_double()+0.5, 0);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            // If we've exceeded the ray bounce limit, no more light is generated. (fixed number of bounces allowed for diffusion)
            if(depth <= 0)
                return color(0, 0, 0);
            hit_record rec;

            // behind the hood, iterate through world hittable_list, call hittable of each object, then color that
            if(world.hit(r, interval(0.001, infinity), rec)){
                // vec3 direction = random_on_hemisphere(rec.normal);
                vec3 direction = rec.normal + random_unit_vector();         // correct rendering of Lambertian
                return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);   // using random ray direction for diffusion and 0.5 is used to half the brightness on each bounce
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif