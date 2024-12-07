#include "day06.h"
#include "../util/util.h"
#include "grid.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>


namespace day06
{
    void partOne(std::string puzzle_input_in)
    {
        std::vector<std::vector<char>> puzzle_input = aoc_util::read_puzzle_input_char(puzzle_input_in);
        day06::Grid grid(puzzle_input);

        while(grid.step()) {}

        std::cout << "Number of unique positions: " << grid.num_positions() << std::endl;

    }

    void partTwo(std::string puzzle_input_in)
    {
        std::vector<std::vector<char>> puzzle_input = aoc_util::read_puzzle_input_char(puzzle_input_in);
        int sum = 0;

        // solve puzzle to work out where the obsticals can be placed
        day06::Grid grid(puzzle_input);
        std::vector<int> starting_position = grid.get_current_position();

        while(grid.step()) {}

        std::set<std::vector<int>> all_visited_positions = grid.get_visited_positions();
        all_visited_positions.erase(starting_position);

        // loop through placing obsticals and determine if an infinate path is created - brute force
        for (auto &new_obstical : all_visited_positions)
        {
            day06::Grid temp(puzzle_input, new_obstical[0], new_obstical[1]);
            std::vector<int> curr_pos = temp.get_current_position();

            while(temp.step() && !temp.has_visited()) {}

            if (temp.has_visited())
            {
                sum++;
            }
        }

        std::cout << "Number of obsticals that can be placed to cause infinite path: " << sum << std::endl;
    }
}