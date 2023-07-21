# Calculator App
This is a simple calculator app that takes in a text file with calculations on each line and outputs the results in another text file.

## Usage
Create a text file with calculations on each line. The calculations can include addition, subtraction, multiplication, division, powers, square roots, logarithms, and brackets. For example:
```
1 + 2 * 3 + (4 / 2) ^ 3 + sqrt(16) /  ((20 + 1)  / (3 * 3))
-7 - 7
((log(sqrt(3 ^ 2 + 2 ^ 2 ^ 2) * 2 * sqrt(100)) - 5))
```
More examples and their answers are located in the folder named 'example'.
Run the calculator app with the input text file as an argument.
The app will output the results of the calculations in another text file.

### Example
Input file:
```
1 + 2 * 3 + (4 / 2) ^ 3 + sqrt(16) /  ((20 + 1)  / (3 * 3))
-7 - 7
((log(sqrt(3 ^ 2 + 2 ^ 2 ^ 2) * 2 * sqrt(100)) - 5))
```
Output file:
```
16.71
-14
-3
```

## Code Explanation
The code reads in the name of the input text file from the user and opens it. If the file is not found, it outputs an error message and exits. Otherwise, it opens an output text file named “answers.txt” and reads in each line of the input text file. For each line, it removes any whitespace characters and processes the calculation using a series of functions to handle different operations such as brackets, roots, logarithms, powers, multiplication, subtraction, minus, and plus. The result of each calculation is then written to the output text file. If the calculation is invalid, “Wrong question!” is written to the output file instead. Also, empty lines will be ignored.

## Functions
- `isNum`: checks if a character in a string is a number or not.
- `Brackets`: processes any brackets in the calculation by finding the last opening bracket and next closing bracket in the string. It then extracts the substring between those brackets and passes it to the root function for further processing.
- `root`: processes any square roots in the calculation by finding the first occurrence of “sqrt” in the string and extracting the number after it. It then calculates the square root of that number and replaces “sqrt” and the number with the result.
- `logarithm`: processes any logarithms in the calculation by finding the first occurrence of “log” in the string and extracting the number after it. It then calculates the base-10 logarithm of that number and replaces “log” and the number with the result.
- `power`: processes any powers in calculation by finding first occurrence of “^” in string and extracting two numbers: one before “^” and one after it. It then calculates first number raised to power of second number and replaces both numbers and “^” with result.
- `Multiplies`: processes any multiplication in calculation by finding first occurrence of “x” or “*” in string and extracting two numbers: one before “x”/“*” and one after it. It then calculates product of both numbers and replaces both numbers and “x”/“*” with result.
- `subtraction`: processes any division in calculation by finding first occurrence of “/” in string and extracting two numbers: one before “/” and one after it. It then calculates division of first number by second number and replaces both numbers and “/” with result.
- `Minus`: processes any subtraction in calculation by finding first occurrence of “-” in string (ignoring if it’s at beginning) and extracting two numbers: one before “-” and one after it. It then calculates subtraction of first number by second number and replaces both numbers and “-” with result.
- `Plus`: processes any addition in calculation by finding first occurrence of “+” in string (ignoring if it’s at beginning) and extracting two numbers: one before “+” and one after it. It then calculates addition of first number by second number and replaces both numbers and “+” with result.

I would appreciate it if you could inform me of any potential bugs that are found.