/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
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

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 *   lsbZero - set 0 to the least significant bit of x 
 *   Example: lsbZero(0x87654321) = 0x87654320
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 1
 */
int lsbZero(int x) {
  // 丢弃最低有效位
  x = x >> 1;
  // 左移一位，最低有效位置0
  x = x << 1;
  return x;
}
/* 
 * byteNot - bit-inversion to byte n from word x  
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByteNot(0x12345678,1) = 0x1234A978
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int byteNot(int x, int n) {
  // 先生成偏移为 n * 8 的 0xff 掩码，再与 x 对应位进行异或
  x = x ^ (0xff << (n << 3));
  return x;
}
//1111 1111 1111 1111 1111 1111 1111 1111
//0000 0000 0000 0000 1111 1111 0000 0000
/* 
 *   byteXor - compare the nth byte of x and y, if it is same, return 0, if not, return 1

 *   example: byteXor(0x12345678, 0x87654321, 1) = 1

 *			  byteXor(0x12345678, 0x87344321, 2) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2 
 */
int byteXor(int x, int y, int n) {
  // 先生成偏移为 n * 8 的 0xff 掩码，再与 x 对应位进行与运算，只保留对应位
  x = x & (0xff << (n << 3));
  // 同x
  y = y & (0xff << (n << 3));
  // 将x与y进行异或运算，结果中仅保留第n个字节
  x = x ^ y; 
  // 两次逻辑非，变为0或1
  return !!x;
}
/* 
 *   logicalAnd - x && y
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalAnd(int x, int y) {
  // 先用两次逻辑非将x, y转化成0或1，再按位与
  return (!!x) & (!!y);
}
/* 
 *   logicalOr - x || y
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalOr(int x, int y) {
  // 同逻辑与
  return (!!x) | (!!y);
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  // 创建一个掩码，将高位的n位设置为1，其余位设置为0
  int a = (~0) << n; 
  // 取反掩码
  a = ~a;
  // 将x右移(32 - n)位，与掩码异或得到原来低(32-n)位
  a = a & (x >> (32 + (~n + 1)));
  // 将x左移n位，低位补零
  x = x << n;
  //按位或，缝合原来高n位和低(32-n)位
  x = x | a;
  return x;
}
/*
 * parityCheck - returns 1 if x contains an odd number of 1's
 *   Examples: parityCheck(5) = 0, parityCheck(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int parityCheck(int x) {
  // 将x的高16位与低16位进行异或，结果中每个位表示对应位上1的个数的奇偶性
  x = x ^ (x >> 16);
  // 将x与右移8位的x进行异或运算，将结果中每个8位子块表示对应子块中1的个数的奇偶性
  x = x ^ (x >> 8);
  // 将x与右移4位的x进行异或运算，将结果中每个4位子块表示对应子块中1的个数的奇偶性
  x = x ^ (x >> 4);
  // 将x与右移2位的x进行异或运算，将结果中每个2位子块表示对应子块中1的个数的奇偶性
  x = x ^ (x >> 2);
  // 将x与右移1位的x进行异或运算，将结果中每个1位子块表示对应子块中1的个数的奇偶性
  x = x ^ (x >> 1);
  // 返回结果的最低位，表示原始x中1的个数的奇偶性
  return x & 0x1;
}
/*
 * mul2OK - Determine if can compute 2*x without overflow
 *   Examples: mul2OK(0x30000000) = 1
 *             mul2OK(0x40000000) = 0
 *         
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2
 */
int mul2OK(int x) {
  int a; // 存储最高位的值
  int z; // 存储次高位的值

  // 得到次高位的值
  z = 1 & (x >> 30);
  // 得到最高位的值
  a = 1 & (x >> 31);
  // 判断次高位和最高位的值是否相同，然后取反返回结果
  return (z ^ a) ^ 1;
}   
/*
 * mult3div2 - multiplies by 3/2 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/2),
 *   including overflow behavior.
 *   Examples: mult3div2(11) = 16
 *             mult3div2(-9) = -13
 *             mult3div2(1073741824) = -536870912(overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int mult3div2(int x) {
  int a;// 临时变量用于存储乘以3的结果
  int s;// 用于存储乘以3后的奇偶性
  int ss;// 用于存储乘以3后的符号位

  // 先乘以2，再加原数
  a = (x << 1) + x;
  // 获取最低位
  s = a & 0x1;
  // 获取符号位
  ss = (a >> 31) & 0x1;
  // 除二
  a = a >> 1;
  // 根据乘以3后的奇偶性和符号位调整结果
  a = a + (s & ss); 
  return a;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int a;// 临时变量用于存储取反加一的结果
  int b;// 用于存储x的符号位
  int c;// 用于存储判断结果
  int d;// 用于存储y的符号位

  // 获取x的符号位
  b = (x >> 31) & 1;
  // 取y负数
  a = ~y + 1;
  // 获取y的符号位
  d = (y >> 31) & 1;
  // x + (-y)
  a = x + a;
  // 获取结果的符号位
  a = (a >> 31) & 1;
  // 结果与x符号位相反表示溢出
  c = a ^ b;
  // 返回判断结果的逻辑非，或者判断y的符号位与x的符号位是否相同
  return !c | (!(d ^ b)) ;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int a;// 用于存储x的符号位
  int b;// 用于存储x的符号位取负的结果

  // 获取x的符号位，广播到整个32位数中去
  a = x >> 31;
  // 符号位取负值
  b = ~a + 1;
  // 对x进行异或操作去除符号位，然后加上符号位负值的结果，得到绝对值
  return (x ^ a) + b;
}
//
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  int a;// 用于存储去除符号位后的结果

  // 去除符号位
  a = uf & 0x7fffffff;
  // 判断是否为NaN
  if (a > 0x7f800000)
    // 若为NaN，则返回参数本身
    return uf;
  else
    // 否则返回去除符号位后的结果，即绝对值
    return a;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int E;// 用于存储解码后的阶码
  int M;// 用于存储解码后的尾数
  unsigned overflow;// 用于表示超出范围时的返回值
  // 解码阶码部分
  E=(uf>>23)&0xff;
  // 解码尾数部分
  M=(uf&0x007fffff)^0x00800000;
  // 超出范围时的返回值
  overflow=0x80000000u; 
  // 超出最大整数范围，返回over
  if(E>158)
    return overflow;
  else if(E<127)
    // 阶码太小，小于1，返回0
    return 0;
  else if(((uf>>31)&0x1)==1)// 负数情况下
  {
    if(E>150)// 小数部分向左移动E-150位，并取反加一
        return(~(M<<(E-150))+1);
    if(E<150)// 小数部分向右移动150-E位，并取反加一
        return(~(M>>(150-E))+1);
  }
  else// 正数情况下
  {
    if(E>150)// 小数部分向左移动E-150位
        return(M<<(E-150));
    if(E<150) // 小数部分向右移动150-E位
        return(M>>(150-E));
  }
}
