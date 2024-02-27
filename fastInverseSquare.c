/**
 * https://www.youtube.com/watch?v=p8u_k2LIZyo
 * 
 * Fast Inverse Square from QUAKE 3 source code
 * Why we need inv sqrt, normalize vector.
 * 
 * To normalize it we have formala as 
 * x * (1 / sqrt( x*x + y*y + z*z )) and so on for 3d
 * 
 * How floating points are represented in binary
 * using IEEE 754 standards
 * we use signtific notation
 * 0.042 = 4.2 * 10 ^ -2.
 * 
 * for a 32 bit float 
 * first bit is signed bit 0-> +ve, 1 -> -ve
 * for our purposes the signed bit is always +ve
 * coz we are calculating sqrt and sqrt(-1) ... come on
 * 
 * then next 8 bits define exponents [128 -127]
 * so bit are shifted to -127
 * for exponent to be 4 it should be x ^ (131 - 127)
 * the expoent bits are set to 131 in binary.
 * 
 * the next 23 bits are Mantissa
 * So, in binary signtific notation, we always have first digit as 
 * non zero like 1.1 * 10 ^ 2, 1.004 * 10 ^ -6 like that
 * So, the first digit before decimal will always be 1, So we don't
 * have to store it. the number will always range from [1, 2)
 * they are known as normalized number
 * 
 * so mantissa are rest of the digits 
 * 1 + <mantissa> * 2^(exponent)
 * 
 * BIT REPRESENTATION 2 ^ 23 * E + M
 *  coz guess what 2^23 does it exponent 23 bits
 *  so binary representation is   1 < 8 E bits> <23 M bits> 
 * 
 * NUMBER ( 1 + M / 2^23 ) * 2 ^ (E - 127) 
 *       1 for the always 1 before Mantissa in scientific notation
 *       M / 2^23 for (.3674637) represeation after decimal
 *       E - 127 coz 8 bits and b/w [128, -127]
 * 
 * take log base 2 for the number, we get
 * log (1 + M / 2^23) + E - 127
 * 
 * take up appx. for small values of x .. 
 *  x + u (small variation for close appx.)
 * take u = 0.0430 gives smallest error b/w [0,1]
 * 
 * 
 * now simple Math
 *  log (1 + M / 2^23) + E - 127
 *  M / 2^23 + u + E - 127
 *  1 / 2^23 (M + 2^23 * E) + u - 127
*/
 
#include <stdio.h>
#include <math.h>

// naive, very slow, so much room for optimization
// Because it contains '/' 
// compiler deals with '+' and '*' much faster
float inverseSquareNaive(float x) {
    return 1 / sqrt(x);
}

float Q_rsqrt( float number ) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;

    // take up the float representation as it is from address
    // for bit manipulation
    i = * (long *) &y; // Evil bit hack

    // x = 1 / sqrt(y)
    // log(x) = -1/2 * log y
    // replace log with its number representaion
    // num = M + 2 ^ 23 * E
    // num = 3/2 * 2^23 (127-u) - 1/2 * num (u = 0.0430)
    i = 0x5f3759df - (i >> 1); // i >> 1 divide by 2
    
    // Reverse the evil bit hack 
    y = * (float  *) &i;
    y = y * ( threehalfs - (x2 * y * y));
    // y = y * ( threehalfs - (x2 * y * y)); 
}

int main(int argc, char** argv) {
    // float x = 1.0F;
    // printf("%f -> %b\n", x, 10);
    return 0;
}