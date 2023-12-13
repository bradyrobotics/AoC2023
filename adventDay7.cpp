#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <tuple>

// Part 2: 

using namespace std;
tuple<long long, long long> calculateHandVal(string hand);

// vals are inversed, because things that come first have higher values
string vals = "J23456789TJQKA";

int main()
{
    freopen("input1.txt", "r", stdin);
    cout << "begin";

    vector<tuple<tuple<long long, long long>, long long>> rankings;
    string line;
    while (getline(cin, line))
    {
        long long index = line.find(' ');

        string hand = line.substr(0, index);
        long long bid = stoi(line.substr(index + 1));

        tuple<long long, long long> handVal = calculateHandVal(hand);

        rankings.push_back(make_tuple(handVal, bid));
    }

    auto comp = [](const auto& a, const auto& b) 
    {
        const auto& a_subtuple = get<0>(a);
        const auto& b_subtuple = get<0>(b);

        // Compare by the first element in the subtuple, which is the rank
        if (get<0>(a_subtuple) < get<0>(b_subtuple)) 
        {
            return true;
        } 
        else if (get<0>(a_subtuple) > get<0>(b_subtuple)) 
        {
            return false;
        }

        // If tie, compare the second element in subtuple, which is the card values in order
        return std::get<1>(a_subtuple) < std::get<1>(b_subtuple);
    };

    // Sort the vector using the comparator
    sort(rankings.begin(), rankings.end(), comp);

    int score = 0;
    for (long long i = 0; i < rankings.size(); i++)
    {
        cout << get<0>(get<0>(rankings[i])) << " : " << get<1>(get<0>(rankings[i])) << " : " << get<1>(rankings[i]) << '\n';
        score += get<1>(rankings[i]) * (i + 1);
    }
    cout << score;
}

// Note: I just chose arbitrary values to seperate different hand values
// Calculate hand value, where the higher the index in string vals, the more value the hand has
tuple<long long, long long> calculateHandVal(string hand)
{  
    // Note: tmp is given distinct names beceause it was giving me an issue in the debugger
    // Keeps track of how many copies there are at a certain index. These copies are tracked by the first occurence of the value
    vector<long long> copiesByIndex;
    for (long long i = 0; i < 5; i++) { copiesByIndex.push_back(0); }

    // For part 2, if there is a joker, add amount of jokers to the highest number in copiesByIndex
    int jCount = 0;
    for (long long i = 0; i < 5; i++)
    {
        if (hand[i] == 'J') { jCount++; }
        // Construct string without hand[i]
        string str = hand.substr(0, i) + hand.substr(i + 1);

        if (str.find(hand[i]) != string::npos && hand[i] != 'J')
        {
            // Increase index in copiesByIndex by 1, at the first index in str where hand[i] has a matching value in str
            size_t loc = str.find(hand[i]);
            // Make sure loc is the right index in case it is after i (Ternary operator>>>>>>>>)
            loc = (loc >= i) ? i : loc;
            copiesByIndex[loc]++;
        }
        // If no match, increase current index by one
        else if (hand[i] != 'J')
        {
            copiesByIndex[i]++;
        }
    }

    // If there is two pair, it does not matter which I increase?
    int mostCopiesIndex = 0;
    for (int i = 1; i < 5; i++)
    {
        if (hand[mostCopiesIndex] == 'J' && hand[i] != 'J')
        {
            mostCopiesIndex = i;
        }
        else if (copiesByIndex[mostCopiesIndex] < copiesByIndex[i] && hand[i] != 'J')
        {
            mostCopiesIndex = i;
        }
    }
    copiesByIndex[mostCopiesIndex] += jCount;

    int mult = 1257728 * vals.find(hand[0]) + 73984 * vals.find(hand[1]) + 4352 * vals.find(hand[2]) + 256 * vals.find(hand[3]) + 16 * vals.find(hand[4]);
    // Five of a kind
    if (find(copiesByIndex.begin(), copiesByIndex.end(), 5) != copiesByIndex.end() || jCount == 5)
    {
        return make_tuple(6, mult);
    }

    // Find four of a kind
    if (find(copiesByIndex.begin(), copiesByIndex.end(), 4) != copiesByIndex.end())
    {
        return make_tuple(5, mult);

    }

    // Find full house and three of a kind
    if (find(copiesByIndex.begin(), copiesByIndex.end(), 3) != copiesByIndex.end())
    {
        // Find full house
        if (find(copiesByIndex.begin(), copiesByIndex.end(), 2) != copiesByIndex.end())
        {
            return make_tuple(4, mult);
        }

        
        return make_tuple(3, mult);
    }


    if (find(copiesByIndex.begin(), copiesByIndex.end(), 2) != copiesByIndex.end())
    {
        // Find two pair
        long long ct = 0;
        for (long long i = 0; i < copiesByIndex.size(); i++)
        {
            if (copiesByIndex[i] == 2)
            {
                ct++;
            }
        }
        if (ct == 2)
        {
            return make_tuple(2, mult);
        }

        return make_tuple(1, mult);
    }

    // Return the hand is all distinct cards
    return make_tuple(0, mult);
}


