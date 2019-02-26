package Controller;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;

import View.PCanva;
import server.ServerGroup;
import server.ServerGroupImpl;
import Main.Main;
public class ListenersPCanva implements MouseListener, MouseMotionListener  {
	private ArrayList<Point> path;
	private PCanva pCanva;
	private ServerGroup serverGroup;
	
	public ListenersPCanva(PCanva pCanva) {
		this.pCanva = pCanva;
		path = new ArrayList<Point>();
		
		Registry registry;
		try {
			registry = LocateRegistry.getRegistry();
			this.serverGroup = (ServerGroup) registry.lookup(Main.USER.getCurrentGroup().getName());
		} catch (RemoteException | NotBoundException e) {
			e.printStackTrace();
		}

	}
	public void changeServer(String name) {
		Registry registry;
		System.out.println("change server");

		try {
			if(Main.adress != null) {
				registry = LocateRegistry.getRegistry(Main.adress);
			}else {
				registry = LocateRegistry.getRegistry();	
			}
			this.serverGroup = (ServerGroup) registry.lookup(name);
		} catch (RemoteException | NotBoundException e) {
			e.printStackTrace();
		}
	}
	public ArrayList<Point> getPath(){
		return path;
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		Registry registry;

		try {
			this.serverGroup.draw(Main.USER, path);
		} catch (RemoteException e1) {
			e1.printStackTrace();
		}
		this.path = new ArrayList<Point>();		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		this.path.add(new Point(e.getX(), e.getY()));
		//pCanva.drawPath();
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

}
