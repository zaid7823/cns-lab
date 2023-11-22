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

    int faults = 0;
    int hits = 0;

    for (int ref_page : reference_string) {
        auto it = find(pages.begin(), pages.end(), ref_page);
        
        if (it != pages.end()) {
            pages.erase(it);
            pages.push_back(ref_page);
            hits++;
        }
        else {
            faults++;
            if (pages.size() < size) {
                pages.push_back(ref_page);
            }
            else {
                pages.erase(pages.begin());
                pages.push_back(ref_page);
            }
        }
    }
    cout << "Total number of Page Hits: " << hits << endl;
    cout << "Total number of Page Faults: " << faults << endl;
    return 0;
}
