/**
 * @author Max Sperling
 */

#include "network/Network.hpp"
#include "reader/Reader.hpp"
#include "utils/Arguments.hpp"
#include "utils/Utils.hpp"

#include "tbb/tbb.h"

#include <chrono>
#include <iostream>
#include <stdfloat>
#include <vector>

int main(int argc, char* argv[])
{
    srand(static_cast<uint32_t>(time(NULL)));

    utils::Arguments args;
    args.parseArguments(argc, argv);

    std::cout << "General" << "\n";
    std::cout << "Threads: " << (args.m_useTBB ? std::to_string(tbb::info::default_concurrency()) : "1") << "\n";
    std::cout << utils::stringifyVector("Topology:", args.m_topo) << "\n";

    // Start timing
    auto trainStart = std::chrono::high_resolution_clock::now();

    network::Network network(args);
    reader::Reader reader(args);
    std::vector<std::float64_t> inputVals, targetVals, resultVals;
    uint32_t epoch = 0;

    while (reader.getNextDataset(inputVals, targetVals))
    {
        network.feedForward(inputVals);
        network.getResults(resultVals);
        network.propagateBack(targetVals);

        if (args.m_verbosity > 0)
        {
            std::cout << "\n" << "Epoch " << epoch << "\n";
            std::cout << utils::stringifyVector("Inputs:", inputVals) << "\n";
            std::cout << utils::stringifyVector("Expected Output:", targetVals) << "\n";
            std::cout << utils::stringifyVector("Actual Output:", resultVals) << "\n";
            std::cout << "Avg Error: " << network.getMvAvgError() << "\n";
        }
        if (args.m_verbosity > 1)
        {
            std::cout << "\n" << network.toString();
        }

        ++epoch;
    }

    // End timing
    auto trainEnd = std::chrono::high_resolution_clock::now();
    auto trainDuration = std::chrono::duration_cast<std::chrono::milliseconds>(trainEnd - trainStart).count();

    std::cout << "\n" << "Summary" << "\n";
    std::cout << "Final Avg Error: " << network.getMvAvgError() << "\n";
    std::cout << "Training time: " << trainDuration / 1000.0 << " seconds (" << trainDuration << " ms)" << "\n";
    std::cout << std::flush;

    return 0;
}
