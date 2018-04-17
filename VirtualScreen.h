//
// Created by jeff2310 on 4/15/18.
//
#ifndef VKSOFTWARERENDER_VIRTUALSCREEN_H
#define VKSOFTWARERENDER_VIRTUALSCREEN_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace VkRenderer {
    class VirtualScreen {
    private:
        string name;
        //pixels中行从y较大的方向开始存
        char **pixels;
        int width, height;
    public:
        VirtualScreen(string name, int width = 1, int height = 1) {
            this->width = width;
            this->height = height;
            pixels = new char *[height];
            for (int i = 0; i < height; i++) {
                pixels[i] = new char[width];
            }
        }
        // todo deep-copy

        ~VirtualScreen() {
            /*
            for(int i=0; i<width; i++){
                delete[] pixels[i];
            }
            */
            delete[] pixels;
        }
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        void Dump(const string& fileName) {
            ofstream dumpFile;
            dumpFile.open(fileName);
            if (!dumpFile.is_open()) {
                cout << "Error dumping to file : cannot open file";
            }
            // pixels中行存储顺序和viewport中y轴正方向相反
            for(int y = height-1; y >=0; y--) {
                for(int x=0; x<width; x++) {
                    dumpFile << pixels[y][x];
                }
                dumpFile<<endl;
            }
            dumpFile.close();
        }

        void DrawPixel(int x, int y, char value);

        void DrawLine(int x1, int y1, int x2, int y2, char value);
    };
}

#endif //VKSOFTWARERENDER_VIRTUALSCREEN_H