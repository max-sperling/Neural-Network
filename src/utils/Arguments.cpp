/**
 * @author Max Sperling
 */

#include "Arguments.hpp"

#include <sstream>
#include <iostream>

namespace utils {

namespace {

std::vector<uint32_t> parseTopology(const std::string& topoStr)
{
    std::vector<uint32_t> topoVec;
    std::stringstream stream(topoStr);
    while (!stream.eof())
    {
        uint32_t n = 0;
        stream >> n;
        topoVec.push_back(n);
    }
    return topoVec;
}

} // namespace

void Arguments::parseArguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--topo" && i+1 < argc)
        {
            m_topo = parseTopology(argv[++i]);
        }
        else if (arg == "--file" && i+1 < argc)
        {
            m_file = argv[++i];
        }
        else if (arg == "--verbosity" && i+1 < argc) {
            m_verbosity = std::stoi(argv[++i]);
        }
        else if (arg == "--tbb") {
            m_useTBB = true;
        }
    }

    if (m_topo.empty() || m_file.empty()) {
        std::cerr << "Usage: " << argv[0]
            << " --topo <topology> --file <filepath> [--verbosity <level> --tbb]" << std::endl;
        std::exit(1);
    }
}

} // namespace utils
