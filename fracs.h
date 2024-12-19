#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>


typedef uint32_t vint;
#define SIGN_BIT (1 << 31) 

typedef struct 
{
    bool sign;
    vint num;
    vint den;

} frac;

frac value2frac(vint x)
{
    return (frac){
        .sign = false,
        .num = x,
        .den = 1
    };
}

double frac2value(frac x)
{
    return ((double)x.num / x.den) * (x.sign ? -1 : 1);
}
void print(frac x)
{
    printf("%lf\n", ((double)x.num / (double)x.den) * (x.sign ? -1 : 1));
}

frac normalize(frac x)
{
    while ((x.num > 0x8000) ||
           (x.den > 0x8000) )
    {
        x.num >>= 1;
        x.den >>= 1;
    }

    return x;
}

frac add(frac a, frac b)
{
    a.num *= b.den;
    b.num *= a.den;

    vint den = a.den * b.den;

    if (a.sign) a.num *= -1;
    if (b.sign) b.num *= -1;

    vint num = a.num + b.num;

    bool sign = (num & SIGN_BIT) != 0;
    if (sign) num *= -1;

    return normalize((frac){
        .sign = sign,
        .num  = num,
        .den  = den
    });
}

frac neg(frac x)
{
    x.sign ^= 1;
    return x; 
}


frac mul(frac a, frac b)
{
    return normalize((frac){
        .sign = (a.sign ^ b.sign),
        .num  = (a.num  * b.num ),
        .den  = (a.den  * b.den )
    });
}

frac reci(frac x)
{
    return (frac){
        .sign = x.sign,
        .den  = x.num,
        .num  = x.den
    };
}

frac div(frac a, frac b)
{
    return mul(a, reci(b));
}

bool comp(frac big, frac small)
{
    return !(add(big, neg(small)).sign);
}

