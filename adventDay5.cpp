#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <tuple>

int main()
{
    using namespace std;
    freopen("input1.txt", "r", stdin);

    vector<vector<vector<long>>> matrix;

    // Get the original seed numbers
    vector<long> seedRange;
    string seeds;
    getline(cin, seeds);
    seeds = seeds.substr(seeds.find(':') + 2);
    string nums;
    istringstream istream(seeds);
    while (getline(istream, nums, ' '))
    {
        seedRange.push_back(stol(nums, nullptr, 10));
    }

    // Create vector of all new seed numbers
    vector<long> seedNums;
    for (int i = 1; i < seedRange.size(); i += 2)
    {
        for (int j = 0; j < seedRange[i]; j++)
        {
            seedNums.push_back(seedRange[i - 1] + j);
        }
    }

    string line;
    
    // Remove first empty line
    getline(cin, line);

    vector<vector<long>> pairs;
    while (getline(cin, line))
    {
        // Push back matrix whenever there is an empty line 
        // Do nothing when line is not empty and does not contain integer
        if (any_of(line.begin(), line.end(), ::isdigit)) 
        {
            vector<long> numLine;
            string num;
            istringstream iss(line);
            while (getline(iss, num, ' '))
            {
                numLine.push_back(stol(num, nullptr, 10));
            }
            
            pairs.push_back(numLine);
        }
        else
        {
            if (line == "")
            {
                matrix.push_back(pairs);
                pairs.clear();
            }
        }
    }
    matrix.push_back(pairs);

    // Loop through seed numbers and find the lowest final seed number
    for (long i = 0; i < seedNums.size(); i++)
    {
        for (long j = 0; j < matrix.size(); j++)
        {
            for (long k = 0; k < matrix[j].size(); k++)
            {
                if (seedNums[i] >= matrix[j][k][1] && seedNums[i] <= matrix[j][k][1] + matrix[j][k][2] - 1)
                {
                    seedNums[i] = seedNums[i] - matrix[j][k][1] + matrix[j][k][0];
                    break;
                }
            }
        }
    }
    cout << *min_element(seedNums.begin(), seedNums.end());
}

// PART 1:
/*
int main()
{
    using namespace std;
    freopen("input1.txt", "r", stdin);

    vector<vector<vector<long>>> matrix;

    // Get the original seed numbers
    vector<long> seedNums;
    string seeds;
    getline(cin, seeds);
    seeds = seeds.substr(seeds.find(':') + 2);
    string nums;
    istringstream istream(seeds);
    while (getline(istream, nums, ' '))
    {
        seedNums.push_back(stol(nums, nullptr, 10));
    }

    string line;
    
    // Remove first empty line
    getline(cin, line);

    vector<vector<long>> pairs;
    while (getline(cin, line))
    {
        // Push back matrix whenever there is an empty line 
        // Do nothing when line is not empty and does not contain integer
        if (any_of(line.begin(), line.end(), ::isdigit)) 
        {
            vector<long> numLine;
            string num;
            istringstream iss(line);
            while (getline(iss, num, ' '))
            {
                numLine.push_back(stol(num, nullptr, 10));
            }
            
            pairs.push_back(numLine);
        }
        else
        {
            if (line == "")
            {
                matrix.push_back(pairs);
                pairs.clear();
            }
        }
    }
    matrix.push_back(pairs);

    // Loop through seed numbers and find the lowest final seed number
    for (long i = 0; i < seedNums.size(); i++)
    {
        for (long j = 0; j < matrix.size(); j++)
        {
            for (long k = 0; k < matrix[j].size(); k++)
            {
                if (seedNums[i] >= matrix[j][k][1] && seedNums[i] <= matrix[j][k][1] + matrix[j][k][2] - 1)
                {
                    seedNums[i] = seedNums[i] - matrix[j][k][1] + matrix[j][k][0];
                    break;
                }
            }
        }
    }
    cout << *min_element(seedNums.begin(), seedNums.end());
}
*/

