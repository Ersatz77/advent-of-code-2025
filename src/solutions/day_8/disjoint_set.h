#ifndef AOC_2025_DAY_8_DISJOINT_SET_H
#define AOC_2025_DAY_8_DISJOINT_SET_H

#include <cstddef>
#include <vector>

namespace aoc
{
    class DisjointSet
    {
    public:
        DisjointSet() = delete;
        explicit DisjointSet(const std::size_t size);

        std::vector<std::size_t> components() const { return m_sizes; }
        std::size_t component_size(const std::size_t value) { return m_sizes[find(value)]; }

        std::size_t find(const std::size_t value);
        void set_union(const std::size_t a, const std::size_t b);
        
    private:
        std::vector<std::size_t> m_parent;
        std::vector<std::size_t> m_sizes;
    };

} // aoc

#endif // !AOC_2025_DAY_8_DISJOINT_SET_H
