/* PROGRAM Jacobi_Conv */
#include <math.h>
#define n 5
#define tolerance .01

/* Global Variables and Spinlocks */
float A[n+2][n+2], B[n+2][n+2];
int i, j;
int count;
spinlock Arrival, Departure;
boolean globaldone;

void Barrier( )  {   
    /* Arrival Phase - Count processes as they arrive */
    Lock(Arrival);     
    count = count + 1;   
    if (count < n)      
        Unlock(Arrival);        /* continue Arrival Phase */     
    else 
        Unlock(Departure); /* end Arrival Phase */   

    /* Departure Phase - Count processes as they leave */
    Lock(Departure);     
    count = count - 1;   
    if (count > 0)      
        Unlock(Departure);    /* continue Departure Phase */     
    else 
        Unlock(Arrival); /* end Departure Phase */ 
}

boolean Aggregate(boolean mydone)  {   
    boolean result;    

    /* Arrival Phase - Count the processes arriving */
    Lock(Arrival);     
    count = count + 1;     
    globaldone = globaldone && mydone; /* aggregation */
    if (count < n)     
        Unlock(Arrival);        /* continue Arrival Phase */     
    else 
        Unlock(Departure); /* end Arrival Phase */   

    /* Departure Phase - Count the processes leaving */
    Lock(Departure);     
    count = count - 1;     
    result = globaldone; /* return "done" flag */
    if (count > 0)      
        Unlock(Departure);   /* continue Departure Phase */     
    else {       
        Unlock(Arrival);   /* terminate Departure Phase */       
        globaldone = true; /* reset for new Aggregation */     
    }   
    return(result); 
}

main() {
    /* Read in initial values for array A */
    cout << "Enter the initial values for the matrix A:\n";
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cin >> A[i][j];
        }
    }

    /* Initialize Shared Variables and Spinlocks */
    count = 0;  /* Initialize "count" */
    Unlock(Arrival);    
    Lock(Departure);   
    globaldone = true;  /* Initialize global flag */

    B = A;

    forall i = 1 to n do { /*Create the processes*/
        int j;
        float change, maxchange;
        boolean done;
        do {
            maxchange = 0;
            for (j = 1; j <= n; j++) {
                /*compute new value for each point in my row*/
                B[i][j] = (A[i-1][j] + A[i+1][j] + 
                           A[i][j-1] + A[i][j+1]) / 4;
                change = fabs(B[i][j] - A[i][j]);
                if (change > maxchange) maxchange = change;
            }
            Barrier();
            A[i] = B[i];
            done = Aggregate(maxchange < tolerance);
        } while (!done); /*iterate until global termination*/
    }
}
