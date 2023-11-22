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
// ====================================
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
// ====================================
public class NextFit {
	Scanner cin = new Scanner(System.in);
	int [] fragmentedBlocks;
	Boolean [] flag;
	// ================================
	public NextFit(int n) {
		fragmentedBlocks = new int[n];
		flag = new Boolean[n];
		for (int i = 0; i < n; i++) {
			flag[i] = false;
		}
	}
	// ================================
	public void allocateMemory(Task [] taskArr, Block [] blockArr, String [] allocatedBlocks, int n1, int n2) {
		int allocatedTasks = 0, i = 0, j, index = 0;

		while (allocatedTasks != n1) {
			j = index;  // this assignment is given, because 'index' stores the previous iteration index
			while (j < n2) {
				if (taskArr[i].taskSize <= blockArr[j].blockSize && flag[i] == false) {
					fragmentedBlocks[i] = blockArr[j].blockSize - taskArr[i].taskSize;
					blockArr[j].blockSize -= taskArr[i].taskSize;
					allocatedBlocks[i] = blockArr[j].blockName;
					flag[i] = true;
					index = (j + 1) % n2;   // next index is stored in the variable so as to continue iteration
					break;
					// break is necessary since it breaks the loop and does not incrment j for the next block
					// if break is not used, the index as well as the loop will be incremented
				}
				// the upper 'break' prevents the following statements from executing
				j = (j + 1) % n2;
				if (j == index) {
					System.out.println("\nUnallocated Task");
					break;
				}
			}
			i++;
			allocatedTasks++;
			System.out.println("\nTotal Allocated tasks = " + allocatedTasks);
		}
	}
	// ================================
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

		NextFit algorithm = new NextFit(n1);
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
			System.out.println(taskQueue[i].taskName + "\t\t" + taskQueue[i].taskSize + "\t\t" + allocatedBlocks[i] + "\t\t" + algorithm.fragmentedBlocks[i]);
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



Total Allocated tasks = 1
Total Allocated tasks = 2

Total Allocated tasks = 3
Unallocated Task

Total Allocated tasks = 4

Task ID         Task Size       Block ID        Fragmented Size

P1              212             B3              288
P2              417             B5              183
P3              112             B2              88
P4              400             null            0
*/
