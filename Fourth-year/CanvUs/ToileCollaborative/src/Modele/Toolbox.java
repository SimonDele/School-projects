package Modele;

import java.io.Serializable;

public class Toolbox implements Serializable{
	private String shapeSelected;
	private int size;
	
	public Toolbox() {
		shapeSelected = "CIRCLE";
		size = 20;
	}
	
	public void setShapeSelected(String s) {
		this.shapeSelected = s;
	}
	public int getSize() {
		return size;
	}
	public void setSize(int size) {
		this.size = size;
	}
	public String getShapeSelected() {
		return shapeSelected;
	}
}
