#include <iostream>
#include <string>

int main()
{
    long long count = 0;
    freopen("input1.txt", "r", stdin);
    for (int i = 0; i < 1000; i++)
    {
        std::string s;
        std::cin >> s;
        
        std::string cal;
        
        for (int j = 0; j < s.length(); j++)
        {

            if (std::isdigit(s[j]))
            {
                cal += s[j];
                break;
            }
            else if (j < s.length() - 2 && s.substr(j, 3) == "one")
            {
                cal += "1";
                break;
            }
            else if (j < s.length() - 2 && s.substr(j, 3) == "two")
            {
                cal += "2";
                break;
            }
            else if (j < s.length() - 4 && s.substr(j, 5) == "three")
            {
                cal += "3";
                break;
            }
            else if (j < s.length() - 3 && s.substr(j, 4) == "four")
            {
                cal += "4";
                break;
            }
            else if (j < s.length() - 3 && s.substr(j, 4) == "five")
            {
                cal += "5";
                break;
            }
            else if (j < s.length() - 2 && s.substr(j, 3) == "six")
            {
                cal += "6";
                break;
            }
            else if (j < s.length() - 4 && s.substr(j, 5) == "seven")
            {
                cal += "7";
                break;
            }
            else if (j < s.length() - 4 && s.substr(j, 5) == "eight")
            {
                cal += "8";
                break;
            }
            else if (j < s.length() - 3 && s.substr(j, 4) == "nine")
            {
                cal += "9";
                break;
            }
        }
        
        for (int j = s.length() - 1; j >= 0; j--)
        {
            if (std::isdigit(s[j]))
            {
                cal += s[j];
                break;
            }
            else if (j > 1 && s.substr(j - 2, 3) == "one")
            {
                cal += "1";
                break;
            }
            else if (j > 1 && s.substr(j - 2, 3) == "two")
            {
                cal += "2";
                break;
            }
            else if (j > 3 && s.substr(j - 4, 5) == "three")
            {
                cal += "3";
                break;
            }
            else if (j > 2 && s.substr(j - 3, 4) == "four")
            {
                cal += "4";
                break;
            }
            else if (j > 2 && s.substr(j - 3, 4) == "five")
            {
                cal += "5";
                break;
            }
            else if (j > 1 && s.substr(j - 2, 3) == "six")
            {
                cal += "6";
                break;
            }
            else if (j > 3 && s.substr(j - 4, 5) == "seven")
            {
                cal += "7";
                break;
            }
            else if (j > 3 && s.substr(j - 4, 5) == "eight")
            {
                cal += "8";
                break;
            }
            else if (j > 2 && s.substr(j - 3, 4) == "nine")
            {
                cal += "9";
                break;
            }
        }

        int brate = std::stoi(cal);
        count += brate;
    }
    std::cout << count;
    std::cout << "\n";
}


