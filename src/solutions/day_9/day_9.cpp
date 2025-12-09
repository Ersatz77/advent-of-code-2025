#include "solutions/day_9/day_9.h"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "fmt/format.h"

#include "solutions/day_9/aabb.h"
#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    using RedTile = Vec2<std::int64_t>;

    static std::vector<RedTile> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<RedTile> red_tiles;
        std::int64_t x = 0;
        std::int64_t y = 0;
        char comma = ' ';
        while (file >> x >> comma >> y)
        {
            red_tiles.emplace_back(x, y);
        }

        return red_tiles;
    }

    std::string Day9::part_1(const std::filesystem::path& input_root) const
    {
        const auto red_tiles = parse_input(input_root / "day_9.txt");

        std::int64_t largest_area = 0;
        for (std::size_t i = 0; i < red_tiles.size(); ++i)
        {
            for (std::size_t j = i + 1; j < red_tiles.size(); ++j)
            {
                const AABB<std::int64_t> rectangle(red_tiles[i], red_tiles[j]);
                const std::int64_t area = rectangle.area();
                if (area > largest_area)
                {
                    largest_area = area;
                }
            }
        }

        return fmt::format("Area of the largest rectangle: {}", largest_area);
    }

    std::string Day9::part_2(const std::filesystem::path& input_root) const
    {
        const auto red_tiles = parse_input(input_root / "day_9.txt");

        std::int64_t largest_area = 0;
        for (std::size_t i = 0; i < red_tiles.size(); ++i)
        {
            for (std::size_t j = i + 1; j < red_tiles.size(); ++j)
            {
                const AABB<std::int64_t> rectangle(red_tiles[i], red_tiles[j]);

                // Check if this rectangle can have the lines drawn around it
                bool valid = true;
                for (std::size_t k = 0; k < red_tiles.size(); ++k)
                {
                    RedTile current = red_tiles[k];
                    RedTile next = red_tiles[(k + 1) % red_tiles.size()];

                    AABB<std::int64_t> line(current, next);
                    if (rectangle.intersects(line))
                    {
                        valid = false;
                        break;
                    }
                }

                // If the rectangle was valid, get the area
                if (valid)
                {
                    const std::int64_t area = rectangle.area();
                    if (area > largest_area)
                    {
                        largest_area = area;
                    }
                }
            }
        }

        return fmt::format("Area of the largest rectangle: {}", largest_area);
    }

} // aoc
