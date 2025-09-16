/**
 * @author Max Sperling
 */

#pragma once

#include <stdfloat>
#include <string>

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
     * @brief Provide the current edge states
     * @return Current edge states
     */
    std::string toString() const;

    std::float64_t m_weight;
    std::float64_t m_deltaWeight;
};

} // namespace network
