package System;

import java.util.ArrayList;
import java.util.Date;

import System.Basic.File;

public class Folder {
	
	private int id;
	private static ArrayList<File> files;
	private String description;
	private Date date;
	
	public Folder() {
		date = new Date();
		files = new ArrayList<>();
		description = "";
		id = ClassSystem.getFolderLength();
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
}
