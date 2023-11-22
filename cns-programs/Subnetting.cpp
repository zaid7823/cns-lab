#include <iostream>
#include <string>
#include <math.h>
#include <bitset>
using namespace std;

void identifySubnetMask(int arr[], int subnetArr[], int n);
void IP_strToInt(string IP, int arr[]);
void makeSubnetMask(int subnetArr[], int n, int networkID);
void decimalToBinary(int arr[], string binArr[], int size);
void complementSubnetMask(string binSubnetArr[], string compArr[], int n);
void firstIPCalculation(string IParr[], string BinArr[], string firstIP[], int n);
void lastIPCalculation(string IParr[], string BinArr[], string lastIP[], int n);
void binToDec(string arr[], int newArr[], int n);
// ===================================
int main(int argc, char const * argv[]) {
	string IP;
	int n, IParr[4], subnetArr[4] = {0};
	string binIParr[4], binSubnetArr[4], compSubnetArr[4], firstIPstr[4], lastIPstr[4];
	int firstIP[4], lastIP[4];
	cout << "== Subnetting ==\n\n";
	cout << "Enter IP Address: ";
	getline(cin, IP);
	cout << "Enter n (network ID): ";
	cin >> n;

	IP = IP + ".";
	IP_strToInt(IP, IParr);

	identifySubnetMask(IParr, subnetArr, 4);

	makeSubnetMask(subnetArr, 4, n);

	decimalToBinary(IParr, binIParr, 4);

	decimalToBinary(subnetArr, binSubnetArr, 4);

	complementSubnetMask(binSubnetArr, compSubnetArr, 4);

	firstIPCalculation(binIParr, binSubnetArr, firstIPstr, 4);
	
	lastIPCalculation(binIParr, compSubnetArr, lastIPstr, 4);

	binToDec(firstIPstr, firstIP, 4);
	cout << "\n\n";
	binToDec(lastIPstr, lastIP, 4);

	cout << "First IP Address: ";
	for (int i = 0; i < 4; i++) {
		cout << firstIP[i];
		if (i != 3) {
			cout << ".";
		}
	}
	cout << "\nLast IP Address: ";
	for (int i = 0; i < 4; i++) {
		cout << lastIP[i];
		if (i != 3) {
			cout << ".";
		}
	}
	cout << "\n\nNo. of Address Blocks = 2^(32 - " << n << ") = " << pow(2, 32-n);
	cout << "\n=============================\n";
	return 0;
}
// ===================================
void IP_strToInt(string IP, int arr[]) {
	string temp = "";
	int i = 0, j = 0, dotCount = 0;
	while (i < IP.length()) {
		if (IP[i] == '.') {
			dotCount++;
			arr[j] = stoi(temp);
			temp = "";
			j++;
			i++;
		} else {
			temp = temp + IP[i];
			i++;
		}
		if (dotCount == 4) {
			break;
		}
	}
}
// ===================================
void identifySubnetMask(int arr[], int subnetArr[], int n) {
	int network = 255, A = 1, B = 2, C = 3;
	if (arr[0] >= 1 && arr[0] <= 126) {
		for (int i = 0; i < A; i++) {
			subnetArr[i] = network;
		}
	} else if (arr[0] >= 128 && arr[0] <= 191) {
		for (int i = 0; i < B; i++) {
			subnetArr[i] = network;
		}
	} else {
		if (arr[0] >= 192 && arr[0] <= 223) {
			for (int i = 0; i < C; i++) {
				subnetArr[i] = network;
			}
		}
	}
	cout << "\nDefault Subnet Mask: ";
	for (int i = 0; i < n; i++) {
		cout << subnetArr[i];
		if (i != n - 1) {
			cout << ".";
		}
	}
}
// ===================================
void makeSubnetMask(int subnetArr[], int n, int networkID) {
	int subnetCount = 0, i;
	int actualSubnet;
	string subnetSTR = "";
	for (i = 0; i < n; i++) {
		if (subnetArr[i] == 255) {
			subnetCount++;
		}
	}
	int networkBits = subnetCount * 8;
	int bitsToAdd = networkID - networkBits;
	cout << "\nTotal Network Bits: " << networkBits << "\nNo. of host bits to borrow: " << bitsToAdd << endl;
	for (i = 0; i < bitsToAdd; i++) {
		subnetSTR += "1";
	}
	for (int j = i; j < 8; j++) {
		subnetSTR += "0";
	}
	int subnetBits[8];
	for (int i = 0; i < 8; i++) {
		subnetBits[i] = subnetSTR[i] - '0';
	}
	actualSubnet = 0;
	for (int i = 7; i >= 0; i--) {
		actualSubnet += pow(2, i) * subnetBits[7 - i];
	}
	for (int i = 0; i < n; i++) {
		if (subnetArr[i] == 0) {
			subnetArr[i] = actualSubnet;
			break;
		}
	}
	cout << "\nSubnet Mask: ";
	for (int i = 0; i < n; i++) {
		cout << subnetArr[i];
		if (i != n - 1) {
			cout << ".";
		}
	}
}
// ===================================
void complementSubnetMask(string binSubnetArr[], string compArr[], int n) {
	for (int i = 0; i < n; i++) {
		string temp = binSubnetArr[i];
		for (int j = 0; j < temp.length(); j++) {
			if (temp[j] == '0') {
				temp[j] = '1';
			} else {
				temp[j] = '0';
			}
		}
		compArr[i] = temp;
	}
}
// ===================================
void decimalToBinary(int arr[], string binArr[], int size) {
	for (int i = 0; i < size; i++) {
		int decNum = arr[i];
		bitset < 8 > binaryRepresentation(decNum);
		
		// Convert to binary string
		binArr[i] = binaryRepresentation.to_string();
	}
}
// ===================================
void firstIPCalculation(string IParr[], string BinArr[], string firstIP[], int n) {
	for (int i = 0; i < n; i++) {
		string temp1 = IParr[i];
		string temp2 = BinArr[i];
		string result = "";
		for (int j = 0; j < temp1.length(); j++) {
			if (temp1[j] == '1' && temp2[j] == '1') {
				result += '1';
			} else {
				result += '0';
			}
		}
		firstIP[i] = result;
	}
}
// ===================================
void lastIPCalculation(string IParr[], string BinArr[], string lastIP[], int n) {
	for (int i = 0; i < n; i++) {
		string temp1 = IParr[i];
		string temp2 = BinArr[i];
		string result = ""; 
		for (int j = 0; j < temp1.length(); j++) {
			if (temp1[j] == '0' && temp2[j] == '0') {
				result += '0';
			} else {
				result += '1';
			}
		}
		lastIP[i] = result;
	}
}
// ===================================
void binToDec(string arr[], int newArr[], int n) {
	for (int i = 0;i < n; i++) {
		string binaryStr = arr[i];

		// Convert the binary string to an integer using base 2
		newArr[i] = stoi(binaryStr, NULL, 2);
	}
}
/*
Output:

== Subnetting ==  

Enter IP Address: 205.16.37.39
Enter n (network ID): 28

Default Subnet Mask: 255.255.255.0      
Total Network Bits: 24
No. of host bits to borrow: 4

Subnet Mask: 255.255.255.240

First IP Address: 205.16.37.32
Last IP Address: 205.16.37.47

No. of Address Blocks = 2^(32 - 28) = 16
=============================
*/
