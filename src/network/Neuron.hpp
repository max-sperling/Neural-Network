/**
 * @author Max Sperling
 */
#pragma once
#include "Edge.hpp"
#include <vector>

namespace network {

class Layer;

/**
 * @brief A neuron is the smallest unit.
 *
 * Legend:
 *
 * - x               ... Input value
 * - y               ... Output value (actual)
 * - ŷ               ... Output value (expected)
 * - w               ... Weight of edge
 * - n               ... Last neuron in layer or last layer in network
 * - [r,c]           ... Position in network
 *                        - r ... Index of layer within network (row)
 *                        - c ... Index of neuron within layer (column)
 * - {[r,c],[r+1,c]} ... Transition in network (from [r,c] to [r+1,c])
 * - E               ... Error function (E(y,ŷ) = 1/2(y-ŷ)²)
 * - A               ... Activation function (A(x) = tanh(x))
 * - ∂f/∂x           ... Partial derivative of f in respect to x
 * - Σ_{i=1}_{n}     ... Sum from i=1 until n
 * - α               ... Learning rate (constant)
 * - β               ... Momentum factor (constant)
 * - ^{t}            ... State at time t
 * - Δ               ... Difference value
 */
class Neuron
{
public:
    /**
     * @brief Construct a neuron
     * @param[in] index      ... Index within its layer
     * @param[in] numOutputs ... Number of output edges
     * @param[in] isBias     ... Indicates if bias node
     */
    Neuron(int index, unsigned numOutputs, bool isBias = false);

    /**
     * @brief Set the output value
     * @param[in] val ... Output value
     */
    void setOutputVal(double val);

    /**
     * @brief Get the output value
     * @return Output value
     */
    double getOutputVal() const;

    /**
     * @brief Calculate output value
     *
     * Formula:
     * 
     * y_[r,c]
     *     = A(Σ_{i=1}_{n}(w_{[r-1,i],[r,c]} * y_[r-1,i]))
     *
     * @param[in] prevLayer ... Previous layer
     */
    void calcOutputVal(Layer& prevLayer);

    /**
     * @brief Calculate input gradient of output neuron
     *
     * Formula:
     * 
     * ∂E_{y_[r,n]}/∂x_[r,n]
     *     = ∂y_[r,n]/∂x_[r,n]    * ∂E_{y_[r,n]}/∂y_[r,n]
     *     = dA(x_[r,n])/dx_[r,n] * (∂/∂y_[r,n] 1/2(y_[r,n]-ŷ_[r,n])²)
     *     = (1-tanh²(x_[r,n]))   * (y_[r,n] - ŷ_[r,n])
     *
     * @param[in] targetVal ... Expected results
     */
    void calcInpGradOutNeuron(double targetVal);

    /**
     * @brief Calculate input gradient of hidden neuron
     *
     * Formula:
     * 
     * ∂E_{y_[r,c]}/∂x_[r,c]
     *     = ∂y_[r,c]/∂x_[r,c]    * ∂E_{y_[r,c]}/∂y_[r,c])
     *     = df(x_[r,c])/dx_[r,c] * Σ_{i=1}_{n}(∂E_{y_[r+1,i]}/∂y_[r,c])
     *     = (1-tanh²(x_[r,c]))   * Σ_{i=1}_{n}(∂x_[r+1,i]/∂y_[r,c] * ∂E_{y_[r+1,i]}/∂x_[r+1,i])
     *     = (1-tanh²(x_[r,c]))   * Σ_{i=1}_{n}(w_{[r,c],[r+1,i]} * ∂E_{y_[r+1,i]}/∂x_[r+1,i])
     *
     * @param[in] nextLayer ... Next layer
     */
    void calcInpGradHidNeuron(Layer& nextLayer);

    /**
     * @brief Update input weights (with momentum)
     *
     * Formula:
     *
     * w_{[r-1,c_1],[r,c_2]}^{t}
     *     = w_{[r-1,c_1],[r,c_2]}^{t-1} + Δw_{[r-1,c_1],[r,c_2]}^{t}
     *
     * Δw_{[r-1,c_1],[r,c_2]}^{t}
     *     = - α * (∂E_{y_[r,c_2]}/∂w_{[r-1,c_1],[r,c_2]})^{t} + β * Δw_{[r-1,c_1],[r,c_2]}^{t-1}
     * 
     * (∂E_{y_[r,c_2]}/∂w_{[r-1,c_1],[r,c_2]})^{t}
     *     = (∂x_[r,c_2]/∂w_{[r-1,c_1],[r,c_2]})^{t} * (∂E_{y_[r,c_2]}/∂x_[r,c_2])^{t}
     *     = x_[r,c_2]^{t} * (∂E_{y_[r,c_2]}/∂x_[r,c_2])^{t}
     *
     * @param[in] prevLayer ... Previous layer
     */
    void updateInputWeights(Layer& prevLayer);

    /**
     * @brief Print out the current neuron states
     */
    void print();

private:
    int m_index;
    std::vector<Edge> m_outputEdges;
    double m_outputVal;
    double m_inputGradient;
};

}
