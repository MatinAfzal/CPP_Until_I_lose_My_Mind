#include <iostream>
using namespace std;

int main() {
	double a = 0, b = 0, result=0;
	char op, menu;

	calculator:
		cout << "Enter number one: ";
		cin >> a;

		cout << "Enter number two: ";
		cin >> b;

		cout << "Select your operation [+ - * /]: ";
		cin >> op;

		switch(op) 
		{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
		default:
			cout << "Operation not found!" << endl;
			goto end;
		}
		
		cout << a << " " << op << " " << b << " == " << result << endl;
		cout << "Do you want to continue? [y/n]: ";
		cin >> menu;

		if (menu == 'y' || menu == 'Y')
			goto calculator;

		end:
			cin.get();
			return 0;
}