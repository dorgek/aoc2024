#include "day02.h"
#include "../util/util.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int report_safe(const std::vector<int> &report, int level_skip) 
{
    bool always_increasing = true;
    bool always_decreasing = true;

    for (unsigned int i = 0; i < report.size() - 1; i++)
    {
        unsigned int j = i + 1;
        if (level_skip >= 0 && i == (unsigned int)level_skip)
        {
            continue;
        }
        else if (level_skip > 0 && i + 1 == (unsigned int)level_skip)
        {
            j++;
        }

        if (report.size() <= j)
        {
            return -1;
        }

        int diff = abs(report[i] - report[j]);

        if (diff > 3) 
        {
            return i;
        }

        if (report[i] < report[j])
        {
            // increasing in size
            if (!always_increasing)
            {
                return i;
            }

            always_decreasing = false;
        } 
        else if (report[i] > report[j])
        {
            // decreasing in size
            if (!always_decreasing)
            {
                return i;
            }

            always_increasing = false;
        }
        else 
        {
            return i;
        }
    }

    return -1;
}

namespace day02
{
    void partOne(std::string puzzle_input_in)
    {
        int count = 0;
        std::vector<std::vector<int>> puzzle_input = aoc_util::read_puzzle_input(puzzle_input_in);
        for (auto &report : puzzle_input)
        {
            if (report_safe(report, -1) == -1)
            {
                count++;
            }
        }

        std::cout << "The number of safe reports is: " << count << std::endl;

    }

    void partTwo(std::string puzzle_input_in)
    {
        int count = 0;
        std::vector<std::vector<int>> puzzle_input = aoc_util::read_puzzle_input(puzzle_input_in);
        
        for (auto &report : puzzle_input)
        {
            int unsafe_level = report_safe(report, -1);
            if (unsafe_level == -1)
            {
                count++;
            }
            else 
            {
                for (unsigned int i = 0; i < report.size(); i++) {
                    if (report_safe(report, i) == -1)
                    {
                        count++;
                        break;
                    }
                }
            }
        }

        std::cout << "The number of safe reports after level skip is: " << count << std::endl;
    }
}