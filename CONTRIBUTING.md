## Open Source Contributions

Contributions are welcome.

This project is intentionally kept simple and readable, making it a good
base for experimenting with rendering techniques and performance optimizations.

If you plan to contribute, please keep changes focused and well-scoped.

---

## Suggested Contribution Areas

### Performance
- Multi-threaded CPU rendering (scanline or tile-based)
- Work scheduling and load balancing across threads
- Per-thread random number generators to avoid contention

### Acceleration Structures
- BVH build optimizations (e.g., centroid splits, SAH-based splitting)
- BVH traversal optimizations
- Better bounding box heuristics

### Rendering Features
- Additional primitives (rectangles, boxes)
- Texture mapping
- Light sources and emissive materials

### Engineering Improvements
- Clean separation of modules
- Improved CMake configuration
- Profiling and benchmarking utilities

---

## Contribution Guidelines

- Keep changes minimal and focused
- Prefer clarity over micro-optimizations
- Ensure rendered output remains visually correct
- Add brief comments where non-obvious logic is introduced