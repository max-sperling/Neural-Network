/**
 * @author Max Sperling
 */

#include "Network.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

namespace network {

Network::Network(const utils::Arguments& args)
    : m_args(args), m_layers(), m_mvAvgError(0.0)
{
    auto& topology = args.m_topo;

    for (uint32_t l = 0; l < topology.size(); ++l)
    {
        Layer::Type layerType = Layer::Type::UNDEF;
        uint32_t outEdges = 0;

        if (l == 0)
        {
            layerType = Layer::Type::INPUT;
            outEdges = topology[l+1];
        }
        else if (l < topology.size()-1)
        {
            layerType = Layer::Type::HIDDEN;
            outEdges = topology[l+1];
        }
        else
        {
            layerType = Layer::Type::OUTPUT;
            outEdges = 0;
        }

        m_layers.emplace_back(layerType, outEdges);

        for (uint32_t n = 0; n < topology[l]; ++n)
        {
            m_layers.back().addNeuron();
        }
    }
}

void Network::feedForward(const std::vector<std::float64_t>& inputVals)
{
    if (inputVals.size() != m_layers.front().size()) {
        std::cerr << "The training data input does not match the number of input neurons\n";
        std::exit(1);
    }

    for (uint32_t l = 0; l < m_layers.size(); ++l)
    {
        auto& layer = m_layers[l];
        bool isFirstLayer = (l == 0);

        for (uint32_t n = 0; n < layer.size(); ++n)
        {
            Neuron& neuron = layer.at(n);
            if (isFirstLayer)
                neuron.setOutputVal(inputVals[n]);
            else
                neuron.calcOutputVal(m_layers[l-1]);
        }
    }
}

void Network::getResults(std::vector<std::float64_t>& resultVals)
{
    resultVals.clear();

    for (uint32_t n = 0; n < m_layers.back().size(); ++n)
    {
        resultVals.push_back(m_layers.back().at(n).getOutputVal());
    }
}

void Network::propagateBack(const std::vector<std::float64_t>& targetVals)
{
    if (targetVals.size() != m_layers.back().size()) {
        std::cerr << "The training data output does not match the number of output neurons\n";
        std::exit(1);
    }

    updateMvAvgError(targetVals);

    // Calc input gradients of neurons
    for (uint32_t l = m_layers.size()-1; l > 0; --l)
    {
        auto& layer = m_layers[l];
        bool isLastLayer = (l == m_layers.size()-1);

        for (uint32_t n = 0; n < layer.size(); ++n)
        {
            Neuron& neuron = layer.at(n);
            if (isLastLayer)
                neuron.calcInpGradOutNeuron(targetVals[n]);
            else
                neuron.calcInpGradHidNeuron(m_layers[l+1]);
        }
    }

    // Update weights of edges
    for (uint32_t l = m_layers.size()-1; l > 0; --l)
    {
        auto& layer = m_layers[l];

        for (uint32_t n = 0; n < layer.size(); ++n)
        {
            layer.at(n).updateInputWeights(m_layers[l-1]);
        }
    }
}

std::float64_t Network::getMvAvgError() const
{
    return m_mvAvgError;
}

std::string Network::toString() const
{
    std::ostringstream oss;
    for (uint32_t l = 0; l < m_layers.size(); ++l)
    {
        oss << "Layer " << l << " (Size=" << m_layers[l].size() << ")\n";
        oss << m_layers[l].toString() << "\n";
        if (l < m_layers.size() - 1) oss << "\n";
    }
    return oss.str();
}

void Network::updateMvAvgError(const std::vector<std::float64_t>& targetVals)
{
    // Calculate RMSE of output layer
    std::float64_t rmse = 0.0;
    for (uint32_t n = 0; n < m_layers.back().size(); ++n)
    {
        rmse += pow(targetVals[n] - m_layers.back().at(n).getOutputVal(), 2);
    }
    rmse = sqrt(rmse / m_layers.back().size());

    // Perform exponential smoothing
    static bool isFirstTime = true;
    if (isFirstTime)
    {
        isFirstTime = false;
        m_mvAvgError = rmse;
    }
    else
    {
        std::float64_t sFactor = 0.1; // Smoothing factor
        m_mvAvgError = sFactor * rmse + (1.0 - sFactor) * m_mvAvgError;
    }
}

} // namespace network
