#include "solutions/day_7/day_7.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    static std::tuple<Point, std::unordered_set<Point>, std::size_t> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        Point start;
        std::unordered_set<Point> splitters;
        std::size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {
            for (std::size_t x = 0; x < line.length(); ++x)
            {
                switch (line[x])
                {
                    case 'S':
                        start = make_point(x, y);
                        break;
                    case '^':
                        splitters.insert(make_point(x, y));
                        break;
                }
            }

            ++y;
        }

        return { start, splitters, y };
    }

    std::string Day7::part_1(const std::filesystem::path& input_root) const
    {
        const auto [start, splitters, max_height] = parse_input(input_root / "day_7.txt");

        std::uint64_t splits = 0;
        std::unordered_set<Point> beams = { start };
        while (true)
        {
            // Break out of loop when all beams reach `max_depth`
            if (std::ranges::all_of(beams, [&max_height](const auto& b) { return b.y >= max_height; }))
            {
                break;
            }

            // Get the next position for the beams
            std::unordered_set<Point> next_beams;
            for (const auto& current : beams)
            {
                const auto& next = current + Point(0, 1);
                if (splitters.contains(next))
                {
                    const auto left = next + Point(-1, 0);
                    const auto right = next + Point(1, 0);

                    next_beams.insert(left);
                    next_beams.insert(right);

                    ++splits;
                }
                else
                {
                    next_beams.insert(next);
                }
            }

            beams = next_beams;
        }

        return fmt::format("Number of times the tachyon beam split: {}", splits);
    }

    std::string Day7::part_2(const std::filesystem::path& input_root) const
    {
        const auto [start, splitters, max_height] = parse_input(input_root / "day_7.txt");

        std::unordered_map<Point, std::uint64_t> beams = { {start, 1} };
        while (true)
        {
            // Break out of loop when all beams reach `max_height`
            if (std::ranges::all_of(beams, [&max_height](const auto& kv) { return kv.first.y >= max_height; }))
            {
                break;
            }

            // Get the next position for the beams while also keeping track of their timeline
            std::unordered_map<Point, std::uint64_t> next_beams;
            for (const auto& [current, timelines] : beams)
            {
                const auto& next = current + Point(0, 1);
                if (splitters.contains(next))
                {
                    const auto left = next + Point(-1, 0);
                    const auto right = next + Point(1, 0);

                    next_beams[left] += timelines;
                    next_beams[right] += timelines;
                }
                else
                {
                    next_beams[next] += timelines;
                }
            }

            beams = next_beams;
        }

        std::uint64_t timelines = std::ranges::fold_left(
            beams, 0ULL,
            [](const auto acc, const auto& kv) { return acc + kv.second; }
        );

        return fmt::format("Number of timelines the tachyon particle created: {}", timelines);
    }

} // aoc
