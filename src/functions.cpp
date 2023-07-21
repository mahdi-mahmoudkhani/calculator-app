#include <cmath>
#include <locale>
#include "../include/functions.h"
#include "../include/globals.h"
#include <string>
using namespace std;

bool isNum(string line, int i)
{
    if (signCounter == 1)
    {
        return false;
    }
    else
    {
        switch (line[i])
        {
        case '-':
            signCounter++;
            if (signCounter <= 1)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 48 ... 57:
            return true;
            break;
        case 46: // for "."
            return true;
            break;
        default:
            return false;
        }
    }
}

string Brackets(string line, string &finalResult) // the priority is with the innermost parenthese
{
    int tempFirstBracket = finalResult.find_last_of("(");
    line = finalResult.substr(tempFirstBracket + 1, finalResult.length() - 1);
    int tempSecondBracket = line.find_first_of(")");
    if (tempFirstBracket >= 0 && tempSecondBracket >= 0)
    {
        firstBracket = tempFirstBracket;
        secondBracket = tempSecondBracket;
        inBracketLength = (secondBracket - firstBracket + 1) + tempFirstBracket;
        line = line.substr(0, secondBracket);
    }
    else
    {
        line = finalResult;
        firstBracket = -1;
        secondBracket = -1;
    }
    return root(line, finalResult);
}

