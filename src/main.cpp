#include <iostream>
#include <fstream>
#include <string>
#include "../include/functions.h"
#include "../include/globals.h"
using namespace std;

int main()
{
    string fileName = "";
    cout << "Enter the question file address: " << endl;
    cin >> fileName;
    fstream questionFile;
    questionFile.open(fileName, ios::in);
    if (!questionFile.is_open())
    {
        cerr << "File not found! try again." << endl;
        return 0;
    }
    else
    {
        fstream answersFile;
        answersFile.open("answers.txt", ios::out | ios::app);
        string line;
        while (getline(questionFile, line))
        {
            if (!line.empty())
            {
                line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
                string answer = Brackets(line, line);
                if (isdigit(answer[0]) || answer[0] == '-') // the first character of answer must be a digit
                {
                    answer.erase(answer.end() - 4, answer.end());
                    double tempResult1 = stod(answer);
                    int tempResult2 = tempResult1;
                    if (tempResult1 == tempResult2)
                    {
                        answersFile << tempResult2 << endl;
                    }
                    else
                    {
                        answersFile << answer << endl;
                    }
                }
                else
                {
                    answersFile << "Wrong question!" << endl;
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
        answersFile << "--------------------------------" << endl;
        cout << "succeed! answers are in \"answers.txt\". " << endl;
        answersFile.close();
    }
    questionFile.close();
    return 0;
}