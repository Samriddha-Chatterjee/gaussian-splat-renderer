#ifndef GAUSSIAN_SPLAT_H
#define GAUSSIAN_SPLAT_H

//GLOBAL VARIABLES
extern int width, height;

extern unsigned char* input;
extern unsigned char* image;

extern float* buffer_r;
extern float* buffer_g;
extern float* buffer_b;

//FUNCTIONS
void save_ppm(const char* filename);

void clr_buffer();

void buffer_to_image();

void load_ppm(const char* filename);

void draw_gaussian(float cx, float cy, float sigma, float r, float g, float b);

float randf();

#endif