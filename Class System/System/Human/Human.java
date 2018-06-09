package System.Human;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Date;

import System.Activity;
import System.Calendar;
import System.ClassSystem;
import System.Recorder;
import System.Basic.Collection;
import System.Basic.Event;
import System.Basic.Update;

public class Human {

	protected int id;
	protected String nickname;
	protected String loginname;
	protected String password;
	protected String title;
	protected int classID;
	protected int age;
	protected boolean gender;
	protected Date date;
	protected Date birthday;
	protected Calendar calendar;
	protected Role role;
	
	// 维护在该用户界面置顶的动态的ID
	protected ArrayList<Integer> topUpdate = new ArrayList<>(); 
	// 维护自己发布的动态的ID
	protected ArrayList<Integer> selfUpdate = new ArrayList<>();
	// 维护收藏夹
	protected ArrayList<Collection> collections = new ArrayList<>(); 
	
	public Human(String nickname, String loginname, String password, int classID, int age, boolean gender,
			String title,Date birthday , Role role) {
		this();
		this.nickname = nickname;
		this.loginname = loginname;
		this.password = password;
		this.classID = classID;
		this.age = age;
		this.gender = gender;
		this.title = title;
		this.birthday = birthday;
		this.role = role;
	}

	public Human(String nick, String login, String pass, int clas) {
		this();
		nickname = nick;
		loginname = login;
		password = pass;
		classID = clas;
	}
	
	public Human() {
		id = ClassSystem.getUserLength();
		date = new Date();
	}
	
	/////////////////////////
		
	public Role getRole() {
		return role;
	}

	public void setRole(Role role) {
		this.role = role;
	}

	public Calendar getCalendar() {
		return calendar;
	}

	// update:
	public void addUpdate( String context, String location, Date start, Date end) {
		Update update = new Update(id, context, location,start,end);
		Activity.addUpdate(update);
		Recorder.addRecord(this.id, "add Update", ""+id+" "+update.getId());
	}
	
	public void modifyUpdate(int id , String attribute, Object object) {
		role.modifyUpdate(id, attribute, object, selfUpdate, this.id);
	}
	
	public void removeUpdate(int id) {
		role.removeUpdate(id, selfUpdate, this.id);
	}
	
	/////////////////////////
	// collection:
	public Collection addCollection(int id) {
		Collection collection = new Collection(collections.size(),id);
		collections.add(collection);
		Recorder.addRecord(this.id, "add Collection", ""+id+" "+collection.getId());
		return collection;
	}
	public void addCollection(int id, String comment) {
		Collection collection = addCollection(id);
		Recorder.addRecord(this.id, "add Collection", ""+id+" "+collection.getId());
		collection.setComment(comment);
	}
	public void modiftyCollection(int id, String attribute, Object object) {
		Collection collection = getCollectionByID(id);
		switch(attribute) {
			case "comment": collection.setComment((String)object); break;
		}
		Recorder.addRecord(this.id, "modify Collection", ""+id+" "+collection.getId()+attribute+object.toString());
	}
	public void removeCollection(int id) {
		Collection collection = getCollectionByID(id);
		collections.remove(collection);
		Recorder.addRecord(this.id, "remove Collection", ""+id+" "+collection.getId());
	}
	public Collection getCollectionByID(int id) {
		for(Collection c : collections)
			if (c.getId()==id)
				return c;
		return null;
	}
	public ArrayList<Collection> getCollections() {
		return collections;
	}
	public int getCollectionIndexByID(int id) {
		for(int i=0; i<collections.size(); i++)
			if (collections.get(i).getId()==id)
				return i;
		return -1;
	}

	public void addTopUpdate(int id) {
		topUpdate.add(id);
	}
	/////////////////////////
	
	// event:
	public void addEvent( String context, String location, Date start, Date end, Color color) {
		Event event = new Event(id, context, location,start,end);
		event.setColor(color);
		Calendar.addEvent(event);
		Recorder.addRecord(this.id, "add Event", ""+id+" "+event.getId());
	}
	public void addEvent(Update update) {
		Event event = new Event(update);
		Calendar.addEvent(event);
		Recorder.addRecord(this.id, "add Event", ""+id+" "+event.getId());
	}
	public void modifyEvent(int id , String attribute, Object object) {
		if(!Calendar.contains(id)) 
			return;
		Event event = Calendar.getEventByID(id);
		switch(attribute) {
			case "startDate": event.setStartDate((Date)object); break;
			case "endDate": event.setEndDate((Date)object); break;
			case "content": event.setContent((String)object); break;
			case "color": event.setColor((Color)object); break;
		}
		Recorder.addRecord(this.id, "modify Event", ""+id+" "+event.getId()+attribute+object);
	}
	public void removeEvent(int id) {
		Calendar.removeEvent(id);
		Recorder.addRecord(this.id, "remove Event", ""+id+" "+id);
	}
	
	
	
	/////////////////////////
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
		Recorder.addRecord(this.id, "set nickname", ""+nickname);
	}
	
	public int getClassID() {
		return classID;
	}
	
	public void setClassID(int classID) {
		this.classID = classID;
		Recorder.addRecord(this.id, "set class", ""+classID);
	}
	
	public int getAge() {
		return age;
	}
	
	public void setAge(int age) {
		this.age = age;
		Recorder.addRecord(this.id, "set age", ""+age);
	}
	
	public boolean getGender() {
		return gender;
	}
	
	public void setGender(boolean gender) {
		this.gender = gender;
		Recorder.addRecord(this.id, "set gender", ""+gender);
	}
	
	public String getTitle() {
		return title;
	}
	
	public void setTitle(String title) {
		this.title = title;
		Recorder.addRecord(this.id, "set title", ""+title);
	}
	
	public String getLoginname() {
		return loginname;
	}
	
	public void setLoginname(String loginname) {
		this.loginname = loginname;
		Recorder.addRecord(this.id, "set loginname", ""+loginname);
	}
	
	public String getPassword() {
		return password;
	}
	
	public void setPassword(String password) {
		this.password = password;
		Recorder.addRecord(this.id, "set password", ""+password);
	}
	
	public void setDate(Date date) {
		this.date = date;
		Recorder.addRecord(this.id, "set date", ""+date);
	}
	
	public Date getBirthday() {
		return birthday;
	}
	
	public void setBirthday(Date birthday) {
		this.birthday = birthday;
		Recorder.addRecord(this.id, "set birthday", ""+birthday);
	}
}
