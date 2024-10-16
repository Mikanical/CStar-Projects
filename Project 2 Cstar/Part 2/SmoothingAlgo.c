#include <stdlib.h>
#define N 10  /* Size of the image (N x N) */

int image[N][N];           /* Original image (2D array of pixel values) */
int smoothed_image[N][N];  /* Array to store the smoothed image */

/* Function to smooth a pixel value using weighted averaging */
void WeightedSmoothPixel(int i, int j) {
    /* Define weights: center pixel has more influence */
    int weight_sum = 16; /* Total weight sum */
    int center_weight = 8;
    int neighbor_weight = 1;

    /* Calculate the weighted average for the pixel */
    smoothed_image[i][j] = (center_weight * image[i][j] +
                            neighbor_weight * (image[i-1][j-1] + image[i-1][j] + image[i-1][j+1] +
                                               image[i][j-1]   +              image[i][j+1] +
                                               image[i+1][j-1] + image[i+1][j] + image[i+1][j+1])) / weight_sum;
}

main() {
    int i, j;

    /* Initialize the image with random pixel values between 0 and 255 */
    for (i = 0; i < N; i++) {
        forall j = 0 to N-1 do
            image[i][j] = rand() % 256;  /* Use rand() to generate random values */
    }

    /* Display the original image */
    cout << "Original Image:" << endl;
    for (i = 0; i < N; i++) {
        forall j = 0 to N-1 do {
            cout << image[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;

    /* Apply the weighted smoothing algorithm in parallel */
    forall i = 1 to N-2 do
        forall j = 1 to N-2 do
            WeightedSmoothPixel(i, j);  /* Apply the weighted smoothing to non-boundary pixels */

    /* Copy the boundary pixels from the original image to maintain edges */
    forall i = 0 to N-1 do {
        smoothed_image[i][0] = image[i][0];        /* Copy left boundary */
        smoothed_image[i][N-1] = image[i][N-1];    /* Copy right boundary */
    }
    forall j = 0 to N-1 do {
        smoothed_image[0][j] = image[0][j];        /* Copy top boundary */
        smoothed_image[N-1][j] = image[N-1][j];    /* Copy bottom boundary */
    }

    /* Display the smoothed image */
    cout << "Smoothed Image:" << endl;
    for (i = 0; i < N; i++) {
        forall j = 0 to N-1 do {
            cout << smoothed_image[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;
}
