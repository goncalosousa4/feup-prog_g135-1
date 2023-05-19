#include <iostream>
#include <algorithm>
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
            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            }
            if (command == "replace"){
                replace();
                continue;
            }
            if (command == "fill") {
                int x,y,w,h;

                input >> x;
                input >> y;
                input >> w;
                input >> h;
                Color color;
                input >> color;
                fill( x, y, w, h, color.red(), color.green(), color.blue());
                continue;
            }
            if (command == "h_mirror"){
                h_mirror();
                continue;
            }
            if (command == "v_mirror") {
                v_mirror();
                continue;
            }
            if (command == "add"){
                add();
                continue;
            }
            if (command == "crop") {
                int x, y, w, h;

                input >> x;
                input >> y;
                input >> w;
                input >> h;
                crop(x,y,w,h);
                continue;

            }
            if(command == "rotate_left"){
                rotate_left();
                continue;
            }
            if (command == "rotate_right") {
                rotate_right();
                continue;
            }
            if (command == "median_filter") {
                int ws;
                input >> ws;
                median_filter(ws);
                continue;
            }
            if (command == "xpm2_open") {
                clear_image_if_any(); //clears possible memory alocated for the image preventing memory leaks
                string file;
                input >> file;
                image = loadFromXPM2(file);
                continue;
            }
            if (command == "xpm2_save") {
                string file;
                input >> file;
                saveToXPM2(file, image);
                continue;
            }
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
    void Script::invert() 
    {
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
    
    void Script::to_gray_scale() 
    {
        int height = image->height();
        int width  = image->width();
        for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < width; column++)
            {
                Color &p    = image->at(column, row);   //get pixel to aplly gray scale
                rgb_value v = (p.red() + p.green() + p.blue()) / 3; //get the gray scale of a specific pixel
                p.red()     = v; //change the red rgb value
                p.green()   = v; //change the green rgb value
                p.blue()    = v; //change the blue rgb value
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
                if(image->at(x, y).red() == r1 && image->at(x, y).green() == g1 && image->at(x, y).blue() == b1)    //check if pixel must be replaced
                { 
                    image->at(x, y).red() = r2;
                    image->at(x, y).green() = g2;
                    image->at(x, y).blue() = b2;
                }
            }
        }
    }
    
    void Script::fill(int x, int y, int w, int h, rgb_value r, rgb_value g, rgb_value b)
    {
        for (int row=y ; row<y+h ;row++){
            for (int column=x; column<x+w; column++)
            {
                image->at(column,row) = Color(r,g,b);   //set the intended rectangle pixels to the desired color one by one
            }
        }
    }
    
    void Script::h_mirror()
    {
        int w = image->width();
        int h = image->height();
        int r1, g1, b1, r2, g2, b2;
        for(int x = 0; x < w/2; x++){
            for(int y = 0; y < h; y++){
                    r1 = image->at(x, y).red();     //copy red values of the pixel
                    g1 = image->at(x, y).green();   //copy green values of the pixel
                    b1 = image->at(x, y).blue();    //copy blue values of the pixel
                    int o = w - 1 - x;              //calculate the y h_mirror position of pixel in position (x,y)
                    int p = y;                      //calculate the x h_mirror position of pixel in position (x,y) 
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
    
    void Script::v_mirror()
    {
        int number_of_lines_positons = image->height(); 
        int swaps_neded = number_of_lines_positons / 2; //calculate the number of operation nedded
        number_of_lines_positons--; //calculate the max address of the rows from the matrix
        for (int i = 0; i<swaps_neded; i++)
        {
            vector<Color> copy_row = image->get_row(i); //copy one row of the matrix
            image->get_row(i) = image->get_row(number_of_lines_positons - i);   //"move" the upper row to the position of its vertical counterpart
            image->get_row(number_of_lines_positons-i) = copy_row;  //"move" the bottom row to the positon of ist vertical counterpart using the copied row
        }
    }
    
    void Script::add()
    {
        
        string filename;    
        input >> filename;
        Image* imagetest = loadFromPNG(filename);
        int r,g,b,o,p;
        input >> r >> g >> b >> o >> p;
        int w = imagetest->width();
        int h = imagetest->height();
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                if(imagetest->at(x, y).red() != r || imagetest->at(x, y).green() != g || imagetest->at(x, y).blue() != b)
                {
                //if the pixel is nor of "neutral" color change it its equivelent in the imagetest
                image->at(o+x, p+y).red() = imagetest->at(x, y).red();
                image->at(o+x, p+y).green() = imagetest->at(x, y).green();
                image->at(o+x, p+y).blue() = imagetest->at(x, y).blue();
            }
            }
        }
        delete imagetest;
    }
    
    void Script::crop(int x, int y, int w, int h)
    {
        vector<vector<Color>> new_image_matrix; //new matrix of the croped area
        for (int row = y; row < y+h ;row++)
        {
            vector<Color> new_row;  //define new row of new matrix
            for (int column = x; column < x+w; column++)
            {
                new_row.push_back(image->at(column,row));   //set the values of the new row
            }
            new_image_matrix.push_back(new_row);    //adds the new row to the new matrix
        }
        (*image) = Image(w,h,new_image_matrix);     // change the original image
    }
    
    void Script::rotate_left()
    {
        int w = image->width();
        int h = image->height();
        Image* image_test = new Image(h, w);    //define the rotated image with only its dimensions
        Color copy;
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                    copy = image->at(x, y);     //take a pixel of the original image
                    int o = w - 1 - x;          //calculate the new y position of the pixel
                    int p = y;                  //calculate the new x position of the pixel
                    image_test->at(p,o) = copy; //put the pixel in its rotated position in the rotated image
            }   
        }
        *image = *image_test;   //change image
        delete image_test;
    }
    
    void Script::rotate_right()
    {
        int original_height = image->height();
        int original_width  = image->width();

        vector<vector<Color>> rotated_image_matrix; //define rotated image matrix
        for (int column = 0; column < original_width; column++)
        {
            vector<Color> new_row(original_height); //define new row of the matrix with original_height length
            int position_in_new_row = 0;
            for (int row = original_height - 1; row >= 0; row--)    //due to the propreties of a rotation a row of the new matrix is defined as the equivelent column from the original matrix backwards
            {
                new_row[position_in_new_row] = image->at(column,row);   //fill the new row with its values from the original image
                position_in_new_row++;
            }
            rotated_image_matrix.push_back(new_row);    //add the new row to the new matrix
        }
        (*image) = Image(original_height, original_width, rotated_image_matrix); //change the original Image
        // In a rotation the height and width must exchange values
    }
    
    vector<Color> get_nearby_pixels(int &column, int &row, int &ws, Image* image)
        //auxiliary function to median_filter, it gets the pixels that are in the square of side ws around a space
    {
        vector<Color> nearby_pixels;
        int initial_row = max(0, row - (ws / 2));                       //get smallest y value of the pixels that are in the square of side ws
        int final_row = min(image->height() - 1, row + (ws / 2));       //get biggest y value of the pixels that are in the square of side ws
        int initial_column = max(0, column - (ws / 2));                 //get smallest x value of the pixels that are in the square of side ws
        int final_column = min(image->width() - 1, column + (ws / 2));  //get biggest x value of the pixels that are in the square of side ws

        for (int nearby_row = initial_row; nearby_row <= final_row; nearby_row++)
        {
            for (int nearby_column = initial_column; nearby_column <= final_column; nearby_column++)
            {
                nearby_pixels.push_back(image->at(nearby_column,nearby_row));    // get colors that are within the ws square with center in Pixel(column,row)
            }
        }
        return nearby_pixels;
    }

    Color median_of_nearby_pixels (vector<Color> nearby_pixels )
        //auxiliary function to median_filter, it calculates the median of a group of Colors
    {
        vector<rgb_value> new_red;      //new_red will colect the red values of the pixels within the square of side ws
        vector<rgb_value> new_green;    //new_green will colect the green values of the pixels within the square of side ws
        vector<rgb_value> new_blue;     //new_blue will colect the blue values of the pixels within the square of side ws
        size_t s = nearby_pixels.size();
        for (size_t pos = 0 ; pos<s ; pos++)
        {
            new_red.push_back(nearby_pixels[pos].red());        //fill the vector new_red
            new_green.push_back(nearby_pixels[pos].green());    //fill the vector new_green
            new_blue.push_back(nearby_pixels[pos].blue());      //fill the vector new_blue
        }
        sort(new_red.begin(),new_red.end());    //sort the values of red from the nearby pixels
        sort(new_green.begin(),new_green.end()); //sort the values of green from the nearby pixels
        sort(new_blue.begin(),new_blue.end());  //sort the values of blue from the nearby pixels

         size_t median_space = new_red.size() / 2; //position of the element in the middle of every vector (because they all have the same size)
        if (new_red.size() % 2 == 0)
        {
            return Color( (new_red[median_space] + new_red[median_space-1]) / 2,
                         (new_green[median_space] + new_green[median_space-1]) / 2,
                         (new_blue[median_space] + new_blue[median_space-1]) / 2);  //return the median when there are an even number of nearby pixels
        }

        return Color(new_red[median_space],new_green[median_space],new_blue[median_space]); //return the median when there are an odd number of nearby pixels

    }

    void Script::median_filter(int ws)
    {
        
        int original_height = image->height();
        int original_width  = image->width();
        //we can't alter the original image directly since it would change the result of get_nearby_pixels
        Image* new_image = new Image(original_width, original_height);  //make an image where we will store the pixels after median_filter
        for (int row = 0; row < original_height; row++)
        {
            for (int column = 0; column < original_width; column++)
            {
            vector<Color> nearby_pixels = get_nearby_pixels(column, row, ws, image);    //find the pixels that are within the square of side ws
            new_image->at(column,row) = median_of_nearby_pixels(nearby_pixels);         //add in the new_image the pixel of the original after median filter
            }
        }
        *image = *new_image;    //change to value of image it's median filter counterpart
        delete new_image;       //prevent a memory leak
    }
}
