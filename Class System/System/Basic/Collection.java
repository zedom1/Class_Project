package System.Basic;

import java.util.Date;
import java.util.HashMap;

public class Collection {

	private int id;
	private int updateID;
	private Date date;
	private String comment;
	
	public Collection(int id, int updateID , String comment) {
		this();
		this.id = id;
		this.updateID = updateID;
		this.comment = comment;
	}
	
	public Collection() {
		date = new Date();
		comment = "";
	}
	
	public Collection(int id, int updateID) {
		this();
		this.id = id;
		this.updateID = updateID;
	}
	
	public HashMap<String, Object> getDesc() {
		HashMap<String, Object> map = new HashMap<>();
		map.put("updateID", updateID );
		map.put("date", date );
		map.put("comment", comment );
		map.put("id", id );
		return map;
	}
	
	public int getId() {
		return id;
	}

	public Date getDate() {
		return date;
	}

	public int getUpdateID() {
		return updateID;
	}

	public void setUpdateID(int updateID) {
		this.updateID = updateID;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
	
}
