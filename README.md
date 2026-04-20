# Gaussian Splat Renderer (C)

A Gaussian splatting-based 2D image reconstruction engine written in C, with groundwork for extending into 3D rendering.

---

##  Features

- 2D Gaussian splatting
- Image reconstruction using Gaussian basis functions
- Dynamic memory management (no fixed-size buffers)
- Modular multi-file C structure
- Foundation for future 3D splatting

---

##  How It Works

The image is reconstructed as a sum of Gaussian functions:

I(x, y) ≈ Σ Gᵢ(x, y)

Each Gaussian:
- Has a position (x, y)
- Has a spread (σ)
- Carries RGB color information

The final image is formed by accumulating these contributions and normalizing.

---

##  Build

```bash
gcc main.c gaussian_splat.c -o render -lm
