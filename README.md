# bit-manipulation
In this project I got to practice bit manipulations in C. 
The goal was to solve the requirements of each function,
given certain restrictions that applied.

Only a certain operations, given from the set of 
(! ~ & ^ | + << >>), and a certain number of them were permitted
given each function, which were given for each function.

We were not allowed to use control constructs such as if,
do, while, for, switch, etc. We could not use any type of casting,
or any data type other than int.  

The Integer constants had to be 0 through 255 (0xFF), inclusive.
We could not use big constants such as 0xffffffff.

Function definitions are supposed to conform to this style:
int Funct(arg1, arg2, ...) {
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

Further, we were told to use the assumption that our machines:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.



