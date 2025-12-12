#include "solutions/day_12/day_12.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/string.h"

namespace aoc
{
    struct TreeRegion
    {
        std::uint64_t area;
        std::vector<std::uint64_t> required_presents;
    };

    static std::pair<std::vector<std::uint64_t>, std::vector<TreeRegion>> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> lines = read_lines(path);
        std::size_t line_idx = 0;

        // Get present sizes
        std::vector<std::uint64_t> present_sizes;
        std::uint64_t current_size = 0;
        while (line_idx < lines.size())
        {
            const auto& line = lines[line_idx];
            if (line.contains('x'))
            {
                break;
            }
            else if (line.empty())
            {
                present_sizes.push_back(current_size);
                current_size = 0;
            }
            else
            {
                current_size += std::ranges::count(line, '#');
            }

            ++line_idx;
        }

        // Get regions and required presents
        std::vector<TreeRegion> regions;
        while (line_idx < lines.size())
        {
            const auto& line = lines[line_idx];
            const auto parts = split(line, ": ");
            const auto raw_area = split(parts.front(), "x");
            const auto raw_required_presents = split(parts.back(), " ");

            const std::uint64_t area = std::stoull(raw_area[0]) * std::stoull(raw_area[1]);
            const std::vector<std::uint64_t> required_presents = raw_required_presents
                | std::views::transform([](const auto& c) { return std::stoull(c); })
                | std::ranges::to<std::vector<std::uint64_t>>();

            regions.emplace_back(area, required_presents);
            ++line_idx;
        }

        return { present_sizes, regions };
    }

    std::string Day12::part_1(const std::filesystem::path& input_root) const
    {
        const auto [present_sizes, regions] = parse_input(input_root / "day_12.txt");

        std::uint64_t can_fit = 0;
        for (const auto& region : regions)
        {
            std::uint64_t area = 0;
            for (std::size_t i = 0; i < region.required_presents.size(); ++i)
            {
                area += present_sizes[i] * region.required_presents[i];
            }

            if (area <= region.area)
            {
                ++can_fit;
            }
        }

        return fmt::format("Number of regions that can fit the presents: {}", can_fit);
    }

    std::string Day12::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("You finish decorating the north pole");
    }

} // aoc
