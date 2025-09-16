/**
 * @author Max Sperling
 */

#pragma once

#include <sstream>
#include <string>

namespace utils {

template<typename T>
std::string stringifyVector(const std::string& label, const std::vector<T>& v)
{
    std::ostringstream oss;
    oss << label << " ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        oss << v[i];
        if (i < v.size() - 1) oss << " ";
    }
    return oss.str();
}

} // namespace utils
