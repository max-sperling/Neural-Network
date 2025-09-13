/**
 * @author Max Sperling
 */

#include "Layer.hpp"

#include <iostream>

namespace network {

Layer::Layer(Type type, uint32_t numOutputs)
    : m_numOutputs(numOutputs), m_neurons(), m_bias()
{
    if (type == Type::UNDEF) {
        std::cerr << "The type of a layer can't be UNDEF\n";
        std::exit(1);
    }

    switch (type)
    {
    case Type::INPUT:
    case Type::HIDDEN:
        {
            int32_t index = -1;
            m_bias = std::make_optional<Neuron>(index, m_numOutputs, true);
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

void Layer::print()
{
    for (uint32_t n = 0; n < m_neurons.size(); ++n)
    {
        m_neurons.at(n).print();
    }

    if (m_bias.has_value())
    {
        m_bias->print();
    }
}

} // namespace network
