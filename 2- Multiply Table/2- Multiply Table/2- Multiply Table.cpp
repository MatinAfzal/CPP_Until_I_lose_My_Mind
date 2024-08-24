#include <iostream>
using namespace std;

int main() {
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			cout << i << " * " << j << " == " << i * j << "\t";
		}
		cout << "\n";
	}

	cin.get();
	return 0;
}