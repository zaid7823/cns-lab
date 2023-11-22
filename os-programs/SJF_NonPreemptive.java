import java.util.Scanner;

class SJF_NonPreemptive {
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
	// ===============================
	public static void displayData(SJF_NonPreemptive[] arr, int[] waitArr, int[] TATime, int n) {
		System.out.println("Task\tBurst Time\tWaiting Time\tTurnAround Time");
		for (int i = 0; i < n; i++) {
			System.out.println(arr[i].task + "\t" + arr[i].burstTime + "\t\t" + waitArr[i] + "\t\t" + TATime[i]);
		}
	}
	// ===============================
	public static void sjfSort(SJF_NonPreemptive [] arr, int n) {
		SJF_NonPreemptive temp;
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1 - i; j++) {
				if (arr[j].burstTime > arr[j+1].burstTime) {
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
	// ===============================
	public static void calculateWT(SJF_NonPreemptive [] arr, int [] waitArr, int n) {
        for (int i = 0; i < n; i++) {
            if (i == 0) {   // first task
                waitArr[i] = 0;
            }
            else {
                waitArr[i] = waitArr[i-1] + arr[i-1].burstTime;
            }
        }
    }
	// ===============================
	public static void calculateTA(SJF_NonPreemptive[] arr, int[] waitArr, int[] TATime, int n) {
		for (int i = 0; i < n; i++) {
			TATime[i] = waitArr[i] + arr[i].burstTime;
		}
	}
	// ===============================
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n;
		System.out.print("Enter the no. of tasks: ");
		n = cin.nextInt();

		SJF_NonPreemptive[] taskQueue = new SJF_NonPreemptive[n];
		int[] waitingTime = new int[n];
		int[] taTime = new int[n];

		for (int i = 0; i < n; i++) {
			taskQueue[i] = new SJF_NonPreemptive();
			taskQueue[i].inputData();
		}
		sjfSort(taskQueue, n);

		calculateWT(taskQueue, waitingTime, n);
		calculateTA(taskQueue, waitingTime, taTime, n);
		
		float avgWT = 0.0f, avgTA = 0.0f;
		for (int i = 0; i < n; i++) {
			avgWT += waitingTime[i];
			avgTA += taTime[i];
		}
		displayData(taskQueue, waitingTime, taTime, n);

		System.out.println("Avg. Waiting Time = " + (avgWT / n) + "\nAvg. TurnAround Time = " + (avgTA / n));
	}
}
/*
Output:

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
P3      1               0               1
P4      3               1               4
P2      4               4               8
P1      7               8               15
Avg. Waiting Time = 3.25
Avg. TurnAround Time = 7.0
*/
