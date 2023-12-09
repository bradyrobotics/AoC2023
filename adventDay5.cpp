#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <tuple>

// Note: Some comments are irrelevant/don't make sense

using namespace std;

void computeSegments(tuple<long, long> range, vector<tuple<long, long, long>> &conversions, vector<tuple<long, long>> &remainingSegments);

// Doesn't need to be global, here for no reason
vector<tuple<long, long>> seedNums;

int main()
{
    freopen("input1.txt", "r", stdin);

    vector<vector<tuple<long, long, long>>> matrix;

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

    // Create vector of tuples that contains the start and end range for seed numbers
    for (long i = 1; i < seedRange.size(); i += 2)
    {
        seedNums.push_back(make_tuple(seedRange[i - 1], seedRange[i - 1] + seedRange[i] - 1));
    }

    string line;
    
    // Remove first empty line
    getline(cin, line);

    vector<tuple<long, long, long>> pairs;
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
            tuple<long, long, long> seedLine = make_tuple(numLine[0], numLine[1], numLine[2]);
            pairs.push_back(seedLine);
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

    
    for (long j = 0; j < matrix.size(); j++)
    {
        // Compute segment and append it to the end of the vector
        // Compute next segments until no segments remain

        // List of all the current ranges. These will be added to as the segment is split through the middle.
        // Segment will be appended to seedNums once everything is computed
        vector<tuple<long, long>> segments;
        for (long i = 0; i < seedNums.size(); i++)
        {
            segments.push_back(seedNums[i]);
        }
        seedNums.clear();

        while (segments.size() != 0)
        {

            /* If entire of seed range is enveloped by source-destination range: compute segment for whole seed
                * If seed range envelopes source-destination range: 
                * If overlap is onesided: compute the side that overlaps, push_back vector for the range that need to still be computed
            */
            computeSegments(segments[0], matrix[j], segments);
        }
    }
    // Find lowest element from the first element of each range
    long smallestElement = get<0>(seedNums[0]);
    for (long i = 0; i < seedNums.size(); i++)
    {
        if (get<0>(seedNums[i]) < smallestElement)
        {
            smallestElement = get<0>(seedNums[i]);
        }
    }
    cout << smallestElement << " <- Answer!";
}

void computeSegments(tuple<long, long> range, vector<tuple<long, long, long>> &conversions, vector<tuple<long, long>> &remainingSegments)
{
    // Check cases where segment is before, after, and in the middle of the range
    for (long i = 0; i < conversions.size(); i++)
    {
        double segStart = get<0>(range);
        double segEnd = get<1>(range);
        double sourceStart = get<1>(conversions[i]);
        double sourceEnd = get<1>(conversions[i]) + get<2>(conversions[i]) - 1;
        double destinationStart = get<0>(conversions[i]);
        double destinationEnd = get<0>(conversions[i]) + get<2>(conversions[i]) - 1;

        if (segStart >= sourceStart && segEnd <= sourceEnd)
        {
            // Compute the entire new segment in the range
            seedNums.push_back(make_tuple(segStart - sourceStart + destinationStart, segEnd - sourceStart + destinationStart));
            remainingSegments.erase(remainingSegments.begin() + 0);
            return;
        }
        // If the seed range envelopes the source-destination range
        else if (segStart <= sourceStart && segEnd >= sourceEnd)
        {
            // Compute the new segment in the range
            seedNums.push_back(make_tuple(destinationStart, destinationEnd));
            remainingSegments.erase(remainingSegments.begin() + 0);

            // Add the segment before the range to remaniningSegments
            if (segStart < sourceStart)
            {
                remainingSegments.push_back(make_tuple(segStart, sourceStart - 1));
            }

            // Add the segment after the range to remainingSegments
            if (segEnd > sourceEnd)
            {
                remainingSegments.push_back(make_tuple(sourceEnd + 1, segEnd));
            }
            return;
        }
        // If left side of seed range is in source-destination range
        else if (segStart >= sourceStart && segStart <= sourceEnd)
        {
            // Compute the side that is in the range, call computeSegments for the segment that is not
            seedNums.push_back(make_tuple(segStart - sourceStart + destinationStart, destinationEnd));
            remainingSegments.erase(remainingSegments.begin());

            if (segEnd > sourceEnd)
            {
                remainingSegments.push_back(make_tuple(sourceEnd + 1, segEnd));
            }
            return;
        }
        // If right side of seed range is in source-destination range
        else if (segEnd >= sourceStart && segEnd <= sourceEnd)
        {
            seedNums.push_back(make_tuple(destinationStart, segEnd - sourceStart + destinationStart));
            remainingSegments.erase(remainingSegments.begin() + 0);

            if (segStart < sourceStart)
            {
                remainingSegments.push_back(make_tuple(segStart, sourceStart - 1));
            }
            return;
        }
    }
    // If segment does not meet any conditions, remove it from remainingSegments and put it back in seedNums
    seedNums.push_back(range);
    remainingSegments.erase(remainingSegments.begin());
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


