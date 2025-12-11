#include "solutions/day_11/day_11.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/string.h"
#include "utility/utility.h"

namespace aoc
{
    using Devices = std::unordered_map<std::string, std::vector<std::string>>;
    using DevicePathCache = std::unordered_map<std::tuple<std::string, bool, bool>, std::uint64_t>;

    static Devices parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        Devices devices;
        for (std::string line; std::getline(file, line); )
        {
            const std::vector<std::string> parts = split(line, ": ");

            const std::string device = parts.front();
            const std::vector<std::string> connections = split(parts.back(), " ");

            devices[device] = connections;
        }

        return devices;
    }

    static std::uint64_t count_paths(DevicePathCache& cache, const Devices& devices, const std::string& device, bool visited_dac, bool visited_fft)
    {
        if (device == "out")
        {
            return visited_dac && visited_fft ? 1 : 0;
        }
        else if (device == "dac")
        {
            visited_dac = true;
        }
        else if (device == "fft")
        {
            visited_fft = true;
        }

        const std::tuple<std::string, bool, bool> key = std::make_tuple(device, visited_dac, visited_fft);
        if (!cache.contains(key))
        {
            for (const auto& connection : devices.at(device))
            {
                cache[key] += count_paths(cache, devices, connection, visited_dac, visited_fft);
            }
        }

        return cache.at(key);
    }

    std::string Day11::part_1(const std::filesystem::path& input_root) const
    {
        const auto devices = parse_input(input_root / "day_11.txt");

        std::unordered_map<std::tuple<std::string, bool, bool>, std::uint64_t> cache;
        const auto paths = count_paths(cache, devices, "you", true, true);

        return fmt::format("Number of paths from 'you' to 'out': {}", paths);
    }

    std::string Day11::part_2(const std::filesystem::path& input_root) const
    {
        const auto devices = parse_input(input_root / "day_11.txt");

        std::unordered_map<std::tuple<std::string, bool, bool>, std::uint64_t> cache;
        const auto paths = count_paths(cache, devices, "svr", false, false);

        return fmt::format("Number of valid paths from 'svr' to 'out': {}", paths);
    }

} // aoc
