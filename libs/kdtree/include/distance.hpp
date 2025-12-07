#pragma once
#include "node.hpp"
#include <cmath>
#include <numeric>


namespace sortedkdtree
{
    /**
     * @brief d = √((x₂ - x₁)² + (y₂ - y₁)² + ... + (n₂ - n₁)²)
     */
    inline double euclideanDistance(const Point &a, const Point &b)
    {
        double ret = 0;

        std::size_t dimensions = a.size();

        for (std::size_t i = 0; i < dimensions; ++i)
        {
            double diff = static_cast<double>(a[i]) - static_cast<double>(b[i]);
            ret += diff * diff;
        }

        return std::sqrt(ret);
    }

    /**
     * @brief d = (x₂ - x₁)² + (y₂ - y₁)² + ... + (n₂ - n₁)²
     *
     */
    inline double squaredEuclideanDistance(const Point &a, const Point &b)
    {
        double ret = 0;

        std::size_t dimensions = a.size();

        for (std::size_t i = 0; i < dimensions; ++i)
        {

            double diff = static_cast<double>(a[i]) - static_cast<double>(b[i]);
            ret += diff * diff;
        }
        return ret;
    }

    inline double manhattanDistance(const Point &a, const Point &b)
    {
        double ret = 0;

        std::size_t dimensions = a.size();
        for (std::size_t i = 0; i < dimensions; ++i)
        {
            ret += std::abs(a[i] - b[i]);
        }
        return ret;
    }

} // namespace kdtree
