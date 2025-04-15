import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Bank extends Remote {
    double checkBalance(String accountNumber) throws RemoteException;
    String deposit(String accountNumber, double amount) throws RemoteException;
    String withdraw(String accountNumber, double amount) throws RemoteException;
}
