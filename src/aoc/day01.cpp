#include "day01.h"
#include "../util/util.h"

#include <iostream>
#include <cmath>
#include <string>

int count_iterations(const std::vector<int> &in_v, int in)
{
    int count = 0;

    for (unsigned int i = 0; i < in_v.size(); i++)
    {
        if (in_v[i] == in)
        {
            count ++;
        }
    }

    return count;
}

namespace day01
{
    void partOne(std::string puzzle_input_in)
    {
        int total_distance = 0;

        std::vector<std::vector<int>> puzzle_input = aoc_util::read_puzzle_input(puzzle_input_in);
        std::vector<std::vector<int>> transpose_input = aoc_util::transpose(puzzle_input);

        for (unsigned int i = 0; i < transpose_input.size(); i++)
        {
            aoc_util::bubble_sort(transpose_input.at(i));
        }

        // get sum of diff in all pairs
        for (unsigned int i = 0; i < transpose_input.front().size(); i++)
        {
            total_distance += abs(transpose_input.at(0).at(i) - transpose_input.at(1).at(i));
        }

        std::cout << "Total distance between points: " << total_distance << std::endl;
    }

    void partTwo(std::string puzzle_input_in)
    {
        int similarity_score = 0;

        std::vector<std::vector<int>> puzzle_input = aoc_util::read_puzzle_input(puzzle_input_in);
        std::vector<std::vector<int>> transpose_input = aoc_util::transpose(puzzle_input);

        for (unsigned int i = 0; i < transpose_input.front().size(); i++)
        {
            similarity_score += transpose_input.at(0).at(i) * count_iterations(transpose_input.at(1), transpose_input.at(0).at(i));
        }

        std::cout << "Similarity score is: " << similarity_score << std::endl;
    }
}

