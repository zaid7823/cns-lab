package SPOS;
import java.util.Scanner;

public class SJF_Preemptive {
	String taskName;
	int arrivalTime, burstTime;

	public void setTask() {
		Scanner cin = new Scanner(System.in);
		System.out.print("Enter Task Name: ");
		taskName = cin.nextLine();
		System.out.print("Enter Arrival Time: ");
		arrivalTime = cin.nextInt();
		System.out.print("Enter Burst Time: ");
		burstTime = cin.nextInt();
		System.out.println();
	}
	// ========================================
	public static void PreemptiveSchedule (SJF_Preemptive [] TaskArr, int [] remainingBurstTime, int [] completionTime, Boolean [] f, int n) {
		int completedProcesses = 0, currentTime = 0; 
		
		while (completedProcesses < n) {
			int min = Integer.MAX_VALUE;
			int currentTask = n;

			for (int i = 0; i < n; i++) {
				if ((TaskArr[i].arrivalTime <= currentTime) && (f[i] == false) && remainingBurstTime[i] < min) {
					min = remainingBurstTime[i];
					currentTask = i;
				}
			}
			if (currentTask == n) {
				currentTime++;
			}
			else {
				currentTime++;
				remainingBurstTime[currentTask]--;

				if (remainingBurstTime[currentTask] == 0) {
					completionTime[currentTask] = currentTime;
					f[currentTask] = true;
					completedProcesses++;
				}
			}
		}
	}
	// ========================================
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n;
		System.out.print("Enter the no. of tasks: ");
		n = sc.nextInt();

		SJF_Preemptive [] taskQueue = new SJF_Preemptive[n];
		
		int [] waitingTime = new int[n];
		int [] turnAroundTime = new int[n];

		int [] completionTime = new int[n];
		int [] remainingBurstTime = new int[n];
		Boolean [] flag = new Boolean[n];

		for (int i = 0; i < n; i++) {
			taskQueue[i] = new SJF_Preemptive();
			taskQueue[i].setTask();
			remainingBurstTime[i] = taskQueue[i].burstTime;
			flag[i] = false;
		}
		PreemptiveSchedule(taskQueue, remainingBurstTime, completionTime, flag, n);

		float avgWait = 0.0f, avgTurnAround = 0.0f;
		// Waiting Time and Turn Around Time Calculation
		for (int i = 0; i < n; i++) {
			turnAroundTime[i] = completionTime[i] - taskQueue[i].arrivalTime;
			waitingTime[i] = turnAroundTime[i] - taskQueue[i].burstTime;

			avgWait += waitingTime[i];
			avgTurnAround += turnAroundTime[i];
		}
		System.out.println("Avg. Waiting Time: " + (avgWait / n));
		System.out.println("Avg. Turn Around Time: " + (avgTurnAround / n));

		System.out.println("\nTask Name\tArrival Time\tBurst Time\tCompletion Time\t\tWaiting Time\tTurnAround Time\n");
		for (int i = 0; i < n; i++) {
			System.out.println(taskQueue[i].taskName + "\t\t" + taskQueue[i].arrivalTime + "\t\t" + taskQueue[i].burstTime + "\t\t" + completionTime[i] + "\t\t\t" + waitingTime[i] + "\t\t" + turnAroundTime[i]);
		}
	}
}
/*
== OUTPUT ==:
Enter the no. of tasks: 4
Enter Task Name: P1
Enter Arrival Time: 4
Enter Burst Time: 7

Enter Task Name: P2
Enter Arrival Time: 0
Enter Burst Time: 4

Enter Task Name: P3
Enter Arrival Time: 2
Enter Burst Time: 1

Enter Task Name: P4
Enter Arrival Time: 3
Enter Burst Time: 3

Avg. Waiting Time: 1.75
Avg. Turn Around Time: 5.5

Task Name       Arrival Time    Burst Time      Completion Time         Waiting Time    TurnAround Time

P1              4               7               15                      4               11
P2              0               4               5                       1               5 
P3              2               1               3                       0               1
P4              3               3               8                       2               5
*/
