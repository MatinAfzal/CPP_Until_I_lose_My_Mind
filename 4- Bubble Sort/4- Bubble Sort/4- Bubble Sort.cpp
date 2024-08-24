#include <iostream>
using namespace std;

void readData(int*, int);
void printData(int*, int, char);
void BubbleSort(int*, int);

int main() {
	const int length = 10;
	int data[length];

	readData(data, length);
	printData(data, length, 'U');
	BubbleSort(data, length);
	printData(data, length, 'S');

	cin.get();
	return 0;
}

//****************************************************
void readData(int* data, int length) {
	cout << "Enter " << length << " numbers to sort: ";

	for (int i = 0; i < length; i++)
		cin >> data[i];
}

void printData(int* data, int length, char stage) {
	if (stage == 'U') // Unsorted
		cout << "Unsorted data: [";
	else
		cout << "Sorted data: [";

	for (int i = 0; i < length; i++)
		cout << data[i] << " ";
	cout << "]" << endl;
}

void BubbleSort(int* data, int length) {
	int temp;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - 1; j++) {
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}
}