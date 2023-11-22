package SPOS;
import java.util.Scanner;

class Task {
	Scanner cin = new Scanner(System.in);
	public String taskName;
	public int taskSize;

	public void setTask() {
		System.out.print("Enter Task Name: ");
		taskName = cin.nextLine();
		System.out.print("Enter Task Size: ");
		taskSize = cin.nextInt();
		System.out.println();
	}
}
// =============================================
class Block {
	Scanner cin = new Scanner(System.in);
	public String blockName;
	public int blockSize;

	public void setBlock() {
		System.out.print("Enter Block Name: ");
		blockName = cin.nextLine();
		System.out.print("Enter Block Size: ");
		blockSize = cin.nextInt();
		System.out.println();
	}
}
// =============================================
public class WorstFit {
	Scanner cin = new Scanner(System.in);
	int [] fragmentedBlock;
	Boolean [] flag;
	// =========================================
	public WorstFit(int n) {
		fragmentedBlock = new int[n];
		flag = new Boolean[n];
		for (int i = 0; i < n; i++) {
			flag[i] = false;
		}
	}
	// =========================================
	public int worstIndex(Block[] arr, int n) {
		int maxSize = arr[0].blockSize;
		int maxIndex = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i].blockSize > maxSize) {
				maxSize = arr[i].blockSize;
				maxIndex = i;
			}
		}
		return maxIndex;
	}
	// =========================================
	public void allocateMemory(Task [] taskArr, Block [] blockArr, String [] allocatedBlock, int n1, int n2) {
		int allocatedTasks = 0, i = 0, j;

		while (allocatedTasks != n1) {
			for (j = 0; j < n2; j++) {
				if (taskArr[i].taskSize <= blockArr[worstIndex(blockArr, n2)].blockSize && flag[i] == false) {
					fragmentedBlock[i] = blockArr[worstIndex(blockArr, n2)].blockSize - taskArr[i].taskSize;
					blockArr[worstIndex(blockArr, n2)].blockSize -= taskArr[i].taskSize;
					allocatedBlock[i] = blockArr[worstIndex(blockArr, n2)].blockName;
					flag[i] = true;
				}
			}
			i++;
			allocatedTasks++;
			System.out.println("Allocated Tasks = " + allocatedTasks);
		}
	}
	// =========================================
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n1, n2;
		System.out.print("Enter no. of tasks: ");
		n1 = cin.nextInt();
		System.out.print("Enter no. of blocks: ");
		n2 = cin.nextInt();
		System.out.println();
		Task [] taskQueue = new Task[n1];
		Block [] blockQueue = new Block[n2];

		WorstFit algorithm = new WorstFit(n1);
		String [] allocatedBlocks = new String[n1];
		System.out.println("-- Tasks --");
		for (int i = 0; i < n1; i++) {
			taskQueue[i] = new Task();
			taskQueue[i].setTask();
		}
		System.out.println("-- Blocks --");
		for (int i = 0; i < n2; i++) {
			blockQueue[i] = new Block();
			blockQueue[i].setBlock();
		}
		System.out.println();
		algorithm.allocateMemory(taskQueue, blockQueue, allocatedBlocks, n1, n2);

		System.out.println("\nTask ID\t\tTask Size\tBlock ID\tFragmented Size\n");
		for (int i = 0; i < n1; i++) {
			System.out.println(taskQueue[i].taskName + "\t\t" + taskQueue[i].taskSize + "\t\t" + allocatedBlocks[i] + "\t\t" + algorithm.fragmentedBlock[i]);
		}
	}
}
/*
Enter no. of tasks: 4
Enter no. of blocks: 5

-- Tasks --      
Enter Task Name: P1
Enter Task Size: 212

Enter Task Name: P2
Enter Task Size: 417

Enter Task Name: P3
Enter Task Size: 112

Enter Task Name: P4
Enter Task Size: 400

-- Blocks --
Enter Block Name: B1
Enter Block Size: 100

Enter Block Name: B2
Enter Block Size: 200

Enter Block Name: B3
Enter Block Size: 500

Enter Block Name: B4
Enter Block Size: 300

Enter Block Name: B5
Enter Block Size: 600


Allocated Tasks = 1
Allocated Tasks = 2
Allocated Tasks = 3
Allocated Tasks = 4

Task ID         Task Size       Block ID        Fragmented Size

P1              212             B3              388
P2              417             B5              83
P3              112             B4              276
P4              400             null            0
*/
