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
            auto verbosity = std::stoi(argv[++i]);
            if (verbosity < 0 || verbosity > 2) {
                std::cerr << "Verbosity level must be between 0 and 2, default is taken instead now" << std::endl;
            }
            else
            {
                m_verbosity = static_cast<uint32_t>(verbosity);
            }
        }
    }

    if (m_topo.empty() || m_file.empty()) {
        std::cerr << "Usage: " << argv[0]
            << " --topo <topology> --file <filepath> [--verbosity <level>]" << std::endl;
        std::exit(1);
    }
}

} // namespace utils
