#include "solutions/day_8/disjoint_set.h"

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <ranges>

namespace aoc
{
    DisjointSet::DisjointSet(const std::size_t size)
    {
        m_parent.resize(size);
        std::ranges::iota(m_parent, 0);

        m_sizes.resize(size);
        std::ranges::fill(m_sizes, 1);
    }

    std::size_t DisjointSet::find(const std::size_t value)
    {
        if (m_parent[value] != value)
        {
            m_parent[value] = find(m_parent[value]);
        }

        return m_parent[value];
    }

    void DisjointSet::set_union(const std::size_t a, const std::size_t b)
    {
        std::size_t set_a = find(a);
        std::size_t set_b = find(b);
        if (set_a != set_b)
        {
            if (m_sizes[set_a] < m_sizes[set_b])
            {
                m_parent[set_a] = set_b;
                m_sizes[set_b] += m_sizes[set_a];
            }
            else
            {
                m_parent[set_b] = set_a;
                m_sizes[set_a] += m_sizes[set_b];
            }
        }
    }

} // aoc
