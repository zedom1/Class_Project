package Support;

import Support.Interface.DatabaseInterface;
import System.Basic.Collection;
import System.Basic.Event;
import System.Basic.Record;
import System.Basic.Update;
import System.Human.Human;

public class MySQL implements DatabaseInterface {

	@Override
	public int getUserlistLength() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Human getUser(String code) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void saveUser(int userid, String code) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public int getFileLength() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getRecordLength() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getFolderLength() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String getUpdateByID(int id) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getCollections(int userID) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getUserUpdateList(int userID) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getTopList(int userID) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getEventList(int userID) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String[] getUserList() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String[] getAdministorList() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getRecord(int id) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String[] getRecordList() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void addUpdate(Update update) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addEvent(Event event) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addCollection(Collection collection) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addTopList(Update update) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addRecord(Record record) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void modifyUpdate(Update update, String attribute, String content) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void modifyEvent(Event event, String attribute, String content) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void modifyCollection(Collection collection, String attribute, String content) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void removeUpdate(int id) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void removeEvent(int id) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void removeCollection(int userID, int id) {
		// TODO Auto-generated method stub
		
	}
	
}
