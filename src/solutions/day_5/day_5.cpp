#include "solutions/day_5/day_5.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "ctre.hpp"
#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    struct IngredientRange
    {
        std::uint64_t start;
        std::uint64_t end;
    };

    static std::pair<std::vector<IngredientRange>, std::vector<std::uint64_t>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<IngredientRange> ranges;
        for (std::string line; std::getline(file, line) && !line.empty(); )
        {
            constexpr ctll::fixed_string range_pattern = R"((?<start>\d+)-(?<end>\d+))";
            const auto match = ctre::match<range_pattern>(line);
            const auto start = match.get<"start">().to_number<std::uint64_t>();
            const auto end = match.get<"end">().to_number<std::uint64_t>();

            ranges.emplace_back(start, end);
        }

        std::vector<std::uint64_t> ingredient_ids;
        for (std::uint64_t id = 0; file >> id; )
        {
            ingredient_ids.push_back(id);
        }

        std::ranges::sort(ranges, [](const auto& left, const auto& right) { return left.start < right.start; });
        std::ranges::sort(ingredient_ids, std::ranges::less());

        return { ranges, ingredient_ids };
    }

    static std::vector<IngredientRange> merge_ranges(const std::vector<IngredientRange>& ranges)
    {
        std::vector<IngredientRange> merged = { ranges.front() };
        for (std::size_t i = 1; i < ranges.size(); ++i)
        {
            const auto& current = ranges[i];
            auto& previous = merged.back();
            if (previous.end < current.start)
            {
                merged.push_back(current);
            }
            else if (current.end <= previous.end)
            {
                continue;
            }
            else
            {
                previous.end = current.end;
            }
        }

        return merged;
    }

    std::string Day5::part_1(const std::filesystem::path& input_root) const
    {
        const auto [ranges, ingredient_ids] = parse_input(input_root / "day_5.txt");
        const auto merged_ranges = merge_ranges(ranges);

        std::uint64_t fresh = 0;
        for (const std::uint64_t id : ingredient_ids)
        {
            for (const auto& range : merged_ranges)
            {
                if (id >= range.start && id <= range.end)
                {
                    ++fresh;
                    break;
                }
            }
        }

        return fmt::format("Number of fresh ingredient IDs: {}", fresh);
    }

    std::string Day5::part_2(const std::filesystem::path& input_root) const
    {
        const auto [ranges, _] = parse_input(input_root / "day_5.txt");
        const auto merged_ranges = merge_ranges(ranges);

        std::uint64_t fresh = std::ranges::fold_left(
            merged_ranges, 0ULL,
            [](const auto acc, const auto& r) { return acc + ((r.end - r.start) + 1); }
        );

        return fmt::format("Number of fresh ingredient IDs: {}", fresh);
    }

} // aoc
