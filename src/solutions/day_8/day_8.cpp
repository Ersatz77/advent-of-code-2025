#include "solutions/day_8/day_8.h"

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

#include "solutions/day_8/disjoint_set.h"
#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    static std::vector<Vec3<std::int64_t>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<Vec3<std::int64_t>> junction_boxes;
        std::int64_t x = 0;
        std::int64_t y = 0;
        std::int64_t z = 0;
        char comma = ' ';
        while (file >> x >> comma >> y >> comma >> z)
        {
            junction_boxes.emplace_back(x, y, z);
        }

        return junction_boxes;
    }

    static std::vector<std::pair<std::size_t, std::size_t>> create_idx_pairs(const std::vector<Vec3<std::int64_t>>& junction_boxes)
    {
        using JunctionBoxPair = std::pair<std::size_t, std::size_t>;

        std::vector<JunctionBoxPair> pairs;
        for (std::size_t i = 0; i < junction_boxes.size(); ++i)
        {
            for (std::size_t j = i + 1; j < junction_boxes.size(); ++j)
            {
                pairs.emplace_back(i, j);
            }
        }

        std::ranges::sort(pairs, [&junction_boxes](const JunctionBoxPair& a, const JunctionBoxPair& b) {
            const auto& a1 = junction_boxes[a.first];
            const auto& a2 = junction_boxes[a.second];
            const auto& b1 = junction_boxes[b.first];
            const auto& b2 = junction_boxes[b.second];

            const auto distance_a = ((a2.x - a1.x) * (a2.x - a1.x)) + ((a2.y - a1.y) * (a2.y - a1.y)) + ((a2.z - a1.z) * (a2.z - a1.z));
            const auto distance_b = ((b2.x - b1.x) * (b2.x - b1.x)) + ((b2.y - b1.y) * (b2.y - b1.y)) + ((b2.z - b1.z) * (b2.z - b1.z));

            return distance_a < distance_b;
        });

        return pairs;
    }

    std::string Day8::part_1(const std::filesystem::path& input_root) const
    {
        const auto junction_boxes = parse_input(input_root / "day_8.txt");
        auto idx_pairs = create_idx_pairs(junction_boxes);

        DisjointSet disjoint(junction_boxes.size());
        for (std::size_t i = 0; i < 1000 && i < idx_pairs.size(); ++i)
        {
            const auto& [a, b] = idx_pairs[i];
            disjoint.set_union(a, b);
        }

        auto components = disjoint.components();
        std::ranges::sort(components, std::ranges::greater());
        std::int64_t result = components[0] * components[1] * components[2];

        return fmt::format("Product of the 3 largest circuits: {}", result);
    }

    std::string Day8::part_2(const std::filesystem::path& input_root) const
    {
        const auto junction_boxes = parse_input(input_root / "day_8.txt");
        auto idx_pairs = create_idx_pairs(junction_boxes);

        DisjointSet disjoint(junction_boxes.size());
        std::int64_t result = 0;
        for (const auto& [a, b] : idx_pairs)
        {
            disjoint.set_union(a, b);
            if (disjoint.component_size(a) == junction_boxes.size())
            {
                result = junction_boxes[a].x * junction_boxes[b].x;
                break;
            }
        }

        return fmt::format("X coordinate product: {}", result);
    }

} // aoc
