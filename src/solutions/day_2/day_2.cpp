#include "solutions/day_2/day_2.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"

namespace aoc
{
    static std::vector<std::pair<std::uint64_t, std::uint64_t>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::pair<std::uint64_t, std::uint64_t>> ranges;
        std::uint64_t start_id = 0;
        std::uint64_t end_id = 0;
        char separator = ' ';
        while (file >> start_id >> separator >> end_id)
        {
            ranges.emplace_back(start_id, end_id);
            file >> separator;
        }

        return ranges;
    }

    static bool is_palindrome(const std::uint64_t id)
    {
        std::size_t num_digits = digits(id);
        if (num_digits % 2 != 0)
        {
            return false;
        }

        std::size_t left_idx = 0;
        std::size_t right_idx = num_digits / 2;
        while (right_idx < num_digits)
        {
            const std::uint64_t left = digit_at(id, left_idx);
            const std::uint64_t right = digit_at(id, right_idx);

            if (left != right)
            {
                return false;
            }

            ++left_idx;
            ++right_idx;
        }

        return true;
    }

    static bool is_repeating(const std::uint64_t id)
    {
        std::size_t num_digits = digits(id);
        for (std::size_t chunk_length = 1; chunk_length <= num_digits / 2; ++chunk_length)
        {
            if (num_digits % chunk_length != 0)
            {
                continue;
            }

            // Create a new ID using the chunk length
            std::uint64_t repeating_id = 0;
            for (std::size_t i = 0; i < num_digits; ++i)
            {
                const std::size_t j = chunk_length - 1 - (i % chunk_length);
                repeating_id *= 10;
                repeating_id += digit_at(id, j);
            }

            // Check if both IDs are the same
            if (id == repeating_id)
            {
                return true;
            }
        }

        return false;
    }

    std::string Day2::part_1(const std::filesystem::path& input_root) const
    {
        const auto ranges = parse_input(input_root / "day_2.txt");

        std::uint64_t sum = 0;
        for (const auto& [start_id, end_id] : ranges)
        {
            for (std::uint64_t id = start_id; id <= end_id; ++id)
            {
                if (is_palindrome(id))
                {
                    sum += id;
                }
            }
        }

        return fmt::format("Sum of invalid IDs: {}", sum);
    }

    std::string Day2::part_2(const std::filesystem::path& input_root) const
    {
        const auto ranges = parse_input(input_root / "day_2.txt");

        std::uint64_t sum = 0;
        for (const auto& [start_id, end_id] : ranges)
        {
            for (std::uint64_t id = start_id; id <= end_id; ++id)
            {
                if (is_repeating(id))
                {
                    sum += id;
                }
            }
        }

        return fmt::format("Sum of invalid IDs: {}", sum);
    }

} // aoc
