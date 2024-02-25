/**
 * @author Max Sperling
 */
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    srand((unsigned)time(NULL));

    for (unsigned i = 0; i < 5000; ++i)
    {
        unsigned in1 = rand() % 2;
        unsigned in2 = rand() % 2;
        unsigned res = in1 ^ in2;

        cout << "in: " << in1 << " " << in2 << endl;
        cout << "out: " << res << endl;
    }

    return 0;
}