// Part 1:

/*
using namespace std;
tuple<long long, long long> calculateHandVal(string hand);

// vals are inversed, because things that come first have higher values
string vals = "J23456789TJQKA";

int main()
{
    freopen("input1.txt", "r", stdin);
    cout << "begin";

    vector<tuple<tuple<long long, long long>, long long>> rankings;
    string line;
    while (getline(cin, line))
    {
        long long index = line.find(' ');

        string hand = line.substr(0, index);
        long long bid = stoi(line.substr(index + 1));

        tuple<long long, long long> handVal = calculateHandVal(hand);

        rankings.push_back(make_tuple(handVal, bid));
    }

    auto comp = [](const auto& a, const auto& b) 
    {
        const auto& a_subtuple = get<0>(a);
        const auto& b_subtuple = get<0>(b);

        // Compare by the first element in the subtuple, which is the rank
        if (get<0>(a_subtuple) < get<0>(b_subtuple)) 
        {
            return true;
        } 
        else if (get<0>(a_subtuple) > get<0>(b_subtuple)) 
        {
            return false;
        }

        // If tie, compare the second element in subtuple, which is the card values in order
        return std::get<1>(a_subtuple) < std::get<1>(b_subtuple);
    };

    // Sort the vector using the comparator
    sort(rankings.begin(), rankings.end(), comp);

    int score = 0;
    for (long long i = 0; i < rankings.size(); i++)
    {
        cout << get<1>(get<0>(rankings[i])) << " : " << get<1>(rankings[i]) << '\n';
        score += get<1>(rankings[i]) * (i + 1);
    }
    cout << score;
}

// Note: I just chose arbitrary values to seperate different hand values
// Calculate hand value, where the higher the index in string vals, the more value the hand has
tuple<long long, long long> calculateHandVal(string hand)
{  
    // Note: tmp is given distinct names beceause it was giving me an issue in the debugger
    // Keeps track of how many copies there are at a certain index. These copies are tracked by the first occurence of the value
    vector<long long> copiesByIndex;
    for (long long i = 0; i < 5; i++) { copiesByIndex.push_back(0); }

    // There is a more long longuitive way to do this, which would be just looping through and counting the occurence of each matching value
    for (long long i = 0; i < 5; i++)
    {
        // Construct string without hand[i]
        string str = hand.substr(0, i) + hand.substr(i + 1);

        if (str.find(hand[i]) != string::npos)
        {
            // Increase index in copiesByIndex by 1, at the first index in str where hand[i] has a matching value in str
            size_t loc = str.find(hand[i]);
            // Make sure loc is the right index in case it is after i (Ternary operator>>>>>>>>)
            loc = (loc >= i) ? i : loc;
            copiesByIndex[loc]++;
        }
        // If no match, increase current index by one
        else
        {
            copiesByIndex[i]++;
        }
    }

    int mult = 1257728 * vals.find(hand[0]) + 73984 * vals.find(hand[1]) + 4352 * vals.find(hand[2]) + 256 * vals.find(hand[3]) + 16 * vals.find(hand[4]);
    // Five of a kind
    if (find(copiesByIndex.begin(), copiesByIndex.end(), 5) != copiesByIndex.end())
    {
        return make_tuple(6, mult);
    }

    // Find four of a kind
    if (find(copiesByIndex.begin(), copiesByIndex.end(), 4) != copiesByIndex.end())
    {
        return make_tuple(5, mult);

    }

    // Find full house and three of a kind
    if (find(copiesByIndex.begin(), copiesByIndex.end(), 3) != copiesByIndex.end())
    {
        // Find full house
        if (find(copiesByIndex.begin(), copiesByIndex.end(), 2) != copiesByIndex.end())
        {
            return make_tuple(4, mult);
        }

        
        return make_tuple(3, mult);
    }


    if (find(copiesByIndex.begin(), copiesByIndex.end(), 2) != copiesByIndex.end())
    {
        // Find two pair
        long long ct = 0;
        for (long long i = 0; i < copiesByIndex.size(); i++)
        {
            if (copiesByIndex[i] == 2)
            {
                ct++;
            }
        }
        if (ct == 2)
        {
            return make_tuple(2, mult);
        }

        return make_tuple(1, mult);
    }

    // Return the hand is all distinct cards
    return make_tuple(0, mult);
}
*/
