#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

// NOTE: The second part only works with input of exactly the same length as mine!
int main()
{
    using namespace std;
    freopen("input1.txt", "r", stdin);

    int count = 0;
    int tracker = 0;

    string input;

    vector<int> copies;
    for (int i = 0; i < 205; i++)
    {
        copies.push_back(1);
    }
    while (getline(cin, input))
    {
        int winCard = 0;
        vector<int> winners;
        input = input.substr(input.find(':') + 2);

        size_t index = input.find('|');
        while (index != string::npos)
        {
            int endIndex;
            for (int i = 0; i < input.length(); i++)
            {
                if (isdigit(input[i]))
                {
                    input = input.substr(i);
                    break;
                }
            }

            if (input.find('|') == string::npos)
            {
                break;
            }
            for (int i = 0; i < input.length(); i++)
            {
                if (!isdigit(input[i]))
                {
                    endIndex = i;
                    break;
                }
            }
            winners.push_back(stoi(input.substr(0, endIndex))); 
            input = input.substr(endIndex);
            index = input.find('|');

        }

        for (int i = 0; i < copies[tracker]; i++)
        {
            size_t nextSpace = input.find(' ');
            while (nextSpace != string::npos)
            {
                int endIndex;
                for (int i = 0; i < input.length(); i++)
                {
                    if (isdigit(input[i]))
                    {
                        input = input.substr(i);
                        break;
                    }
                }
                for (int i = 0; i < input.length(); i++)
                {
                    if (!isdigit(input[i]))
                    {
                        endIndex = i; // End Index is the next value where its not a digit, but it can be before the digits too!
                        break;
                    }
                    else if (i == input.length() - 1)
                    {
                        endIndex = input.length();
                    }
                }
                int num = stoi(input.substr(0, endIndex));
                auto isIn = find(winners.begin(), winners.end(), num);
                if (isIn != winners.end())
                {
                    winCard++;
                }

                input = input.substr(endIndex);

                nextSpace = input.find(' ');
            }
            if (winCard > 0)
            {
                for (int j = 0; j < winCard; j++)
                {
                    // if (tracker + j + 1 < copies.size() - 1)
                    // {
                        copies[tracker + j + 1]++;
                    
                }
            }
        }
        tracker++;
    }
    count = accumulate(copies.begin(), copies.end(), 0);
    cout << count << " ";
}




// PT: 1
/* int main()
{
    using namespace std;
    freopen("input1.txt", "r", stdin);

    int count = 0;

    string input;
    while (getline(cin, input))
    {
        vector<int> vect;
        int cardCount = 0;
        vector<int> winners;
        input = input.substr(input.find(':') + 2);

        size_t index = input.find('|');
        while (index != string::npos)
        {
            int endIndex;
            for (int i = 0; i < input.length(); i++)
            {
                if (isdigit(input[i]))
                {
                    input = input.substr(i);
                    break;
                }
            }

            if (input.find('|') == string::npos)
            {
                break;
            }
            for (int i = 0; i < input.length(); i++)
            {
                if (!isdigit(input[i]))
                {
                    endIndex = i;
                    break;
                }
            }
            winners.push_back(stoi(input.substr(0, endIndex))); 
            input = input.substr(endIndex);
            index = input.find('|');

        }

        size_t nextSpace = input.find(' ');
        while (nextSpace != string::npos)
        {
            int endIndex;
            for (int i = 0; i < input.length(); i++)
            {
                if (isdigit(input[i]))
                {
                    input = input.substr(i);
                    break;
                }
            }
            for (int i = 0; i < input.length(); i++)
            {
                if (!isdigit(input[i]))
                {
                    endIndex = i; // End Index is the next value where its not a digit, but it can be before the digits too!
                    break;
                }
                else if (i == input.length() - 1)
                {
                    endIndex = input.length();
                }
            }
            int num = stoi(input.substr(0, endIndex));
            auto isIn = find(winners.begin(), winners.end(), num);
            if (isIn != winners.end())
            {
                cardCount = ((cardCount == 0) ? 1 : cardCount * 2);
            }

            input = input.substr(endIndex);

            nextSpace = input.find(' ');
        }
        count += cardCount;
    }
    cout << count << " ";
}
*/
