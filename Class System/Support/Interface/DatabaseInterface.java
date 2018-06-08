package Support.Interface;

import System.Human.User;

public interface DatabaseInterface {
	
	public abstract int getUserlistLength();
	
	public abstract User getUser(String code);
	
	public abstract void saveUser(int userid, String code);
	
}
