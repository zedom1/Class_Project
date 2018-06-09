package Support.Interface;

import System.Human.Human;

public interface DatabaseInterface {
	
	public abstract int getUserlistLength();
	
	public abstract Human getUser(String code);
	
	public abstract void saveUser(int userid, String code);
	
	public abstract int getFileLength();
	
	public abstract int getRecordLength();
	
	public abstract int getFolderLength();
}
