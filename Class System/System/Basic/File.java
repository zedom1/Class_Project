package System.Basic;

import java.util.Date;

import System.ClassSystem;

public class File {
	
	private int id;
	private int userID;
	private String title;
	private String link;
	private String icon;
	private String content;
	private Date date;
	
	public File() {
		id = ClassSystem.getFileLength();
		date = new Date();
	}
	
	public File(int userID, String title, String link, String icon, String content) {
		this();
		this.userID = userID;
		this.title = title;
		this.link = link;
		this.icon = icon;
		this.content = content;
	}

	public int getUserID() {
		return userID;
	}

	public void setUserID(int userID) {
		this.userID = userID;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getLink() {
		return link;
	}

	public void setLink(String link) {
		this.link = link;
	}

	public String getIcon() {
		return icon;
	}

	public void setIcon(String icon) {
		this.icon = icon;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public Date getDate() {
		return date;
	}

	public int getId() {
		return id;
	}
	
	
}
