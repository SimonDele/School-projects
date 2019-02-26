package server;

import java.awt.Point;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

import Modele.Group;
import Modele.Member;

public interface ServerGroup extends Remote{
	public void addMember(Member member) throws RemoteException;
	public void draw(Member member, ArrayList<Point> pixelsToDraw) throws RemoteException;
	public String getName() throws RemoteException;
	public boolean equals(String name) throws RemoteException;
	public Group getGroup() throws RemoteException;
	public void sendDrawing(Member member) throws RemoteException;
	public void logOut(Member user) throws RemoteException;
}
