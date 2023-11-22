import java.util.Scanner;

class Task {
	public String taskName;
	public int taskSize;
	Scanner obj = new Scanner(System.in);

	public void setTask() {
		System.out.print("Enter Task Name: ");
		taskName = obj.nextLine();
		System.out.print("Enter Task Size: ");
		taskSize = obj.nextInt();
	}
}
class Block {
	public String blockName;
	public int blockSize;
	Scanner obj = new Scanner(System.in);

	public void setBlock() {
		System.out.print("Enter Block Name: ");
		blockName = obj.nextLine();
		System.out.print("Enter block size: ");
		blockSize = obj.nextInt();
	}
}
// ====================================
public class FirstFit {
	Scanner obj = new Scanner(System.in);

	int [] fragmentedBlock;
	Boolean [] flag;
  
	public FirstFit(int n) {
		// here n = n1, i.e. no of tasks
		fragmentedBlock = new int[n];
		flag = new Boolean[n];

		for (int i = 0; i < n; i++) {
			flag[i] = false;
		}
	} 
	// ================================
	public void allocateMemory(Task [] taskArr, Block [] blockArr, String [] allocatedBlocks, int n1, int n2) {
		int allocatedTasks = 0, i = 0, j;

		while (allocatedTasks != n1) {
			for (j = 0; j < n2; j++) {
				if (taskArr[i].taskSize <= blockArr[j].blockSize && flag[i] == false) {
          
					fragmentedBlock[i] = blockArr[j].blockSize - taskArr[i].taskSize;
					blockArr[j].blockSize -= taskArr[i].taskSize;
					allocatedBlocks[i] = blockArr[j].blockName;
					flag[i] = true;
				}
			}
			System.out.println();
			allocatedTasks++;   // Still increments even if memory block is not found just so while loop can stop
			i++;
			System.out.println("\nTotal Allocated tasks = " + allocatedTasks);
		}
	}
	// ================================
	public static void main(String[] args) {
		int n1, n2;
		Scanner cin = new Scanner(System.in);
		System.out.println("--- First Fit Algorithm ---");
		System.out.print("\nEnter no. of tasks: ");
		n1 = cin.nextInt();

		Task [] taskQueue = new Task[n1];

		System.out.print("Enter no. of blocks: ");
		n2 = cin.nextInt();
		Block [] blocks = new Block[n2];

		String [] allocatedBlock = new String[n1];

		System.out.println("\n-- Tasks --");
		for (int i = 0; i < n1; i++) {
			taskQueue[i] = new Task();
			taskQueue[i].setTask();
			System.out.println();
		}
		System.out.println("\n-- Blocks --");
		for (int i = 0; i < n2; i++) {
			blocks[i] = new Block();
			blocks[i].setBlock();
			System.out.println();
		}
		// =======================
		FirstFit algo = new FirstFit(n1);
		
		algo.allocateMemory(taskQueue, blocks, allocatedBlock, n1, n2);

		System.out.println("\nTask ID\t\tTask Size\tBlock ID\tFragmented Size\n");
		for (int i = 0; i < n1; i++) {
			System.out.println(taskQueue[i].taskName + "\t\t" + taskQueue[i].taskSize + "\t\t" + allocatedBlock[i] + "\t\t" + algo.fragmentedBlock[i]);
		}
	}  
}
/*
--- First Fit Algorithm ---

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
Enter block size: 100

Enter Block Name: B2
Enter block size: 200

Enter Block Name: B3
Enter block size: 500

Enter Block Name: B4
Enter block size: 300

Enter Block Name: B5
Enter block size: 600

Total Allocated tasks = 1

Total Allocated tasks = 2

Total Allocated tasks = 3

Total Allocated tasks = 4

Task ID         Task Size       Block ID        Fragmented Size

P1              212             B3              288
P2              417             B5              183
P3              112             B2              88
P4              400             null            0
*/
