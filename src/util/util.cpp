#include "util.h"

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

// todo: look at making a matrix class
namespace aoc_util 
{
    std::vector<std::vector<int>> read_puzzle_input(std::string filePath) 
    {
        std::ifstream file(filePath);
        std::string str;
        std::string currentChar = "";
        std::vector<std::vector<int>> puzzle_input;

        while (std::getline(file, str))
        {
            bool last_character_digit = true;
            std::vector<int> current_line;

            for (auto &ch : str)
            {
                if (isdigit(ch))
                {

                    currentChar += ch;
                    last_character_digit = true;
                }
                else if (last_character_digit)
                {

                    current_line.push_back(stoi(currentChar));
                    currentChar = "";
                    last_character_digit = false;
                } 
                else 
                {
                    last_character_digit = false;
                }


            }

            current_line.push_back(stoi(currentChar));
            puzzle_input.push_back(current_line);
            currentChar = "";
        }

        return puzzle_input;
    }

    std::vector<std::string> read_puzzle_input_string(std::string filePath) 
    {
        std::ifstream file(filePath);
        std::string str;
        std::string currentChar = "";
        std::vector<std::string> puzzle_input;

        while (std::getline(file, str))
        {
            puzzle_input.push_back(str);
        }

        return puzzle_input;
    }

    std::vector<std::vector<char>> read_puzzle_input_char(std::string filePath) 
    {
        std::ifstream file(filePath);
        std::string str;
        std::vector<std::vector<char>> puzzle_input;

        while (std::getline(file, str))
        {
            std::vector<char> current_line;

            for (auto &ch : str)
            {
                current_line.push_back(ch);
            }

            puzzle_input.push_back(current_line);
        }

        return puzzle_input;
    }

    // Todo: use pointers in the future
    std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> in)
    {
        std::vector<std::vector<int>> transpose_in;
        int x = in.front().size();
        int y = in.size();

        for (int px = 0; px < x; px++) 
        {
            std::vector<int> x_in;

            for (int py = 0; py < y; py++)
            {
                x_in.push_back(in.at(py).at(px));
            }

            transpose_in.push_back(x_in);
        }

        return transpose_in;
    }

    void bubble_sort(std::vector<int> &in) 
    {
        int n = in.size();

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (in[j] > in[j + 1])
                {
                    int temp = in[j];
                    in[j] = in[j + 1];
                    in[j + 1] = temp;
                }
            }
        }

    }

    void print_vector(std::vector<int> &array) {
        for (unsigned int i = 0; i < array.size(); ++i) {
            std::cout << "  " << array[i];
        }
        std::cout << "\n";
    }

    std::vector<int> split_string(std::string line_in, const char delimiter)
    {
        std::string line = line_in;
        unsigned int next_delimiter_pos;
        unsigned int prev_delimiter_pos = 0;
        std::vector<int> output;

        do 
        {
            next_delimiter_pos = line.find(delimiter);
            output.push_back(std::stoi(line.substr(prev_delimiter_pos, next_delimiter_pos)));
            line = line.substr(next_delimiter_pos+1, line.size());

        } while (next_delimiter_pos <= line.size());



        return output;
    }

    std::vector<long long> read_all_numbers(std::string line)
    {
        std::vector<long long> ret;
        std::stringstream ss;
        
        ss << line;

        std::string temp;

        long long found;

        while (!ss.eof())
        {
            ss >> temp;

            if (std::stringstream(temp) >> found)
            {
                ret.push_back(found);
            }

            temp = "";
        }

        return ret;
    }
}