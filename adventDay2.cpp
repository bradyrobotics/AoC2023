// Part 2:
#include <iostream>
#include <string>

// For some reason compiler throws an error with the string::substr, but it works though...
int main()
{
    using namespace std;

    freopen("input1.txt", "r", stdin);

    string dice;

    int count = 0;
    string line;
    while (getline(cin, line)) 
    {
        int largestBlue = 0;
        int largestRed = 0;
        int largestGreen = 0;

        size_t index = line.find(":");
        int gameNum = stoi(line.substr(5, index - 5));
        
        string temp = line.substr(index + 2);
        while (temp.find(",") != string::npos || temp.find(";") != string::npos)
        {
            size_t commaIndex = temp.find(",");
            size_t semicolonIndex = temp.find(";");
            size_t endIndex = min(commaIndex, semicolonIndex);

            dice = temp.substr(0, endIndex);
            temp = temp.substr(endIndex + 2);

            // Beginning of individual dice checking
            int space = dice.find(" ");
           
            if (dice.substr(space + 1) == "red")
            {
                if (stoi(dice.substr(0, space)) > largestRed)
                {
                    largestRed = stoi(dice.substr(0, space));
                }
            }
            else if (dice.substr(space + 1) == "green")
            {
                if (stoi(dice.substr(0, space)) > largestGreen)
                {
                    largestGreen = stoi(dice.substr(0, space));
                }
            }
            else if (dice.substr(space + 1) == "blue")
            {
                if (stoi(dice.substr(0, space)) > largestBlue)
                {
                    largestBlue = stoi(dice.substr(0, space));
                }
            }
        

        }

        dice = temp;
        int space = dice.find(" ");
        if (dice.substr(space + 1) == "red")
        {
            if (stoi(dice.substr(0, space)) > largestRed)
            {
                largestRed = stoi(dice.substr(0, space));
            }
        }
        else if (dice.substr(space + 1) == "green")
        {
            if (stoi(dice.substr(0, space)) > largestGreen)
            {
                largestGreen = stoi(dice.substr(0, space));
            }
        }
        else if (dice.substr(space + 1) == "blue")
        {
            if (stoi(dice.substr(0, space)) > largestBlue)
            {
                largestBlue = stoi(dice.substr(0, space));
            }
        }
        count += largestRed * largestGreen * largestBlue;
    }
    cout << count;
}



/*

PART I:
#include <iostream>
#include <string>

int main()
{
    using namespace std;

    freopen("input1.txt", "r", stdin);

    int count = 0;
    string line;
    while (getline(cin, line)) 
    {
        int largestBlue = 0;
        int largestRed = 0;
        int largestGreen = 0;
        
        bool addPts = true;
        size_t index = line.find(":");
        int gameNum = stoi(line.substr(5, index - 5));
        
        string temp = line.substr(index + 2);
        while (temp.find(",") != string::npos || temp.find(";") != string::npos)
        {
            size_t commaIndex = temp.find(",");
            size_t semicolonIndex = temp.find(";");
            size_t endIndex = min(commaIndex, semicolonIndex);

            string dice = temp.substr(0, endIndex);
            temp = temp.substr(endIndex + 2);

            // Beginning of individual dice checking
            int space = dice.find(" ");
            if (dice.substr(space + 1) == "red")
            {
                if (stoi(dice.substr(0, space)) > 12)
                {
                    addPts = false;
                }
            }
            else if (dice.substr(space + 1) == "green")
            {
                if (stoi(dice.substr(0, space)) > 13)
                {
                    addPts = false;
                }
            }
            else if (dice.substr(space + 1) == "blue")
            {
                if (stoi(dice.substr(0, space)) > 14)
                {
                    addPts = false;
                }
            }
        }

        string dice = temp;
        int space = dice.find(" ");
        if (dice.substr(space + 1) == "red")
        {
            if (stoi(dice.substr(0, space)) > 12)
            {
                addPts = false;
            }
        }
        else if (dice.substr(space + 1) == "green")
        {
            if (stoi(dice.substr(0, space)) > 13)
            {
                addPts = false;
            }
        }
        else if (dice.substr(space + 1) == "blue")
        {
            if (stoi(dice.substr(0, space)) > 14)
            {
                addPts = false;
            }
        }

        if (addPts)
        {
            count += gameNum;
        }
    }
    cout << count;
}


*/
