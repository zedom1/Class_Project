package System.Basic;

import java.awt.Color;
import java.util.Date;
import java.util.HashMap;

import System.Activity;

public class Event {

	private int id;
	private int userID;
	private Date date;
	private Date startDate;
	private Date EndDate;
	private String context;
	private String location;
	private Color color;
	
	public Event( int userID, String context, String location, Date start, Date end) {
		this();
		this.userID = userID;
		this.context = context;
		this.location = location;
		this.startDate = start;
		this.EndDate = end;
	}
	
	public Event() {
		id = Activity.getUpdateLength();
		date = new Date();
	}

	public HashMap<String, Object> getDesc() {
		HashMap<String, Object> map = new HashMap<>();
		map.put("userID", userID );
		map.put("date", date );
		map.put("context", context );
		map.put("location", location );
		return map;
	}
	
	public int getUserID() {
		return userID;
	}
	public void setUserID(int userID) {
		this.userID = userID;
	}
	public String getContext() {
		return context;
	}
	public void setContext(String context) {
		this.context = context;
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
		return EndDate;
	}
	public void setEndDate(Date endDate) {
		EndDate = endDate;
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
