#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "gaussian_splat.h"

int main() {
    int step = 6;
    float sigma=step*0.6f;

    load_ppm("input.ppm");


    
    buffer_r=malloc(width*height*sizeof(float));
    buffer_g=malloc(width*height*sizeof(float));
    buffer_b=malloc(width*height*sizeof(float));
    
    image=malloc(width*height*3*sizeof(unsigned char));

    
    for (int i = 0; i < width * height; i++) {
        buffer_r[i] = 0.0f;
        buffer_g[i] = 0.0f;
        buffer_b[i] = 0.0f;
    }


    for (int y = 0; y<height; y+=step) {
        for(int x=0; x<width;x+=step){
            // int idx=(y*width+x)*3;

            // unsigned char r8=input[idx];
            // unsigned char g8=input[idx+1];
            // unsigned char b8=input[idx+2];

            // float r=r8/255.0f;
            // float g=g8/255.0f;
            // float b=b8/255.0f;

            float r_sum=0, g_sum=0, b_sum=0;
            int count=0;

            for(int dy=0; dy<step; dy++){
                for(int dx=0; dx<step; dx++){

                    int px=x+dx;
                    int py=y+dy;

                    if(px>=width || py>=height) continue;

                    int idx=(py*width +px)*3;

                    r_sum+=input[idx];
                    g_sum+=input[idx+1];
                    b_sum+=input[idx+2];

                    count++;

                }
            }


            float r=(r_sum/count)/255.0f;
            float g=(g_sum/count)/255.0f;
            float b=(b_sum/count)/255.0f;

            float cx=x+step/2.0f;
            float cy=y+step/2.0f;
            
           // printf("r=%f g=%f b=%f\n", r, g, b);
        

            draw_gaussian(cx, cy, sigma, r, g, b);
        }
    }

    
    buffer_to_image();
    save_ppm("output.ppm");
    return 0;
}