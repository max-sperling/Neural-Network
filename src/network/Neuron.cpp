/**
 * @author Max Sperling
 */
#include "Neuron.hpp"
#include "Layer.hpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

namespace {

double activationFunction(double x)
{
    return tanh(x);
}

double activationFunctionDerivative(double x)
{
    // d/dx(tanh(x)) = 1 - tanh²(x)

    return 1.0 - pow(tanh(x), 2);
}

double errorFunctionDerivative(double actual, double expected)
{
    // d/dx(1/2(tanh(y-ŷ))²) = y - ŷ

    return actual - expected;
}

}

namespace network {

void printVector(vector<Edge>& v)
{
    for (unsigned i = 0; i < v.size(); ++i)
    {
        v[i].print();
        cout << endl;
    }
}

Neuron::Neuron(int index, unsigned numOutputs, bool isBias)
    : m_index(index), m_outputEdges(), m_outputVal(0.0), m_inputGradient(0.0)
{
    for (unsigned i = 0; i < numOutputs; ++i)
    {
        m_outputEdges.push_back(Edge());
        m_outputEdges.back().m_weight = rand() / double(RAND_MAX);
    }

    m_outputVal = (!isBias ? 0.0 : 1.0);
}

void Neuron::setOutputVal(double val)
{
    m_outputVal = val;
}

double Neuron::getOutputVal() const
{
    return m_outputVal;
}

void Neuron::calcOutputVal(Layer& prevLayer)
{
    double sum = 0.0;

    auto addInputVal = [this, &sum] (Neuron& neuron)
    {
        sum += neuron.m_outputEdges[m_index].m_weight
             * neuron.getOutputVal();
    };

    for (unsigned n = 0; n < prevLayer.size(); ++n)
    {
        addInputVal(prevLayer.at(n));
    }

    optional<Neuron>& biasNode = prevLayer.getBias();
    if (biasNode.has_value())
    {
        addInputVal(biasNode.value());
    }

    m_outputVal = activationFunction(sum);
}

void Neuron::calcInpGradOutNeuron(double targetVal)
{
    // ∂y_[r,n]/∂x_[r,n]
    double localGradient = activationFunctionDerivative(m_outputVal);

    // ∂E_{y_[r,n]}/∂y_[r,n]
    double outputGradient = errorFunctionDerivative(m_outputVal, targetVal);

    // ∂E_{y_[r,n]}/∂x_[r,n]
    m_inputGradient = outputGradient * localGradient;
}

void Neuron::calcInpGradHidNeuron(Layer& nextLayer)
{
    // ∂y_[r,c]/∂x_[r,c]
    double localGradient = activationFunctionDerivative(m_outputVal);

    // ∂E_{y_[r,c]}/∂y_[r,c])
    auto calcOutputGrad = [this, &nextLayer] ()
    {
        double sum = 0.0;

        for (unsigned n = 0; n < nextLayer.size(); ++n)
        {
            sum += m_outputEdges[n].m_weight * nextLayer.at(n).m_inputGradient;
        }

        return sum;
    };
    double outputGradient = calcOutputGrad();

    // ∂E_{y_[r,c]}/∂x_[r,c]
    m_inputGradient = outputGradient * localGradient;
}

void Neuron::updateInputWeights(Layer& prevLayer)
{
    double learnRate = 0.09; // Learning rate
    double momFactor = 0.50; // Momentum factor

    auto updateWeight = [this, &learnRate, &momFactor] (Neuron& neuron)
    {
        double oldDeltaWeight = neuron.m_outputEdges[m_index].m_deltaWeight;
        double newDeltaWeight = - learnRate * neuron.getOutputVal() * m_inputGradient
                                + momFactor * oldDeltaWeight;

        neuron.m_outputEdges[m_index].m_deltaWeight = newDeltaWeight;
        neuron.m_outputEdges[m_index].m_weight += newDeltaWeight; 
    };

    for (unsigned n = 0; n < prevLayer.size(); ++n)
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
    cout << "Neuron " << m_index << " outVal=" << m_outputVal << " inpGrad=" << m_inputGradient << endl;
    printVector(m_outputEdges);
    cout << endl;
}

}
