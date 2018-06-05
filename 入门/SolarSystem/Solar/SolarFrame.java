package Solar;

import java.awt.Graphics;
import java.awt.Image;
import Util.*;
/**
 * 太阳系的主窗口
 * @author Shinelon
 *
 */
public class SolarFrame extends Util.MyFrame {
	Image bg = Util.GameUtil.getImage("images/bg.jpg");
	Star sun = new Star("images/sun.jpg",(double)Constant.GAME_HEIGHT/2, (double)Constant.GAME_WIDTH/2);
	Planet earth = new Planet("images/earth.jpg",150,100,0.1,sun);
	Planet mars = new Planet("images/Mars.jpg", 200, 130,0.2,sun);
	Planet moon = new Planet("images/moon.jpg", 20,30,0.1, earth,true);
	
	public void paint(Graphics g) {
		g.drawImage(bg,0, 0,null);
		sun.draw(g);
		earth.draw(g);
		mars.draw(g);
		moon.draw(g);
	}
	
	 public static void main(String[] args) {
		new SolarFrame().launchFrame();
	}
	
}
