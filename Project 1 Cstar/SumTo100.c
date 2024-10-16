#include <stdlib.h>

int main() {
	
	int i;
	int sum;
	
	for (i = 1; i <= 100; i++) {
		cout << i << endl;
		sum += i;
	}
	
	cout << endl;
	cout << "The sum is: " << sum << endl;
}