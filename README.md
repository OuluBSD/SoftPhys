# SoftPhys

SoftPhys is a modern, decoupled C++ physics and cloth simulation engine designed for Ultimate++ (U++).

## Features

- **Rigid Body Dynamics**: Rigid bodies, collision detection, and spatial partitioning (`Space`, `QuadTree`).
- **Cloth & Spring Dynamics**: Particle networks, structural springs, constraint solving, and soft-body cloth emulation.
- **Cross-Platform**: Zero third-party runtime dependencies beyond `BazaarCore` and `UppGeometry`. Verified on Ubuntu GCC/Clang, macOS Clang, and Windows MSVC.
- **UppBuilder & Portage Integration**: Fully manageable and discoverable via `UppBuilder` and `UppOverlay` (`DevCpp/SoftPhys`).

## Package Structure

- `uppsrc/SoftPhys`: Core physics engine, cloth simulation, collision volumes, and solver algorithms.
- `tests/SoftPhysTests`: Automated unit test suite verifying world dynamics, body kinematic states, particle/spring systems, and quadtree spatial queries.

## Building & Testing

Build and test with `UppBuilder`:

```bash
uppbuilder tests/SoftPhysTests --bazaarcore <path-to-BazaarCore> --uppgeometry <path-to-UppGeometry>
./bin/SoftPhysTests
```

## CI Matrix

Continuous integration verifies 4 platforms on every push:
- Ubuntu Linux (GCC)
- Ubuntu Linux (Clang)
- macOS (Apple Clang)
- Windows (MSVC 2022 x64)
