#include "solutions/day_1/day_1.h"

#include <cmath>
#include <fstream>
#include <string>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"

namespace aoc
{
    static std::vector<int> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<int> rotations;
        char direction = ' ';
        int rotation = 0;
        while (file >> direction >> rotation)
        {
            switch (direction)
            {
                case 'L':
                    rotations.emplace_back(-rotation);
                    break;
                case 'R':
                    rotations.emplace_back(rotation);
                    break;
            }
        }

        return rotations;
    }

    std::string Day1::part_1(const std::filesystem::path& input_root) const
    {
        const auto rotations = parse_input(input_root / "day_1.txt");

        int dial = 50;
        int zeros = 0;
        for (const auto& rotation : rotations)
        {
            dial = mod(dial + rotation, 100);
            zeros += dial == 0;
        }

        return fmt::format("Number of times the dial points at zero: {}", zeros);
    }

    std::string Day1::part_2(const std::filesystem::path& input_root) const
    {
        const auto rotations = parse_input(input_root / "day_1.txt");
        
        int dial = 50;
        int zeros = 0;
        for (const auto& rotation : rotations)
        {
            // Rotations that stay positive are handled correctly, but left rotations
            // that become 0 or negative need 1 zero added
            const int next_dial = dial + rotation;
            zeros += std::abs(next_dial) / 100;
            zeros += dial > 0 && next_dial <= 0;

            dial = mod(next_dial, 100);
        }

        return fmt::format("Number of times the dial points at zero: {}", zeros);
    }

} // aoc
