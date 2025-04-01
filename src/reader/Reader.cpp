/**
 * @author Max Sperling
 */
#include "Reader.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace reader {

Reader::Reader(const string& filename)
{
    m_dataFile.open(filename.c_str());
}

Reader::~Reader()
{
    m_dataFile.close();
}

bool Reader::getNextDataset(vector<float64_t>& inputVals,
                            vector<float64_t>& outputVals)
{
    assert(m_dataFile.is_open());

    inputVals.clear();
    outputVals.clear();

    string inputLine, outputLine;
    getline(m_dataFile, inputLine);
    getline(m_dataFile, outputLine);

    if (inputLine.empty() || outputLine.empty()) { return false; }

    {
        stringstream inpStream(inputLine);

        string label;
        inpStream >> label;
        if (label.compare("in:") == 0)
        {
            float64_t val;
            while (inpStream >> val)
            {
                inputVals.push_back(val);
            }
        }
    }

    {
        stringstream outpStream(outputLine);

        string label;
        outpStream >> label;
        if (label.compare("out:") == 0)
        {
            float64_t val;
            while (outpStream >> val)
            {
                outputVals.push_back(val);
            }
        }
    }

    return true;
}

} // namespace reader
