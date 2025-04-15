import java.rmi.Naming;
import java.util.Scanner;

public class BankClient {
    public static void main(String[] args) {
        try {
            Bank bank = (Bank) Naming.lookup("rmi://localhost:5000/BankService");

            Scanner scanner = new Scanner(System.in);
            int ans = 1;
            System.out.print("Enter Account Number: ");
            String accountNumber = scanner.nextLine();
            while (ans != 0) {
                System.out.println("1. Check Balance");
                System.out.println("2. Deposit");
                System.out.println("3. Withdraw");
                System.out.println("4. Exit");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();

                switch (choice) {
                    case 1:
                        System.out.println("Balance: " + bank.checkBalance(accountNumber));
                        break;
                    case 2:
                        System.out.print("Enter deposit amount: ");
                        double depositAmount = scanner.nextDouble();
                        System.out.println(bank.deposit(accountNumber, depositAmount));
                        break;
                    case 3:
                        System.out.print("Enter withdrawal amount: ");
                        double withdrawAmount = scanner.nextDouble();
                        System.out.println(bank.withdraw(accountNumber, withdrawAmount));
                        break;
                    case 4:
                        System.out.println("Thank you!");
                        ans = 0;
                        break;
                    default:
                        System.out.println("Invalid option.");
                }
                if (ans != 0) {
                    System.out.println("Do you want to continue? Enter 1 or 0: ");
                    ans = scanner.nextInt();
                }
            }
            scanner.close();
        } catch (Exception e) {
            System.out.println("Client Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
