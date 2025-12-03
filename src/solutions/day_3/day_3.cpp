#include "solutions/day_3/day_3.h"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <ranges>
#include <string>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    static std::vector<std::vector<int>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::vector<int>> banks;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<int> bank = line
                | std::views::transform([](const char c) { return c - '0';  })
                | std::ranges::to<std::vector<int>>();

            banks.push_back(bank);
        }

        return banks;
    }

    static std::uint64_t largest_joltage(const std::vector<int>& bank, const std::size_t num_batteries)
    {
        std::uint64_t largest_joltage = 0;
        std::size_t start_idx = 0;
        for (std::size_t b = 0; b < num_batteries; ++b)
        {
            const std::size_t end_offset = num_batteries - 1 - b;

            // Find the first largest joltage between `start_idx` and `end_idx` (inclusive)
            int max = std::numeric_limits<int>::min();
            std::size_t next_start_idx = 0;
            for (std::size_t i = start_idx; i <= bank.size() - 1 - end_offset; ++i)
            {
                if (bank[i] > max)
                {
                    max = bank[i];
                    next_start_idx = i + 1;
                }
            }

            // Add joltage and update start index
            largest_joltage = (largest_joltage * 10) + max;
            start_idx = next_start_idx;
        }

        return largest_joltage;
    }

    std::string Day3::part_1(const std::filesystem::path& input_root) const
    {
        const auto banks = parse_input(input_root / "day_3.txt");

        std::uint64_t sum = 0;
        for (const auto& bank : banks)
        {
            sum += largest_joltage(bank, 2);
        }

        return fmt::format("Sum of the largest joltages in each bank: {}", sum);
    }

    std::string Day3::part_2(const std::filesystem::path& input_root) const
    {
        const auto banks = parse_input(input_root / "day_3.txt");

        std::uint64_t sum = 0;
        for (const auto& bank : banks)
        {
            sum += largest_joltage(bank, 12);
        }

        return fmt::format("Sum of the largest joltages in each bank: {}", sum);
    }

} // aoc
