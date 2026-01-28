# Ray Tracer (Work In Progress)

This project is a **CPU-based ray tracer**.

At the current stage, the renderer includes:

- Perspective camera with configurable field of view
- Ray-sphere intersection
- Material models:
  - Lambertian (diffuse)
  - Metal (specular with fuzz)
  - Dielectric (refraction / glass)
- Recursive ray tracing with depth limiting
- Stochastic sampling for anti-aliasing
- Image output in **PPM format**

The implementation prioritizes **physical correctness and rendering accuracy** over performance.

---

## Current Rendering State

- The renderer is capable of producing visually correct images for complex scenes
- A test render consisting of **~500 spheres** was successfully generated
- That render took approximately **2 hours 57 minutes** on CPU
- Runtime currently scales **linearly with the number of objects**, since:
  - Every ray is tested against every object
  - No spatial acceleration structures are implemented yet

This performance is expected at this stage of the renderer.

---

## Render Output (Pre-Acceleration)

Below is an example render produced **before** adding any acceleration structures:

![Ray Tracer Output](/images/render_pre_bvh.png)

---

## Next Steps

The next phase focuses on reducing ray-object intersection cost by introducing:

- Axis-Aligned Bounding Boxes (AABB)
- Bounding Volume Hierarchy (BVH)

These will significantly improve performance while keeping rendering behavior unchanged.

## Requirements

* **CMake** (version 3.10 or higher)
* **C++17-compatible compiler** (e.g., g++, clang, MSVC)

## Build & Run

### Windows (MSVC / Visual Studio)

```bash
cmake -B build
cmake --build build --config Debug
./build/Debug/rayTracer.exe > image.ppm
```

For optimized builds:

```bash
cmake --build build --config Release
./build/Release/rayTracer.exe > image.ppm
```

### Linux / macOS (GCC or Clang)

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/rayTracer > image.ppm
```


### This is what I do on my linux system
```bash
cmake -B build
cmake --build build
build/rayTracer > image.ppm
```


## Output

The program writes a PPM image to stdout. <br>
Redirect the output to a file and open it using any image viewer that supports PPM.


## Upcoming Work

The next development phase focuses on **performance optimization**, starting with:

- Axis-Aligned Bounding Boxes (AABB)
- Bounding Volume Hierarchy (BVH)

These changes will significantly reduce ray–object intersection cost and
enable scalable rendering for larger scenes.