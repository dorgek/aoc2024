#include "day05.h"
#include "../util/util.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>

const char DELIMITER = '|';

// process ordering instructions
std::map<int, std::set<int>> process_instructions_list(const std::vector<std::string> &puzzle_input_in)
{
    std::map<int, std::set<int>> processed_instructions;

    for (auto &line : puzzle_input_in)
    {
        if (line.empty())
        {
            break;
        }

        int num_one = std::stoi(line.substr(0, line.find(DELIMITER)));
        int num_two = std::stoi(line.substr(line.find(DELIMITER) + 1, line.size()));

        processed_instructions[num_one].insert(num_two);
    }

    return processed_instructions;
}

// process update orders
std::vector<std::vector<int>> process_update_order(const std::vector<std::string> &puzzle_input_in)
{
    std::vector<std::vector<int>> update_order;

    for (size_t i = puzzle_input_in.size(); i--;)
    {
        if (puzzle_input_in[i].empty())
        {
            break;
        }

        std::vector<int> update_order_line = aoc_util::split_string(puzzle_input_in[i], ',');

        update_order.push_back(update_order_line);
    }

    return update_order;
}

bool check_rule(const std::vector<int> &update_order, std::map<int, std::set<int>> &instructions)
{
    for (auto i = update_order.size() - 1; i > 0; i--)
    {
        
        for (int j = i - 1; j >= 0; j--)
        {
            if (instructions[update_order[i]].count(update_order[j]) == 1)
            {
                // invalid
                return false;
            }
        }
    }

    return true;
}

bool fix_update_rule(std::vector<int> &update_order, std::map<int, std::set<int>> &instructions)
{
    bool rule_invalid = false;

    for (auto i = update_order.size() - 1; i > 0; i--)
    {
        
        for (int j = i - 1; j >= 0; j--)
        {
            if (instructions[update_order[i]].count(update_order[j]) == 1)
            {
                // swap numbers and return
                int temp = update_order[i];
                update_order[i] = update_order[j];
                update_order[j] = temp;
                rule_invalid = true;
            }
        }
    }   

    return !rule_invalid;
}


namespace day05
{
    void partOne(std::string puzzle_input_in)
    {
        std::vector<std::string> puzzle_input = aoc_util::read_puzzle_input_string(puzzle_input_in);

        std::map<int, std::set<int>> instructions = process_instructions_list(puzzle_input);
        std::vector<std::vector<int>> update_orders = process_update_order(puzzle_input);
        int sum = 0;

        for (auto &update_order : update_orders)
        {
            if (check_rule(update_order, instructions))
            {
                // find the middle number
                int middle_number = ceil(update_order.size() / 2);
                sum += update_order[middle_number];
            }
        }

        std::cout << "Sum of the middle number of all correct rules is: " << sum << std::endl;
    }

    void partTwo(std::string puzzle_input_in)
    {
        std::vector<std::string> puzzle_input = aoc_util::read_puzzle_input_string(puzzle_input_in);

        std::map<int, std::set<int>> instructions = process_instructions_list(puzzle_input);
        std::vector<std::vector<int>> update_orders = process_update_order(puzzle_input);
        int sum = 0;

        for (auto &update_order : update_orders)
        {
            if (!check_rule(update_order, instructions))
            {
                // try and order the rules
                while (!fix_update_rule(update_order, instructions)) {} // probably optimise later but brute force it for now

                int middle_number = ceil(update_order.size() / 2);
                sum += update_order[middle_number];
            }
        }

        std::cout << "Sum of the middle number of all incorrect rules is: " << sum << std::endl;
    }
}