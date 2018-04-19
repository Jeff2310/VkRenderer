//
// Created by jeff2310 on 4/15/18.
//

#include "VirtualDevice.h"
#include "Rasterisation.h"

namespace VkRenderer {

    void VirtualDevice::setBackgroundColor(float r, float g, float b){
        glClearColor(r,g,b, 1.0f);
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                RasterlizePixel(*this, i, j, -1.0f, getColor(r, g, b, 1.0f));
            }
        }
    }

    void VirtualDevice::drawPixel(int x, int y, VkColor color){
        char r, g, b, a;
        r = (char)((color & 0xFF000000) >> 24),
        g = (char)((color & 0x00FF0000) >> 16),
        b = (char)((color & 0x0000FF00) >> 8),
        a = (char)((color & 0x000000FF));
        framebuffer[(y*width+x)*4] = r;
        framebuffer[(y*width+x)*4+1] = g;
        framebuffer[(y*width+x)*4+2] = b;
        framebuffer[(y*width+x)*4+3] = a;
    }
}