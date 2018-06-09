package System.Human;

import java.util.ArrayList;
import java.util.Date;
import System.Activity;
import System.Recorder;
import System.Basic.Update;

public class Administor extends Role{

	public void modifyUpdate(int id , String attribute, Object object, ArrayList<Integer> selfUpdate, int userID) {
		Update update = Activity.getUpdateByID(id);
		switch(attribute) {
			case "startDate": update.setStartDate((Date)object); break;
			case "endDate": update.setEndDate((Date)object); break;
			case "content": update.setContent((String)object); break;
			case "location": update.setLocation((String)object); break;
		}
		Recorder.addRecord(userID, "modify Update", ""+id+" "+update.getId()+attribute+object);
	}
	
	public void removeUpdate(int id,ArrayList<Integer> selfUpdate, int userID) {
		Update update = Activity.getUpdateByID(id);
		Activity.removeUpdate(id);
		for(int i=0; i<selfUpdate.size(); i++)
			if(selfUpdate.get(i)==id)
				selfUpdate.remove(i);
		Recorder.addRecord(userID, "remove Update", ""+id+" "+update.getId());
	}
	
	
}
