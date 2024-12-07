#pragma once

#include <string>
#include <vector>

namespace aoc_util 
{
    std::vector<std::vector<int>> read_puzzle_input(std::string filePath);

    std::vector<std::string> read_puzzle_input_string(std::string filePath); 

    std::vector<std::vector<char>> read_puzzle_input_char(std::string filePath); 

    std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> in);

    void bubble_sort(std::vector<int> &in);

    void print_vector(std::vector<int> &array);

    std::vector<int> split_string(std::string line, const char delimiter);

    std::vector<long long> read_all_numbers(std::string line);
}
