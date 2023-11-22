import java.util.Scanner;

public class PriorityScheduling {
    String task;
    int burstTime, priority;

    public void setTask() {
		Scanner cin = new Scanner(System.in);
		System.out.print("Enter Task Name: ");
		task = cin.nextLine();
		System.out.print("Enter Burst Time: ");
		burstTime = cin.nextInt();
        System.out.print("Enter Task Priority: ");
        priority = cin.nextInt();
	}
	// =======================================
    public static void prioritySort(PriorityScheduling [] arr, int n) {
        PriorityScheduling temp;
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (arr[j].priority > arr[j+1].priority) {
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
                // sort tasks on the basis of burst time if they have the same priority
                else if (arr[j].priority == arr[j+1].priority && arr[j].burstTime > arr[j+1].burstTime) {
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
	// =======================================
    public static void waitingTime(int [] waitArr, PriorityScheduling [] arr, int n) {
		for (int i = 0; i < n; i++) {
			if (i == 0) {
				waitArr[i] = 0;
			}
			else {
				waitArr[i] = waitArr[i-1] + arr[i].burstTime;
			}
		}
	}
	// =======================================
	public static void turnAroundTime(int [] waitArr, int [] TA_Arr, PriorityScheduling [] arr, int n) {
		for (int i = 0; i < n; i++) {
			TA_Arr[i] = waitArr[i] + arr[i].burstTime;
		}
	}
    // =======================================
    public static void main(String [] args) {
		Scanner obj = new Scanner(System.in);
		int n;
		float avgWait = 0.0f, avgTurnAround = 0.0f;
		int [] waitingTimeArray = new int[10];
		int [] turnAroundArray = new int[10];
		
		PriorityScheduling [] taskQueue = new PriorityScheduling[50];
		
		System.out.print("How many tasks do you want to schedule?\n -> ");
		n = obj.nextInt();
		
		for (int i = 0; i < n; i++) {
		    taskQueue[i] = new PriorityScheduling();
			taskQueue[i].setTask();
			System.out.println();
		}
        prioritySort(taskQueue, n);

		waitingTime(waitingTimeArray, taskQueue, n);
		turnAroundTime(waitingTimeArray, turnAroundArray, taskQueue, n);
		
		System.out.println("Gantt Chart:\n");
		for (int i = 0; i < n; i++) {
			System.out.print(taskQueue[i].task + "\t");
		}
		System.out.println();
		for (int i = 0; i < n; i++) {
			System.out.print(waitingTimeArray[i] + "\t");
		}
		System.out.println();		
		for (int i = 0; i < n; i++) {
			System.out.print(turnAroundArray[i] + "\t");
			avgWait += waitingTimeArray[i];
			avgTurnAround += turnAroundArray[i];
		}
		System.out.println("\n\nAvg. Waiting Time: " + (avgWait/n) + "\nAvg. Turn-Around Time: " + (avgTurnAround/n));
		
		System.out.println("\nTask\tPriority\tBurst Time\tWaiting Time\tTurn-AroundTime");
		for (int i = 0; i < n; i++) {
			System.out.println(taskQueue[i].task + "\t" + taskQueue[i].priority +"\t\t" + taskQueue[i].burstTime + "\t\t" + waitingTimeArray[i] + "\t\t" + turnAroundArray[i]);
		}
	}
}
/*
How many tasks do you want to schedule?
 -> 4
Enter Task Name: P1
Enter Burst Time: 7
Enter Task Priority: 4

Enter Task Name: P2
Enter Burst Time: 4
Enter Task Priority: 3

Enter Task Name: P3
Enter Burst Time: 1
Enter Task Priority: 2

Enter Task Name: P4
Enter Burst Time: 3
Enter Task Priority: 1

Gantt Chart:

P4      P3      P2      P1
0       3       4       8
3       4       8       15

Avg. Waiting Time: 3.75
Avg. Turn-Around Time: 7.5

Task    Priority        Burst Time      Waiting Time    Turn-AroundTime
P4      1               3               0               3
P3      2               1               3               4
P2      3               4               4               8
P1      4               7               8               15
*/
