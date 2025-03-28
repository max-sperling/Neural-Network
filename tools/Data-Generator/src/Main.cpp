/**
 * @author Max Sperling
 */

#include <array>
#include <bitset>
#include <cstdint>
#include <ctime>
#include <iostream>

using namespace std;

namespace
{

void generate_xor(uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t in1 = rand() % 2;
        uint32_t in2 = rand() % 2;
        uint32_t res = in1 ^ in2;

        cout << "in: " << in1 << " " << in2 << endl;
        cout << "out: " << res << endl;
    }
}

void generate_mul(uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t in1 = rand() % 4;
        uint32_t in2 = rand() % 4;
        uint32_t res = in1 * in2;

        cout << "in: ";
        for (char c : bitset<2>(in1).to_string()) { cout << c << " "; }
        for (char c : bitset<2>(in2).to_string()) { cout << c << " "; }
        cout << endl;

        cout << "out: ";
        for (char c : bitset<4>(res).to_string()) { cout << c << " "; }
        cout << endl;
    }
}

void generate_div(uint32_t count)
{
    static constexpr array<array<uint32_t, 20>, 10> numbers = {{
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

        bitset<10> divisors;
        for (uint32_t d = 1; d <= 9; ++d)
        {
            if (num % d == 0)
            {
                divisors.set(9 - d);
            }
        }

        cout << "in: ";
        for (uint32_t i = 0; i < 20; ++i)
        {
            cout << numbers[num][i] << " ";
        }
        cout << endl;

        cout << "out: ";
        for (uint32_t i = 0; i < divisors.size(); ++i)
        {
            cout << divisors[i] << " ";
        }
        cout << endl;
    }
}

} // namespace

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned>(time(NULL)));

    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <mul|xor|div>" << " <count>" << endl;
        return 1;
    }

    string mode = argv[1];
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
        cerr << "Invalid argument. Use 'mul', 'xor' or 'div'." << endl;
        return 1;
    }

    return 0;
}
