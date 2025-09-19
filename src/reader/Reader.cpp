/**
 * @author Max Sperling
 */

#include "Reader.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

namespace reader {

Reader::Reader(const utils::Arguments& args)
    : m_args(args)
{
    m_dataFile.open(m_args.m_file.c_str());
}

Reader::~Reader()
{
    m_dataFile.close();
}

bool Reader::getNextDataset(std::vector<std::float64_t>& inputVals,
                            std::vector<std::float64_t>& outputVals)
{
    if (!m_dataFile.is_open()) {
        std::cerr << "The training data file is not open, but it should be\n";
        std::exit(1);
    }

    inputVals.clear();
    outputVals.clear();

    std::string inputLine;
    std::string outputLine;
    getline(m_dataFile, inputLine);
    getline(m_dataFile, outputLine);

    if (inputLine.empty() || outputLine.empty()) { return false; }

    {
        std::stringstream inpStream(inputLine);

        std::string label;
        inpStream >> label;
        if (label.compare("in:") == 0)
        {
            std::float64_t val;
            while (inpStream >> val)
            {
                inputVals.push_back(val);
            }
        }
    }

    {
        std::stringstream outpStream(outputLine);

        std::string label;
        outpStream >> label;
        if (label.compare("out:") == 0)
        {
            std::float64_t val;
            while (outpStream >> val)
            {
                outputVals.push_back(val);
            }
        }
    }

    return true;
}

} // namespace reader
