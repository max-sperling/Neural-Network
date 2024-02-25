/**
 * @author Max Sperling
 */
#include "Layer.hpp"
#include <cassert>
#include <iostream>

using namespace std;

namespace network {

Layer::Layer(Type type, unsigned numOutputs)
    : m_numOutputs(numOutputs), m_neurons(), m_bias()
{
    assert(type != Type::UNDEF);

    switch (type)
    {
    case Type::INPUT:
    case Type::HIDDEN:
        {
            int index = -1;
            m_bias = std::make_optional<Neuron>(index, m_numOutputs, true);
        }
    }
}

void Layer::addNeuron()
{
    int index = m_neurons.size();
    m_neurons.push_back(Neuron(index, m_numOutputs));
}

Neuron& Layer::at(unsigned position)
{
    return m_neurons.at(position);
}

unsigned Layer::size() const
{
    return m_neurons.size();
}

std::optional<Neuron>& Layer::getBias()
{
    return m_bias;
}

void Layer::print()
{
    for (unsigned n = 0; n < m_neurons.size(); ++n)
    {
        m_neurons.at(n).print();
    }

    if (m_bias.has_value())
    {
        m_bias->print();
    }
}

}
