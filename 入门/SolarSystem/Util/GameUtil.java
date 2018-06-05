package Util;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * 游戏开发中常用的工具类
 * 如加载图片等方法
 * @author Shinelon
 *
 */

public class GameUtil {
	
	private GameUtil () {} //工具类构造方法私有
	public static Image getImage(String path) {
		java.net.URL u = GameUtil.class.getClassLoader().getResource(path);
		BufferedImage image = null;
		try {
			image = ImageIO.read(u);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return image;
	}
}
