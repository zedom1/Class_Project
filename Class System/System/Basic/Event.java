package System.Basic;

import java.awt.Color;
import java.util.Date;
import java.util.HashMap;

import System.Activity;
import System.Calendar;

public class Event {

	private int id;
	private int userID;
	private Date date;
	private Date startDate;
	private Date endDate;
	private String content;
	private String location;
	private Color color;
	
	public Event(Update update) {
		this();
		this.userID = update.getUserID();
		this.startDate = update.getStartDate();
		this.endDate = update.getEndDate();
		this.content = update.getContent();
		this.location = update.getLocation();
	}
	
	public Event( int userID, String content, String location, Date start, Date end) {
		this();
		this.userID = userID;
		this.content = content;
		this.location = location;
		this.startDate = start;
		this.endDate = end;
	}
	
	public Event() {
		id = Calendar.getEventLength();
		date = new Date();
	}

	public HashMap<String, Object> getDesc() {
		HashMap<String, Object> map = new HashMap<>();
		map.put("userID", userID );
		map.put("date", date );
		map.put("startDate", startDate);
		map.put("endDate", endDate);
		map.put("color", color);
		map.put("content", content );
		map.put("location", location );
		return map;
	}
	
	public int getUserID() {
		return userID;
	}
	public void setUserID(int userID) {
		this.userID = userID;
	}
	public String getContent() {
		return content;
	}
	public void setContent(String content) {
		this.content = content;
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public Date getStartDate() {
		return startDate;
	}
	public void setStartDate(Date startDate) {
		this.startDate = startDate;
	}
	public Date getEndDate() {
		return endDate;
	}
	public void setEndDate(Date end) {
		endDate = end;
	}

	public int getId() {
		return id;
	}

	public Date getDate() {
		return date;
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
	}
	
}
