import java.util.Scanner;

class Process {
    private int logicalClock;
    private int processId;
    private int tickValue; // Tick value for the process

    public Process(int id, int tick) {
        this.processId = id;
        this.logicalClock = 0;
        this.tickValue = tick;
    }

    // Internal event
    public void internalEvent() {
        logicalClock += tickValue;
        System.out.println("Process " + processId + " performed an internal event. Logical Clock: " + logicalClock);
    }

    // Sending a message
    public int sendMessage() {
        logicalClock += tickValue;
        System.out.println("Process " + processId + " sent a message. Logical Clock: " + logicalClock);
        return logicalClock;
    }

    // Receiving a message
    public void receiveMessage(int receivedTimestamp) {
        logicalClock = Math.max(logicalClock, receivedTimestamp) + tickValue;
        System.out.println("Process " + processId + " received a message. Updated Logical Clock: " + logicalClock);
    }

    public int getLogicalClock() {
        return logicalClock;
    }

    public int getProcessId() {
        return processId;
    }
}

public class LamportLogicalClockWithTick {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get number of processes
        System.out.print("Enter the number of processes: ");
        int numProcesses = scanner.nextInt();
        Process[] processes = new Process[numProcesses];

        // Get tick values and initialize processes
        for (int i = 0; i < numProcesses; i++) {
            System.out.print("Enter tick value for process P" + (i + 1) + ": ");
            int tickValue = scanner.nextInt();
            processes[i] = new Process(i + 1, tickValue);
        }

        while (true) {
            System.out.println("\nChoose an event type: (1) Internal (2) Send Message (3) Receive Message (-1 to Exit)");
            int eventType = scanner.nextInt();

            if (eventType == -1) {
                System.out.println("Exiting program...");
                break;
            }

            if (eventType == 1) {  // Internal event
                System.out.print("Enter process number: ");
                int processNum = scanner.nextInt();
                if (processNum < 1 || processNum > numProcesses) {
                    System.out.println("Invalid process number! Try again.");
                    continue;
                }
                processes[processNum - 1].internalEvent();

            } else if (eventType == 2) { // Send message
                System.out.print("Enter sender process number: ");
                int sender = scanner.nextInt();
                if (sender < 1 || sender > numProcesses) {
                    System.out.println("Invalid sender process number! Try again.");
                    continue;
                }

                System.out.print("Enter receiver process number: ");
                int receiver = scanner.nextInt();
                if (receiver < 1 || receiver > numProcesses || sender == receiver) {
                    System.out.println("Invalid receiver process number! Try again.");
                    continue;
                }

                int timestamp = processes[sender - 1].sendMessage();
                processes[receiver - 1].receiveMessage(timestamp);

            } else if (eventType == 3) { // Receive message
                System.out.print("Enter receiver process number: ");
                int receiver = scanner.nextInt();
                if (receiver < 1 || receiver > numProcesses) {
                    System.out.println("Invalid receiver process number! Try again.");
                    continue;
                }

                System.out.print("Enter sender process number: ");
                int sender = scanner.nextInt();
                if (sender < 1 || sender > numProcesses || sender == receiver) {
                    System.out.println("Invalid sender process number! Try again.");
                    continue;
                }

                System.out.print("Enter the timestamp of the received message: ");
                int receivedTimestamp = scanner.nextInt();
                processes[receiver - 1].receiveMessage(receivedTimestamp);

            } else {
                System.out.println("Invalid choice! Try again.");
                continue;
            }

            // Print logical clocks after each event
            System.out.println("\nLogical Clocks of all Processes:");
            printLogicalClocks(processes);
        }

        // Print final logical clocks in table format
        System.out.println("\nFinal Logical Clocks of All Processes:");
        printLogicalClocksTable(processes);
        scanner.close();
    }

    // Method to print logical clocks in a simple list format
    private static void printLogicalClocks(Process[] processes) {
        for (Process process : processes) {
            System.out.println("Process " + process.getProcessId() + " -> Logical Clock: " + process.getLogicalClock());
        }
    }

    // Method to print logical clocks in a table format
    private static void printLogicalClocksTable(Process[] processes) {
        System.out.println("+------------------+");
        System.out.println("| Process | Clock |");
        System.out.println("+------------------+");
        for (Process process : processes) {
            System.out.printf("|   %4d   |   %4d   |%n", process.getProcessId(), process.getLogicalClock());
        }
        System.out.println("+------------------+");
    }
}
