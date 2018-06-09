package System;

import java.util.ArrayList;
import java.util.Date;

import System.Basic.File;

public class Folder {
	
	private int id;
	private static ArrayList<File> files;
	private String name;
	private String description;
	private Date date;
	
	public Folder() {
		date = new Date();
		files = new ArrayList<>();
		description = "";
		id = ClassSystem.getFolderLength();
	}
	
	public Folder(String name, String description) {
		this();
		this.name = name;
		this.description = description;
	}

	public static void addFile(File file) {
		files.add(file);
	}
	
	public static void removeFile(File file) {
		files.remove(file);
	}
	
	public static void removeFile(int id) {
		for(int i=0; i<files.size(); i++) {
			if(files.get(i).getId()==id)
				files.remove(i);
		}
	}
	
	public static File getFileByID(int id) {
		for(int i=0; i<files.size(); i++) {
			if(files.get(i).getId()==id)
				return files.get(i);
		}
		return null;
	}
	
	public static File getFileByIndex(int index) {
		return files.get(index);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public int getId() {
		return id;
	}

	public Date getDate() {
		return date;
	}
}
