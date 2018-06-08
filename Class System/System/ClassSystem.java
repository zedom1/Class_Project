package System;

import Support.Factory;
import Support.Interface.DatabaseInterface;
import Support.Interface.LoginInterface;
import Support.Interface.RegisterInterface;
import Support.Interface.UserBase;
import System.Human.User;

public class ClassSystem {

	static private User currentUser;
	private static DatabaseInterface database;
	private static UserBase userinterface;
	
	public ClassSystem() throws InstantiationException, IllegalAccessException, ClassNotFoundException{
		database = Factory.getFactory().getDataBase();
		userinterface = Factory.getFactory().getUserBase();
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
	
	public static int getUserLength() {
		return database.getUserlistLength();
	}
	
	public static void main(String[] args) {
		
	}

}
