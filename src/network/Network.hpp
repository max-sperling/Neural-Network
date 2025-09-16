/**
 * @author Max Sperling
 */

#pragma once

#include "Layer.hpp"

#include <cstdint>
#include <stdfloat>
#include <string>
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
    Network(const std::vector<uint32_t>& topology);

    /**
     * @brief Feed values into the network (input layer neurons)
     * @param[in] inputVals ... Values to be feed into the network
     */
    void feedForward(const std::vector<std::float64_t>& inputVals);

    /**
     * @brief Get results from the network (output layer neurons)
     * @param[out] resultVals ... Actual results
     */
    void getResults(std::vector<std::float64_t>& resultVals);

    /**
     * @brief Optimize the network (beginning from the back)
     *
     * Backpropagation is a special case of a gradient descent
     *
     * @param[in] targetVals ... Expected results
     */
    void propagateBack(const std::vector<std::float64_t>& targetVals);

    /**
     * @brief Get the moving average error (exponentially smoothed)
     * @return Moving average error
     */
    std::float64_t getMvAvgError() const;

    /**
     * @brief Provide the current network states
     * @return Current network states
     */
    std::string toString() const;

private:
    void updateMvAvgError(const std::vector<std::float64_t>& targetVals);

    std::vector<Layer> m_layers;
    std::float64_t m_mvAvgError;
};

} // namespace network
