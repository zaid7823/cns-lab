import java.util.Scanner;

class FCFS {
    String task;
    int burstTime;

    public void inputData() {
        Scanner cin = new Scanner(System.in);
        System.out.print("Enter Task Name: ");
        task = cin.nextLine();
        System.out.print("Enter Burst Time: ");
        burstTime = cin.nextInt();
        System.out.println();
    }
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    public static void displayData(FCFS [] arr, int [] waitingTime, int [] TATime, int n) {
        System.out.println("Task\tBurst Time\tWaiting Time\tTurnAround Time");
        for (int i = 0; i < n; i++) {
            System.out.println(arr[i].task + "\t" + arr[i].burstTime + "\t\t" + waitingTime[i] + "\t\t" + TATime[i]);
        }
    }
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    public static void calculateWT(FCFS [] arr, int [] waitArr, int n) {
        for (int i = 0; i < n; i++) {
            if (i == 0) {   // first task
                waitArr[i] = 0;
            }
            else {
                waitArr[i] = waitArr[i-1] + arr[i-1].burstTime;
            }
        }
    }
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    public static void calculateTA(FCFS [] arr, int [] waitArr, int [] TATime, int n) {
        for (int i = 0; i < n; i++) {
            TATime[i] = waitArr[i] + arr[i].burstTime;
        }
    }
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int n;
        System.out.print("Enter the no. of tasks: ");
        n = cin.nextInt();

        FCFS [] taskQueue = new FCFS[n];
        int [] waitingTime = new int[n];
        int [] taTime = new int[n];
        for (int i = 0; i < n; i++) {
            taskQueue[i] = new FCFS();
            taskQueue[i].inputData();
        }
        calculateWT(taskQueue, waitingTime, n);
        calculateTA(taskQueue, waitingTime, taTime, n);

        float avgWT = 0.0f, avgTA = 0.0f;
        for (int i = 0; i < n; i++) {
            avgWT += waitingTime[i];
            avgTA += taTime[i];
        }
        System.out.println();
        displayData(taskQueue, waitingTime, taTime, n);
        System.out.println("Avg. Waiting Time = " + (avgWT / n) + "\nAvg. TurnAround Time = " + (avgTA / n) + "\n");

    }
}
/*
Enter the no. of tasks: 4
Enter Task Name: P1
Enter Burst Time: 7

Enter Task Name: P2
Enter Burst Time: 4

Enter Task Name: P3
Enter Burst Time: 1

Enter Task Name: P4
Enter Burst Time: 3


Task    Burst Time      Waiting Time    TurnAround Time
P1      7               0               7
P2      4               7               11
P3      1               11              12
P4      3               12              15
Avg. Waiting Time = 7.5
Avg. TurnAround Time = 11.25
*/
