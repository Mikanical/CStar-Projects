#include <stdlib.h>
#include <math.h>

#define n 2000 /* number of values to be sorted */
#define m 100  /* each number is in range [0, m-1] */
#define bucket_number 10 /* each bucket for all numbers with the same 10th digit value */
#define MAX_BUCKET_SIZE 2000  /* Set a limit for the number of elements in a bucket */

int data[n+1], sortedData[n+1];
int bucket[bucket_number][MAX_BUCKET_SIZE];
int bucketSizes[bucket_number]; /* To keep track of the number of elements in each bucket */

/* Simple Bubble Sort for Debugging */
void bubble_sort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* Main Function */
int main() {
    int i, j, v, b_i, index, k = 0;

    /* Initialize bucket sizes */
    for (i = 0; i < bucket_number; i++) {
        bucketSizes[i] = 0;  /* Initialize all bucket sizes to 0 */
    }

    /* Sequential section - Random data initialization using a while loop */
    seqoff;
    int count = 1;
    while (count <= n) {
        data[count] = rand() % m; /* Generate random number in the range [0, m-1] */
        count++;
    }
    seqon;

    /* Parallel section - Distribution step: Assign values to corresponding buckets */
    forall i = 1 to n do {
        v = data[i];
        b_i = (int)(v / 10.0); /* bucket-index = the 10th digit */

        /* Check if the bucket is full to avoid invalid index */
        if (bucketSizes[b_i] < MAX_BUCKET_SIZE) {
            bucket[b_i][bucketSizes[b_i]++] = v; /* Insert value into bucket */
        } else {
            cout << "Error: Bucket overflow in bucket " << b_i << endl;
        }
    }

    /* Sequential sorting of each bucket using bubble sort */
    for (i = 0; i < bucket_number; i++) {
        if (bucketSizes[i] > 0) {  /* Only sort non-empty buckets */
            bubble_sort(bucket[i], bucketSizes[i]); /* Use bubble sort */
        }
    }

    /* Append sorted buckets back to sortedData array */
    k = 1;
    for (i = 0; i < bucket_number; i++) {
        for (j = 0; j < bucketSizes[i]; j++) {
            sortedData[k++] = bucket[i][j];
        }
    }

    /* Output the sorted data */
    for (i = 1; i <= n; i++) {
        cout << "sortedData[" << i << "]=" << sortedData[i] << endl;
    }

    return 0;
}
