#include "day04.h"
#include "../util/util.h"

#include <iostream>
#include <string>
#include <vector>
#include <regex>

const char SEARCH[4] = {'X', 'M', 'A', 'S'};
const char SEARCH_TWO[3] = {'M', 'A', 'S'};

const int POSITION_VECTORS[8][3][2] = {
    {{1, 0},   {2, 0},   {3, 0}},
    {{-1, 0},  {-2, 0},  {-3, 0}},
    {{0, 1},   {0, 2},   {0, 3}},
    {{0, -1},  {0, -2},  {0, -3}},
    {{1, 1},   {2, 2},   {3, 3}},
    {{1, -1},  {2, -2},  {3, -3}},
    {{-1, 1},  {-2, 2},  {-3, 3}},
    {{-1, -1}, {-2, -2}, {-3, -3}}
};

const int POSITION_VECTORS_TWO_ONE[2][3][2] = {
    {{-1, -1},   {0, 0},   {1, 1}},
    {{1, 1},  {0, 0},  {-1, -1}}
};

const int POSITION_VECTORS_TWO_TWO[2][3][2] = {
    {{1, -1},   {0, 0},   {-1, 1}},
    {{-1, 1},  {0, 0},  {1, -1}}
};


int find_search_pattern(const std::vector<std::vector<char>> &input, unsigned int x_in, unsigned int y_in, const char search[], int search_start_idx, const int position_vectors_in[][3][2], unsigned int pos_size)
{
    unsigned int x_max = input.front().size();
    unsigned int y_max = input.size();
    int matches_found = 0;

    for (unsigned int i = 0; i < pos_size; i++)
    {
        // int position[3][2] = position_vectors_in[i];
        int search_position = search_start_idx;
        bool found = true;

        // loop through indexes to work out if a pattern is found
        for (auto &vector : position_vectors_in[i])
        {
            unsigned int x = x_in + vector[0];
            unsigned int y = y_in + vector[1];

            if (x >= x_max || y >= y_max)
            {
                found = false;
                break;
            }

            if (input[y][x] != search[search_position++])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            matches_found++;
        }
    }

    return matches_found;

}

namespace day04
{
    void partOne(std::string puzzle_input_in)
    {
        std::vector<std::vector<char>> puzzle_input = aoc_util::read_puzzle_input_char(puzzle_input_in);
        unsigned int x_max = puzzle_input.front().size();
        unsigned int y_max = puzzle_input.size();

        int sum = 0;

        for (unsigned int x = 0; x < x_max; x++)
        {
            for (unsigned int y = 0; y < y_max; y++)
            {
                if (puzzle_input[y][x] == SEARCH[0])
                {
                    sum += find_search_pattern(puzzle_input, x, y, SEARCH, 1, POSITION_VECTORS, 8);
                }
            }
        }

        std::cout << "Number of matches for XMAS found: " << sum << std::endl;
    }

    void partTwo(std::string puzzle_input_in)
    {
        std::vector<std::vector<char>> puzzle_input = aoc_util::read_puzzle_input_char(puzzle_input_in);
        unsigned int x_max = puzzle_input.front().size();
        unsigned int y_max = puzzle_input.size();

        int sum = 0;

        for (unsigned int x = 0; x < x_max; x++)
        {
            for (unsigned int y = 0; y < y_max; y++)
            {
                if (puzzle_input[y][x] == SEARCH_TWO[1])
                {
                    if (find_search_pattern(puzzle_input, x, y, SEARCH_TWO, 0, POSITION_VECTORS_TWO_ONE, 2) > 0 && 
                        find_search_pattern(puzzle_input, x, y, SEARCH_TWO, 0, POSITION_VECTORS_TWO_TWO, 2) > 0)
                    {
                        sum++;
                    }
                }
            }
        }

        std::cout << "Number of matches for X-MAS found: " << sum << std::endl;
    }
}