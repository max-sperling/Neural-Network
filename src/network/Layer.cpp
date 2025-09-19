/**
 * @author Max Sperling
 */

#include "Layer.hpp"

#include <iostream>
#include <sstream>

namespace network {

Layer::Layer(Type type, uint32_t numOutputs)
    : m_numOutputs(numOutputs), m_neurons(), m_bias()
{
    switch (type)
    {
    case Type::UNDEF:
        {
            std::cerr << "The type of a layer can't be UNDEF\n";
            std::exit(1);
        }
    case Type::INPUT:
    case Type::HIDDEN:
        {
            int32_t index = -1;
            m_bias = std::make_optional<Neuron>(index, m_numOutputs, true);
            break;
        }
    case Type::OUTPUT:
        {
            // No bias neuron for output layer
            break;
        }
    }
}

void Layer::addNeuron()
{
    int32_t index = m_neurons.size();
    m_neurons.push_back(Neuron(index, m_numOutputs));
}

Neuron& Layer::at(uint32_t position)
{
    return m_neurons.at(position);
}

uint32_t Layer::size() const
{
    return m_neurons.size();
}

std::optional<Neuron>& Layer::getBias()
{
    return m_bias;
}

std::string Layer::toString() const
{
    std::ostringstream oss;
    if (m_bias.has_value())
    {
        oss << m_bias.value().toString() << "\n";
    }
    for (size_t n = 0; n < m_neurons.size(); ++n)
    {
        oss << m_neurons[n].toString();
        if (n < m_neurons.size() - 1) oss << "\n";
    }
    return oss.str();
}

} // namespace network
