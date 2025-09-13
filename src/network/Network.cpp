/**
 * @author Max Sperling
 */

#include "Network.hpp"

#include "tbb/parallel_for.h"

#include <cmath>
#include <iostream>
#include <vector>

namespace network {

Network::Network(const std::vector<uint32_t>& topology)
    : m_layers(), m_mvAvgError(0.0)
{
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

        m_layers.push_back(Layer(layerType, outEdges));

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
        bool isFirstLayer = (l == 0);

        tbb::parallel_for(static_cast<uint32_t>(0), m_layers[l].size(),
            [this, l, isFirstLayer, &inputVals](uint32_t n)
            {
                Neuron& neuron = m_layers[l].at(n);

                if (isFirstLayer)
                {
                    neuron.setOutputVal(inputVals[n]);
                }
                else
                {
                    neuron.calcOutputVal(m_layers[l-1]);
                }
            }
        );
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
        bool isLastLayer = (l == m_layers.size()-1);

        tbb::parallel_for(static_cast<uint32_t>(0), m_layers[l].size(),
            [this, l, isLastLayer, &targetVals](uint32_t n)
            {
                Neuron& neuron = m_layers[l].at(n);

                if (isLastLayer)
                {
                    neuron.calcInpGradOutNeuron(targetVals[n]);
                }
                else
                {
                    neuron.calcInpGradHidNeuron(m_layers[l+1]);
                }
            }
        );
    }

    // Update weights of edges
    for (uint32_t l = m_layers.size()-1; l > 0; --l)
    {
        tbb::parallel_for(static_cast<uint32_t>(0), m_layers[l].size(),
            [this, l](uint32_t n)
            {
                m_layers[l].at(n).updateInputWeights(m_layers[l-1]);
            }
        );
    }
}

std::float64_t Network::getMvAvgError() const
{
    return m_mvAvgError;
}

void Network::print()
{
    for (uint32_t l = 0; l < m_layers.size(); ++l)
    {
        m_layers[l].print();
    }
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
