#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int size, refLength;
    
    cout << "Enter length of Reference String: ";
    cin >> refLength;
    vector<int> reference_string(refLength);

    cout << "Enter length of page frame: ";
    cin >> size;
    vector<int> pages(size, -1); // initialize with -1

    cout << "\nEnter page numbers:\n";
    for (int i = 0; i < refLength; i++) {
        cout << ">> ";
        cin >> reference_string[i];
    }
	int faults = 0, hits = 0, currentIndex = 0;


	for (int ref_page : reference_string) {
		auto it = find(pages.begin(), pages.end(), ref_page);
		
		if (it != pages.end()) {
			hits++;
		}
		else {
			faults++;
			if (pages.size() < size) {
				pages.push_back(ref_page);
			}
			else {
				pages[currentIndex] = ref_page;
				currentIndex = (currentIndex + 1) % size; // Update the index for FIFO
			}
		}
	}
	
	cout << "Total number of Page Hits: " << hits << endl;
	cout << "Total number of Page Faults: " << faults << endl;
	
	return 0;
}
