# AGENTS.md — SoftPhys Architecture & Extension Guide

## Overview

`SoftPhys` is a standalone physics and soft-body simulation engine decoupled from legacy monolithic U++ repositories. It provides collision detection, particle springs, cloth solvers, and rigid-body abstractions.

## Dependencies

- Foundation: `BazaarCore` (supplies `Core` and patched stdsrc foundation)
- Math & Linear Algebra: `UppGeometry` (supplies `Geometry`, `Draw/Extensions`, `plugin/Eigen`)

## Directory Layout

- `uppsrc/SoftPhys/`:
  - `Common.h`, `Internal.h`, `SoftPhys.h`: Core definitions, math types, and macros.
  - `World.h`, `World.cpp`: Top-level physics world manager encapsulating `PhysicsSystem` and joint groups.
  - `PhysicsSystem.h`, `PhysicsSystem.cpp`: Main simulation solver executing impulse resolution, constraint solving, and kinematic updates.
  - `Body.h`, `Body.cpp`: Rigid body state encapsulation (mass, inertia, velocities, transforms).
  - `Geometry.h`, `Geometry.cpp`, `Geometry2D.h`, `Geometry3D.h`: Abstract geometric entities and collision shapes.
  - `Particle.h`, `Particle.cpp`, `Spring.h`, `Cloth.h`, `Cloth.cpp`: Particle dynamics, spring models, and cloth grids.
  - `Space.h`, `Space.cpp`, `QuadTree.h`, `QuadTree.cpp`: Spatial partitioning and broadphase collision dispatch.
- `tests/SoftPhysTests/`:
  - Automated headless test harness covering `World`, `Body`, `PhysicsSystem`, `Cloth`, and `QuadTree`.

## Build Verification

Run with `UppBuilder`:
```bash
uppbuilder tests/SoftPhysTests --bazaarcore <path-to-BazaarCore> --uppgeometry <path-to-UppGeometry> -v
./bin/SoftPhysTests
```
CI builds across 4 platforms (Ubuntu GCC, Ubuntu Clang, macOS Clang, Windows MSVC).
