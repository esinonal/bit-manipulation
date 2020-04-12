/*
 * CS:APP Data Lab
 *
 * <Esin Onal, esin, 10447998>
 *
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif

/************************************************
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int isneg = x>>31; //Now its 1111 if neg, and 0000 if pos.
  x = x^isneg;
  x = x + (~isneg+1);
  return x;
}

/************************************************
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int signX = x>>31;
  int signY = y>>31;
  int xandydiff = signX^signY; //If diff then this is 1.Same=0
  int signZ;
  int xandzdiff;
  xandydiff = ~xandydiff+1;
  signZ = (x+y)>>31;
  xandzdiff = signX^signZ; //If diff then this is 1.Same=0
  xandzdiff = ~xandzdiff+1;
  return (xandydiff&1)|( ~xandzdiff&1);
}

/************************************************
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int num8bit = 85;
  int num32bit = (num8bit | (num8bit<<8) | (num8bit<<16) | (num8bit<<24));
  return !((x&num32bit)^num32bit);
}

/************************************************
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  int numIsZero = x|(~x+1); //if the result is 0, then x is 0, then we should print 1.
  return (numIsZero>>31) +1;
}

/************************************************
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int mask1small = ((17)|(17<<8));
  int mask1 = mask1small|(mask1small<<16);

  int mask2 = mask1<<1;
  int mask3 = mask1<<2;
  int mask4 = mask1<<3;

  //pickup and push/ alignment.
  int mask1x = mask1&x;
  int mask2x = (mask2&x)>>1;
  int mask3x = (mask3&x)>>2;
  int mask4x = ((mask4&x)>>3)&mask1; //15

  //break them off until we get to the 1s. And then add them together.
  int sum = mask1x+mask2x+mask3x+mask4x; //now, one 32bit number.
  int section1 = sum&15;
  int section2;
  int section3;
  int section4;
  int section5;
  int section6;
  int section7;
  int section8;
  int numones;

  sum = sum>>4;
  section2 = sum&15;
  sum = sum>>4;
  section3 = sum&15;
  sum = sum>>4;
  section4 = sum&15;
  sum = sum>>4;
  section5 = sum&15;
  sum = sum>>4;
  section6 = sum&15;

  sum = sum>>4;
  section7 = sum&15;

  sum = sum>>4;
  section8 = sum&15;

  numones = section1+section2+section3+section4+section5+section6+section7+section8;
  return numones;
}

/************************************************
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  return (~x)&(~y);
}

/************************************************
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int maskn = 255<<(n<<3);
  int maskm = 255<<(m<<3);

  int mask1s = (1<<31)>>31;
  int nthbyteatm = ((((maskn&x)>>(n<<3))&255)<<(m<<3));
  int mthbyteatn = ((((maskm&x)>>(m<<3))&255)<<(n<<3));

  return (((maskn | maskm)^mask1s)&x) | (nthbyteatm&mask1s) | (mthbyteatn&mask1s);
}

/************************************************
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = !!x;
  x = ~x+1;
  return (x&y)|((~x)&z);
}

/************************************************
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  return ((x << 1) + x + ((((x<<1)+x)>>31)&3) )>>2;
}

/************************************************
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //find higher order 1s (the "upper" complement of n):
  int highnum = ~n + 33; //number of spaces left.
  int value = !(((x << highnum)>>highnum)^x);
  return value;
} // ((1<<31)&x)>>(highnum+ ~1+1);

/************************************************
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int mask = 255; //need to multiply n by 8. so thats 2^3. so push n<<3.
  n = n<<3;
  mask = mask<<n;
  return ((x&mask)>>n)&255;
}

/************************************************
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
int greatestBitPos(int x) {
  int isneg = (x>>31); //is 1111 if x is neg. else, it is 0000.
  //printf("isneg %d\n", isneg);
  int highest1 = x | (x >> 1);
  int themask;
  highest1 |= (highest1 >> 2);
  highest1 |= (highest1 >> 4);
  highest1 |= (highest1 >> 8);
  highest1 |= (highest1 >> 16); //Now, will have 000011111111111 where 1 is where num starts.
  //printf("highest1 %d\n", highest1);
  themask = ((~highest1)>>1)&x; //Do and x so that if there is weird 1s at start, get rid of them.

  return (isneg&(1<<31))|(~isneg&themask );
}

/************************************************
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
  return (!x)|(!!y);
}

/************************************************
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int condition_1 = (!((x+(~48+1)) >> 31));
  int condition_2 = (!((57 + (~x+1)) >> 31)); //And we want them both to be 1. So;
  return (condition_1 & condition_2 & 1);
}

/************************************************
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x^y);
}

/************************************************
 * isLess - if x < y  then return 1, else return 0
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {  // y-x>0, so y+ ~x +1 >0, y+ ~x >-1, y + ~x >=0.
           //so: !((y + ~x)>>31)
  int negmask = (1<<31);
  int xispos = !(negmask&x); //1 if pos, 0 if neg.
  int yispos = !(negmask&y);  //if x and y are the same sign, no overflow problem.
  int yminusxgreqzero = !((y + ~x)>>31); //if true, 1, else, 0;
  int xandydiff = !(xispos^yispos); // -->if this is 0, they are diff signs.
  int splitmask = ~xandydiff+1; ///if 1111, they are both same sign, else 000.
  int issamenum = ~(!!(x^y))+1; //if is same num, returns 0; , else its 1111.
  return  ((splitmask&yminusxgreqzero)|(~splitmask&(!xispos))) & issamenum;
}

/************************************************
 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  int isneg = !(x>>31);
  return isneg;
}

/************************************************
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int isneg = !((1<<31)&x);
  int hasonlyone1 = !(x&(x+ ~1+1));
  isneg = ~isneg+1; //if ==1111, is pos, else if 0000, is neg.
  hasonlyone1 = ~hasonlyone1+1;//if 1111, has only one1, if 0000, has more.
  x = !(!x);
  return (isneg & hasonlyone1 & 1 & x); //!!x to make sure its not 0.
}

/************************************************
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) { //Trick: - * Tmin = Tmin. Mult by -1 gives itself. Only number.
  int minusTMin = ~x+1;
  int isSame = !(minusTMin^x);
  return (isSame & (!(!x)));  //Only other num for which this is true is 0, so break its impact.
}

/************************************************
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return (~1+1);
}

/************************************************
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */

int rotateLeft(int x, int n) {
  int mask = 0;
  int nzero = !(!n);
  int num;
  int thenumber = ~1+1;
  int mask2 = (1<<n)+ thenumber;
  nzero = ~nzero + 1;                   // If n is zero, nzero is 0. Else, nzero=1111.
  mask = ((~nzero & mask) | (nzero & ((1<<31)>> (n + thenumber))));
  num = ((mask&x)>>(32+ ~n+1))&(mask2);

  return ((x<<n) | (mask2&num));
  //The above example is when unsigned.My code gives -8??
  //return ((x << n) | (x >> (((~n)+1) & 31)));
}

/************************************************
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax) 2147483647
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin) -2147483648
 *   Legal ops: ! ~ & ^ | + << >>./
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) { /////NEED TO ELIMINATE ONE OPERATION !!!!
  int isneg = x>>31; //if neg, is 1111.
  int times2 = (x<<1);
  int times2isneg = times2>>31; //if neg, is 1111.
  int overflow = isneg^times2isneg; //if overflow, 1111. else, 0000.
  int tmin = 1<<31;
  int tmax = tmin+ ~1+1;

  return (overflow&isneg&tmin) | (overflow&(~isneg)&tmax) | ((~overflow)&times2);
}
