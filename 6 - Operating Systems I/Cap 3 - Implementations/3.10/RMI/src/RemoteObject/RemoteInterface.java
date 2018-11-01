package RemoteObject;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RemoteInterface extends Remote
{
    public abstract String getFortune() throws RemoteException;
}