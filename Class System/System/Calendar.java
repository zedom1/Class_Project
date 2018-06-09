package System;

import java.util.ArrayList;
import java.util.Date;

import System.Basic.Event;

public class Calendar {
	
	private static ArrayList<Event> events = new ArrayList<>();
	private static int currentUser;
	
	public Calendar(int id) {
		currentUser = id;
	}
	
	public static int getEventLength() {
		return events.size();
	}
	public static boolean contains(int id) {
		for(Event event : events)
			if(event.getId()==id)
				return true;
		return false;
	}
	
	public static void addEvent(Event event) {
		events.add(event);
	}
	public static void addEvent( Date date, Date startDate, Date endDate, String context, String location) {
		events.add(new Event(currentUser, context, location, startDate, endDate));
	}
	public static void removeEvent(int id) {
		for(int i=0; i<events.size(); i++)
			if(events.get(i).getId()==id)
				events.remove(i);
	}
	public static Event getEventByID(int id) {
		for(Event up:events)
			if(up.getId()==id)
				return up;
		return null;
	}

	public static ArrayList<Event> getEventlist() {
		return events;
	}

	public static int getCurrentUser() {
		return currentUser;
	}

	public static void setCurrentUser(int currentUser) {
		Calendar.currentUser = currentUser;
	}
	
	
}
