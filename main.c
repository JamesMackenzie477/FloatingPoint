#include <stdio.h>
#include <stdlib.h>

// reads the sign bit of a floating point value
#define READ_SIGN(I) ((*(int*)&I >> 31) & 1)
// reads the exponent of a floating point value
#define READ_EXPONENT(I) (((*(int*)&I >> 23) & 0xFF) - 127)
// reads the mantissa of a floating point value
#define READ_MANTISSA(I) (*(int*)&I & 0x7FFFFF)
// reads the decimal part of a floating point value
#define READ_DECIMAL(I) (0b1 << READ_EXPONENT(I)) + ((READ_MANTISSA(I) >> (23 - READ_EXPONENT(I))) & (0xFFFFFFFF >> (32 - READ_EXPONENT(I))))
// reads the fractional part of a floating point value
#define READ_FRACTION(I) (READ_MANTISSA(I) & (0x7FFFFF >> READ_EXPONENT(I)))

// prints the bits of the given value
void PrintBits(const char* string, int value)
{
    // declares the counter
    int i;
    // stores the current bit
    int bit;
    // finds the start of the binary number
    for (i = 31; i > 0; i--)
    {
        // sets the bit
        bit = ((value >> i) & 1);
        // checks the bit
        if (bit == 1)
        {
            // breaks from the loop
            break;
        }
    }
    // prints the string
    printf(string);
    // iterates through the value
    for (; i >= 0; i--)
    {
        printf("%d", ((value >> i) & 1));
    }
    // adds a newline
    printf("\n");
}

int main()
{
    // defines the floating point value on the stack
    float value = -56.23f;
    // prints the actual value
    printf("actual value: %f\n", value);
    // prints the attributes of the float
    printf("\nsign: %d\n", READ_SIGN(value));
    printf("exponent: %d\n", READ_EXPONENT(value));
    // prints the bits of the mantissa since the value is meaningless
    PrintBits("mantissa: ", READ_MANTISSA(value));
    // checks the sign
    if (READ_SIGN(value) == 1)
        // prints the float
        printf("\ncalculated value: -%d.%d\n", READ_DECIMAL(value), READ_FRACTION(value));
    else
        // prints the float
        printf("\ncalculated value: %d.%d\n", READ_DECIMAL(value), READ_FRACTION(value));
    // exits program
    return 0;
}
