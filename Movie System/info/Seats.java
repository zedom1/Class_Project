package info;

import java.util.Random;

public class Seats {
	public int width;
	public int length;
	private boolean[][] booked;
	
	public Seats(int w , int l) {
		this();
		width = w;
		length = l;
	}
	
	public Seats() {
		width = 8;
		length = 5;
		booked = new boolean[width][length];
//		Random rand = new Random();
//		for(int i=0; i<width; i++)
//			for(int j=0; j<length; j++)
//				booked[i][j] = rand.nextBoolean();
	}
	
	public boolean[][] getSeatMap() {
		return booked;
	}
	public void addBook(int w , int l) {
		booked[w][l]=true;
	}
	public int[] getSeatShape() {
		return new int[] {width, length};
	}
	public void setMap(boolean [][] map) {
		booked = map;
	}
}
