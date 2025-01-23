// A simple program that demonstrates the use of an enumeration type.

#include <stdio.h>

enum month{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

enum month get_month(enum month m) {
    return(m);
}

int main()
{
    printf("%u\n", get_month(apr));

    return 0;
}