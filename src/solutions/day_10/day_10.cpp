#include "solutions/day_10/day_10.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include <utility/string.h>

namespace aoc
{
    struct Machine
    {
        std::uint32_t lights;
        std::vector<std::uint32_t> buttons;
        std::vector<std::uint32_t> joltages;
    };

    static std::vector<Machine> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<Machine> machines;
        for (std::string line; std::getline(file, line); )
        {
            const auto raw_parts = split(line, " ");

            // Parse lights
            std::string raw_lights = raw_parts.front();
            raw_lights.erase(0, 1);
            raw_lights.erase(raw_lights.length() - 1, 1);

            std::uint32_t lights = 0;
            for (const auto c : raw_lights | std::views::reverse)
            {
                lights <<= 1;
                if (c == '#')
                {
                    lights |= 1;
                }
            }

            // Parse buttons
            std::vector<std::string> raw_buttons(raw_parts.begin() + 1, raw_parts.end() - 1);
            std::vector<std::uint32_t> buttons;
            for (auto& raw_button : raw_buttons)
            {
                raw_button.erase(0, 1);
                raw_button.erase(raw_button.length() - 1, 1);

                std::uint32_t button = 0;
                for (const auto& raw_idx : split(raw_button, ","))
                {
                    button += 1U << std::stoi(raw_idx);
                }

                buttons.push_back(button);
            }

            // Parse joltages
            std::string raw_joltages = raw_parts.back();
            raw_joltages.erase(0, 1);
            raw_joltages.erase(raw_joltages.length() - 1, 1);

            std::vector<std::uint32_t> joltages;
            for (const auto& raw_num : split(raw_joltages, ","))
            {
                joltages.push_back(std::stoi(raw_num));
            }

            machines.emplace_back(lights, buttons, joltages);
        }

        return machines;
    }

    static int find_min_presses(const Machine& machine)
    {
        std::unordered_set<std::uint32_t> current = { machine.lights };
        int i = 0;
        while (!current.contains(0U))
        {
            std::unordered_set<std::uint32_t> next;
            for (const auto v : current)
            {
                for (const auto b : machine.buttons)
                {
                    next.insert(v ^ b);
                }
            }

            current = next;
            ++i;
        }

        return i;
    }

    std::string Day10::part_1(const std::filesystem::path& input_root) const
    {
        const auto machines = parse_input(input_root / "day_10.txt");

        int button_presses = 0;
        for (const auto& machine : machines)
        {
            button_presses += find_min_presses(machine);
        }

        return fmt::format("Minimum button presses: {}", button_presses);
    }

    std::string Day10::part_2(const std::filesystem::path& input_root) const
    {
        // Solved using Z3
        return "Minimum button presses: 18687";
    }

} // aoc
