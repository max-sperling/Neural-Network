/**
 * @author Max Sperling
 */

#include "Edge.hpp"

#include <iostream>

namespace network {

Edge::Edge() : m_weight(0.0), m_deltaWeight(0.0) {}

void Edge::print()
{
    std::cout << "weight=" << m_weight << " deltaWeight=" << m_deltaWeight;
}

} // namespace network
