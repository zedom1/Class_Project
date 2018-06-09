package System;

import java.util.ArrayList;
import java.util.Date;

import System.Basic.Update;

public class Activity {
	
	private static ArrayList<Update> updatelist = new ArrayList<>();
	private static ArrayList<Update> toplist = new ArrayList<>();
	
	public static void addUpdate(Update update) {
		updatelist.add(update);
	}
	
	public static Update addUpdate(int userID, String context, String location, Date start, Date end) {
		Update update = new Update(userID, context , location, start , end);
		return update;
	}
	
	public static void removeUpdate(int id) {
		for(int i=0; i<updatelist.size(); i++)
			if(updatelist.get(i).getId()==id)
				updatelist.remove(i);
	}
	
	// add toplist from updatelist by id or index
	public static void addToplistByID(int id) {
		for(Update up : updatelist)
			if(up.getId()==id)
				toplist.add(up);
	}
	public static void addToplistByIndex(int index) {
		if(index>=updatelist.size())
			return;
		toplist.add(updatelist.get(index));
	}
	
	public static int getUpdateLength() {
		return updatelist.size();
	}
	
	public static Update getUpdateByID(int id) {
		for(Update up:updatelist)
			if(up.getId()==id)
				return up;
		return null;
	}

	public static ArrayList<Update> getUpdatelist() {
		return updatelist;
	}
	
	
}
