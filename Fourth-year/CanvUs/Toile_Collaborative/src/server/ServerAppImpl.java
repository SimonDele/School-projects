package server;

import java.awt.Color;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

import Modele.Group;
import Modele.Member;

public class ServerAppImpl extends UnicastRemoteObject implements ServerApp {
	
	HashSet<ServerGroup> listServerGroup;
	public final String nameGroupPublic = "public"; 
	Group groupPublic;
	final File fileMembers = new File("listeMembers.txt");
	
	protected ServerAppImpl() throws RemoteException {
		super();
		listServerGroup = new HashSet<ServerGroup>();

		//Create public canvas.
		this.groupPublic = new Group(nameGroupPublic);
		ServerGroupImpl newServerGroup = new ServerGroupImpl(groupPublic,null);
		this.listServerGroup.add(newServerGroup);
		
		Registry registry = LocateRegistry.getRegistry();
		ServerGroup serverGroupPublic;
		try {
			serverGroupPublic = (ServerGroup) registry.lookup(nameGroupPublic);
			//And add it to the listServerGroup
			listServerGroup.add(serverGroupPublic);
		} catch (NotBoundException e) {
			e.printStackTrace();
		}
	}
 

	@Override
	public Member register(String pseudo, String password,  Color color) throws RemoteException {
		System.out.println("registered");
		//Create member
		Member member = new Member(pseudo, password, color);
		member.setCurrentGroup(groupPublic);
		member.getGroupList().add(groupPublic);
		//Add him to the group/server public 
		connectToServerGroup(groupPublic, member);
		
		//Update file
		ArrayList<Member> listMembers = this.readFileMembers();
		listMembers.add(member);
		this.writeFileMembers(listMembers);	
		
		return member;
	}
	
	public void connectToServerGroup(Group group, Member member) throws RemoteException{
		boolean serverFound = false;
		Iterator iteratorServer = listServerGroup.iterator();
		ServerGroup serverGroup = null;
		while(!serverFound && iteratorServer.hasNext()){
			serverGroup = (ServerGroup) iteratorServer.next();
			System.out.println("while " + serverGroup.getName());
			try {
				serverFound = (serverGroup.getName().equals(group.getName()));
				System.out.println(serverGroup.getName() +" " + group.getName() + " " + serverFound);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		if(serverFound) {
			try {
				System.out.println("(ServerApp connectoserver)" + member.getPseudo() + " ajouté au server "+ serverGroup.getName());
				serverGroup.addMember(member);
			} catch (RemoteException e) {
				e.printStackTrace();
			}	
		}else {
			// TODO create a server
// Erreur ici quelque part 
			ServerGroup newServerGroup = new ServerGroupImpl(group, null);
			newServerGroup.addMember(member);
			listServerGroup.add(newServerGroup);
		}

	}
	@Override
	public Member connection(String pseudo, String password) throws RemoteException {
		
		System.out.println("connection to the server...");
		
		ArrayList<Member> listMember = readFileMembers();
		Iterator iterator = listMember.iterator();
		boolean found = false;
		Member member = null;
		while(!found && iterator.hasNext()) {
			member = (Member) iterator.next();
			found = ((password.equals(member.getPassword())) && (pseudo.equals(member.getPseudo())));
		}
		if(found) {
			//Check if all the group of member.getGroupList() have a "ServerGroup" otherwise it must be created 
			
			//For Each group
			for (Iterator itGroup = member.getGroupList().iterator(); itGroup.hasNext();) {
				Group group = (Group) itGroup.next();
				this.connectToServerGroup(group, member);
			}
			member.setCurrentGroup(groupPublic);
			return member;
		}else {
			//Not yet registered
			return null;
		}

	}
	public void addNewServerGroup(Member creator, Group group) throws RemoteException {
		ServerGroupImpl newServerGroup = new ServerGroupImpl(group,null);
		creator.setCurrentGroup(group);
		newServerGroup.addMember(creator);
		this.listServerGroup.add(newServerGroup);
	}
	public void writeFileMembers(ArrayList<Member> listMembers) throws RemoteException{
		try {
			ObjectOutputStream oos = new ObjectOutputStream(
			          new BufferedOutputStream(
			            new FileOutputStream(fileMembers)));
		    for (int i=0; i<listMembers.size();i++) {
				Member member = listMembers.get(i);
				oos.writeObject(member);	
			}
			oos.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public ArrayList<Member> readFileMembers() throws RemoteException{
		ArrayList<Member> res = new ArrayList<Member>();
		ObjectInputStream ois;

		try {
			ois = new ObjectInputStream(
			          new BufferedInputStream(
			            new FileInputStream(this.fileMembers)));
				while(true) {
					try {
						Member obj = (Member)ois.readObject();
						res.add(obj);
					}catch(EOFException | ClassNotFoundException e) { // Catch if we have reached the end of the file
						ois.close();
						break;
					}

				}
				
			ois.close();
		} catch (FileNotFoundException e) {
			//e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}	
		return res;
	}
	
	
	@Override
	public Member getMember(String pseudo) throws RemoteException {
		
		ArrayList<Member> listMembers = readFileMembers();
		for (Iterator iterator = listMembers.iterator(); iterator.hasNext();) {
			Member member = (Member) iterator.next();
			if(member.getPseudo().equals(pseudo)) {
				return member;
			}
		}
		return null; //If the member doesn't exist
	}

	public static void main(String[] args) throws RemoteException {
		try {
			ServerAppImpl serverAppImpl = new ServerAppImpl();
			if(args.length > 0) {
				Registry registry = LocateRegistry.getRegistry(args[0]);
				registry.rebind("ServerApp", serverAppImpl);
			}else {
				Registry registry = LocateRegistry.getRegistry();
				registry.rebind("ServerApp", serverAppImpl);
			}
			
		} catch (RemoteException e) {
			e.printStackTrace();
		}
		System.out.println("Server App running");
	}


	@Override
	public String getNameGroupPublic() throws RemoteException {
		return this.nameGroupPublic;
	}


	@Override
	public void logOut(Member user) throws RemoteException {
		for (Iterator iterator = user.getGroupList().iterator(); iterator.hasNext();) {
			Group group = (Group) iterator.next();
			for (Iterator iterator2 = listServerGroup.iterator(); iterator2.hasNext();) {
				ServerGroup serverGroup = (ServerGroup) iterator2.next();
				if(serverGroup.getName().equals(group.getName())) {
					serverGroup.logOut(user);
				}
			}
		}
	}



}
