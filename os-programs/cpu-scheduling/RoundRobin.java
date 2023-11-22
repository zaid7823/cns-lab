import java.util.Scanner;

public class RoundRobin {
    String task;
    int burstTime;
    // ====================================
    public void inputData() {
        Scanner cin = new Scanner(System.in);
        System.out.print("\nEnter Task Name: ");
        task = cin.nextLine();
        System.out.print("Enter Burst Time: ");
        burstTime = cin.nextInt();
    }
    // ====================================
    public static void scheduleTasks(RoundRobin [] arr, int [] waitingTime, int [] TATime, int [] remainingBurstTime, int n, float avgWT) {
        Scanner cin = new Scanner(System.in);
        int quantumTime, currentTime = 0;
        System.out.print("Enter Quantum Time: ");
        quantumTime = cin.nextInt();

        Boolean completed = false;
        while (!completed) {
            completed = true;

            for (int i = 0; i < n; i++) {
                if (remainingBurstTime[i] > 0) {
                    completed = false;

                    if (remainingBurstTime[i] > quantumTime) {
                        currentTime += quantumTime;
                        remainingBurstTime[i] -= quantumTime;
                    }
                    else {
                        currentTime += remainingBurstTime[i];
                        waitingTime[i] = currentTime - arr[i].burstTime;
                        remainingBurstTime[i] = 0;
                    }
                    TATime[i] = waitingTime[i] + arr[i].burstTime;
                    avgWT += waitingTime[i];
                }
            }
        }
        avgWT = avgWT / n;
    }
    // ====================================
    public static void displayData(RoundRobin [] arr, int [] waitingTime, int [] TATime, int n) {
        System.out.println("Task ID\t\tBurst Time\tWaiting Time\tTurn Around Time\n");
        for (int i = 0; i < n; i++) {
            System.out.println(arr[i].task + "\t\t" + arr[i].burstTime + "\t\t" + waitingTime[i] + "\t\t" + TATime[i]);
        }
    }
// ====================================
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int n;
        System.out.print("Enter no. of tasks: ");
        n = cin.nextInt();
        RoundRobin [] taskQueue = new RoundRobin[n];
        int [] waitingTime = new int[n];
		int [] TATime = new int[n];
		int [] remainingBurstTime = new int[n];

        for (int i = 0; i < n; i++) {
            taskQueue[i] = new RoundRobin();
            taskQueue[i].inputData();
            remainingBurstTime[i] = taskQueue[i].burstTime;
        }

        float avgWT = 0.0f;
        float avgTA = 0.0f;

        scheduleTasks(taskQueue, waitingTime, TATime, remainingBurstTime, n, avgWT);

        for (int i = 0; i < n; i++) {
            avgTA += TATime[i];
        }
        System.out.println("\nAvg. Waiting Time = " + avgWT / n);
        System.out.println("Avg. TurnAround Time = " + avgTA / n);
        displayData(taskQueue, waitingTime, TATime, n);
    }
}
