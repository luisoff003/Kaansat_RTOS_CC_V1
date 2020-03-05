#include <stdio.h>
#include <stdlib.h>
#include "param.h"

int main()
{
    InitParam( &P);
    printf("%0.4f\n",P.Jx);
    return 0;
}
