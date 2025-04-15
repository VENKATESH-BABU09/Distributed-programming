import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class BankServer {
    public static void main(String[] args) {
        try {
            Bank bank = new BankImpl();
            LocateRegistry.createRegistry(5000); // Start RMI registry on 5000
            Naming.rebind("rmi://localhost:5000/BankService", bank);
            System.out.println("Bank Server is running on port 5000...");
        } catch (Exception e) {
            System.out.println("Server Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
