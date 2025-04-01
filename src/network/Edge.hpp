/**
 * @author Max Sperling
 */

#pragma once

#include <stdfloat>

namespace network {

/**
 * @brief An edge connects two neurons.
 */
class Edge
{
public:
    /**
     * @brief Construct an edge
     */
    Edge();

    /**
     * @brief Print out the edge
     */
    void print();

    std::float64_t m_weight;
    std::float64_t m_deltaWeight;
};

} // namespace network
