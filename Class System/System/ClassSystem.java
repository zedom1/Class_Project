package System;

import Support.Interface.DatabaseInterface;
import Support.Interface.Factory;
import Support.Interface.LoginInterface;
import Support.Interface.RegisterInterface;
import Support.Interface.UserBase;
import System.Human.Human;

public class ClassSystem {

	private static Human currentUser;
	private static Recorder recorder;
	private static Cloud cloud;
	private static DatabaseInterface database;
	private static UserBase userinterface;
	
	
	public ClassSystem() throws InstantiationException, IllegalAccessException, ClassNotFoundException {
		initAdapter();
	}
	
	public void initAdapter() throws InstantiationException, IllegalAccessException, ClassNotFoundException{
		Factory factory = Factory.getFactory();
		database = factory.getDataBase();
		userinterface = factory.getUserBase();
	}
	
	public static void login() {
		String code = ((LoginInterface)userinterface).login();
		currentUser = database.getUser(code);
	}
	
	public static int register(String nick, String login, String pass, int clas) {
		String code = ((RegisterInterface)userinterface).register();
		currentUser = new Human(nick,login,pass,clas);
		int id = currentUser.getID();
		database.saveUser(id, code);
		return id;
	}
	
	public static void logout() {
		currentUser = null;
	}
	
	public static int getRecordLength() {
		return database.getRecordLength();
	}
	
	public static int getUserLength() {
		return database.getUserlistLength();
	}
	
	public static int getFileLength() {
		return database.getFileLength();
	}
	
	public static int getFolderLength() {
		return database.getFolderLength();
	}
	
	public static void main(String[] args) {
		
	}

}
