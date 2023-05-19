#include "XPM2.hpp"
#include "Script.hpp"
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <algorithm>

namespace prog {

    void upper_case( string& hexadecimal_color_string)
    //auxiliar function of hexavalue_to_rgb
    {
        for ( char &digit : hexadecimal_color_string)
        {
            if ((digit >= 'a') && (digit <= 'f'))
            {
                digit = 'A' + (digit-'a');  //turn every letter to its upper case counterpart
            }
        }
    }


    rgb_value hexavalue_to_rgb(string hexaColor)
    //return the rgb_value represented by hexaColor
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
        char_to_int['A']=10;
        char_to_int['B']=11;
        char_to_int['C']=12;
        char_to_int['D']=13;
        char_to_int['E']=14;
        char_to_int['F']=15;
        upper_case(hexaColor);  //in order to include upper and lower case letters turns every letter in hexaColor to upper case 
        rgb_value color = char_to_int[ (hexaColor[0])];
        color *= 16;
        color += char_to_int[ (hexaColor[1])];
        return color;
    }

    Color Hexavalue_to_Color(string hexaColors)
    {
        string Numbers_of_Red = hexaColors.substr(0,2);     //seperate the string that represent the red value
        string Numbers_of_Green = hexaColors.substr(2,2);   //seperate the string that represent the green value
        string Numbers_of_Blue = hexaColors.substr(4,2);    //seperate the string that represent the blue value
        return Color(hexavalue_to_rgb(Numbers_of_Red),hexavalue_to_rgb(Numbers_of_Green),hexavalue_to_rgb(Numbers_of_Blue));    //return the Color represented by Number_of_Red, Number_of_Green, Number_of_Blue
    }

    Image* loadFromXPM2(const std::string& file) {
        vector<vector<Color >> new_image_matrix;
        ifstream input (file);
        string line_of_header;
        getline(input,line_of_header);  //ignore the !XPM2 line
        getline(input,line_of_header);  //get line with the size and number of colors information
        int width, height, number_of_colors;    //the number of chars per color is contant so it's not stored in any variable
        stringstream(line_of_header) >> width >> height >> number_of_colors;
        std::map<char,Color> maping_of_colors;
        for (int define_color = 0; define_color < number_of_colors; define_color++)
        {
            getline(input, line_of_header);
            char char_of_color; char is_it_a_color; string hexadecimal_Color;   //the is_it_a_color variable is ignored but it could be used to know what information is in the line being read  
            stringstream(line_of_header) >> char_of_color >> is_it_a_color >> hexadecimal_Color;

            maping_of_colors[char_of_color] = Hexavalue_to_Color(hexadecimal_Color.substr(1,6));    //associate the character to its equivelent Color
                                                                                                    //substr(1,6) is used in order to ignore the '#' simbol
        }

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
       
        Image *img = new Image(width,height,new_image_matrix);
        return img;
    }

    vector<Color> get_different_colors(const Image* image)
        //return a vector with the different colors in image 
    {
        vector<Color> colors_in_the_image;  // define a vector that will store every different color in the image
        int height = image->height();
        int width = image->width();
        for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < width; column++)
            {
                if (find(colors_in_the_image.begin(), colors_in_the_image.end(), image->at(column,row)) == colors_in_the_image.end() )
                {
                    colors_in_the_image.push_back(image->at(column,row));   //if the color in position (column, row) is't in colors_in_the_image add it 
                }
            }
        }
        return colors_in_the_image;
    }

    string rgb_value_to_hexadecimal(rgb_value rgb)
        //turn a rgb_value to it's corresponding string in hexadecimal
        //only 2 chars are nedded to represent rgb in hexadecimal since it won't be bigger that 255
    {
        string hexadecimal_rgb_value;
        int remainder = rgb % 16;   //calculate the second char using %16, it will be put in the first position of the string
        if (remainder < 10)
        {
            hexadecimal_rgb_value.push_back('0' + remainder);   //used if second char is a number 
        }
        else
        {
            hexadecimal_rgb_value.push_back('7' + remainder );  //used if second char is a letter
        }
        rgb /= 16;
        remainder = rgb % 16;      //calculate the first char using %16, it will be put in the second position of the string
        if (remainder < 10)
        {
            hexadecimal_rgb_value.push_back('0' + remainder);   //used if second char is a number
        }
        else
        {
            hexadecimal_rgb_value.push_back('7' + remainder );  //used if second char is a letter
        }
        reverse(hexadecimal_rgb_value.begin(), hexadecimal_rgb_value.end());    //reverses the string so that the second and first character will be in the correct position
        return hexadecimal_rgb_value;
    }
    string Color_to_hexadecimal(Color color)
        //turn a Color to it's string in hexadecimal
    {
        string hexadecimal_color = "#";
        hexadecimal_color += rgb_value_to_hexadecimal(color.red());     //add the chars for red to hexadecimal_color
        hexadecimal_color += rgb_value_to_hexadecimal(color.green());   //add the chars for green to hexadecimal_color
        hexadecimal_color += rgb_value_to_hexadecimal(color.blue());    //add the chars for blue to hexadecimal_color
        return hexadecimal_color;
    }

char find_correspondent_char(Color color,vector<pair<Color, char>> Color_to_char )
    //find the character that correspons to a given Color
{
    for (pair<Color, char> pair : Color_to_char)
    {
        if (pair.first == color){
            return pair.second;
        }
    }
    return '\0';
}

    void saveToXPM2(const std::string& file, const Image* image) 
    {
        ofstream output_file(file);
        output_file << "! XPM2" << '\n';
        vector<Color> colors_in_the_image = get_different_colors(image);    //get all different colors in a image   
        int width = image->width(); int height = image->height();
        int number_different_colors = colors_in_the_image.size();           //get number of different colors in a image
        output_file << width << " " << height << " " << number_different_colors << " 1" << '\n';    //write the line with the image dimensions and number of colors
        vector<pair<Color, char>> Color_to_char;    //Vector containing pair with a Color and it's corresponding char
        for (int number_of_color = 0; number_of_color < number_different_colors;number_of_color++ )
        {
            char temp_simbol = ('A' + number_of_color); //calculate the simbol that will represent a Color
            output_file << temp_simbol << " c " << (Color_to_hexadecimal(colors_in_the_image[number_of_color])) << '\n';    //write a line of the corresponding char and it's Color
            Color_to_char.push_back( {colors_in_the_image[number_of_color], temp_simbol} );
        }
        for (int row = 0; row < height; row++ )
        {
            for (int column = 0; column < width; column++)
            {
            output_file << find_correspondent_char(image->at(column, row), Color_to_char);  //write the line of chars that represent the matrix of the image
            }
            output_file << '\n';
        }

    }
}
