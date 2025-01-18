#include <stdio.h>

int main()
{
    enum month{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
    
    enum month get_month(enum month m) {
        return(m);
    }
    
    printf("%u\n", get_month(apr));

    return 0;
}