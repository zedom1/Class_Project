package info;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

import support.DataInterface;
import support.Search;

public class Cinema {
	
	static public ArrayList<User> userlist = new ArrayList<>();
	static public ArrayList<Movie> movielist = new ArrayList<>();
	static public Book book = new Book();
	
	public static Movie getMovieByID(int id) {
		for(int i=0 ;i<movielist.size(); i++) {
			if(movielist.get(i).id==id)
				return movielist.get(i);
		}
		return null;
	}
	
	public static String getNameByID(int id) {
		for(int i=0 ;i<movielist.size(); i++) {
			if(movielist.get(i).id==id)
				return movielist.get(i).getName();
		}
		return null;
	}
	
	public static Movie createMovie(String[]line) {
		int id = Integer.parseInt(line[0]);
		Movie movie = new Movie(id);
		movie.createDesc(line[1], line[2], line[3].split(" "), Integer.parseInt(line[4].replaceAll("元","")), Integer.parseInt(line[5].replace("分钟","")), line[6], line[7], line[8]);
		movielist.add(movie);
		return movie;
	}
	
	public static User createUser(String [] line) {
		User user = new User( Integer.parseInt(line[0]), line[1], line[2], line[3], line[4].equals("0"), line[5], line[6], line[7]);
		userlist.add(user);
		return user;
	}
	
	public static BookItem makeNewItem(int u, int m , int s ,  int p) {
		BookItem b = new BookItem(u,m,s,p);
		return b;
	}
	
	public static void addNewItem(BookItem b) throws IOException {
		book.makeNewBook(b);
	}
	
	public static int[] search(String s) {
		HashMap hmap = new HashMap();
		double[] a = new double[movielist.size()];
		for(int i=0; i<movielist.size(); i++) {
			String[] slist = movielist.get(i).getDescPure().split("\n");
			double score = 0;
			for(int j=0; j<slist.length;j++) {
				score = Math.max(j==0?score*3:score, Search.getScore(s, slist[j]))+Math.random()/100000;
			}
			a[i]=score;
			hmap.put(score, i);
		}
		Arrays.sort(a);
		int[] result = new int[movielist.size()];
		for(int i=movielist.size()-1; i>=0; i--)
			result[movielist.size()-1-i]=(int) hmap.get(a[i]);
		return result;
	}
	
	public static void main(String [] args) throws IOException {
		Cinema cinema = new Cinema();
		DataInterface.initData();
	}
}
