#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }
    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            }
            if (command == "invert"){
                invert();
                continue;
            }
            if (command == "replace"){
                replace();
                continue;
            }
            if (command == "h_mirror"){
                h_mirror();
                continue;
            }
            if (command == "add"){
                add();
                continue;
            }
            if(command == "rotate_left"){
                rotate_left();
                continue;
            }
            // TODO ...

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert() {
        // Replace each individual pixel (r, g, b) to (255-r,255-g,255-b).
        int w = image->width();
        int h = image->height();
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                image->at(x, y).red() = 255 - image->at(x,y).red();
                image->at(x, y).green() = 255 - image->at(x,y).green();
                image->at(x, y).blue() = 255 - image->at(x,y).blue();
            }
        }
    }
    void Script::replace(){
        int w = image->width();
        int h = image->height();                
        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1;
        input >> r2 >> g2 >> b2;
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                if(image->at(x, y).red() == r1 && image->at(x, y).green() == g1 && image->at(x, y).blue() == b1){
                    image->at(x, y).red() = r2;
                    image->at(x, y).green() = g2;
                    image->at(x, y).blue() = b2;
                }
            }
        }
    } 
    void Script::h_mirror(){
        int w = image->width();
        int h = image->height();
        int r1, g1, b1, r2, g2, b2;
        for(int x = 0; x < w/2; x++){
            for(int y = 0; y < h; y++){
                    r1 = image->at(x, y).red();
                    g1 = image->at(x, y).green();
                    b1 = image->at(x, y).blue();
                    int o = w - 1 - x;
                    int p = y;
                    r2 = image->at(o, p).red();
                    g2 = image->at(o, p).green();
                    b2 = image->at(o, p).blue();
                    image->at(x, y).red() = r2;
                    image->at(x, y).green() = g2;
                    image->at(x, y).blue() = b2;
                    image->at(o, p).red() = r1;
                    image->at(o, p).green() = g1;
                    image->at(o, p).blue() = b1;
                        }

                }
        }
    void Script::add(){
        
        string filename;    
        input >> filename;
        Image* imagetest = loadFromPNG(filename);
        int r,g,b,o,p;
        input >> r >> g >> b >> o >> p;
        int w = imagetest->width();
        int h = imagetest->height();
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                if(imagetest->at(x, y).red() != r || imagetest->at(x, y).green() != g || imagetest->at(x, y).blue() != b){
                image->at(o+x, p+y).red() = imagetest->at(x, y).red();
                image->at(o+x, p+y).green() = imagetest->at(x, y).green();
                image->at(o+x, p+y).blue() = imagetest->at(x, y).blue();
            }
            }
        }
        delete imagetest;
    }
    void Script::rotate_left(){
        int w = image->width();
        int h = image->height();
        Image* image_test = new Image(h, w);
        Color copy;
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                    copy = image->at(x, y);
                    int o = w - 1 - x;
                    int p = y;
                    image_test->at(p,o) = copy;

            }   
        }
        
        *image = *image_test;
        delete image_test;


    }
}
