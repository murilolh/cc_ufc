package RemoteObject;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Client
{
    public Client() {}

    public static void main(String[] args)
    {
        String host = "rmi://127.0.1.1/RemoteInterface";
        try 
        {
            Registry registry = LocateRegistry.getRegistry(host);
            RemoteInterface stub = (RemoteInterface)registry.lookup("RemoteInterface");
            String response = stub.getFortune();
            System.out.println("Mensagem: " + response);
        } catch (Exception e) {
            System.err.println("Exceção do Cliente: " + e.toString());
            e.printStackTrace();
        }
    }
}