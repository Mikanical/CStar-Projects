#include <math.h>
#define n 100                  /* Upper limit for prime numbers */
boolean Prime[n+1];            /* Boolean array to track primes */
int sqrt_n;

/* Function to mark non-primes */
void mark_non_primes(int num) {
    int loc = num * num;
    while (loc <= n) {
        Prime[loc] = false;
        loc += num;
    }
}

main() {
    int i, num, loc;  /* Declare all necessary loop variables */

    /* Initialize Prime array */
    forall i = 2 to n do
        Prime[i] = true;

    sqrt_n = (int)sqrt((double)n);  /* Cast sqrt result to integer */

    /* First process to find primes and mark multiples */
    forall num = 2 to sqrt_n do
        if (Prime[num]) {
            mark_non_primes(num); /* Mark non-primes */
        }

    /* Other processes handle range beyond sqrt(n) */
    forall i = sqrt_n + 1 to n do
        loc = i * i;
        while (loc <= n) {
            Prime[loc] = false;
            loc += i;  /* Increment by step i */
        }

    /* Output all prime numbers */
    forall i = 2 to 10 do
        if (Prime[i]) {
            cout << i << " is prime\n";
        }
}