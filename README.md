# Ray Tracer

This project is a **CPU-based ray tracer written in C++** with a focus on
**physical correctness, clean architecture, and performance optimization**.

---

## Features

- Perspective camera with configurable field of view
- Ray–sphere intersection
- Material models:
  - Lambertian (diffuse)
  - Metal (specular with fuzz)
  - Dielectric (refraction / glass)
- Recursive ray tracing with depth limiting
- Stochastic sampling for anti-aliasing
- Image output in **PPM format**
- **Spatial acceleration using AABB and BVH**

---

## Rendering & Performance

A complex test scene consisting of **~500 spheres** was rendered before and
after introducing acceleration structures.

## Performance Comparison (Same Scene ~500 Spheres)

| Configuration              | Acceleration | Build Type | Render Time |
|---------------------------|--------------|------------|-------------|
| Brute Force               | None         | Release    | ~2h 57m     |
| AABB + BVH                | Enabled      | Debug      | ~1h 25m     |
| AABB + BVH                | Enabled      | Release    | **~12m 33s** |

This confirms a **significant performance improvement** while preserving
rendering correctness.

---

## Render Output

### Pre-BVH (Brute Force)
![Ray Tracer Output - Pre BVH](/images/Render_pre_bvh.png)

### Post-BVH (Accelerated)
![Ray Tracer Output - Post BVH](/images/Render_post_bvh.png)

---

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
cmake -B build
cmake --build build
./build/rayTracer > image.ppm
```
For optimized builds:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/rayTracer > image.ppm
```


## Output

The program writes a PPM image to stdout. <br>
Redirect the output to a file and open it using any image viewer that supports PPM.

