#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include <iostream>
#include "Color.hpp"
#include <vector>
using namespace std;

namespace prog
{
  class Image
  {
  private:
    int _width, _height;
    vector<vector <Color>> image_matrix;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    Image(int w, int h, const vector<vector <Color>> manual_image);
    ~Image();                                                 
    int width() const;                                        
    int height() const;                                       
    Color &at(int x, int y);                                  
    const Color &at(int x, int y) const;
    vector<Color>& get_row(int position_of__row);
  };
}
#endif
