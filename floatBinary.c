/* FLOATING POINT NUMBER IEE754 standards
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
*/

#include <stdio.h>

//////////////////////////////////////////////

void printBinary(int n, int i){
	int k;
	for (k = i - 1; k >= 0; k--) {
		printf ((n >> k) & 1 ? "1" :"0");
	}
}

typedef union {
	float f;
	struct{
		unsigned int mantissa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} raw;
} myfloat;

void printIEEE(myfloat var){
	printf("%d | ", var.raw.sign);
	printBinary(var.raw.exponent, 8);
	printf(" | ");
	printBinary(var.raw.mantissa, 23);
	printf("\n");
}

/////////////////////////////////////////////////////////

void binary( float number ) {
    size_t y = * (size_t *) &number; // Evil bit hack
    char s[33] = "\0";
    // printf("%d: %f\n", y, *(float *)&y);

    for (int i = 31; i >= 0; i--) {
        s[i] = y & 1 ? '1' : '0';
        y >>= 1;
    }

    printf("%s\n", s);
}

int main() {
    float x = 16.75F;
    myfloat var;
    var.f = 2.25;

    // binary(x);
    printIEEE(var);

    return 0;
}
