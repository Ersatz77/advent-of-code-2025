#include "solutions/day_4/day_4.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    static std::unordered_set<Point> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_set<Point> paper_rolls;
        std::size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {
            for (std::size_t x = 0; x < line.length(); ++x)
            {
                if (line[x] == '@')
                {
                    paper_rolls.insert(make_point(x, y));
                }
            }

            ++y;
        }

        return paper_rolls;
    }

    std::string Day4::part_1(const std::filesystem::path& input_root) const
    {
        const auto paper_rolls = parse_input(input_root / "day_4.txt");

        int accessible = 0;
        for (const auto& paper_roll : paper_rolls)
        {
            // Find how many paper rolls are adjacent to this one
            int adjacent = 0;
            for (const auto& adj : paper_roll.adjacent())
            {
                if (paper_rolls.contains(adj))
                {
                    ++adjacent;
                }
            }

            // Paper roll is accessible if it has less than 4 paper rolls adjacent to it
            if (adjacent < 4)
            {
                ++accessible;
            }
        }

        return fmt::format("Number of paper rolls that can be accessed by a forklift: {}", accessible);
    }

    std::string Day4::part_2(const std::filesystem::path& input_root) const
    {
        auto paper_rolls = parse_input(input_root / "day_4.txt");

        int removed = 0;
        while (true)
        {
            std::unordered_set<Point> new_paper_rolls;
            for (const auto& paper_roll : paper_rolls)
            {
                // Find how many paper rolls are adjacent to this one
                int adjacent = 0;
                for (const auto& adj : paper_roll.adjacent())
                {
                    if (paper_rolls.contains(adj))
                    {
                        ++adjacent;
                    }
                }

                // Paper roll can be removed it has less than 4 paper rolls adjacent to it
                // Otherwise, add it to the new set of paper rolls
                if (adjacent < 4)
                {
                    ++removed;
                }
                else
                {
                    new_paper_rolls.insert(paper_roll);
                }
            }

            // Break out of the loop if nothing was removed
            if (paper_rolls.size() == new_paper_rolls.size())
            {
                break;
            }

            // Update paper rolls
            paper_rolls = new_paper_rolls;
        }

        return fmt::format("Number of paper rolls that can be removed: {}", removed);
    }

} // aoc
