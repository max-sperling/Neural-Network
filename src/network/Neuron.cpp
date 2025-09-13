/**
 * @author Max Sperling
 */

#include "Neuron.hpp"
#include "Layer.hpp"

#include <cmath>
#include <iostream>
#include <vector>

namespace network {

namespace {

std::float64_t activationFunction(std::float64_t x)
{
    return tanh(x);
}

std::float64_t activationFunctionDerivative(std::float64_t x)
{
    // d/dx(tanh(x)) = 1 - tanh²(x)

    return 1.0 - pow(tanh(x), 2);
}

std::float64_t errorFunctionDerivative(std::float64_t actual, std::float64_t expected)
{
    // d/dx(1/2(tanh(y-ŷ))²) = y - ŷ

    return actual - expected;
}

} // namespace

void printVector(std::vector<Edge>& v)
{
    for (uint32_t i = 0; i < v.size(); ++i)
    {
        v[i].print();
        std::cout << std::endl;
    }
}

Neuron::Neuron(int32_t index, uint32_t numOutputs, bool isBias)
    : m_index(index), m_outputEdges(), m_outputVal(0.0), m_inputGradient(0.0)
{
    for (uint32_t i = 0; i < numOutputs; ++i)
    {
        m_outputEdges.push_back(Edge());
        m_outputEdges.back().m_weight = rand() / std::float64_t(RAND_MAX);
    }

    m_outputVal = (!isBias ? 0.0 : 1.0);
}

void Neuron::setOutputVal(std::float64_t val)
{
    m_outputVal = val;
}

std::float64_t Neuron::getOutputVal() const
{
    return m_outputVal;
}

void Neuron::calcOutputVal(Layer& prevLayer)
{
    std::float64_t sum = 0.0;

    auto addInputVal = [this, &sum] (Neuron& neuron)
    {
        sum += neuron.m_outputEdges[m_index].m_weight
             * neuron.getOutputVal();
    };

    for (unsigned n = 0; n < prevLayer.size(); ++n)
    {
        addInputVal(prevLayer.at(n));
    }

    std::optional<Neuron>& biasNode = prevLayer.getBias();
    if (biasNode.has_value())
    {
        addInputVal(biasNode.value());
    }

    m_outputVal = activationFunction(sum);
}

void Neuron::calcInpGradOutNeuron(std::float64_t targetVal)
{
    // ∂y_[r,n]/∂x_[r,n]
    std::float64_t localGradient = activationFunctionDerivative(m_outputVal);

    // ∂E_{y_[r,n]}/∂y_[r,n]
    std::float64_t outputGradient = errorFunctionDerivative(m_outputVal, targetVal);

    // ∂E_{y_[r,n]}/∂x_[r,n]
    m_inputGradient = outputGradient * localGradient;
}

void Neuron::calcInpGradHidNeuron(Layer& nextLayer)
{
    // ∂y_[r,c]/∂x_[r,c]
    std::float64_t localGradient = activationFunctionDerivative(m_outputVal);

    // ∂E_{y_[r,c]}/∂y_[r,c])
    auto calcOutputGrad = [this, &nextLayer] ()
    {
        std::float64_t sum = 0.0;

        for (uint32_t n = 0; n < nextLayer.size(); ++n)
        {
            sum += m_outputEdges[n].m_weight * nextLayer.at(n).m_inputGradient;
        }

        return sum;
    };
    std::float64_t outputGradient = calcOutputGrad();

    // ∂E_{y_[r,c]}/∂x_[r,c]
    m_inputGradient = outputGradient * localGradient;
}

void Neuron::updateInputWeights(Layer& prevLayer)
{
    std::float64_t learnRate = 0.09; // Learning rate
    std::float64_t momFactor = 0.50; // Momentum factor

    auto updateWeight = [this, &learnRate, &momFactor] (Neuron& neuron)
    {
        std::float64_t oldDeltaWeight = neuron.m_outputEdges[m_index].m_deltaWeight;
        std::float64_t newDeltaWeight = - learnRate * neuron.getOutputVal() * m_inputGradient
                                   + momFactor * oldDeltaWeight;

        neuron.m_outputEdges[m_index].m_deltaWeight = newDeltaWeight;
        neuron.m_outputEdges[m_index].m_weight += newDeltaWeight; 
    };

    for (uint32_t n = 0; n < prevLayer.size(); ++n)
    {
        updateWeight(prevLayer.at(n));
    }

    std::optional<Neuron>& biasNode = prevLayer.getBias();
    if (biasNode.has_value())
    {
        updateWeight(biasNode.value());
    }
}

void Neuron::print()
{
    std::cout << "Neuron " << m_index << " outVal=" << m_outputVal << " inpGrad=" << m_inputGradient << std::endl;
    printVector(m_outputEdges);
    std::cout << std::endl;
}

} // namespace network
