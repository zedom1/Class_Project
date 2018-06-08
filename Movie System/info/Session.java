package info;

public class Session {
	public int id;
	public String date;
	public String time;
	public int num;
	
	private Seats seat = new Seats();
	
	public Session(int i, String d , String t, int n) {
		id = i;
		date = d;
		time = t;
		num = n;
	}
	
	public Session(int i, String d , String t, int n, int width, int length) {
		this(i,d,t,n);
		seat = new Seats(width, length);
	}
	
	public String getDesc() {
		String sentence = String.format("Session ID : %d \n Date: %s \n Time : %s \n Place: %d号厅",id,date,time,num);
		return sentence;
	}
	
	public int[] getSeatSize() {
		return new int[] {seat.width , seat.length};
	}
	
	public boolean[][] getBook() {
		return seat.getSeatMap();
	}
	public void addBook(int w , int l) {
		seat.addBook(w,l);
	}
	public void setSeatMap(boolean [][]map) {
		seat.setMap(map);
	}
}
