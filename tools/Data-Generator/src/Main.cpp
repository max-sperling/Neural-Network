/**
 * @author Max Sperling
 */

#include <array>
#include <bitset>
#include <cstdint>
#include <ctime>
#include <iostream>

namespace {

void generate_xor(uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t in1 = rand() % 2;
        uint32_t in2 = rand() % 2;
        uint32_t res = in1 ^ in2;

        std::cout << "in: " << in1 << " " << in2 << "\n";
        std::cout << "out: " << res << "\n";
    }
    std::cout << std::flush;
}

void generate_mul(uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t in1 = rand() % 4;
        uint32_t in2 = rand() % 4;
        uint32_t res = in1 * in2;

        std::cout << "in: ";
        for (char c : std::bitset<2>(in1).to_string()) { std::cout << c << " "; }
        for (char c : std::bitset<2>(in2).to_string()) { std::cout << c << " "; }
        std::cout << "\n";

        std::cout << "out: ";
        for (char c : std::bitset<4>(res).to_string()) { std::cout << c << " "; }
        std::cout << "\n";
    }
    std::cout << std::flush;
}

void generate_div(uint32_t count)
{
    static constexpr std::array<std::array<uint32_t, 20>, 10> numbers = {{
        {1, 1, 1, 1,  1, 0, 0, 1,  1, 0, 0, 1,  1, 0, 0, 1,  1, 1, 1, 1}, // 0
        {0, 0, 1, 1,  0, 1, 0, 1,  1, 0, 0, 1,  0, 0, 0, 1,  0, 0, 0, 1}, // 1
        {1, 1, 1, 1,  0, 0, 0, 1,  1, 1, 1, 1,  1, 0, 0, 0,  1, 1, 1, 1}, // 2
        {1, 1, 1, 1,  0, 0, 0, 1,  0, 1, 1, 1,  0, 0, 0, 1,  1, 1, 1, 1}, // 3
        {1, 0, 0, 0,  1, 0, 1, 0,  1, 1, 1, 1,  0, 0, 1, 0,  0, 0, 1, 0}, // 4
        {1, 1, 1, 1,  1, 0, 0, 0,  1, 1, 1, 1,  0, 0, 0, 1,  1, 1, 1, 1}, // 5
        {1, 1, 1, 1,  1, 0, 0, 0,  1, 1, 1, 1,  1, 0, 0, 1,  1, 1, 1, 1}, // 6
        {1, 1, 1, 1,  0, 0, 0, 1,  0, 0, 1, 0,  0, 1, 0, 0,  1, 0, 0, 0}, // 7
        {1, 1, 1, 1,  1, 0, 0, 1,  1, 1, 1, 1,  1, 0, 0, 1,  1, 1, 1, 1}, // 8
        {1, 1, 1, 1,  1, 0, 0, 1,  1, 1, 1, 1,  0, 0, 0, 1,  1, 1, 1, 1}  // 9
    }};

    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t num = rand() % 10;

        std::bitset<10> divisors;
        for (uint32_t d = 1; d <= 9; ++d)
        {
            if (num % d == 0)
            {
                divisors.set(9 - d);
            }
        }

        std::cout << "in: ";
        for (uint32_t i = 0; i < 20; ++i)
        {
            std::cout << numbers[num][i] << " ";
        }
        std::cout << "\n";

        std::cout << "out: ";
        for (uint32_t i = 0; i < divisors.size(); ++i)
        {
            std::cout << divisors[i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
}

} // namespace

int main(int argc, char* argv[])
{
    srand(static_cast<uint32_t>(time(NULL)));

    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <xor|mul|div> <count>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    uint32_t count = strtoul(argv[2], NULL, 10);

    if (mode == "xor")
    {
        generate_xor(count);
    }
    else if (mode == "mul")
    {
        generate_mul(count);
    }
    else if (mode == "div")
    {
        generate_div(count);
    }
    else
    {
        std::cerr << "Invalid argument. Use 'xor', 'mul' or 'div'." << std::endl;
        return 1;
    }

    return 0;
}
