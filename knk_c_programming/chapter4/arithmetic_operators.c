/*
[4. Expressions]
Expressions: formulas that show how to compute a value

e.g., the simplest expression - variable or constant itself
*/

int a = (b + c) * 2;  // (b + c) * 2 is expression, the whole line is statement


/*
Operators
- Arithmetic
- Relational / Comparison
- Logical
- Assignment 
...

[4.1 Arithmetic Operator]

- Unary: requires "one" operand
- Binary: requires "two" operands

*/

// Both plus and minus here are unary operators
i = +1;
j = -i; 

/*
Binary operators are allowed to mix integer and floting-type numbers, except for the "% (remainder)". 
For %, both operands should be integer.
*/

int a = 10 % 3  // --> 1
int b = 12 % 4  // --> 0
float c = 9 + 2.5f  // --> 11.5
float d = 6.7f / 2  // --> 3.35

/*

/ and % operators require special care:

- For / operator, if both operands are integer, the results is "truncated" into the integer as well, by dropping the fractional part.
e.g., 1 / 2 is 0, not 0.5
- The % operator requires BOTH operands to be integer. (if not, the program won't compile)
- Using zero on the right side of / or % cause "undefined behavior"
- Describing the result when / and % are used with "negative" operands is tricky.
-> In C89, if either operand is negative, the result of a division can be rounded either up or down (e.g., -9 / 7 could be either -1 or -2).
-> Also, the sign of i % j in C89 depends on the implementation (e.g., -9 & 7 could be either -2 or 5).
(이거 조금 헷갈릴 수 있는데, 나머지가 음수임을 허용하냐 아니냐에 따라 갈리는 것. 나머지가 -2처럼 음수여도 된다면, 몫이 -1 이고 나머지가 -2 인것. 만약 나머지가 양수여야 한다면 몫이 -2, 나머지가 5인것) (-9 = -7 * 몫 + 나머지)
- In C99, truncation in division is always towards zero (-9 / 7 = -1) and remainder always has the same sign as i in i % j (-9 % 7 = -2).

*/

/*
[Operator precedende and associativity]
- Operator precedence:

<Highest>
+ - (unary)
* / %
+ - (binary)
<Lowest>

*/

i + j * k  // equivalent to i + (j * k)
-i + -j  // equivalent to (-i) + (-j)
+i + j / k // equivalent to (+i) + (j / k)

/*
Operator precedence rules alone are not enough when an expression contains two or more operators at the same level of precedence
--> Associativity comes in. 

Left associative: if it groups from left to right
ALL binary arithmetic operators (*, /, %, +, -) are all left associative

*/

i - j - k  // equivalent to (i - j) - k
i * j / k  // equivalent to (i * j) / k

/*
Right associative: if it groups from right to left
*/

- + i  // equivalent to -(+i)
