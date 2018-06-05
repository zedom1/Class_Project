package info;

import java.util.ArrayList;

public class BookItem {
	private static int COUNT = 0;
	public int id;
	public int userID;
	public int movieID;
	public int sessionID;
	private ArrayList<int[]> seatNum = new ArrayList<>();
	public int price;
	
	public BookItem( int u, int m , int s ,  int p) {
		id = COUNT;
		userID = u;
		movieID = m;
		sessionID = s;
		price = p;
	}
	
	public void addSeat(int [] seats, int p) {
		seatNum.add(seats);
		price+=p;
	}
	
	public void clearSeat() {
		seatNum.clear();
		price = 0;
	}
	
	public String getDesc() {
		Movie movie = Cinema.getMovieByID(movieID);
		String s1 = String.format("订单编号：%d \n用户编号：%d \n电影名：%s\n场次日期：%s\n场次时间：%s\n", 
				id,userID,movie.getName(), movie.getSessionByID(sessionID).date,movie.getSessionByID(sessionID).time);
		for(int [] seat : seatNum) {
			s1 += String.format("座位号：%d 行 , %d 列\n", seat[1]+1,seat[0]+1);
		}
		s1 += String.format("价格：%d 元\n", price );
		return s1;
	}
	
	public String getDescPure() {
		Movie movie = Cinema.getMovieByID(movieID);
		String s1 = String.format("%d\t%d\t%d\t%d", 
				id,userID,movie.id, sessionID);
		for(int [] seat : seatNum) {
			s1 += String.format("\t%d\t%d", seat[1]+1,seat[0]+1);
		}
		s1 += String.format("\t%d\n",price );
		return s1;
	}
}