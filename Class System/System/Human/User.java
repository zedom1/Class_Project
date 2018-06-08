package System.Human;

import java.util.ArrayList;
import java.util.Date;

import System.ClassSystem;
import System.Basic.Collection;

public class User {
	
	protected int id;
	protected String nickname;
	protected String loginname;
	protected String password;
	protected int classID;
	protected int age;
	protected boolean gender;
	protected String title;
	protected Date date;
	
	protected ArrayList<Integer> topUpdate = new ArrayList<>(); 
	protected ArrayList<Collection> collections = new ArrayList<>(); 
	
	public User(String nickname, String loginname, String password, int classID, int age, boolean gender,
			String title) {
		this();
		this.nickname = nickname;
		this.loginname = loginname;
		this.password = password;
		this.classID = classID;
		this.age = age;
		this.gender = gender;
		this.title = title;
	}

	public User(String nick, String login, String pass, int clas) {
		this();
		nickname = nick;
		loginname = login;
		password = pass;
		classID = clas;
	}
	
	public User() {
		id = ClassSystem.getUserLength();
		date = new Date();
	}
	
	public void addTopUpdate(int id) {
		topUpdate.add(id);
	}
	
	public Collection addCollection(int id) {
		Collection collection = new Collection(collections.size(),id);
		collections.add(collection);
		return collection;
	}
	
	public void addCollection(int id, String comment) {
		Collection collection = addCollection(id);
		collection.setComment(comment);
	}
	
	
	
	
	
	
	public ArrayList<Collection> getCollections() {
		return collections;
	}

	public ArrayList<Integer> getTopUpdate() {
		return topUpdate;
	}

	public int getID() {
		return id;
	}

	public String getNickname() {
		return nickname;
	}

	public void setNickname(String nickname) {
		this.nickname = nickname;
	}

	public int getClassID() {
		return classID;
	}

	public void setClassID(int classID) {
		this.classID = classID;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public boolean getGender() {
		return gender;
	}

	public void setGender(boolean gender) {
		this.gender = gender;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getLoginname() {
		return loginname;
	}

	public void setLoginname(String loginname) {
		this.loginname = loginname;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}
	
	public void setDate(Date date) {
		this.date = date;
	}
}
