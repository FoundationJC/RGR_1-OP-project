#include <iostream>
#include <string>
using namespace std;
// "-123" "1q23" "0123" "0"
bool isInteger( char  str[], int n) {
	if (n == 0) { return false; }
	
	int i = 0;
	if (str[i] == '-' || str[i] == '+') {

		i++;
	
	
	}
	
	if (str[i] == '0' && i > n-1) {// i = 0, 0 < 0

		return false;
	}
	
	for (int j = i; j < n; j++) {

		if (!isDigit(str[j])) {
			return false;
		}

	}

}
bool isDigit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

int main() {
	char str1[] = "01";
	cout << str1 << endl;
	cout << isInteger(str1, strlen(str1)) << endl;
	return 0;
}