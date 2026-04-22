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


![Gaussian Reconstruction](output.jpg)

##  Effect of Sampling Density (Step Size)

> Step size defines the spatial sampling frequency of the renderer.

- Larger step → fewer samples → blocky/dotted output  
- Smaller step → more samples → smoother reconstruction  

---

### Step = 6 (Moderate Sampling)
![Step 6](patch_avg_6_step.jpg)

---

### Step = 4 (High Sampling)
![Step 4](patch_avg_4_step.jpg)

---

### Step = 2 (Very High Sampling)
![Step 2](patch_avg_2_step.jpg)

---

### Step = 1 (Near Pixel Level Detail)
![Step 1](patch_avg_1_step.jpg)

---

###  Tradeoff

Reducing step size improves quality but increases computational cost, as more Gaussians must be rendered.

---

###  Insight

Reducing step size increases sampling density, which improves reconstruction quality and reduces visible artifacts.

This demonstrates a key rendering principle:

> Higher sampling density leads to better approximation of the original signal.

---

##  Patch Averaging (Improved Sampling)

###  Problem

Initially, each Gaussian sampled only a single pixel:

- Produced noisy color estimates  
- Caused unstable and blotchy regions  
- Missed local color variation  

---

###  Solution

Instead of sampling a single pixel, we average colors over a small region (patch):

\[
R = \frac{1}{N} \sum I(x_i, y_i)
\]

This is implemented by sampling all pixels within the step-sized patch and averaging their values.

---

###  Benefits

- Smoother color transitions  
- Reduced noise  
- More stable reconstruction  
- Better approximation of the original image  

---

##  Build

```bash
gcc main.c gaussian_splat.c -o render -lm
