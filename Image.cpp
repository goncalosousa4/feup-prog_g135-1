#include "Image.hpp"
#include <iostream>
using namespace std;


namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    _width=w;
    _height=h;
    Color used_fill = fill;
    for(int row = 0; row < h ; row++){
      image_matrix.push_back(vector<Color>());
      for(int collum = 0; collum < w ;collum++){
        image_matrix[row].push_back(used_fill);
      }
    }
  }
  Image::~Image(){
  }
  int Image::width() const
  {
    return _width;
  }
  int Image::height() const
  {
    return _height;
  }
    Color &Image::at(int x, int y)
  {
    return image_matrix[y][x];
  }

  const Color &Image::at(int x, int y) const
  {
    return image_matrix[y][x];
  }

}
