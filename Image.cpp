#include "Image.hpp"
#include "Color.hpp"
#include <iostream>
using namespace std;


namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    _width  = w;
    _height = h;

    for(int row = 0; row < _height ; row++)
    {
      vector<Color> new_row(_width, fill);
      image_matrix.push_back(new_row);

    }
  }

  Image::~Image()
  {
  }

  int Image::width() const
  {
    return _width;
  }

  int Image::height() const
  {
    return _height;
  }

  Color& Image:: at(int x, int y)
  {
    return image_matrix[y][x];
  }

    const Color& Image::at(int x, int y) const
  {
    return image_matrix[y][x];
  }
}
