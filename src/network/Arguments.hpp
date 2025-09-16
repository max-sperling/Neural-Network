/**
 * @author Max Sperling
 */

#pragma once

namespace network {

class Arguments
{
public:
    static Arguments& getInstance();
    bool isUseTBB() const;
    Arguments(const Arguments&) = delete;
    Arguments& operator=(const Arguments&) = delete;
private:
    friend void setupArguments(bool useTBB);
    explicit Arguments(bool useTBB);
    bool m_useTBB;
};

void setupArguments(bool useTBB);

} // namespace network
