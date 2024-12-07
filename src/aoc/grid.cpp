#include "./grid.h"

#include <vector>
#include <map>

const char GUARD_POSITION = '^';
const char OBSTICAL = '#';

std::map<day06::Direction, std::vector<int>> DIRECTION_VECTOR_MAP = {
    {day06::Direction::FOWARD, {0, -1}},
    {day06::Direction::RIGHT, {1, 0}},
    {day06::Direction::BACK, {0, 1}},
    {day06::Direction::LEFT, {-1, 0}}
};

namespace day06
{
    Grid::Grid(const std::vector<std::vector<char>> &grid_in)
    {
        grid = grid_in;
        x_obstical = -1;
        y_obstical = -1;

        _find_start_position();
    }

    Grid::Grid(const std::vector<std::vector<char>> &grid_in, int x_obstical_in, int y_obstical_in)
    {
        x_obstical = x_obstical_in;
        y_obstical = y_obstical_in;
        grid = grid_in;

        _find_start_position();
    }

    int Grid::num_positions()
    {
        return visited_positions.size();
    }

    bool Grid::step()
    {
        std::vector<int> next_position_vector = DIRECTION_VECTOR_MAP[direction];
        int next_x = current_x + next_position_vector[0];
        int next_y = current_y + next_position_vector[1];

        // if out of bounds then end
        if (next_y < 0 || (unsigned int)next_y >= grid.size() || next_x < 0 || (unsigned int)next_x >= grid[0].size())
        {
            return false;
        }

        visited_positions_direction[direction].insert({current_x, current_y});

        while (grid[next_y][next_x] == OBSTICAL || (next_x == x_obstical && next_y == y_obstical))
        {
            direction = _rotate();
            next_position_vector = DIRECTION_VECTOR_MAP[direction];
            next_x = current_x + next_position_vector[0];
            next_y = current_y + next_position_vector[1];
        }

        visited_positions.insert({next_x, next_y});
        current_x = next_x;
        current_y = next_y;

        return true;
    }

    bool Grid::has_visited()
    {
        return visited_positions_direction[direction].count({current_x, current_y}) != 0;
    }

    std::vector<int> Grid::get_current_position()
    {
        return {current_x, current_y};
    }

    std::set<std::vector<int>> Grid::get_visited_positions()
    {
        return visited_positions;
    }

    day06::Direction Grid::_rotate()
    {
        switch (direction)
        {
            case FOWARD: return day06::Direction::RIGHT;
            case RIGHT: return day06::Direction::BACK;
            case BACK: return day06::Direction::LEFT;
            case LEFT: return day06::Direction::FOWARD;
        }

        return direction;
    }

    void Grid::_find_start_position()
    {
        for (size_t y = 0; y < grid.size(); y++)
        {
            for (size_t x = 0; x < grid.front().size(); x++)
            {
                if (grid[y][x] == GUARD_POSITION)
                {
                    current_x = x;
                    current_y = y;
                    direction = day06::Direction::FOWARD;

                    visited_positions.insert({current_x, current_y});

                    return;
                }
            }
        }
    }
}