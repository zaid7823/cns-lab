#include <iostream>
using namespace std;

class generatorPoly {
	public:
	int coeff, exponent;
};
class CRC {
	string dividend, codeword, divisor;
	int *codeWordArr, *remainder;
	int n;
	public:
	// ==============================
	CRC(string divisor, string dividend) {
		this->divisor = divisor;
		this->dividend = dividend;
		codeword = this->dividend;

		n = dividend.length() + divisor.length() - 1;   // length of dividend with redundancy
		remainder = new int[divisor.length()];  // For storing the remainder
	}
	// ==============================
	void toArr() {
		codeWordArr = new int[n];   // length = dividend + initial redundancy

		for (int i = 0; i < divisor.length() - 1; i++) {
			codeword = codeword + "0";  // string is added here, not char
		}
		cout << "\nDividend w/ redundancy: ";
		// Adding dividend with redundancy to the array
		for (int i = 0; i < n; i++) {
			codeWordArr[i] = codeword[i] - '0'; // value of the char is subtracted from every bit
			cout << codeWordArr[i];
		}
		cout << endl;
	}
	// ==============================
	void binaryDivision() {
		int i, divisorArr[divisor.length()];
		int remLength = 0;
		for (i = 0; i < divisor.length(); i++) {
			remainder[i] = codeWordArr[i];      // Initial dividend assignment
			divisorArr[i] = divisor[i] - '0';   // Transferring divisor in an array
		}
		// cout << endl;
		i = divisor.length();
		while(i <= n) {
			// i <= n because it needs an extra iteration to reach the
			// final remainder after taking the final bit of the dividend
			if (remainder[0] == 0) {
				for (int j = 0; j < divisor.length(); j++) {
					remainder[j] = remainder[j] ^ 0;
				}
			}
			else {
				if (remainder[0] == 1) {
					for (int j = 0; j < divisor.length(); j++) {
						remainder[j] = remainder[j] ^ divisorArr[j];
					}
				}
			}
			// If this is not the last operation, then shift the remainder
			// If it is, then don't shift as the original remainder is needed
			if (i != n) {
				shiftRemainder(remainder);
				remainder[divisor.length() - 1] = codeWordArr[i];
			}
			i++;
		}
		errorDisplay(remainder);
	}
	// ==============================
	void receiverSide(int remainder[]) {
		cout << "- - - - - - - - - - - - -\nAt receiver's side:";
		for (int i = 0; i < divisor.length() - 1; i++) {   // n = length of dividend with redundancy i.e. 7 in this case
			codeWordArr[dividend.length() + i] = remainder[i+1];
		}
		binaryDivision();
	}
	// ==============================
	void shiftRemainder(int rem[]) {
		for (int i = 1; i < divisor.length(); i++) {
			rem[i-1] = rem[i];
		}
	}
	// ==============================
	void errorDisplay(int remainder[]) {
		bool flag = false;
		cout << "\nRemainder : ";
		for (int k = 1; k < divisor.length(); k++) {
			cout << remainder[k];
			if (remainder[k] == 1) {
				flag = true;
			}
		}
		if (flag) {
			cout << "\nError!\nData rejected\n";
			receiverSide(remainder);
		}
		else cout << "\nNo Error!\nData accepted\n- - - - - - - - - - - - -\n";
	}
};
// ==================================
int main(int argc, char const *argv[]) {
	string divisor, dividend;
	int n, ch;
	cout << "-- Cyclic Redundancy Check --\n\n";
	cout << "Enter sender data (dividend): ";
	getline(cin, dividend);

	cout << "\n(1) Use Divisor\n";
	cout << "(2) Use Generator Polynomial\n>> ";
	cin >> ch;
	cin.ignore();
	cout << endl;
	switch(ch) {
		case 1:
			cout << "Enter divisor: ";
			getline(cin, divisor);
			break;
		
		case 2:
			cout << "Enter highest exponent of polynomial: ";
			cin >> n;
			generatorPoly p1[n+1];

			cout << "Enter polynomial terms (descending order):\n";
			for (int i = 0; i <= n; i++) {
				cout << "Power (" << n-i << "):";
				cout << "\nEnter coefficient: ";
				cin >> p1[i].coeff;
				p1[i].exponent = n-i;
			}
			// --------
			cout << "Generator Polynomial: ";
			for (int i = 0; i <= n; i++) {
				if (p1[i].coeff == 0) { // when the term is not present in the polynomial
					continue;
				}
				if (p1[i].exponent == 0) {  // for constant terms
					cout << p1[i].coeff;
				}
				else if (p1[i].coeff == 1) {
					if (p1[i].exponent == 1) {
						cout << "x + ";
					}
					else {
						cout << "x^" << p1[i].exponent << " + ";
					}
				}
				else if (p1[i].exponent == 1) {  // for x terms
					if (i == n) {
						cout << p1[i].coeff << "x"; // when x term is the final term & there is no x^0 term
					}
					else if (p1[i].coeff == 1) {
						cout << "x + ";
					}
					else {  // when there is an x^0 term
						cout << p1[i].coeff << "x + ";
					}
				}
				else {
					cout << p1[i].coeff << "x^" << p1[i].exponent << " + ";
				}
			}
			// --------
			for (int i = 0; i <= n; i++) {
				divisor += p1[i].coeff + '0';   // extracting divisor from generator polynomial
			}
			cout << "\nDivisor: " << divisor;
			break;
	}

	CRC c(divisor, dividend);
	c.toArr();
	cout << "\nSender's Side:";
	c.binaryDivision();
	return 0;
}

/*
Output:
-- Cyclic Redundancy Check -- 

Enter sender data (dividend): 1100

(1) Use Divisor
(2) Use Generator Polynomial
>> 1

Enter divisor: 1110

Dividend w/ redundancy: 1100000

Sender's Side:
Remainder : 010
Error!
Data rejected
- - - - - - - - - - - - -      
At receiver's side:
Remainder : 000
No Error!
Data accepted
- - - - - - - - - - - - -
*/
