#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>


typedef uint32_t vint;
#define SIGN_BIT (1 << (sizeof(vint)*8 - 1)) 

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

vint gcd(uint64_t a, uint64_t b)
{
    if ((a | b) == 0) return 1;
    if (a == 0) return b;
    if (b == 0) return a;

    while (a != b)
        if (a > b) a -= b;
        else       b -= a;

    return a ? a : 1;
}

frac normalize(frac x)
{
    vint f = gcd(x.num, x.den);
    x.num /= f;
    x.den /= f;

    return x;
}

frac add(frac a, frac b)
{

    vint sharedNumA = a.num * b.den;
    vint sharedNumB = b.num * a.den;
    vint sharedDen  = a.den * b.den;

    assert((sharedNumA & SIGN_BIT) == 0);
    assert((sharedNumA & SIGN_BIT) == 0);

    if (a.sign) sharedNumA *= -1;
    if (b.sign) sharedNumB *= -1;

    vint resultNum = sharedNumA + sharedNumB;

    bool sign = (resultNum & SIGN_BIT) != 0;
    if (sign) resultNum *= -1;

    return normalize((frac){
        .sign = sign,
        .num  = resultNum,
        .den  = sharedDen
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
    return !add(big, neg(small)).sign;
}

void print(frac x)
{
    printf("%lf\n", ((double)x.num / (double)x.den) * (x.sign ? -1 : 1));
}
