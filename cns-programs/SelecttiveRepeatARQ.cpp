#include <iostream>
using namespace std;

void senderSide(int framesize, int windowsize);
int receiverSide(int seqNum, int winSize);
void resendLostFrame(int acknowledgement);
// =====================================
int main(int argc, char const *argv[]) {
    int frameSize, windowSize;
    cout << "-- Selective Repeat ARQ Protocol Simulation --";
    cout << "\n\nEnter the frame size: ";
    cin >> frameSize;
    cout << "\nEnter window size: ";
    cin >> windowSize;

    senderSide(frameSize, windowSize);
    return 0;
}
// =====================================
void senderSide(int framesize, int windowsize) {
    int sequenceNum;
    char acknowledgement;
    
    int i = 0, count = 0;
    while (i < framesize) {
        sequenceNum = i;
        int remainingFrames = framesize - i; // calculates framesize - current frame
        int framesToSend = min(windowsize, remainingFrames); // Send up to windowsize frames or remainingFrames frames, whichever is smaller.
        
        for (int j = i; j < i + framesToSend; j++) {
            cout << "Sending data frame " << j + 1 << endl;
        }
        
        acknowledgement = receiverSide(sequenceNum, framesToSend);
        if (acknowledgement != -1) {
            // cout << "Retransmitting the window...\n";
            resendLostFrame(acknowledgement);
            i += framesToSend;
        }
        else {
            cout << "Moving on to the next window...\n";
            i += framesToSend;
        }
    }
    cout << "\nFrames transmitted successfully!\n";
}
// =====================================
void resendLostFrame(int acknowledgement) {
    char ch = 'n';
    while (ch != 'y' && ch != 'Y') {
        cout << "\nResending frame " << acknowledgement << "...\nWas the frame sent?\n>> ";
        cin >> ch;
    }
}
// =====================================
int receiverSide(int seqNum, int winSize) {
    int lostFrame;
    char opt;
    cout << "Which frame was not received? ('-1' if all frames were received)\n>> ";
    cin >> lostFrame;
    return lostFrame;
}
