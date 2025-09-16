/**
 * @author Max Sperling
 */

#include "Edge.hpp"

#include <sstream>

namespace network {

Edge::Edge() : m_weight(0.0), m_deltaWeight(0.0) {}

std::string Edge::toString() const
{
    std::ostringstream oss;
    oss << "weight=" << m_weight << " deltaWeight=" << m_deltaWeight;
    return oss.str();
}

} // namespace network
