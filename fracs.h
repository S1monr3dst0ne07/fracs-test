#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct 
{
    bool sign;
    uint64_t num;
    uint64_t den;

} frac;

frac value2frac(uint64_t x)
{
    return (frac){
        .sign = false,
        .num = x,
        .den = 1
    };
}

uint64_t frac2value(frac x)
{
    return (x.num / x.den) * (x.sign ? -1 : 1);
}

uint64_t gcd(uint64_t a, uint64_t b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    while (a != b)
        if (a > b) a -= b;
        else       b -= a;

    return a;
}

frac normalize(frac x)
{
    uint64_t f = gcd(x.num, x.den);
    x.num /= f;
    x.den /= f;

    return x;
}

frac add(frac a, frac b)
{
    return normalize((frac){
        .sign = (a.sign       ^ b.sign      ),
        .num  = (a.num*b.den  + b.num*a.den ),
        .den  = (a.den        * b.den       )
    });
}

frac neg(frac x)
{
    x.sign ^= 1;
    return x; 
}

frac sub(frac a, frac b)
{
    return add(a, neg(b));
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
