#include <iostream>
using namespace std;

void senderSide(int framesize, int windowsize);
char receiverSide(int seqNum, int winSize);

int main(int argc, char const *argv[]) {
    int frameSize, windowSize;
    cout << "-- Go-Back-N ARQ Protocol Simulation --";
    cout << "\n\nEnter the frame size: ";
    cin >> frameSize;
    cout << "\nEnter window size: ";
    cin >> windowSize;

    senderSide(frameSize, windowSize);
    return 0;
}
void senderSide(int framesize, int windowsize) {
    int sequenceNum; 
    char acknowledgement;
    
    int i = 0;
    while (i < framesize) {
        sequenceNum = i;
        int remainingFrames = framesize - i; // calculates framesize - current frame 
        int framesToSend = min(windowsize, remainingFrames); // Send up to windowsize frames or remainingFrames frames, whichever is smaller.
        
        for (int j = i; j < i + framesToSend; j++) {
            cout << "Sending data frame " << j + 1 << endl;
        }
        
        acknowledgement = receiverSide(sequenceNum, framesToSend);
        if (acknowledgement == 'n' || acknowledgement == 'N') {
            cout << "Retransmitting the window...\n";
        } else {
            if (acknowledgement == 'y' || acknowledgement == 'Y') {
                cout << "Moving on to the next window...\n";
                i += framesToSend;
            }
        }
    }
    cout << "\nFrames transmitted successfully!\n";
}
// ========================================
char receiverSide(int seqNum, int winSize) {
    char opt;
    for (int i = seqNum; i < seqNum + winSize; i++) {
        cout << "Was frame " << i+1 << " received?\n>> ";
        cin >> opt;
        if (opt == 'n' || opt == 'N') {
            return opt;
            // break;
        }
    }
    return opt;
}
