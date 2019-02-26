package Controller;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.rmi.RemoteException;
import java.util.ArrayList;

import javax.swing.JTextField;

import Modele.Group;
import Modele.Member;
import View.MenuMembers;
import Main.Main;

public class ListenerAddMember implements KeyListener{
//	private Group group;
	private JTextField inputMember;
	private MenuMembers menuMembers;
	
	public ListenerAddMember(JTextField inputMember, MenuMembers menuMembers) {
		this.inputMember = inputMember;
		this.menuMembers = menuMembers;
	}


	@Override
	public void keyReleased(KeyEvent arg0) {
		if(arg0.getKeyCode() == 10) { //Enter key
			Member memberToAdd;
			try {
				memberToAdd = Main.serverApp.getMember(inputMember.getText());
				if(memberToAdd != null) {
					
					if (memberToAdd.isInGroup(Main.USER.getCurrentGroup().getName())) {
						System.out.println("Ce membre est déjà dans le groupe");
					} else {
						Main.USER.getCurrentGroup().addMember(memberToAdd);
						menuMembers.addMember();
						memberToAdd.getGroupList().add(Main.USER.getCurrentGroup());
						System.out.println(memberToAdd.getPseudo() + " ajout� dans " + Main.USER.getCurrentGroup().getName());
					}
				}else {
					System.out.println("Membre inexistant");
				}
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
	}
	@Override
	public void keyPressed(KeyEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	
	

}
