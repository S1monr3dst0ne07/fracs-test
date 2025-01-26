#include <stdio.h>
#include <stdbool.h>
#include "fracs.h"


int main()
{
    frac accu = value2frac(0);
    vint den = 2;

    for (int i = 0; i < 5; i++)
    {
        accu = add(accu, (frac){
            .sign = false,
            .num = 1,
            .den = den,
        });
        den *= 2;

        print(accu);
    }

}
