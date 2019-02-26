package server;

import java.awt.Point;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

import javax.swing.ImageIcon;

import Main.Main;
import Modele.Group;
import Modele.Member;

public class UserServerImpl extends UnicastRemoteObject implements UserServer {

	public UserServerImpl() throws RemoteException {
		super();
	}

	@Override
	public void drawPath(Member drawer, ArrayList<Point> path) throws RemoteException{
		System.out.println("update");
		Main.USER.getCurrentGroup().getCanvas().drawPath(drawer, path);
	}

	@Override
	public void updateGroup(Group group) throws RemoteException {
		Main.USER.setCurrentGroup(group);		
	}

	@Override
	public void loadDrawing(ImageIcon drawing) throws RemoteException {
		Main.USER.getCurrentGroup().getCanvas().setDrawing(drawing);
		
	}

	@Override
	public Group getCurrentGroup() throws RemoteException {
		return Main.USER.getCurrentGroup();
	}

}
