package banking.domain;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Date;

import IO.StringIO;

public class Transaction {
	
	private String classname;
	private String operation;
	private String description;
	
	private boolean isOK;
	private int id;
	private long time;
	private double amount;
	
	static public int CLASS_SIZE = 20;
	static public int OPERATION_SIZE = 8;
	static public int DESCRIPTION_SIZE = 20;
	static public int TOTAL_SIZE = CLASS_SIZE + OPERATION_SIZE + DESCRIPTION_SIZE + Long.BYTES + Integer.BYTES*2 + Double.BYTES;
	
	public void writeData(RandomAccessFile raf) throws IOException {
		StringIO.writeFixedLengthString(classname, CLASS_SIZE, raf);
		StringIO.writeFixedLengthString(operation, OPERATION_SIZE, raf);
		StringIO.writeFixedLengthString(description, DESCRIPTION_SIZE, raf);
		raf.writeInt(isOK==true?1:0);
		raf.writeInt(id);
		raf.writeLong(time);
		raf.writeDouble(amount);
	}
	public static Transaction readData(RandomAccessFile raf) throws IOException {
		Transaction tran = new Transaction();
		tran.classname = StringIO.readFixedLengthString( CLASS_SIZE, raf).trim();
		tran.operation=StringIO.readFixedLengthString( OPERATION_SIZE, raf).trim();
		tran.description=StringIO.readFixedLengthString( DESCRIPTION_SIZE, raf).trim();
		tran.isOK = raf.readInt()==1?true:false;
		tran.id=raf.readInt();
		tran.time=raf.readLong();
		tran.amount=raf.readDouble();
		return tran;
	}
	public int setData(ArrayList<Object>array, int m) {
		classname = (String)array.get(m++);
		operation = (String)array.get(m++);
		description = (String)array.get(m++);
		isOK = ((int)array.get(m++))==1?true:false;
		id = (int)array.get(m++);
		time = (long)array.get(m++);
		amount = (double)array.get(m++);
		
		return m;
	}
	public ArrayList<Object> writeData(ArrayList<Object> array){
		array.add(classname);
		array.add(operation);
		array.add(description);
		array.add(isOK==true?1:0);
		array.add(id);
		array.add(time);
		array.add(amount);
		return array;
	}
	
	public Transaction() {
		time = System.currentTimeMillis();
	}
	public Transaction(String clas, int id , boolean isOK, String operation, double amount, String description) {
		this();
		this.classname = clas;
		this.id = id;
		this.isOK = isOK;
		this.operation = operation;
		this.amount = amount;
		this.description = description;
	}

	public void setDescrption(String s) {
		description = s;
	}
	public void setOp(String s , double amt , boolean is) {
		operation = s;
		amount = amt;
		isOK = is;
	}
	public void setClass(String classname, int id) {
		this.classname = classname;
		this.id = id;
	}
	
	public String toString() {
		return new Date(time)+" "+" type: "+classname+" id: "+id+" result: "+isOK+" operation: "+operation+" amount: "+amount+" descripition: "+description;
	}
	public int getID() {
		return id;
	}
	public String getType() {
		return classname;
	}
	public long getTime() {
		return time;
	}
	public boolean equals(Transaction tran) {
		return time==tran.time&&id==tran.id&&amount==tran.amount&&classname.equals(tran.classname)&&operation.equals(tran.operation)&&description.equals(tran.description)&&isOK==tran.isOK;
	}
}
