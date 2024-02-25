/**
 * @author Max Sperling
 */
#pragma once

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

    double m_weight;
    double m_deltaWeight;
};

}
