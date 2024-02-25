/**
 * @author Max Sperling
 */
#include "reader/Reader.hpp"
#include "network/Network.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace network;
using namespace reader;
using namespace std;

namespace {

bool verbose = false;

void readTopology(char* topoStr, vector<unsigned>& topoVec)
{
    stringstream stream(topoStr);
    while (!stream.eof())
    {
        unsigned n = 0;
        stream >> n;
        topoVec.push_back(n);
    }
}

template<typename T>
void printVector(string label, vector<T>& v)
{
    cout << label << " ";
    for (unsigned i = 0; i < v.size()-1; ++i)
    {
        cout << v[i] << " ";
    }
    cout << v.back() << endl;
}

}

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));

    if (argc != 3)
    {
        cout << "Usage: program <topology> <filepath>" << endl;
        return 1;
    }

    vector<unsigned> topology;
    readTopology(argv[1], topology);
    printVector("Topo:", topology);
    Network network(topology);

    vector<double> inputVals, targetVals, resultVals;
    unsigned epoch = 0;

    Reader reader(argv[2]);
    while (reader.getNextDataset(inputVals, targetVals))
    {
        if (verbose)
        {
            cout << endl;
            network.print();
        }

        cout << endl << "Epoch " << epoch++ << endl;

        network.feedForward(inputVals);
        network.getResults(resultVals);

        printVector("Inputs:", inputVals);
        printVector("Expected Output:", targetVals);
        printVector("Actual Output:", resultVals);

        network.propagateBack(targetVals);

        cout << "Avg Error: " << network.getMvAvgError() << endl;
    }

    return 0;
}
