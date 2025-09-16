/**
 * @author Max Sperling
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace utils {

class Arguments
{
public:
    void parseArguments(int argc, char* argv[]);

    std::vector<uint32_t> m_topo;
    std::string m_file;
    uint32_t m_verbosity{};
    bool m_useTBB{};
};

} // namespace utils
