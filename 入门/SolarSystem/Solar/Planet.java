package Solar;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;

import Util.GameUtil;

public class Planet extends Star {
	
	// 长轴、短轴、速度、角度、环绕中心
	double longAxis;
	double shortAxis;
	double speed;
	double degree;
	Star center;
	
	boolean satellite;
	
	public void draw(Graphics g) {
		super.draw(g);
		move();
		if(!satellite)
			drawTrace(g);
	}
	public void drawTrace(Graphics g) {
		double xx,yy,width1,height1;
		
		width1 = longAxis*2;
		height1 = shortAxis *2;
		xx = center.x + center.width/2 - longAxis;
		yy = center.y + center.height/2 - shortAxis;
		Color color = g.getColor();
		g.setColor(Color.BLUE);
		g.drawOval((int)xx, (int)yy, (int)width1, (int)height1);
		g.setColor(color);
	}
	
	public void move() {
		x = center.x + center.width/2 + longAxis * Math.cos(degree);
		y = center.y + center.height/2 + shortAxis * Math.sin(degree);
		degree += speed;
	}
	
	public Planet(String path,  double longAxis, double shortAxis, double speed, Star center) {
		super(GameUtil.getImage(path));
		this.longAxis = longAxis;
		this.shortAxis = shortAxis;
		this.speed = speed;
		this.center = center;
		x = center.x + longAxis;
		y = center.y;
	}
	
	public Planet(String path,  double longAxis, double shortAxis, double speed, Star center,boolean satellite) {
		this(path, longAxis, shortAxis, speed, center);
		this.satellite=satellite;
	}
	public Planet(Image image , double x, double y) {
		super(image, x, y);
	}
	public Planet(String path , double x, double y) {
		super(path, x, y);
	}
}
