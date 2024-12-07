#pragma once

#include <vector>
#include <set>
#include <map>

namespace day06
{
    enum Direction
    {
        FOWARD = 0,
        RIGHT = 1,
        BACK = 2,
        LEFT = 3
    };

    class Grid 
    {
        private:
            std::vector<std::vector<char>> grid; // TODO: look at making a 2d point
            std::set<std::vector<int>> visited_positions;
            std::map<day06::Direction, std::set<std::vector<int>>> visited_positions_direction;
            int current_x;
            int current_y;
            int x_obstical;
            int y_obstical;
            day06::Direction direction;

            void _find_start_position();
            day06::Direction _rotate();

        public:
            Grid(const std::vector<std::vector<char>> &grid_in);
            Grid(const std::vector<std::vector<char>> &grid_in, int x_obstical_in, int y_obstical_in);
            std::vector<int> get_current_position();
            std::set<std::vector<int>> get_visited_positions();
            bool step();
            bool has_visited();
            int num_positions();
    };
}