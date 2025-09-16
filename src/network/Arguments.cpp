/**
 * @author Max Sperling
 */

#include "Arguments.hpp"

namespace network {

namespace {

Arguments* g_args = nullptr;

} // namespace

Arguments& Arguments::getInstance()
{
    return *g_args;
}

bool Arguments::isUseTBB() const
{
    return m_useTBB;
}

Arguments::Arguments(bool useTBB) : m_useTBB(useTBB) {}

void setupArguments(bool useTBB)
{
    if (!g_args)
    {
        g_args = new Arguments(useTBB);
    }
}

} // namespace network
