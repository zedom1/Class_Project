package support;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.util.ArrayList;

import info.BookItem;
import info.Cinema;
import info.Movie;
import info.Session;

public class DataInterface {
	
	private static final String bookpath = "data/book.txt";
	private static final String moviepath = "data/movie.txt";
	private static final String sessionpath = "data/session.txt";
	private static final String userpath = "data/user.txt";
	private static final String seatpath = "data/seat.txt";
	private static final String encoding = "utf8";
	
	public static void saveNewBook(BookItem book) throws IOException {
		FileWriter writer = new FileWriter(bookpath, true);
		String[] s = book.getDescPure().split("\t");
		saveSeat(s);
		int length = (s.length-6)/2;
		int prelength = 4;
		String presen = "";
		for(int i=0; i<prelength ; i++)
			presen = presen+"\t"+s[i];
		for(int i=0; i<length; i++) {
			writer.write(presen.trim() + "\t"+s[prelength +i*2]+ "\t"+s[prelength+1+i*2]+ "\t" + s[s.length-1]);
		}
		writer.close();
	}
	
	public static void saveSeat(String [] s) throws IOException {
		// id,userID,movie.id, sessionID
		int prelength = 4;
		int length = (s.length-prelength)/2;
		int movieID = Integer.parseInt(s[2]);
		int sessionID = Integer.parseInt(s[3]);
		Session session = Cinema.getMovieByID(movieID).getSessionByID(sessionID);
		int [] seatSize = session.getSeatSize();
		ArrayList<int[]> seatlist = new ArrayList<>();
		//System.out.println(length);
		for(int i=0; i<length; i++)
			seatlist.add(new int[] { Integer.parseInt(s[prelength +i*2]), Integer.parseInt(s[prelength+1+i*2])});   
		
		String ll = null;
		for(int round=0; round<seatlist.size(); round++) {
			RandomAccessFile raf = new RandomAccessFile(new File(seatpath), "rw");
			raf.seek(0);
			int aimrow = seatlist.get(round)[0];
			int aimline = seatlist.get(round)[1];
			//System.out.println(aimrow);
			//System.out.println(aimline);
			int flag=0;
			while(flag==0&&(ll = raf.readLine()) != null) {
				ll = ll.trim();
				String [] temlist = ll.split("\t");
				if(Integer.parseInt(temlist[0].trim())!=movieID || Integer.parseInt(temlist[1].trim())!=sessionID ) {
					int skip = Integer.parseInt(temlist[3]);
					while(skip-->0)
						raf.readLine();
				}
				else {
					flag=1;
					int skip = aimrow;
					while((--skip)>0)
						raf.readLine();
					raf.seek(raf.getFilePointer()+aimline-1);
					raf.writeByte(1);
					break;
				}
			}
			if(flag==0) {
				raf.seek(raf.length());
				raf.writeUTF(String.format("%d\t%d\t%d\t%d\n",movieID,sessionID,seatSize[0],seatSize[1]));
				boolean [][] seatMap = session.getBook();
				for(int i=0; i<seatSize[1]; i++) {
					for(int j=0; j<seatSize[0]; j ++) {
						raf.writeByte(seatMap[j][i]==false?0:1);
					}
					raf.writeUTF("\n");
				}
			}
			raf.close();
		}
		
	}
	
	public static void readSeat() throws IOException {
		RandomAccessFile raf = new RandomAccessFile(new File(seatpath), "r");
		String ll = null;
		while ((ll = raf.readLine()) != null) {
			String [] s = (ll.split("\t"));
			int movieID = Integer.parseInt(s[0].trim());
			int sessionID = Integer.parseInt(s[1].toString());
			Session session = Cinema.getMovieByID(movieID).getSessionByID(sessionID);
			int [] seatSize = session.getSeatSize();
			boolean [][]map = new boolean[seatSize[0]][seatSize[1]];
			for(int i=0; i<seatSize[1]; i++) {
				for(int j=0; j<seatSize[0]; j ++) {
					map[j][i] = (int)(raf.read()) == 1;
				}
				raf.readUTF();
			}
			session.setSeatMap(map);
		}
		raf.close();
	}
	
	public static void readMovie() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(moviepath), encoding));
		String ll = null;
		while ((ll = br.readLine()) != null)
			Cinema.createMovie(ll.split("\t"));
		br.close();
	}
	public static void readUser() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(userpath), encoding));
		String ll = null;
		while ((ll = br.readLine()) != null)
			Cinema.createUser(ll.split("\t"));
		br.close();
	}
	public static void readSession() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(sessionpath), encoding)); 
		String ll = null;
		while ((ll = br.readLine()) != null) {
			String[] line = ll.split("\t");
			int movieID = Integer.parseInt(line[0]);
			Movie movie = Cinema.getMovieByID(movieID);
			movie.createSession(Integer.parseInt(line[1]), line[2], line[3], Integer.parseInt(line[4].replaceAll("号厅", "")));
		}
		br.close();
	}
	public static void initData()  {
		
		try {
			readUser();
			readMovie();
			readSession();
			readSeat();
		} catch (IOException e) {
		}
	}
	
	public static void main(String [] args) throws IOException {
		RandomAccessFile raf = new RandomAccessFile(new File("a.txt"), "rw");
		raf.readLine();
		raf.seek(raf.getFilePointer()+4*3);
		raf.writeInt(9);
	}
}
