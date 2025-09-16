/**
 * @author Max Sperling
 */

#include "network/Arguments.hpp"
#include "network/Network.hpp"
#include "network/Utils.hpp"
#include "reader/Reader.hpp"

#include "tbb/tbb.h"

#include <chrono>
#include <iostream>
#include <stdfloat>
#include <sstream>
#include <vector>

using namespace network;
using namespace reader;
using namespace std;

namespace {

void readTopology(const string& topoStr, vector<uint32_t>& topoVec)
{
    stringstream stream(topoStr);
    while (!stream.eof())
    {
        uint32_t n = 0;
        stream >> n;
        topoVec.push_back(n);
    }
}

} // namespace

int main(int argc, char* argv[])
{
    srand(static_cast<uint32_t>(time(NULL)));

    std::string topo;
    std::string file;
    uint32_t verboseLvl = 0;
    bool useTBB = false;

    // Parse arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--topo" && i+1 < argc)
        {
            topo = argv[++i];
        }
        else if (arg == "--file" && i+1 < argc)
        {
            file = argv[++i];
        }
        else if (arg == "--verbose-lvl" && i+1 < argc) {
            verboseLvl = stoi(argv[++i]);
        }
        else if (arg == "--tbb") {
            useTBB = true;
        }
    }
    if (topo.empty() || file.empty()) {
        std::cerr << "Usage: " << argv[0]
            << " --topo <topology> --file <filepath> [--verbose-lvl <level> --tbb]" << endl;
        return 1;
    }
    setupArguments(useTBB);

    std::vector<uint32_t> topology;
    readTopology(topo, topology);
    Network network(topology);

    cout << "General" << "\n";
    cout << "Number of usable threads: "
        << (Arguments::getInstance().isUseTBB()
            ? std::to_string(tbb::info::default_concurrency()) : "1")
        << "\n";
    cout << stringifyVector("Topology of the MLP:", topology) << "\n";

    vector<float64_t> inputVals, targetVals, resultVals;
    uint32_t epoch = 0;

    // Start timing
    auto trainStart = std::chrono::high_resolution_clock::now();

    Reader reader(file);
    while (reader.getNextDataset(inputVals, targetVals))
    {
        network.feedForward(inputVals);
        network.getResults(resultVals);
        network.propagateBack(targetVals);

        if (verboseLvl > 0)
        {
            cout << "\n" << "Epoch " << epoch << "\n";
            cout << stringifyVector("Inputs:", inputVals) << "\n";
            cout << stringifyVector("Expected Output:", targetVals) << "\n";
            cout << stringifyVector("Actual Output:", resultVals) << "\n";
            cout << "Avg Error: " << network.getMvAvgError() << "\n";
        }
        if (verboseLvl > 1)
        {
            cout << "\n" << network.toString();
        }

        ++epoch;
    }

    // End timing
    auto trainEnd = std::chrono::high_resolution_clock::now();
    auto trainDuration = std::chrono::duration_cast<std::chrono::milliseconds>(trainEnd - trainStart).count();

    cout << "\n" << "Summary" << "\n";
    cout << "Final Avg Error: " << network.getMvAvgError() << "\n";
    cout << "Training time: " << trainDuration / 1000.0 << " seconds (" << trainDuration << " ms)" << "\n";
    cout << std::flush;

    return 0;
}