string root(string line, string &finalResult)
{
    int rootSign = line.find_first_of("sqrt");
    if (rootSign >= 0)
    {
        string number = "";
        int i = rootSign + 4; // +4 : length of the word "sqrt"
        int rootLoc = rootSign;
        int locCounter = 0;
        while (i < line.length())
        {
            number += line[i];
            i++;
            locCounter++;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        double num = stod(number);
        double tempResult = sqrt(num);
        string result = to_string(tempResult);
        line.replace(rootLoc, locCounter + 4, result);
        return root(line, finalResult);
    }
    return logarithm(line, finalResult);
}

// logarithm func is same as root func, because it finds only one number whitch is after the word "log"

string logarithm(string line, string &finalResult)
{
    int logSign = line.find_first_of("log");
    if (logSign >= 0)
    {
        string number = "";
        int i = logSign + 3; // +3 : length of the word "log"
        int logLoc = logSign;
        int locCounter = 0;
        while (i < line.length())
        {
            number += line[i];
            i++;
            locCounter++;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        double num = stod(number);
        double tempResult = log10(num);
        string result = to_string(tempResult);
        line.replace(logLoc, locCounter + 2, result);
        return logarithm(line, finalResult);
    }
    return power(line, finalResult);
}

// in the rest of the functions, we have to find two numbers; the first one is before sign and the second one is after that
// witch it means these funcs are also similar to eachother
// the main algorithm is still like previous funcs
// functions are arranged according to their priority

string power(string line, string &finalResult)
{
    int powerSign = line.find_first_of("^");
    if (powerSign >= 0)
    {
        string firstNum, secondNum = "";
        int i = powerSign - 1;
        while (i >= 0) // digits are read from the end to the begin
        {
            firstNum += line[i];
            i--;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        firstLoc = i + 1;
        i = powerSign + 1;
        while (i < line.length())
        {
            secondNum += line[i];
            i++;
            if (!isNum(line, i))
            {
                break;
            }
        }
        secondLoc = i;
        reverse(firstNum.begin(), firstNum.end()); // for finding the real number
        double first = stod(firstNum), second = stod(secondNum);
        double tempResult = pow(first, second);
        string result = to_string(tempResult);
        line.replace(firstLoc, secondLoc - firstLoc, result);
        return power(line, finalResult);
    }
    return Multiplies(line, finalResult);
}

string Multiplies(string line, string &finalResult)
{
    int mulSign = line.find_first_of("x");
    if (mulSign < 0)
    {
        mulSign = line.find_first_of("*");
    }
    if (mulSign >= 0)
    {
        string firstNum, secondNum = "";
        int i = mulSign - 1;
        while (i >= 0)
        {
            firstNum += line[i];
            i--;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        firstLoc = i + 1;
        i = mulSign + 1;
        while (i < line.length())
        {
            secondNum += line[i];
            i++;
            if (!isNum(line, i))
            {
                break;
            }
        }
        secondLoc = i;
        reverse(firstNum.begin(), firstNum.end());
        double first = stod(firstNum), second = stod(secondNum);
        double tempResult = first * second;
        string result = to_string(tempResult);
        line.replace(firstLoc, secondLoc - firstLoc, result);
        return Multiplies(line, finalResult);
    }

    return subtraction(line, finalResult);
}

string subtraction(string line, string &finalResult)
{
    int subSign = line.find_first_of("/");
    if (subSign >= 0)
    {
        string firstNum, secondNum = "";
        int i = subSign - 1;
        while (i >= 0)
        {
            firstNum += line[i];
            i--;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        firstLoc = i + 1;
        i = subSign + 1;
        while (i < line.length())
        {
            secondNum += line[i];
            i++;
            if (!isNum(line, i))
            {
                break;
            }
        }
        secondLoc = i;
        reverse(firstNum.begin(), firstNum.end());
        double first = stod(firstNum), second = stod(secondNum);
        double tempResult = first / second;
        string result = to_string(tempResult);
        line.replace(firstLoc, secondLoc - firstLoc, result);
        return subtraction(line, finalResult);
    }
    return Minus(line, finalResult);
}

string Minus(string line, string &finalResult)
{
    int minusSign = line.find_first_of("-");
    if (minusSign >= 0)
    {
        string firstNum, secondNum = "";
        if (minusSign == 0)
        {
            minusSign = line.find_last_of("-");
        }
        int i = minusSign - 1;
        while (i >= 0)
        {
            firstNum += line[i];
            i--;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        firstLoc = i + 1;
        i = minusSign + 1;
        while (i < line.length())
        {
            secondNum += line[i];
            i++;
            if (!isNum(line, i))
            {
                break;
            }
        }
        if (firstNum.empty())
        {
            firstNum = "0";
        }
        secondLoc = i;
        reverse(firstNum.begin(), firstNum.end());
        if (firstNum == "-")
        {
            line.replace(firstLoc, secondLoc - firstLoc, secondNum);
        }
        else
        {
            double first = stod(firstNum), second = stod(secondNum);
            double tempResult = first - second;
            string result = to_string(tempResult);
            line.replace(firstLoc, secondLoc - firstLoc, result);
            if (line.find_last_of("-") == 0 || line.find_last_of("-") == 1)
            {
                return Plus(line, finalResult);
            }
            return Minus(line, finalResult);
        }
    }
    return Plus(line, finalResult);
}

string Plus(string line, string &finalResult)
{
    int plusSign = line.find_first_of("+");
    if (plusSign >= 0)
    {
        string firstNum, secondNum = "";
        int i = plusSign - 1;
        while (i >= 0)
        {
            firstNum += line[i];
            i--;
            if (!isNum(line, i))
            {
                signCounter = 0;
                break;
            }
        }
        if (firstNum.empty())
        {
            firstNum = "0";
        }
        firstLoc = i + 1;
        i = plusSign + 1;
        while (i < line.length())
        {
            secondNum += line[i];
            i++;
            if (!isNum(line, i))
            {
                break;
            }
        }
        secondLoc = i;
        reverse(firstNum.begin(), firstNum.end());
        double first = stod(firstNum), second = stod(secondNum);
        double tempResult = first + second;
        string result = to_string(tempResult);
        line.replace(firstLoc, secondLoc - firstLoc, result);
        return Plus(line, finalResult);
    }
    if (firstBracket >= 0 && secondBracket >= 0)
    {
        finalResult.replace(firstBracket, inBracketLength + 1, line);
    }
    else if (firstLoc >= 0 && secondLoc == finalResult.length())
    {
        finalResult.replace(firstLoc, secondLoc - firstLoc + 1, line);
    }
    else
    {
        finalResult = line; // when there's nothing to calculate
    }
    if (line == finalResult)
    {
        return finalResult;
    }
    else
    {
        return Brackets(line, finalResult);
    }
}
