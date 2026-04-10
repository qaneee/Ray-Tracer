*This project has been created as part of the 42 curriculum by arvardan, ipogodae.*

# miniRT

## Description
`miniRT` is a small ray tracer written in C with MiniLibX.
Its goal is to render a 3D scene from a `.rt` descriptor by implementing the core ray-tracing pipeline from scratch: parsing, camera rays, intersections, lighting, and image output.

This implementation includes:
- Mandatory scene elements: ambient light, camera, and point lights
- Objects: sphere (`sp`), plane (`pl`), cylinder (`cy`), cone (`co`)
- Lighting: ambient + diffuse + specular, shadows
- Materials and extras: reflections, checkerboard pattern, bump mapping (`.xpm`), skybox
- Interactive edition at runtime (camera/object/light movement, rotation, selection, resize)

## Instructions
### Prerequisites
- Linux
- `cc` and `make`
- X11 development libraries (for MiniLibX), typically `libx11-dev` and `libxext-dev`

### Compilation
```bash
make
```

Optional debug builds:
```bash
make DEBUG=debug
make DEBUG=full
```

### Execution
```bash
./miniRT <scene_file.rt>
```

Example:
```bash
./miniRT scene/cols.rt
```

If the program is launched without exactly one `.rt` file, it exits with an error.

### Useful Make targets
```bash
make clean
make fclean
make re
```

## Usage Notes
### Minimal scene identifiers
- Exactly one `A` (ambient)
- Exactly one `C` (camera)
- At least one `L` (light)
- Optional `S` for skybox (`.xpm`)

### Optional object parameters
- `mirror `1.0`
- `checkerboard`
- texture path ending in `.xpm`
- `specular=<float>` and `shininess=<float>` (must be provided together)

### Runtime controls
- Mode switch: `C` camera mode, `O` object mode, `L` light mode
- Selection: `N` next object/light, `P` previous object/light
- Movement: `W/A/S/D` (or arrow keys), `Q/E` up/down
- Rotation: `R/F` (X axis), `T/G` (Y axis), `Y/H` (Z axis)
- Resize (object mode): `V/M` diameter +/- , `I/K` cylinder height +/-
- Exit: `Esc`

## Resources
- 42 Network project subject for `miniRT` (official evaluation requirements)
- *Ray Tracing in One Weekend* by Peter Shirley: https://raytracing.github.io/books/RayTracingInOneWeekend.html
- Scratchapixel (ray tracing and rendering math): https://www.scratchapixel.com/
- LearnOpenGL, Lighting chapter (Phong/Blinn-Phong background): https://learnopengl.com/Lighting/Basic-Lighting
- MiniLibX documentation (42): `minilibx-linux/man/`

### AI Usage
- Task 1: Checking and getting math formulas.
- Task 2: Structuring this `README.md`.
- Task 3: Making Makefile cool.
