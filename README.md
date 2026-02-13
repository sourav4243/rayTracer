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

## Branch Structure

This repository maintains two implementations:

- `main` → Single-threaded renderer (baseline implementation)
- `feature/multithread` → Multithreaded renderer (parallelized version built on top of the baseline)

### How to Switch Between Versions

Clone to repo:
```bash
git clone https://github.com/sourav4243/rayTracer.git
cd rayTracer
```

To use the **single-threaded version** (at root of project):

```bash
git checkout main
```

To use the **multithreaded version** (at root of project):
```bash
git checkout feature/multithread
```

---

## Performance Evaluation

A complex test scene consisting of **~500 spheres** was rendered under multiple configurations to evaluate acceleration and parallelization strategies.

_All test counts shown in **billions (10⁹)**_

| Method                   | Threads        | Ray–Object Tests (×10⁹) | BVH Node Tests (×10⁹) | Render Time |
|--------------------------|---------------|--------------------------|------------------------|-------------|
| Brute Force (No BVH)     | 1             | **533.19**               | —                      | **52m 20s** |
| BVH (Random Axis Split)  | 1             | **7.03**                 | **52.22**              | **9m 47s**  |
| BVH (Longest Axis Split) | 1             | **5.28**                 | **44.31**              | **8m 57s**  |
| BVH (Longest Axis Split) | Multi-threaded| **2.23**                 | **8.94**               | **8m 40s**  |

### Key Findings

- BVH reduced ray–object intersection tests from **~533 billion** to approximately **~5 billion**, achieving nearly a **100× reduction** in expensive geometric operations.
- Longest-axis splitting demonstrated better spatial partitioning efficiency than random-axis splitting.
- Multithreading reduced wall-clock render time by distributing workload across CPU cores.


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

Single-thread Debug build
```bash
cmake -B build
cmake --build build
./build/rayTracer > image.ppm
```
Multi-thread Debug build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/rayTracer > image.ppm
```
For optimized builds (same for both singe and multi thread version):

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/rayTracer > image.ppm
```


## Output

The program writes a PPM image to stdout. <br>
Redirect the output to a file and open it using any image viewer that supports PPM.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidelines and
suggested areas of improvement.