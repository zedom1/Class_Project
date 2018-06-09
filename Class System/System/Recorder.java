package System;

import java.util.ArrayList;

import System.Basic.Record;

public class Recorder {

	public static ArrayList<Record> records;
	
	public static void addRecord(Record record) {
		records.add(record);
	}
	
	public static void addRecord(int user, String title, String content) {
		records.add(new Record(user, title, content));
	}
	
}
