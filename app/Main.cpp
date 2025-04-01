/**
 * @author Max Sperling
 */

#include "reader/Reader.hpp"
#include "network/Network.hpp"

#include "tbb/tbb.h"

#include <iostream>
#include <stdfloat>
#include <sstream>
#include <vector>

using namespace network;
using namespace reader;
using namespace std;

namespace {

bool verbose = false;

void readTopology(char* topoStr, vector<uint32_t>& topoVec)
{
    stringstream stream(topoStr);
    while (!stream.eof())
    {
        uint32_t n = 0;
        stream >> n;
        topoVec.push_back(n);
    }
}

template<typename T>
void printVector(string label, vector<T>& v)
{
    cout << label << " ";
    for (uint32_t i = 0; i < v.size()-1; ++i)
    {
        cout << v[i] << " ";
    }
    cout << v.back() << endl;
}

} // namespace

int main(int argc, char* argv[])
{
    srand(static_cast<uint32_t>(time(NULL)));

    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <topology> <filepath>" << endl;
        return 1;
    }

    cout << "General" << endl;
    cout << "Number of usable threads: " << tbb::info::default_concurrency() << endl;

    vector<uint32_t> topology;
    readTopology(argv[1], topology);
    printVector("Topology of the MLP:", topology);

    Network network(topology);
    vector<float64_t> inputVals, targetVals, resultVals;
    uint32_t epoch = 0;

    Reader reader(argv[2]);
    while (reader.getNextDataset(inputVals, targetVals))
    {
        if (verbose)
        {
            cout << endl;
            network.print();
        }

        cout << endl << "Epoch " << epoch++ << endl;

        network.feedForward(inputVals);
        network.getResults(resultVals);

        printVector("Inputs:", inputVals);
        printVector("Expected Output:", targetVals);
        printVector("Actual Output:", resultVals);

        network.propagateBack(targetVals);

        cout << "Avg Error: " << network.getMvAvgError() << endl;
    }

    return 0;
}
