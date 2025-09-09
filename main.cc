#include<iostream>
using namespace std;

int main(){
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    cout<< "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j=0; j<image_height; j++){
        clog<<"\rScanlines remaining: "<< (image_height-j) << ' ' << flush; // progress bar
        for(int i=0; i<image_width; i++){
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            int ir = int(255.999*r);
            int ig = int(255.999*g);
            int ib = int(255.999*b);

            cout<< ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    clog << "\rDone.                \n";    // progress bar
}