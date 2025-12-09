#ifndef AOC_2025_DAY_9_AABB_H
#define AOC_2025_DAY_9_AABB_H

#include <cmath>

#include "utility/utility.h"
#include "utility/vec.h"

namespace aoc
{
    template<Number T>
    class AABB
    {
    public:
        AABB() = delete;

        AABB(const T a_x, const T a_y, const T b_x, const T b_y) :
            m_min(std::min(a_x, b_x), std::min(a_y, b_y)),
            m_max(std::max(a_x, b_x), std::max(a_y, b_y))
        {
        }

        AABB(const Vec2<T>& a, const Vec2<T>& b) :
            m_min(std::min(a.x, b.x), std::min(a.y, b.y)),
            m_max(std::max(a.x, b.x), std::max(a.y, b.y))
        {
        }

        T area() const
        {
            return (std::abs(m_max.x - m_min.x) + 1) * (std::abs(m_max.y - m_min.y) + 1);
        }

        bool in_area(const T x, const T y) const
        {
            return x >= m_min.x && x <= m_max.x && y >= m_min.x && y <= m_max.x;
        }

        bool in_area(const Vec2<T>& p) const
        {
            return in_area(p.x, p.y);
        }

        bool intersects(const AABB& other) const
        {
            return m_min.x < other.m_max.x
                && m_max.x > other.m_min.x
                && m_min.y < other.m_max.y
                && m_max.y > other.m_min.y;
        }

    private:
        Vec2<T> m_min;
        Vec2<T> m_max;
    };

} // aoc

#endif // !AOC_2025_DAY_9_AABB_H
