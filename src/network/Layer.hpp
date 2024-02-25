/**
 * @author Max Sperling
 */
#pragma once
#include "Neuron.hpp"
#include <optional>
#include <vector>

namespace network {

/**
 * @brief A layer consists of neurons.
 * 
 * It can be an input, a hidden or an output layer.
 */
class Layer
{
public:
    enum Type
    {
        UNDEF, INPUT, HIDDEN, OUTPUT
    };

    /**
     * @brief Construct a layer
     * @param[in] type       ... Type of the layer
     * @param[in] numOutputs ... Number of output edges (per neuron)
     */
    Layer(Type type, unsigned numOutputs);

    /**
     * @brief Add neuron to the layer
     */
    void addNeuron();

    /**
     * @brief Get neuron by position
     * @param[in] position ... Position of the neuron
     * @return Neuron at position
     */
    Neuron& at(unsigned position);

    /**
     * @brief Get the size of the layer
     * @return Size of the layer
     */
    unsigned size() const;

    /**
     * @brief Get the bias of the layer
     * @return Bias neuron (if existent)
     */
    std::optional<Neuron>& getBias();

    /**
     * @brief Print out the current layer states
     */
    void print();

private:
    unsigned m_numOutputs;
    std::vector<Neuron> m_neurons;
    std::optional<Neuron> m_bias;
};

}
