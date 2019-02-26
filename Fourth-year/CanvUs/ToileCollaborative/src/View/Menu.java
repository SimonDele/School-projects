package View;

import javax.swing.BoxLayout;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import Modele.Canvas;
import Modele.Group;
import Modele.Member;

public class Menu extends JPanel {
	public static MenuMembers menuMembers;
	public static MenuGroups menuGroups;

	public Menu(Group group, Member member, Canvas canvas) {
		menuMembers = new MenuMembers(group);
		menuGroups = new MenuGroups(member.getGroupList(), canvas);
		
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		this.add(new JScrollPane(menuGroups));
		this.add(new JScrollPane(menuMembers));
	}
}
