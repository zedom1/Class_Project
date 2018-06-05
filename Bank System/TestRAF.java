import java.io.EOFException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Scanner;

import IO.StringIO;
import banking.domain.*;
import banking.reports.*;

public class TestRAF {
	
	public static ArrayList<Object> readRAF(RandomAccessFile datFile, File schemaFile) throws IOException{
		Scanner sche = new Scanner(schemaFile);
		ArrayList<recordFormat> record = new ArrayList<>();
		String line;
		String[] tem;
		while(sche.hasNextLine()) {
			line = sche.nextLine();
			tem = line.split(" ");
			recordFormat temRecord = new recordFormat();
			temRecord.name = tem[0];
			temRecord.type = tem[1];
			if(tem[1].equals("String")) 
				temRecord.lengthInByte = Integer.valueOf(tem[2]);
			record.add(temRecord);
		}
		datFile.seek(0);
		ArrayList<Object> array = new ArrayList<>();
		try{
			while(true) {
				for(int i=0; i<record.size(); i++) {
					switch(record.get(i).type) {
					case "String":
						array.add(StringIO.readFixedLengthString(record.get(i).lengthInByte, datFile).trim());
						break;
					case "int":
						array.add(datFile.readInt());
						break;
					case "double":
						array.add(datFile.readDouble());
						break;
					case "long":
						array.add(datFile.readLong());
						break;
					}
				}
			}
		}
		catch(EOFException e) {
		}
		sche.close();
		return array;
	}
	public static void writeRAF(RandomAccessFile datFile, File schemaFile , ArrayList<Object> array) throws IOException{
		Scanner sche = new Scanner(schemaFile);
		ArrayList<recordFormat> record = new ArrayList<>();
		String line;
		String[] tem;
		while(sche.hasNextLine()) {
			line = sche.nextLine();
			tem = line.split(" ");
			recordFormat temRecord = new recordFormat();
			temRecord.name = tem[0];
			temRecord.type = tem[1];
			if(tem[1].equals("String")) 
				temRecord.lengthInByte = Integer.valueOf(tem[2]);
			record.add(temRecord);
		}
		datFile.seek(0);
		int i=0;
		while(i<array.size()) {
			for(int j=0; j<record.size(); j++) {
				switch(record.get(j).type) {
				case "String":
					StringIO.writeFixedLengthString((String)array.get(i++),record.get(j).lengthInByte, datFile);
					break;
				case "int":
					datFile.writeInt((int)array.get(i++));
					break;
				case "double":
					datFile.writeDouble((double)array.get(i++));
					break;
				case "long":
					datFile.writeLong((long)array.get(i++));
					break;
				}
			}
		}
		
		sche.close();
	}
	
	public static void recoveryCustomer(ArrayList<Object>array) {
		int i=0;
		while(i<array.size()) {
			Customer customer = new Customer("","");
			i = customer.setData(array,i);
			Customer tem = bank.getCustomerByID(customer.getID());
			if(tem!=null)
				customer = tem;
			bank.addCustomer(customer);
		}
	}
	public static void recoveryCA(ArrayList<Object>array) {
		int m=0;
		for(int i=0; i<bank.getNumOfCustomers()&&m<array.size(); i++) {
			Customer customer = bank.getCustomer(i);
			for(int j=0 ; j<customer.numCA&&m<array.size(); j++) {
				CheckingAccount ca = new CheckingAccount(0);
				m=ca.setData(array,m);
				Customer tem = Bank.getBank().getCustomerByAccountID(ca.getID());
				if(tem!=null) {
					ca = (CheckingAccount) tem.getAccountByID(ca.getID());
				}
				customer.setAccount(ca);
			}
		}
	}
	public static void recoverySA(ArrayList<Object>array) {
		int m=0;
		for(int i=0; i<bank.getNumOfCustomers()&&m<array.size(); i++) {
			Customer customer = bank.getCustomer(i);
			for(int j=0 ; j<customer.numSA&&m<array.size(); j++) {
				SavingAccount sa = new SavingAccount(0.0,0.0);
				m=sa.setData(array,m);
				Customer tem = Bank.getBank().getCustomerByAccountID(sa.getID());
				if(tem!=null) {
					sa = (SavingAccount) tem.getAccountByID(sa.getID());
				}
				customer.setAccount(sa);
			}
		}
	}
	public static void recoveryTran(ArrayList<Object>array) {
		int i=0;
		while(i<array.size()) {
			Transaction tran = new Transaction();
			i = tran.setData(array,i);
			if(bank.detectSameTran(tran))
				continue;
			bank.addTransaction(tran);
			Customer cust = null;
			if(tran.getType().equals("Customer")) {
				cust = bank.getCustomerByID(tran.getID());
				cust.addTransaction(tran);
			}
			else {
				cust = bank.getCustomerByAccountID(tran.getID());
				Account account = cust.getAccountByID(tran.getID());
				cust.addTransaction(tran);
				account.addTransaction(tran);
			}
		}
	}
	
