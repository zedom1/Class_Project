package info;

public class User {
	public int id;
	public String count;
	private String password;
	public String name;
	public boolean gender;
	public String mail;
	public String tele;
	public String address;
	
	public User(int i, String c , String p, String n, boolean g, String m, String t, String a) {
		id = i;
		count = c;
		password = p;
		name = n;
		gender = g;
		mail = m;
		tele = t;
		address = a;
	}
}