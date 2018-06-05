package info;

import java.util.ArrayList;

public class Movie {
	public int id;
	private MovieDescription desc;
	public ArrayList<Session> session = new ArrayList<>();
	
	public String getDesc() {
		String sentence = String.format("Movie Name : %s \n Director: %s \n Price : %d元 \n Time : %d分钟 \n Profile: %s \n", desc.name,desc.director,(int)desc.price,desc.time, desc.profile);
		return sentence;
	}
	public String getDescPure() {
		String sentence = String.format("%s\n%s\n%d\n%d\n%s", desc.name,desc.director,(int)desc.price,desc.time, desc.profile);
		return sentence;
	}
	public Movie(int tid, Session[] ss, MovieDescription dd) {
		this(tid);
		desc = dd;
		for(Session tem : ss)
			session.add(tem);
	}
	public Movie(int tid) {
		id = tid;
	}
	public void createSession(int i, String d , String t, int n) {
		Session sess = new Session(i,d,t,n);
		session.add(sess);
	}
	public void createDesc(String n, String d , String[] act , int p , int t, String tt, String pro, String pos) {
		desc = new MovieDescription(n,d,act,p,t,tt,pro,pos);
	}
	public int getPrice() {
		return desc.price;
	}
	public String getName() {
		return desc.name;
	}
	public Session getSessionByID(int id) {
		for(int i=0 ;i<session.size(); i++) {
			if(session.get(i).id==id)
				return session.get(i);
		}
		return null;
	}
}
