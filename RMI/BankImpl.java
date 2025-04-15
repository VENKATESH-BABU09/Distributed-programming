import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.util.HashMap;

public class BankImpl extends UnicastRemoteObject implements Bank {
    private HashMap<String, Double> accounts;

    protected BankImpl() throws RemoteException {
        super();
        accounts = new HashMap<>();
        // Sample accounts
        accounts.put("12345", 1000.0);
        accounts.put("67890", 500.0);
    }

    @Override
    public double checkBalance(String accountNumber) throws RemoteException {
        return accounts.getOrDefault(accountNumber, 0.0);
    }

    @Override
    public String deposit(String accountNumber, double amount) throws RemoteException {
        accounts.put(accountNumber, accounts.getOrDefault(accountNumber, 0.0) + amount);
        return "Deposit successful. New Balance: " + accounts.get(accountNumber);
    }

    @Override
    public String withdraw(String accountNumber, double amount) throws RemoteException {
        double balance = accounts.getOrDefault(accountNumber, 0.0);
        if (balance >= amount) {
            accounts.put(accountNumber, balance - amount);
            return "Withdrawal successful. Remaining Balance: " + accounts.get(accountNumber);
        } else {
            return "Insufficient funds.";
        }
    }
}
