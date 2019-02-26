package Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import Main.Main;
import Modele.Canvas;
import Modele.Group;
import View.MainFrame;
import View.Menu;
import server.ServerGroup;

public class ListenerSwitchGroup implements ActionListener {
/*
 * This listener is call when we want to switch from one group to another
 * It will change : 
 * 1) the current canvas 
 * 2) the list of members

 * 2) Not yet implemented
 */
	Canvas canvas;
	Group newGroup;
	
	public ListenerSwitchGroup(Canvas canvas, Group group) {
		this.canvas = canvas;
		this.newGroup = group;
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		
		Registry registry;
		try {
			// retrieve the newGroup on the server
			if(Main.adress != null) {
				registry = LocateRegistry.getRegistry(Main.adress);
			}else {
				registry = LocateRegistry.getRegistry();	
			}
			ServerGroup serverGroup = (ServerGroup) registry.lookup(this.newGroup.getName());
			this.newGroup = serverGroup.getGroup();
			
			// set all variables
			Main.USER.setCurrentGroup(this.newGroup);
			MainFrame.currentGroup = this.newGroup;
			MainFrame.pCanva.switchCanvas();
			System.out.println(this.newGroup.getMemberList());
			Menu.menuMembers.setListMembers(this.newGroup.getMemberList());
			System.out.println(Main.USER.getCurrentGroup().getName() + "current group");
		
			// load Drawing
			serverGroup.sendDrawing(Main.USER);
					
		} catch (RemoteException | NotBoundException e) {
			e.printStackTrace();
		}
	}
}
