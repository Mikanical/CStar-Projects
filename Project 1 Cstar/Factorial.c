#include <stdlib.h>

int main() {
	int number;
	int factorial = 1;
	int i;
	
	cout << "Enter positive integer n: " << endl;
	cin >> number;
	cout << "You entered: " << number << endl;
	
	for (i = number; i >= 1; i--) {
	factorial = factorial * i;
	}
	
	cout << "The factorial of" << number << " is:" << factorial << endl;
}
