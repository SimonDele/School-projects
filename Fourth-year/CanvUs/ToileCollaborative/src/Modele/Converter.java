package Modele;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.ImageIcon;

public class Converter {
	public static BufferedImage toBufferedImage(ImageIcon icon) {
		BufferedImage bimg = new BufferedImage(
			    icon.getIconWidth(),
			    icon.getIconHeight(),BufferedImage.TYPE_3BYTE_BGR);
		Graphics g = bimg.createGraphics();
        // paint the Icon to the BufferedImage.
        icon.paintIcon(null, g, 0,0);
        g.dispose();
        return bimg;
	}
	public static ImageIcon toIcon(BufferedImage image){
		return new ImageIcon(image);
	}
}
