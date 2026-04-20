#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "gaussian_splat.h"

//#define WIDTH 800
//#define HEIGHT 600

unsigned char* input;
int width, height;

unsigned char* image;
float* buffer_r;
float* buffer_g;
float* buffer_b;

//ALL BUFFER ALLOCATIONS ARE IN MAIN FUNCTION

// void clr_img(unsigned char r, unsigned char g, unsigned char b){
//     for(int y=0;y<HEIGHT;y++){
//         for(int x=0;x<WIDTH;x++){

//             image[y][x][0]=r;
//             image[y][x][1]=g;
//             image[y][x][2]=b;
//         }
//     }
// }

void save_ppm(const char* filename) {
    FILE* f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);

    fwrite(image, 1, width * height * 3, f);
    fclose(f);
}

void clr_buffer(){
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){

            int idx=y*width+x;
            buffer_r[idx]=0.0f;
            buffer_g[idx]=0.0f;
            buffer_b[idx]=0.0f;
        }
    }
}

void buffer_to_image() {
    float max_val = 0.0f;
    int idx,img_idx;
    // max
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++){

            idx=y*width+x;
            if (buffer_r[idx] > max_val)max_val = buffer_r[idx];
            if (buffer_g[idx] > max_val)max_val = buffer_g[idx];
            if (buffer_b[idx] > max_val)max_val = buffer_b[idx];}

    // normalize
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            idx=y*width+x;
            img_idx=idx*3;

            float r = buffer_r[idx] / max_val;
            float g = buffer_g[idx] / max_val;
            float b = buffer_b[idx] / max_val;

            image[img_idx] = (unsigned char)(r*255);
            image[img_idx+1] = (unsigned char)(g*255);
            image[img_idx+2] = (unsigned char)(b*255);
        }
    }
}

void load_ppm(const char* filename){
    FILE* f = fopen(filename, "rb");

    if(!f){
        printf("Error opening file\n");
        exit(1);
    }

    char format[3];
    int maxval;

    fscanf(f, "%2s", format);
    fscanf(f, "%d %d", &width, &height);
    fscanf(f, "%d", &maxval);
    fgetc(f);

    input = malloc(width*height*3);

    fread(input, 1, width*height*3, f);

    fclose(f);
}

void draw_gaussian(float cx, float cy, float sigma, float r,float g,float b){
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            int idx;
            float dx=x-cx;
            float dy=y-cy;

            float dist=dx*dx+dy*dy;

            float intensity=exp(-dist/(2*sigma*sigma));

            unsigned char val=(unsigned char)(intensity*255);

            idx=y*width+x;

            buffer_r[idx] +=intensity*r;
            buffer_g[idx] +=intensity*g;
            buffer_b[idx] +=intensity*b;


        }
    }
}

float randf() {
    return (float)rand() / RAND_MAX;
}

