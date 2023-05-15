#include "XPM2.hpp"

namespace prog {
#include "XPM2.hpp"
#include <fstream>
#include <sstream>
#include <map>


namespace prog {
    rgb_value hexavalue_to_rgb(string hexaColor)
    {
        std::map<char,int> char_to_int;
        char_to_int['0']=0;
        char_to_int['1']=1;
        char_to_int['2']=2;
        char_to_int['3']=3;
        char_to_int['4']=4;
        char_to_int['5']=5;
        char_to_int['6']=6;
        char_to_int['7']=7;
        char_to_int['8']=8;
        char_to_int['9']=9;
        char_to_int['a']=10;
        char_to_int['b']=11;
        char_to_int['c']=12;
        char_to_int['d']=13;
        char_to_int['e']=14;
        char_to_int['f']=15;

        rgb_value color = char_to_int[hexaColor[0]];
        color *= 16;
        color += char_to_int[hexaColor[1]];
        return color;
    }


    Color Hexavalue_to_Color(string hexaColors)
    {
        string Numbers_of_Red = hexaColors.substr(0,2);
        string Numbers_of_Green = hexaColors.substr(2,2);
        string Numbers_of_Blue = hexaColors.substr(4,2);
        return Color(hexavalue_to_rgb(Numbers_of_Red),hexavalue_to_rgb(Numbers_of_Green),hexavalue_to_rgb(Numbers_of_Blue));
    }
    Image* loadFromXPM2(const std::string& file) {
        ifstream input (file);
        string line_of_heather;
        std::getline(input,line_of_heather);
        getline(input,line_of_heather);
        int width, height, number_of_colors;
        stringstream(line_of_heather) >> width;
        stringstream(line_of_heather) >> height;
        stringstream(line_of_heather) >> number_of_colors;

        std::map<char,Color> maping_of_colors;
        for (int define_color = 0; define_color < number_of_colors; define_color++)
        {
            getline(input, line_of_heather);
            char char_of_color;
            string hexadecimal_Color;
            string is_it_a_color;
            stringstream(line_of_heather) >> char_of_color;
            stringstream(line_of_heather) >> is_it_a_color;
            stringstream(line_of_heather) >> hexadecimal_Color;
            maping_of_colors[char_of_color] = Hexavalue_to_Color(hexadecimal_Color.substr(1,6));
        }

        vector<vector<Color>> new_image_matrix;
        string matrix_line;
        for (int row = 0; row < height; row++)
        {
            vector<Color> new_row;
            getline(input, matrix_line);
            for (char simbol : matrix_line)
            {
                new_row.push_back(maping_of_colors[simbol]);
            }
            new_image_matrix.push_back(new_row);
        }
        static Image *img;
        *img = Image(width,height,new_image_matrix);
        return img;
    }
        

    void saveToXPM2(const std::string& file, const Image* image) {

    }
}
