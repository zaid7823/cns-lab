#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findOptimalIndex(const vector <int> &reference_string, const vector <int> &pages, int currentIndex) {
    int optimalIndex = -1;
    int farthest = currentIndex;

    for (int i = 0; i < pages.size(); i++) {
        int j;
        for (j = currentIndex; j < reference_string.size(); j++) {
            if (pages[i] == reference_string[j]) {
                if (j > farthest) {
                    farthest = j;
                    optimalIndex = i;
                }
                break;
            }
        }
        if (j == reference_string.size()) {
            return i;
        }
    }
    if (optimalIndex == -1) {
        return 0;
    }
    else {
        return optimalIndex;
    }
}
// =======================================
int main(int argc, char const *argv[]) {
    int refLength, size;
    cout << "Enter length of reference string: ";
    cin >> refLength;
    vector <int> reference_string(refLength);

    cout << "Enter size of page frame: ";
    cin >> size;
    vector <int> pages(size, -1);

    cout << "\nEnter page numbers:\n";
    for (int i = 0; i < refLength; i++) {
        cout << ">> ";
        cin >> reference_string[i];
    }
    int hits = 0, faults = 0;

    for (int i = 0; i < reference_string.size(); i++) {
        auto it = find(pages.begin(), pages.end(), reference_string[i]);

        if (it != pages.end()) {
            hits++;
        }
        else {
            faults++;

            if (pages.size() < size) {
                pages.push_back(reference_string[i]);
            }
            else {
                int index = findOptimalIndex(reference_string, pages, i);
                pages[index] = reference_string[i];
            }
        }
    }
    cout << "Total Page Hits = " << hits << "\nTotal Page Faults = " << faults << endl;
    return 0;
}
/*
Output:
Enter length of reference string: 16
Enter size of page frame: 4

Enter page numbers:
>> 7
>> 0
>> 1
>> 2
>> 0
>> 3
>> 0
>> 4
>> 2
>> 3
>> 0
>> 3
>> 0
>> 3
>> 2
>> 3
Total Page Hits = 10
Total Page Faults = 6
*/
