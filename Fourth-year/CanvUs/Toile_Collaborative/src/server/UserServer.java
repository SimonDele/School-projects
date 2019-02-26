package server;

import java.awt.Point;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

import javax.swing.ImageIcon;

import Modele.Group;
import Modele.Member;

public interface UserServer extends Remote{
	public void updateGroup(Group group) throws RemoteException;
	public void drawPath(Member drawer, ArrayList<Point> path) throws RemoteException;
	public void loadDrawing(ImageIcon drawing) throws RemoteException;
	public Group getCurrentGroup() throws RemoteException;
}
