#include "rsdl.hpp"
#include <cmath>
#include <vector>
#include <fstream>
#include "headers.hpp"
using namespace std;
float distance_calculator(Point a, Point b)
{
    float d = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return d;
}
int remainder(int seed, int mod)
{
    int remanant = seed % mod;
    while (remanant < 0)
    {
        remanant = remanant + mod;
    }
    return remanant;
}
vector<string> read_file()
{
    vector<string> data;
    ifstream map;
    int t = 0;
    map.open(INPUT_FILE);
    string temp;
    map >> temp;
    while (map.eof() != true)
    {
        map >> temp;
        if (t != 0)
        {
            t++;
        }
        data.push_back(temp);
    }
    map.close();
    return data;
}