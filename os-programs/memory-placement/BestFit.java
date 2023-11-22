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
        System.out.println();
    }
}
// =================================
class Block {
    public String blockName;
    public int blockSize;
    Scanner obj = new Scanner(System.in);

    public void setBlock() {
        System.out.print("Enter Block Name: ");
        blockName = obj.nextLine();
        System.out.print("Enter block size: ");
        blockSize = obj.nextInt();
        System.out.println();
    }
}
// ===========================================
public class BestFit {
    Scanner obj = new Scanner(System.in);

    int [] fragmentedBlock;
    Boolean [] flag;
    // =================================
    public BestFit(int n) { // here n = no of tasks

        fragmentedBlock = new int[n];
        flag = new Boolean[n];

        for (int i = 0; i < n; i++) {
            flag[i] = false;
        }
    }
    // =================================
	public void sortBlock(Block [] arr, int n) {
		Block temp;
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < n-i-1; j++) {
				if (arr[j].blockSize > arr[j+1].blockSize) {
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
    // =================================
	public void allocateMemory(Task [] taskArr, Block [] blockArr,String [] allocatedBlocks, int n1, int n2) {
		int allocatedTasks = 0, i = 0, j;

		while (allocatedTasks != n1) {
			for (j = 0; j < n2; j++) {
                if (taskArr[i].taskSize <= blockArr[j].blockSize && flag[i] == false) {

                    fragmentedBlock[i] = blockArr[j].blockSize - taskArr[i].taskSize;
                    blockArr[j].blockSize -= taskArr[i].taskSize;
                    allocatedBlocks[i] = blockArr[j].blockName;
                    flag[i] = true;
                    sortBlock(blockArr, n2);
                }
            }
            allocatedTasks++;
            i++;
            System.out.println("Total Allocated Tasks: " + allocatedTasks);
		}
	}
    // =================================
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int n1, n2;
        System.out.print("Enter the no. of tasks: ");
        n1 = cin.nextInt();
        System.out.print("Enter the no. of blocks: ");
        n2 = cin.nextInt();

        Task [] taskQueue = new Task[n1];
        Block [] blockQueue = new Block[n2];
		String [] allocatedBlocks = new String[n1];

        BestFit algorithm = new BestFit(n1);

        System.out.println("-- Tasks --\n");
        for (int i = 0; i < n1; i++) {
            taskQueue[i] = new Task();
            taskQueue[i].setTask();
        }
        System.out.println("-- Blocks --\n");
        for (int i = 0; i < n2; i++) {
            blockQueue[i] = new Block();
            blockQueue[i].setBlock();
        }
        algorithm.sortBlock(blockQueue, n2);

        algorithm.allocateMemory(taskQueue, blockQueue, allocatedBlocks, n1, n2);

        System.out.println("\nTask ID\t\tTask Size\tBlock ID\tFragmented Size\n");
        for (int i = 0; i < n1; i++) {
            System.out.println(taskQueue[i].taskName + "\t\t" + taskQueue[i].taskSize + "\t\t" + allocatedBlocks[i] + "\t\t" + algorithm.fragmentedBlock[i]);
        }
    }
}
/*
Output:
Enter the no. of tasks: 4
Enter the no. of blocks: 5
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

Total Allocated Tasks: 1
Total Allocated Tasks: 2
Total Allocated Tasks: 3
Total Allocated Tasks: 4

Task ID         Task Size       Block ID        Fragmented Size

P1              212             B4              88
P2              417             B3              83
P3              112             B2              88
P4              400             B5              200
*/
