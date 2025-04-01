/**
 * @author Max Sperling
 */

#pragma once

#include <fstream>
#include <stdfloat>
#include <string>
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
     */
    Reader(const std::string& filename);

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
    std::ifstream m_dataFile;
};

} // namespace reader
