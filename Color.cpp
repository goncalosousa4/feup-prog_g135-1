#include "Color.hpp"

namespace prog {
    //constructors
    Color::Color() 
        {
         //set RGB to black (0,0,0)
         _red=0;
        _green=0;
        _blue=0;
        }
    Color::Color(const Color& other) 
        {
        //copy constructor
        this->_red=other._red;
        this->_green=other._green;
        this->_blue=other._blue;
        }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) 
        {
        //constructer with specified values
        _red = red;
        _green = green;
        _blue = blue;
        }

    // get member values
    rgb_value Color::red() const
        {
        //get current red
        return _red;
        }
    rgb_value& Color::red()
        {
        //get mutable red (breaks encapsulation)
        return _red;
        }
        

    rgb_value Color::green() const 
        {
        //get current green
        return _green;
        }
    rgb_value& Color::green()
        {
        //get mutable green (breaks encapsulation)
        return _green;
        }


    rgb_value Color::blue() const 
        {
        //get current blue
        return _blue;
        }

    rgb_value& Color::blue()
        {
        //get mutable blue (breaks encapsulation)
        return _blue;
        }


/*
    // TODO: remove this DUMMY variable once you have appropriate fields for representing colors.
    rgb_value DUMMY_rgb_value = 0; 

    rgb_value& Color::red()  {
        return DUMMY_rgb_value;
    }
    rgb_value& Color::green()  {
      return DUMMY_rgb_value;
    }
    rgb_value& Color::blue()  {
      return DUMMY_rgb_value;
    }
    */
}
