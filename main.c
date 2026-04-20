#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "gaussian_splat.h"


int main() {
    int step = 8;
    for (int i = 0; i < width * height; i++) {
    buffer_r[i] = 0.0f;
    buffer_g[i] = 0.0f;
    buffer_b[i] = 0.0f;
}
    load_ppm("input.ppm");
    buffer_r=malloc(width*height*sizeof(float));
    buffer_g=malloc(width*height*sizeof(float));
    buffer_b=malloc(width*height*sizeof(float));
    
    image=malloc(width*height*3*sizeof(unsigned char));

    for (int y = 0; y<height; y+=step) {
        for(int x=0; x<width;x+=step){
            int idx=(y*width+x)*3;

            unsigned char r8=input[idx];
            unsigned char g8=input[idx+1];
            unsigned char b8=input[idx+2];

            float r=r8/255.0f;
            float g=g8/255.0f;
            float b=b8/255.0f;
        

            draw_gaussian(x, y, step, r, g, b);
        }
    }

    
    buffer_to_image();
    save_ppm("output.ppm");
    return 0;
}