#include "Image.hpp"
#include "Color.hpp"
#include <iostream>
using namespace std;


namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    _width  = w;  // define the width of the matrix (basically is the number of columns)
    _height = h;  // define the height of the matrix (basically is the number of rows)

    for(int row = 0; row < _height ; row++)
    {
      vector<Color> new_row(_width, fill);  // defines a new row that will be added to the final matrix below
      image_matrix.push_back(new_row);  // adds the previous row to the end of the matrix with the push.back function 

    }
  }
  
  Image::Image(int w, int h, const vector<vector<Color>> manual_image)
  {
    _width = w; // define the width of the matrix (basically is the number of columns)
    _height = h;  // define the height of the matrix (basically is the number of rows)
    image_matrix = manual_image;  //defines the image with an already defined matrix
  }
  
  
  Image::~Image()
  {
    // unused destructor
  }


  int Image::width() const
  {
    return _width;  // gets the width of the matrix returning it
  }

  int Image::height() const
  {
    return _height; // gets the height of the matrix returning it
  }

  Color& Image:: at(int x, int y)
  {
    return image_matrix[y][x];  // references the (x, y) pixel of the matrix 
  }

    const Color& Image::at(int x, int y) const
  {
    return image_matrix[y][x];  // returns the value present on the (x, y) matrix coordinate, a pixel
  }
  
    vector<Color>& Image::get_row(int position_of__row)
  {
    return image_matrix[position_of__row];  // return a specified row of the matrix
  }
} 
