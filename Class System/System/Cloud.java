package System;

import java.util.ArrayList;


public class Cloud {
	
	private static ArrayList<Folder> folders;
	
	public Cloud(){
	}
	
	public static void addFolder(String title , String description) {
		Folder folder = new Folder(title,description);
		folders.add(folder);
	}
	
	public static void removeFolder(int id) {
		for(int i=0; i<folders.size(); i++)
			if(folders.get(i).getId()==id)
				folders.remove(i);
	}
	
	public static Folder getFolderByID(int id) {
		for(int i=0; i<folders.size(); i++)
			if(folders.get(i).getId()==id)
				return folders.get(i);
		return null;
	}
	
	public static Folder getFolderByIndex(int index) {
		return folders.get(index);
	}
	
}
