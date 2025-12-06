#include "solutions/day_6/day_6.h"

#include <algorithm>
#include <cctype>
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

namespace aoc
{
    enum class MathHomeworkOperation
    {
        ADD = 0,
        MULTIPLY
    };

    static std::vector<std::pair<MathHomeworkOperation, std::vector<std::string>>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        // Read all the lines in the file
        std::vector<std::string> lines;
        for (std::string line; std::getline(file, line); )
        {
            lines.push_back(line + ' ');
        }

        // Extract the line with the math operations
        std::string raw_ops = lines.back();
        lines.pop_back();

        // Get the math problems
        std::vector<std::pair<MathHomeworkOperation, std::vector<std::string>>> problems;
        std::size_t start = 0;
        while (!raw_ops.empty())
        {
            // Get the math operation
            MathHomeworkOperation op = raw_ops.front() == '+' ? MathHomeworkOperation::ADD : MathHomeworkOperation::MULTIPLY;
            raw_ops.erase(0, 1);

            // Figure out how wide the numbers are
            std::size_t length = raw_ops.length();
            raw_ops.erase(raw_ops.begin(), std::ranges::find_if(raw_ops, [](const char c) { return !std::isspace(c); }));
            length -= raw_ops.length();

            // Get the numbers for this problem
            std::vector<std::string> numbers;
            for (const std::string& line : lines)
            {
                numbers.emplace_back(line.substr(start, length));
            }

            // Add the problem and update start position
            problems.emplace_back(op, numbers);
            start += length + 1;
        }

        return problems;
    }

    std::string Day6::part_1(const std::filesystem::path& input_root) const
    {
        const auto problems = parse_input(input_root / "day_6.txt");

        std::uint64_t total = 0;
        for (const auto& [op, numbers] : problems)
        {
            // Get the answer to this math problem
            std::uint64_t answer = op == MathHomeworkOperation::ADD ? 0 : 1;
            for (const auto& number : numbers)
            {
                switch (op)
                {
                    case MathHomeworkOperation::ADD:
                        answer += std::stoull(number);
                        break;
                    case MathHomeworkOperation::MULTIPLY:
                        answer *= std::stoull(number);
                        break;
                }
            }

            total += answer;
        }

        return fmt::format("Grand total: {}", total);
    }

    std::string Day6::part_2(const std::filesystem::path& input_root) const
    {
        const auto problems = parse_input(input_root / "day_6.txt");

        std::uint64_t total = 0;
        for (const auto& [op, numbers] : problems)
        {
            // Get the answer to this math problem
            std::uint64_t answer = op == MathHomeworkOperation::ADD ? 0 : 1;
            for (std::size_t i = 0; i < numbers.front().length(); ++i)
            {
                // Get the number for this column
                std::uint64_t column_number = 0;
                for (const auto& number : numbers)
                {
                    if (std::isdigit(number[i]))
                    {
                        column_number *= 10;
                        column_number += static_cast<std::uint64_t>(number[i] - '0');
                    }
                }

                // Perform the math operation using this number
                switch (op)
                {
                    case MathHomeworkOperation::ADD:
                        answer += column_number;
                        break;
                    case MathHomeworkOperation::MULTIPLY:
                        answer *= column_number;
                        break;
                }
            }

            total += answer;
        }

        return fmt::format("Grand total: {}", total);
    }

} // aoc
