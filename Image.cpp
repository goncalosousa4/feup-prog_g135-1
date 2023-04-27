#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    _width=w;
    _height=h;
    Color used_fill;
    used_fill.Color(fill)
    for (int row=0;row<h ;row++){
      for(int collum=0; collum<w ;collum++){
        image_matrix.push_back(used_fill);
      }
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

  // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
  Color DUMMY_color;

  Color& Image::at(int x, int y)
  {
    return DUMMY_color;
  }

  const Color& Image::at(int x, int y) const
  {
    return DUMMY_color;
  }
}
