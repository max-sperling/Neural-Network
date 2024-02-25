/**
 * @author Max Sperling
 */
#pragma once
#include "Layer.hpp"
#include <vector>

namespace network {

/**
 * @brief A network consists of layers.
 */
class Network
{
public:
    /**
     * @brief Construct a network
     * @param[in] topology ... Topology of the network
     */
    Network(const std::vector<unsigned>& topology);

    /**
     * @brief Feed values into the network (input layer neurons)
     * @param[in] inputVals ... Values to be feed into the network
     */
    void feedForward(const std::vector<double>& inputVals);

    /**
     * @brief Get results from the network (output layer neurons)
     * @param[out] resultVals ... Actual results
     */
    void getResults(std::vector<double>& resultVals);

    /**
     * @brief Optimize the network (beginning from the back)
     *
     * Backpropagation is a special case of a gradient descent
     *
     * @param[in] targetVals ... Expected results
     */
    void propagateBack(const std::vector<double>& targetVals);

    /**
     * @brief Get the moving average error (exponentially smoothed)
     * @return Moving average error
     */
    double getMvAvgError() const;

    /**
     * @brief Print out the current network states
     */
    void print();

private:
    void updateMvAvgError(const std::vector<double>& targetVals);

    std::vector<Layer> m_layers;
    double m_mvAvgError;
};

}
