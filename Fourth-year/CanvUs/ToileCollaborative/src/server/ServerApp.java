package server;

import java.awt.Color;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

import Modele.Group;
import Modele.Member;

public interface ServerApp extends Remote {
	
	
	public Member connection(String pseudo, String password) throws RemoteException;
	public Member register(String pseudo, String password, Color color) throws RemoteException;
	public void addNewServerGroup(Member creator, Group group) throws RemoteException;
	public void connectToServerGroup(Group group, Member member) throws RemoteException;
	public Member getMember(String pseudo) throws RemoteException;
	public ArrayList<Member> readFileMembers() throws RemoteException;
	public void writeFileMembers(ArrayList<Member> listMembers) throws RemoteException;
	public String getNameGroupPublic() throws RemoteException;
	public void logOut(Member user) throws RemoteException;
}
