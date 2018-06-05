package info;

public class MovieDescription {
	public String name;
	public String director;
	public String[] actors;
	public int price;
	public int time;
	public String type;
	public String profile;
	public String post;
	
	public MovieDescription(String n, String d , String[] act , int p , int t, String tt, String pro, String pos) {
		name = n;
		director = d;
		actors = act;
		price = p;
		time = t;
		type = tt;
		profile = pro;
		post = pos;
	}
}