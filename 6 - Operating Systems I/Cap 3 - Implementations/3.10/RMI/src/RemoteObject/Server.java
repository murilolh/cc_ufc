package RemoteObject;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

public class Server implements RemoteInterface
{
    public Server() {}

    public String getFortune()
    {
        Random rd = new Random();
        String[] fortunes = new String[30];
        fortunes[1]= "aaaaaaa";
        fortunes[2]= "bbbbbbb";
        fortunes[3]= "ccccccc";
        fortunes[4]= "ddddddd";
        fortunes[5]= "eeeeeee";
        fortunes[6]= "fffffff";
        fortunes[7]= "ggggggg";
        fortunes[8]= "hhhhhhh";
        fortunes[9]= "iiiiiii";
        fortunes[10]= "jjjjjjj";
        fortunes[11]= "kkkkkkk";
        fortunes[12]= "lllllll";
        fortunes[13]= "mmmmmmm";
        fortunes[14]= "nnnnnnn";
        fortunes[15]= "ooooooo";
        fortunes[16]= "ppppppp";
        fortunes[17]= "qqqqqqq";
        fortunes[18]= "rrrrrrr";
        fortunes[19]= "sssssss";
        fortunes[20]= "ttttttt";
        fortunes[21]= "uuuuuuu";
        fortunes[22]= "vvvvvvv";
        fortunes[23]= "wwwwwww";
        fortunes[24]= "xxxxxxx";
        fortunes[25]= "yyyyyyy";
        fortunes[26]= "zzzzzzz";
        int r = rd.nextInt(26);
        return fortunes[r];
    }

    public static void main(String args[])
    {
	    try
        {
            Server obj = new Server();
            RemoteInterface stub = (RemoteInterface) UnicastRemoteObject.exportObject(obj, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.bind("RemoteInterface", stub);
            System.err.println("----Servidor Pronto------");
        } catch (Exception e) {
            System.err.println("Exceção do Servidor: " + e.toString());
            e.printStackTrace();
        }
    }
}