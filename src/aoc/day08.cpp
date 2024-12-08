#include "day08.h"
#include "../util/util.h"
#include "grid.h"
#include "bits/stdc++.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>

std::map<char, std::vector<std::vector<unsigned int>>> find_signal_locations(const std::vector<std::vector<char>> &puzzle_input)
{
    std::map<char, std::vector<std::vector<unsigned int>>> antenna_locations;

    for (unsigned int y = 0; y < puzzle_input.size(); y++)
    {
        for (unsigned int x = 0; x < puzzle_input[0].size(); x++)
        {
            if (puzzle_input[y][x] != '.')
            {
                antenna_locations[puzzle_input[y][x]].push_back({x, y});
            }
        }
    }

    return antenna_locations;
}

std::set<std::vector<unsigned int>> determine_antinode_locations(const std::vector<std::vector<unsigned int>> &antenna, unsigned int max_x, unsigned int max_y, bool reasonant_harmonics)
{
    std::set<std::vector<unsigned int>> antinode_locations;

    for (unsigned int i = 0; i < antenna.size() - 1; i++)
    {
        for (unsigned int j = i + 1; j < antenna.size(); j++)
        {
            int x_vector = antenna[i][0] - antenna[j][0];
            int y_vector = antenna[i][1] - antenna[j][1];

            int gcd = std::gcd(x_vector, y_vector); // always 1           
            bool caclulate_antinode_one = reasonant_harmonics;
            bool caclulate_antinode_two = reasonant_harmonics;
            int node_one_x = antenna[i][0];
            int node_one_y = antenna[i][1];
            int node_two_x = antenna[j][0];
            int node_two_y = antenna[j][1];

            // current position of node will create resonant frequency
            if (reasonant_harmonics)
            {
                antinode_locations.insert({antenna[i][0], antenna[i][1]});
                antinode_locations.insert({antenna[j][0], antenna[j][1]});
            }

            do 
            {
                int antinode_one_x = node_one_x + x_vector / gcd; 
                int antinode_one_y = node_one_y + y_vector / gcd;

                if (antinode_one_x >= 0 && (unsigned int)antinode_one_x < max_x && antinode_one_y >= 0 && (unsigned int)antinode_one_y < max_y)
                {
                    antinode_locations.insert({(unsigned int)antinode_one_x, (unsigned int)antinode_one_y});
                    node_one_x = antinode_one_x;
                    node_one_y = antinode_one_y;
                } 
                else 
                {
                    caclulate_antinode_one = false;
                }
            } while(caclulate_antinode_one);

            do 
            {
                int antinode_two_x = node_two_x - x_vector / gcd; 
                int antinode_two_y = node_two_y - y_vector / gcd;

                if (antinode_two_x >= 0 && (unsigned int)antinode_two_x < max_x && antinode_two_y >= 0 && (unsigned int)antinode_two_y < max_y)
                {
                    antinode_locations.insert({(unsigned int)antinode_two_x, (unsigned int)antinode_two_y});
                    node_two_x = antinode_two_x;
                    node_two_y = antinode_two_y;
                }
                else 
                {
                    caclulate_antinode_two = false;
                }
            } while (caclulate_antinode_two);
        }
    }

    return antinode_locations;
}

namespace day08
{
    void partOne(std::string puzzle_input_in)
    {
        std::vector<std::vector<char>> puzzle_input = aoc_util::read_puzzle_input_char(puzzle_input_in);
        std::map<char, std::vector<std::vector<unsigned int>>> antenna_locations = find_signal_locations(puzzle_input);
        std::set<std::vector<unsigned int>> antinode_locations;

        for (auto & [key, val] : antenna_locations)
        {
            std::set<std::vector<unsigned int>> temp = determine_antinode_locations(val, puzzle_input[0].size(), puzzle_input.size(), false);
            antinode_locations.insert(temp.begin(), temp.end());
        }

        std::cout << "Total number of unique antinode locations are: " << antinode_locations.size() << std::endl;
    }

    void partTwo(std::string puzzle_input_in)
    {
        std::vector<std::vector<char>> puzzle_input = aoc_util::read_puzzle_input_char(puzzle_input_in);
        std::map<char, std::vector<std::vector<unsigned int>>> antenna_locations = find_signal_locations(puzzle_input);
        std::set<std::vector<unsigned int>> antinode_locations;

        for (auto & [key, val] : antenna_locations)
        {
            std::set<std::vector<unsigned int>> temp = determine_antinode_locations(val, puzzle_input[0].size(), puzzle_input.size(), true);
            antinode_locations.insert(temp.begin(), temp.end());
        }

        std::cout << "Total number of unique antinode locations with resonants are: " << antinode_locations.size() << std::endl;
    }
}