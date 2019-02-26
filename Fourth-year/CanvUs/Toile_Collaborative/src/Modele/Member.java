package Modele;

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
import java.io.Serializable;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Iterator;

import server.ServerApp;
import Main.Main;
public class Member implements Serializable {
	
	private String pseudo;
	private String password;
	private Color color; 
	private ArrayList<Group> groupList;
	
	private Toolbox toolbox;
	private Group currentGroup;
	
	public Member(String pseudo,String password, Color color) {
		groupList = new ArrayList<Group>(); // Creation of an empty groupList
		this.pseudo = pseudo;
		this.password = password;
		this.color = color;
		this.setToolbox(new Toolbox());

	}
	public String getPseudo() {
		return pseudo;
	}
	public Color getColor() {
		return color;
	}
	public String getPassword() {
		return password;
	}
	public ArrayList<Group> getGroupList() {
		return groupList;
	}
	public Group getCurrentGroup() {
		return currentGroup;
	}
	public void setCurrentGroup(Group currentGroup) {
		this.currentGroup = currentGroup;
	}

	public void createNewGroup(String name) {
		//Create the group and add it to the list of groups
		Group newgroup = new Group(name);
		this.groupList.add(newgroup);
		
		try {
			Main.serverApp.addNewServerGroup(this,newgroup);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
		
		//Update the file on the server
		ArrayList<Member> members;
		try {
			// Get the list of all the members
			members = Main.serverApp.readFileMembers();
			// Then updating of the file
			for(int i=0; i<members.size();i++) { //Modify the current User
				if(members.get(i).pseudo.equals(this.pseudo) && members.get(i).password.equals(this.password)) {
					members.set(i,this);
				}
			}
			
			Main.serverApp.writeFileMembers(members); //And rewrite everything
		} catch (RemoteException e) {
			e.printStackTrace();
		} 
	}
/*
	public void saveBeforeExit() {
		ArrayList<Member> member = readFileMembers(); // Get the list of all the members
		writeFileMembers(member); //And rewrite it
		for(int i=0; i<this.groupList.size(); i++) {
			try {
				this.groupList.get(i).getCanvas().save(this.groupList.get(i).getName());
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
*/
	public Toolbox getToolbox() {
		return toolbox;
	}
	public void setToolbox(Toolbox toolbox) {
		this.toolbox = toolbox;
	}
	public boolean isInGroup(String groupName) {
		boolean is = false;
		for (Group group : groupList) {
			if (group.getName().equals(groupName)) {
				is = true;
				break;
			}
		}
		return is;
	}
}
