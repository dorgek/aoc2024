#include "day07.h"
#include "../util/util.h"
#include "grid.h"
#include "bits/stdc++.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const char DELIMITER = ':';

std::vector<std::vector<int>> get_next_permutation_batch(int n, bool extra_operation, const std::vector<int> &prev_permutation)
{
    int overflow = (extra_operation) ? 3 : 2;
    std::vector<std::vector<int>> all_permutations;
    std::vector<int> operation(prev_permutation);

    for (size_t j = n; j--;)
    {
        int temp = operation[j] + 1;

        if (temp != overflow)
        {
            operation[j] = temp;
            break;
        }
        else
        {
            operation[j] = 0;
        }
    }

    do 
    {
        all_permutations.push_back(operation);
    } while(std::next_permutation(operation.begin(), operation.end()));

    return all_permutations;
}

int calculate_possible(const std::vector<long long> &equation, const std::vector<int> &operation)
{
    long long curr_number = equation[1];

    for (size_t i = 2; i < equation.size(); i++)
    {
        size_t operation_idx = i - 2;

        if (operation[operation_idx] == 1)
        {
            // perform +
            curr_number += equation[i];
        }
        else if (operation[operation_idx] == 0)
        {
            // perform *
            curr_number *= equation[i];
        }
        else 
        {
            // combine numbers
            unsigned pow = 10;
            while (equation[i] >= pow)
                pow *= 10;

            curr_number = curr_number * pow + equation[i];
        }

        if (curr_number > equation[0])
        {
            return 1;
        }
    }

    long long result = curr_number - equation[0];

    if (result > 0)
    {
        return 1;
    }
    else if (result == 0)
    {
        return 0;
    }
    else 
    {
        return -1;
    }
}

namespace day07
{
    void partOne(std::string puzzle_input_in)
    {
        long long sum = 0;

        std::vector<std::string> puzzle_input = aoc_util::read_puzzle_input_string(puzzle_input_in);

        for (std::string &equation : puzzle_input)
        {
            std::vector<long long> all_numbers = aoc_util::read_all_numbers(equation);
            std::vector<int> first_permutation(all_numbers.size() - 2, 0);
            std::vector<std::vector<int>> batch_permutation({first_permutation});
            bool more_permutation = true;

            do 
            {
                bool completed = false;
                
                for (auto &permutation : batch_permutation)
                {
                    int result = calculate_possible(all_numbers, permutation);


                    if (result == 0)
                    {
                        sum += all_numbers[0];
                        completed = true;
                        break;
                    } 
                }

                if (completed || std::ranges::all_of(batch_permutation[0], [&](int i) { return i == 1; }))
                {
                    more_permutation = false;
                } 
                else 
                {
                    batch_permutation = get_next_permutation_batch(all_numbers.size() - 2, false, batch_permutation[0]);
                }


            } while (more_permutation);
        }

        std::cout << "Total sum of correct equation results: " << sum << std::endl;
    }

    void partTwo(std::string puzzle_input_in)
    {
        long long sum = 0;

        std::vector<std::string> puzzle_input = aoc_util::read_puzzle_input_string(puzzle_input_in);

        for (std::string &equation : puzzle_input)
        {
            std::vector<long long> all_numbers = aoc_util::read_all_numbers(equation);
            std::vector<int> first_permutation(all_numbers.size() - 2, 0);
            std::vector<std::vector<int>> batch_permutation({first_permutation});
            bool more_permutation = true;

            do // brute force it
            {
                bool completed = false;
                
                for (auto &permutation : batch_permutation)
                {
                    int result = calculate_possible(all_numbers, permutation);


                    if (result == 0)
                    {
                        sum += all_numbers[0];
                        completed = true;
                        break;
                    } 
                }

                if (completed || std::ranges::all_of(batch_permutation[0], [&](int i) { return i == 2; }))
                {
                    more_permutation = false;
                } 
                else 
                {
                    batch_permutation = get_next_permutation_batch(all_numbers.size() - 2, true, batch_permutation[0]);
                }


            } while (more_permutation);
        }

        std::cout << "Total sum of correct equation results with 3 operations: " << sum << std::endl;
    }
}