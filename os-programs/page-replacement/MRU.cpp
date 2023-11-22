#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[]) {
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
            pages.insert(pages.begin(), ref_page); // Insert at the beginning to simulate MRU
            hits++;
        }
        else {
            faults++;
            if (pages.size() < size) {
                pages.insert(pages.begin(), ref_page); // Insert at the beginning if there's space
            }
            else {
                pages.pop_back(); // Remove the least recently used page (at the end)
                pages.insert(pages.begin(), ref_page); // Insert at the beginning
            }
        }
    }
    cout << "Total number of Page Hits: " << hits << endl;
    cout << "Total number of Page Faults: " << faults << endl;

    return 0;
}
