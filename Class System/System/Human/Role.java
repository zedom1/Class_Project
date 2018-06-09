package System.Human;

import java.util.ArrayList;

public abstract class Role {
	
	public abstract void modifyUpdate(int id , String attribute, Object object,ArrayList<Integer> selfUpdate, int userID);
	
	public abstract void removeUpdate(int id,ArrayList<Integer> selfUpdate, int userID);
	
	
	
}
