/**
 * @author Max Sperling
 */

#pragma once

#include "utils/Arguments.hpp"

#include <fstream>
#include <stdfloat>
#include <vector>

namespace reader {

/**
 * @brief The reader extracts the datasets from the data file.
 */
class Reader
{
public:
    /**
     * @brief Construct a reader
     * @param[in] args ... Arguments including filename
     */
    Reader(const utils::Arguments& args);

    /**
     * @brief Destruct a reader
     */
    ~Reader();

    /**
     * @brief Get next dataset from file
     * @param[out] inputVals  ... Input values
     * @param[out] outputVals ... Output values
     * @return Dataset still available?
     */
    bool getNextDataset(std::vector<std::float64_t>& inputVals,
                        std::vector<std::float64_t>& outputVals);

private:
    const utils::Arguments& m_args;
    std::ifstream m_dataFile;
};

} // namespace reader
