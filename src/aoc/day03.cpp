#include "day03.h"
#include "../util/util.h"

#include <iostream>
#include <string>
#include <vector>
#include <regex>

namespace day03
{
    void partOne(std::string puzzle_input_in)
    {
        int sum = 0;
        std::vector<std::string> puzzle_input = aoc_util::read_puzzle_input_string(puzzle_input_in);

        std::regex re("mul\\([0-9]+,[0-9]+\\)");
        std::regex re_num("[0-9]+");

        for (auto &input : puzzle_input)
        {
            std::string subject(input);
            std::smatch m;

            while (regex_search(subject, m, re))
            {
                std::string nums(m.str());
                std::smatch m_nums;

                regex_search(nums, m_nums, re_num);
                int num_one = std::stoi(m_nums.str());

                std::string remaining = m_nums.suffix().str();

                regex_search(remaining, m_nums, re_num);
                int num_two = std::stoi(m_nums.str());

                sum += num_one * num_two;

                subject = m.suffix().str();
            }
        }

        std::cout << "Total sum of the multiplied numbers are: " << sum << std::endl;
    }

    void partTwo(std::string puzzle_input_in)
    {
        int sum = 0;
        std::vector<std::string> puzzle_input = aoc_util::read_puzzle_input_string(puzzle_input_in);

        std::regex tokenise_re(".+?(?=don't\\(\\)|do\\(\\))");
        std::regex re("mul\\([0-9]+,[0-9]+\\)");
        std::regex re_num("[0-9]+");

        std::vector<std::string> instructions;

        for (auto &input : puzzle_input)
        {
            std::string subject(input);
            std::smatch m;

            while (regex_search(subject, m, tokenise_re))
            {
                instructions.push_back(m.str());
                subject = m.suffix().str();
            }

            // add last string as there should be no more do's and don'ts
            instructions.push_back(subject);
        }

        for (auto &instruction : instructions) 
        {
            if (instruction.rfind("don't()") != 0)
            {
                std::string subject(instruction);
                std::smatch m;

                while (regex_search(subject, m, re))
                {
                    std::string nums(m.str());
                    std::smatch m_nums;

                    regex_search(nums, m_nums, re_num);
                    int num_one = std::stoi(m_nums.str());

                    std::string remaining = m_nums.suffix().str();

                    regex_search(remaining, m_nums, re_num);
                    int num_two = std::stoi(m_nums.str());

                    sum += num_one * num_two;

                    subject = m.suffix().str();
                }
            }
        }

        std::cout << "Total sum of the multiplied numbers with new instruction set are: " << sum << std::endl;
    }
}