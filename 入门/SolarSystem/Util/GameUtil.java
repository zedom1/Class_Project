package Util;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * ��Ϸ�����г��õĹ�����
 * �����ͼƬ�ȷ���
 * @author Shinelon
 *
 */

public class GameUtil {
	
	private GameUtil () {} //�����๹�췽��˽��
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