	public static ArrayList<Object> convertCustomer(){
		ArrayList<Object> array = new ArrayList<>();
		for(int i=0; i<bank.getNumOfCustomers(); i++) {
			bank.getCustomer(i).writeData(array);
		}
		return array;
	}
	public static ArrayList<Object> convertCA(){
		ArrayList<Object> array = new ArrayList<>();
		for(int i=0; i<bank.getNumOfCustomers(); i++) {
			for(int j=0; j<bank.getCustomer(i).getNumOfAccounts(); j++) {
				Account ac =bank.getCustomer(i).getAccount(j);
				boolean ca = ac.getClass().getSimpleName().equals("CheckingAccount");
				if(ca) {
					ac.writeData(array);
				}
			}
		}
		return array;
	}
	public static ArrayList<Object> convertSA(){
		ArrayList<Object> array = new ArrayList<>();
		for(int i=0; i<bank.getNumOfCustomers(); i++) {
			for(int j=0; j<bank.getCustomer(i).getNumOfAccounts(); j++) {
				Account ac =bank.getCustomer(i).getAccount(j);
				boolean ca = ac.getClass().getSimpleName().equals("CheckingAccount");
				if(!ca) {
					ac.writeData(array);
				}
			}
		}
		return array;
	}
	public static ArrayList<Object> convertTran(){
		ArrayList<Object> array = new ArrayList<>();
		for(int i=0; i<bank.getNumOfCustomers(); i++) {
			for(int j=0; j<bank.getCustomer(i).getNumOfAccounts(); j++) {
				Account ac =bank.getCustomer(i).getAccount(j);
				boolean ca = ac.getClass().getSimpleName().equals("CheckingAccount");
				if(ca) {
					for(int k=0; k<ac.getNumOfTransaction(); k++)
						ac.getTransaction(k).writeData(array);
				}
			}
			for(int j=0; j<bank.getCustomer(i).getNumOfAccounts(); j++) {
				Account ac =bank.getCustomer(i).getAccount(j);
				boolean ca = ac.getClass().getSimpleName().equals("CheckingAccount");
				if(!ca) {
					for(int k=0; k<ac.getNumOfTransaction(); k++)
						ac.getTransaction(k).writeData(array);
				}
			}
		}
		return array;
	}
	
	private static Bank bank = Bank.getBank();
	private static String[] inpp = {"1"};
	
	public static void initData() throws IOException {
		if((new File("customer.dat")).exists()&&(new File("savingaccount.dat")).exists()&&(new File("checkingaccount.dat")).exists()&&(new File("transaction.dat")).exists())
			loadData();
		else
			TestBanking.main(inpp);
	}
	public static void saveData() throws IOException {
		writeRAF(new RandomAccessFile("customer.dat","rw"),new File("customerSchema.txt"),convertCustomer());
		writeRAF(new RandomAccessFile("checkingaccount.dat","rw"),new File("caSchema.txt"),convertCA());
		writeRAF(new RandomAccessFile("savingaccount.dat","rw"),new File("saSchema.txt"),convertSA());
		writeRAF(new RandomAccessFile("transaction.dat","rw"),new File("trSchema.txt"),convertTran());
	}
	public static void loadData() throws IOException {
		recoveryCustomer(readRAF(new RandomAccessFile("customer.dat","rw"),new File("customerSchema.txt")));
		recoveryCA(readRAF(new RandomAccessFile("checkingaccount.dat","rw"),new File("caSchema.txt")));
		recoverySA(readRAF(new RandomAccessFile("savingaccount.dat","rw"),new File("saSchema.txt")));
		recoveryTran(readRAF(new RandomAccessFile("transaction.dat","rw"),new File("trSchema.txt")));
	}
	public static void main(String[] args) throws FileNotFoundException, IOException {
		initData();
		CustomerReport.generateReport();
		saveData();
	}
	static class recordFormat{
		String name;
		String type;
		int lengthInByte;
	}
}
