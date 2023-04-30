#include "Image.hpp"
#include "Color.hpp"
#include <iostream>
using namespace std;


namespace prog
{
  //constructor
  Image::Image(int w, int h, const Color &fill)
  {
    _width  = w;
    _height = h;
    vector<Color> new_row(_width, fill); //define the row
    for(int row = 0; row < _height ; row++)
    {
      image_matrix.push_back(new_row); //fill the matrix row by row
    }
  }
  //unused destructor
  Image::~Image()
  {
  }

  //get with
  int Image::width() const
  {
    return _width;
  }

  //get height
  int Image::height() const
  {
    return _height;
  }

  //get reference to a pixel (braks encapsulation)
  Color& Image:: at(int x, int y)
  {
    return image_matrix[y][x]; 
    //the matrix is defined row by row therefore the 'Y' is used as index before 'X'
  }

  //get values of a pixel 
  const Color& Image::at(int x, int y) const
  {
    return image_matrix[y][x];
    //the matrix is defined row by row therefore the 'Y' is used as index before 'X'
  }
}
