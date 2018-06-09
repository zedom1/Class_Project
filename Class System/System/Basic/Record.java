package System.Basic;

import java.util.Date;

import System.ClassSystem;

public class Record {
	
	private Date date;
	private int id;
	private int userID;
	private String title;
	private String content;
	
	public Record() {
		date = new Date();
		id = ClassSystem.getRecordLength();
	}
	
	public Record(int userID, String title, String content) {
		this();
		this.userID = userID;
		this.title = title;
		this.content = content;
	}
	
	
	
}
