#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <tuple>
#include <deque>

// Part 2: Brute Force takes to long. Solution is to identify where current node becomes a cycle, and then find where all cycles overlap
using namespace std;

long long leastCommonMultiple(deque<long long> nums);

int main()
{
    // Every node cycles
    freopen("input1.txt", "r", stdin);

    string pattern;
    getline(cin, pattern);
    vector<tuple<string, string, string>> nodes;

    string s;
    while (getline(cin, s))
    {
        if (!s.empty())
        {
            string start = s.substr(0, 3);
            string left = s.substr(7, 3);
            string right = s.substr(12, 3);

            nodes.push_back(make_tuple(start, left, right));
        }
    }

    vector<string> currentNodes;
    for (long long i = 0; i < nodes.size(); i++)
    {
        if (get<0>(nodes[i]).substr(2) == "A")
        {
            currentNodes.push_back(get<0>(nodes[i]));
        }
    }

    deque<long long> cycleList;
    long long patternIndex = 0;

    for (long long i = 0; i < currentNodes.size(); i++)
    {
        long long count = 0;
        while (currentNodes[i].substr(2) != "Z")
        {
            for (long long j = 0; j < nodes.size(); j++)
            {
                if (currentNodes[i] == get<0>(nodes[j]))
                {
                    currentNodes[i] = (pattern[patternIndex] == 'L') ? get<1>(nodes[j]) : get<2>(nodes[j]);
                    break;
                }
            }
            count++;
            patternIndex++;
            patternIndex = patternIndex % pattern.length();
        }
        cycleList.push_back(count);
    }

    cout << leastCommonMultiple(cycleList);
}

long long leastCommonMultiple(deque<long long> nums)
{
    long long lcm = 0;
    long long gcd;
    // Calculate GCD using Euclidean algorithm
    long long a;
    long long b;
    if (nums[0] >= nums[1])
    {
        a = nums[0];
        b = nums[1];
    }
    else
    {
        b = nums[0];
        a = nums[1];
    }

    long long remainder = -1;
    while (remainder != 0)
    {
        remainder = a % b;
        a = b;
        b = remainder;
        remainder = a % b;
    }
    gcd = b;



    lcm = (nums[0] * nums[1]) / gcd;

    if (nums.size() == 2) { return lcm; }

    // Return recursive call of function for the LCM + rest of nums
    nums.pop_front();
    nums.pop_front();
    nums.push_front(lcm);
    return leastCommonMultiple(nums);
}

// Part 1:
/*
long long main()
{
    freopen("input1.txt", "r", stdin);

    string pattern;
    getline(cin, pattern);
    vector<tuple<string, string, string>> nodes;

    string s;
    while (getline(cin, s))
    {
        if (!s.empty())
        {
            string start = s.substr(0, 3);
            string left = s.substr(7, 3);
            string right = s.substr(12, 3);

            nodes.push_back(make_tuple(start, left, right));
        }
    }

    string currentNode = "AAA";
    long long patternIndex = 0;
    long long count = 0;

    while (currentNode != "ZZZ")
    {
        for (long long i = 0; i < nodes.size(); i++)
        {
            if (currentNode == get<0>(nodes[i]))
            {
                currentNode = (pattern[patternIndex] == 'L') ? get<1>(nodes[i]) : get<2>(nodes[i]);
                patternIndex++;
                patternIndex = patternIndex % pattern.length();
                break;
            } 
        }
        count++;
    }
    cout << count;
}
*/
