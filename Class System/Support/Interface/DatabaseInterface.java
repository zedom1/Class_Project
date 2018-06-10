package Support.Interface;

import System.Basic.Collection;
import System.Basic.Event;
import System.Basic.Record;
import System.Basic.Update;
import System.Human.Human;

public interface DatabaseInterface {
	
	public abstract int getUserlistLength();
	
	public abstract Human getUser(String code);
	
	public abstract void saveUser(int userid, String code);
	
	public abstract int getFileLength();
	
	public abstract int getRecordLength();
	
	public abstract int getFolderLength();
	
	public abstract String getUpdateByID(int id);
	
	public abstract String getCollections(int userID);
	
	public abstract String getUserUpdateList(int userID);
	
	public abstract String getTopList(int userID);
	
	public abstract String getEventList(int userID);
	
	public abstract String getRecord(int id);
	
	public abstract String[] getRecordList();
	
	public abstract String[] getUserList();
	
	public abstract String[] getAdministorList();
	
	public abstract void addUpdate(Update update);
	
	public abstract void addEvent(Event event);
	
	public abstract void addCollection(Collection collection);
	
	public abstract void addTopList(Update update);
	
	public abstract void addRecord(Record record);
	
	public abstract void modifyUpdate(Update update, String attribute, String content);
	
	public abstract void modifyEvent(Event event, String attribute, String content);
	
	public abstract void modifyCollection(Collection collection, String attribute, String content);
	
	public abstract void removeUpdate(int id);
	
	public abstract void removeEvent(int id);
	
	public abstract void removeCollection(int userID, int id);
	
}
