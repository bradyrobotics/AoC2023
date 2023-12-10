#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <tuple>

// Note: Part 2 is not very efficient, but it works

// Part 2:
using namespace std;

int totalWins();

// Specific indexes in times corresponds to the same index in distances
long times;
long distances;

int main()
{
    freopen("input1.txt", "r", stdin);
    int count = 1;

    string t;
    getline(cin, t);
    size_t index = t.find_first_of("0123456789");
    t = t.substr(index);
    istringstream tread(t);

    string temp;
    while (tread >> temp)
    {
        times = stol(to_string(times) + temp);
    }

    string d;
    getline(cin, d);
    size_t ind = d.find_first_of("0123456789");
    d = d.substr(ind);
    istringstream dread(d);

    string tmp;
    while (dread >> tmp)
    {
        distances = stol(to_string(distances) + tmp);
    }

    count *= totalWins();

    cout << count;
}

int totalWins() // Var i is the race number
{
    vector<long> outcomes;
    long total = 0;

    for (long k = 0; k < times; k++)
    {
        outcomes.push_back(k * (times - k));
    }

    for (long k = 0; k < outcomes.size(); k++)
    {
        if (outcomes[k] > distances)
        {
            total++;
        }
    }

    return total;
}

// Part 1:
// int totalWins(int i);

// // Specific indexes in times corresponds to the same index in distances
// vector<int> times;
// vector<int> distances;

// int main()
// {
//     freopen("input1.txt", "r", stdin);
//     int count = 1;

//     string t;
//     getline(cin, t);
//     size_t index = t.find_first_of("0123456789");
//     t = t.substr(index);
//     istringstream tread(t);

//     string temp;
//     while (tread >> temp)
//     {
//         times.push_back(stoi(temp));
//     }

//     string d;
//     getline(cin, d);
//     index = d.find_first_of("0123456789");
//     d = d.substr(index);
//     istringstream dread(d);
//     while (dread >> temp)
//     {
//         distances.push_back(stoi(temp));
//     }

//     for (int i = 0; i < distances.size(); i++)
//     {
//         count *= totalWins(i);
//     }

//     cout << count;
// }

// int totalWins(int i) // Var i is the race number
// {
//     vector<int> outcomes;
//     int total = 0;

//     for (int k = 0; k < times[i]; k++)
//     {
//         outcomes.push_back(k * (times[i] - k));
//     }

//     for (int k = 0; k < outcomes.size(); k++)
//     {
//         if (outcomes[k] > distances[i])
//         {
//             total++;
//         }
//     }

//     return total;
// }
