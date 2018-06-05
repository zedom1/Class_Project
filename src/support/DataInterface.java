package support;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

import info.BookItem;
import info.Cinema;
import info.Movie;

public class DataInterface {
	
	private static final String bookpath = "book.txt";
	private static final String moviepath = "movie.txt";
	private static final String sessionpath = "session.txt";
	private static final String userpath = "user.txt";
	private static final String encoding = "utf8";
	
	public static void saveNewBook(BookItem book) throws IOException {
		FileWriter writer = new FileWriter(bookpath, true);
		String[] s = book.getDescPure().split("\t");
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
	public static void readSessio() throws NumberFormatException, IOException {
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
	public static void initData() throws IOException {
		readUser();
		readMovie();
		readSessio();
	}
}
