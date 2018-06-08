package System;

import Support.MySQL;
import Support.Interface.DatabaseInterface;
import Support.Interface.LoginInterface;
import System.Human.User;

public class ClassSystem {

	static private User currentUser;
	private static DatabaseInterface database;
	
	ClassSystem(){
		database = new MySQL();
	}
	
	public static void login() {
		currentUser = LoginInterface.login();
	}
	
	public static int register() {
		User user = new User();
		//userlist.add(user);
		return user.getID();
	}
	
	public static int getUserLength() {
		return database.getUserlistLength();
	}
	
	public static void main(String[] args) {
		
	}

}
