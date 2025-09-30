<!-- # Ray Tracer (Work In Progress)

Currently, this project is a simple C++ program that generates a gradient image in PPM format.

## Requirements

- **CMake** (version 3.10 or higher)
- **C++17-compatible compiler** (e.g., g++, clang++, MSVC)

## Build & Run

```bash
cmake -B build
cmake --build build
./build/Debug/rayTracer.exe > image.ppm
```

For optimized builds (recommended for better performance):

```bash
cmake --build build --config Release
./build/Release/rayTracer.exe > image.ppm
```

On Mac or Linux, for a release build, run:

```bash
build/inOneWeekend > image.ppm
``` -->

# Ray Tracer (Work In Progress)

Currently, this project is a simple C++ program that generates a gradient image in PPM format.

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
