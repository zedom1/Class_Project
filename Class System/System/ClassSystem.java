package System;

import java.util.ArrayList;

import Support.Factory;
import Support.Interface.DatabaseInterface;
import Support.Interface.LoginInterface;
import Support.Interface.RegisterInterface;
import Support.Interface.UserBase;
import System.Basic.Record;
import System.Human.User;

public class ClassSystem {

	static private User currentUser;
	private static DatabaseInterface database;
	private static UserBase userinterface;
	private static Recorder recorder;

	
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
		currentUser = new User(nick,login,pass,clas);
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
