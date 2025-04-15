import java.util.Arrays;
import java.util.Scanner;

class Process {
    private int processId;
    private int[] vectorClock;
    private int totalProcesses;

    public Process(int id, int numProcesses) {
        this.processId = id;
        this.totalProcesses = numProcesses;
        this.vectorClock = new int[numProcesses]; // Initialize vector clock
    }

    // Internal event: Increment the clock for this process
    public void internalEvent() {
        vectorClock[processId]++;
        System.out.println("Process " + (processId + 1) + " performed an internal event. Vector Clock: " + Arrays.toString(vectorClock));
    }

    // Sending a message
    public int[] sendMessage() {
        vectorClock[processId]++;
        System.out.println("Process " + (processId + 1) + " sent a message. Vector Clock: " + Arrays.toString(vectorClock));
        return vectorClock.clone(); // Send a copy of the current vector clock
    }

    // Receiving a message and updating the vector clock
    public void receiveMessage(int[] receivedVector) {
        for (int i = 0; i < totalProcesses; i++) {
            vectorClock[i] = Math.max(vectorClock[i], receivedVector[i]);
        }
        vectorClock[processId]++; // Increment after receiving the message
        System.out.println("Process " + (processId + 1) + " received a message. Updated Vector Clock: " + Arrays.toString(vectorClock));
    }

    public int[] getVectorClock() {
        return vectorClock;
    }
}

public class VectorClockSimulation {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get number of processes
        System.out.print("Enter the number of processes: ");
        int numProcesses = scanner.nextInt();
        Process[] processes = new Process[numProcesses];

        // Initialize processes
        for (int i = 0; i < numProcesses; i++) {
            processes[i] = new Process(i, numProcesses);
        }

        while (true) {
            System.out.println("\nChoose an event type: (1) Internal (2) Send Message (3) Receive Message (-1 to Exit)");
            int eventType = scanner.nextInt();

            if (eventType == -1) {
                System.out.println("Exiting program...");
                break;
            }

            if (eventType == 1) { // Internal event
                System.out.print("Enter process number (1 to " + numProcesses + "): ");
                int processNum = scanner.nextInt();
                if (processNum < 1 || processNum > numProcesses) {
                    System.out.println("Invalid process number! Try again.");
                    continue;
                }
                processes[processNum - 1].internalEvent();

            } else if (eventType == 2) { // Send message
                System.out.print("Enter sender process number (1 to " + numProcesses + "): ");
                int sender = scanner.nextInt();
                if (sender < 1 || sender > numProcesses) {
                    System.out.println("Invalid sender process number! Try again.");
                    continue;
                }

                System.out.print("Enter receiver process number (1 to " + numProcesses + "): ");
                int receiver = scanner.nextInt();
                if (receiver < 1 || receiver > numProcesses || sender == receiver) {
                    System.out.println("Invalid receiver process number! Try again.");
                    continue;
                }

                int[] message = processes[sender - 1].sendMessage();
                processes[receiver - 1].receiveMessage(message);

            } else if (eventType == 3) { // Receive message
                System.out.print("Enter receiver process number (1 to " + numProcesses + "): ");
                int receiver = scanner.nextInt();
                if (receiver < 1 || receiver > numProcesses) {
                    System.out.println("Invalid receiver process number! Try again.");
                    continue;
                }

                System.out.print("Enter sender process number (1 to " + numProcesses + "): ");
                int sender = scanner.nextInt();
                if (sender < 1 || sender > numProcesses || sender == receiver) {
                    System.out.println("Invalid sender process number! Try again.");
                    continue;
                }

                System.out.println("Enter the received vector clock values separated by spaces:");
                int[] receivedVector = new int[numProcesses];
                for (int i = 0; i < numProcesses; i++) {
                    receivedVector[i] = scanner.nextInt();
                }
                processes[receiver - 1].receiveMessage(receivedVector);

            } else {
                System.out.println("Invalid choice! Try again.");
                continue;
            }

            // Print vector clocks after each event
            System.out.println("\nVector Clocks of all Processes:");
            printVectorClocks(processes);
        }

        // Print final vector clocks in table format
        System.out.println("\nFinal Vector Clocks of All Processes:");
        printVectorClockTable(processes);
        scanner.close();
    }

    // Method to print vector clocks in a simple list format
    private static void printVectorClocks(Process[] processes) {
        for (int i = 0; i < processes.length; i++) {
            System.out.println("Process " + (i + 1) + ": " + Arrays.toString(processes[i].getVectorClock()));
        }
    }

    // Method to print vector clocks in a table format
    private static void printVectorClockTable(Process[] processes) {
        System.out.println("+------------------------------------------------+");
        System.out.print("| Process |");
        for (int i = 0; i < processes.length; i++) {
            System.out.printf(" P%-3d |", (i + 1));
        }
        System.out.println("\n+------------------------------------------------+");

        for (int i = 0; i < processes.length; i++) {
            System.out.printf("|   %4d   |", (i + 1));
            int[] clock = processes[i].getVectorClock();
            for (int value : clock) {
                System.out.printf(" %3d |", value);
            }
            System.out.println();
        }
        System.out.println("+------------------------------------------------+");
    }
}
