package Main;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import Modele.Member;
import View.MainFrame;
import View.SignIn_Up;
import server.ServerApp;
import server.ServerGroup;
import server.UserServerImpl;
/**
 * @author s1m0n
 * Entry point of the app
 *
 */
public class Main {
	public static Member USER;
	public static ServerApp serverApp;
	public static String adress;
	
	public static void main(String[] args) {

		Registry registry = null;
		try {
			if(args.length > 0) {
				adress = args[0];
				registry = LocateRegistry.getRegistry(args[0]);
			}else {
				registry = LocateRegistry.getRegistry();	
			}
			serverApp = (ServerApp) registry.lookup("ServerApp");
		} catch (RemoteException | NotBoundException e) {
			System.out.println("Can't connect to the Server App");
		}
				
		SignIn_Up signIn_Up = new SignIn_Up(null);
		USER = signIn_Up.getMember();

		System.out.println("(main) " + USER.getColor());
		UserServerImpl userServerImpl;
		try {
			userServerImpl = new UserServerImpl();
			registry.rebind(USER.getPseudo(), userServerImpl);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
		
		//Load the public drawing 
		try {
			ServerGroup serverPublic = (ServerGroup) registry.lookup(serverApp.getNameGroupPublic());
			serverPublic.sendDrawing(USER);
		} catch (RemoteException | NotBoundException e) {
			e.printStackTrace();
		}
				
		MainFrame mainFrame = new MainFrame(USER);
		mainFrame.setVisible(true);		
	}
}
