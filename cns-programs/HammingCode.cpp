#include <iostream>
#include <math.h>
using namespace std;

class HammingCode {
    int p1[4] = {6, 4, 2, 0};
    int p2[4] = {5, 4, 1, 0};
    int p4[4] = {3, 2, 1, 0};
    /*
    the arrays above are just parity bit positions for a 7 bit codeword
    P1 = {1, 3, 5, 7} when mapped to array indices, result in {6, 4, 2, 0} index values
    P2 = {2, 3, 6, 7} when mapped to array indices, result in {5, 4, 1, 0} index values
    P4 = {4, 5, 6, 7} when mapped to array indices, result in {3, 2, 1, 0} index values
    */
    
    string senderData, receiverData;
    int *senderArr, *receiverArr;
    int p1_check = 0, p2_check = 0, p4_check = 0;
    int finalPosition = 0;
    int parityBinary[3];

    public:
    HammingCode(int n) {
        senderArr = new int[n];
        receiverArr = new int[n];
    }
    // =====================================
    void setData() {
        cout << "Enter sender data (for reference): ";
        getline(cin, senderData);
        
        for (int i = 0; i < senderData.length(); i++) {
            senderArr[i] = senderData[i] - 48;
        }
        cout << "Enter receiver data: ";
        getline(cin, receiverData);

        for (int i = 0; i < receiverData.length(); i++) {
            receiverArr[i] = receiverData[i] - 48;
        }
    }
    // =====================================
    void parityCheck() {
        for (int i = 0; i < 4; i++) {
            p1_check = p1_check ^ receiverArr[p1[i]];
			p2_check = p2_check ^ receiverArr[p2[i]];
			p4_check = p4_check ^ receiverArr[p4[i]];
        }

        parityBinary[0] = p1_check;
		parityBinary[1] = p2_check;
		parityBinary[2] = p4_check;
		cout << "P4:P2:P1 = ";

		for (int i = 2; i >= 0; i--) {
			cout << parityBinary[i];
            
		}
		cout << endl;
        
		for (int i = 2; i >= 0; i--) {
			finalPosition += pow(2, i) * parityBinary[i];
		}
		cout << "Position of error bit: " << finalPosition;
		if (receiverArr[receiverData.length() - finalPosition] == 1) {
			receiverArr[receiverData.length() - finalPosition] = 0;
		}
		else {
			receiverArr[receiverData.length() - finalPosition] = 1;
		}
		cout << "\nCorrected Receiver Data: ";
		for (int i = 0; i < receiverData.length(); i++) {
			cout << receiverArr[i];
		}
    }
};
// =========================================
int main(int argc, char const *argv[]) {
    cout << "--- Hamming Code ---\n\n";
    int n;
    cout << "Enter length of sender data: ";
    cin >> n;
	cin.ignore();
    HammingCode h1(n);
	cout << "\n";
	h1.setData();
	h1.parityCheck();

    return 0;
}
/*
Output:

--- Hamming Code ---

Enter length of sender data: 7

Enter sender data (for reference): 1010101
Enter receiver data: 1110101
P4:P2:P1 = 110
Position of error bit: 6        
Corrected Receiver Data: 1010101
*/
