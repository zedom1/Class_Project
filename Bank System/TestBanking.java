/*
 * This class creates the program to test the banking classes.
 * It creates a set of customers, with a few accounts each,
 * and generates a report of current account balances.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

import banking.domain.*;
import banking.reports.CustomerReport;

public class TestBanking {

	public static void print(Customer[] cust) throws IOException {
		FileWriter fw = new FileWriter("output.txt",true);
		PrintWriter pw = new PrintWriter(fw);
		for(int i=0; i<cust.length ; i++) {
			pw.println("Find the customers "+cust[i].getFirstName()+" "+cust[i].getLastName());
			System.out.println("Find the customers "+cust[i].getFirstName()+" "+cust[i].getLastName());
			Customer customer = cust[i];
			String out = String.format("Customer: %s, %s",customer.getLastName(),customer.getFirstName());
			pw.println(out);
			System.out.println(out);
			for(int j=0; j<customer.getNumOfAccounts(); j++) {
				Account account = customer.getAccount(j);
				boolean account_type = account instanceof CheckingAccount;
				out = String.format("\t%s: current balance is %.2f",account_type?"Checking Account":"Saving Account",account.getBalance());
		    	pw.println(out);
				System.out.println(out);
			}
			pw.println("");
			System.out.println("");
		}
		pw.close();
	}
	public static void generateReport() throws IOException {
		Bank bank = Bank.getBank();
		CustomerReport report = new CustomerReport();
		report.generateReport();
		
		FileWriter fw = new FileWriter("output.txt",true);
		PrintWriter pw = new PrintWriter(fw);
		Scanner input = new Scanner (System.in);
		
		Customer [] cust=null;
		int len = 0;
		String comment = "You can use first name or last name or both names to search customers, you can also use number to search customers with balance or overdraft protection higher than that number.";
		pw.println(comment);
		System.out.println(comment);
		while(len==0) {
			int c =0;
			while(!(c<=4&&c>=1)) {
				pw.println("Search for : \n 1. enter first name \n 2. enter last name \n 3. enter both first name and last name\n 4. number search: ");
				System.out.println("Search for : \n 1. enter first name \n 2. enter last name \n 3. enter both first name and last name\n 4. number search: ");
				c = input.nextInt();
			}
			if(c!=4) {
				pw.println("Enter the name: ");
				System.out.println("Enter the name: ");
				String s1,s2;
				s1 = input.next();
				switch(c) {
				case 1: 
					cust = bank.searchCustomers(s1, c);
					break;
				case 2: 
					cust = bank.searchCustomers(s1,c);
					break;
				case 3: 
					s2 = input.next();
					cust = bank.searchCustomers(s1, s2);
					break;
				}
				len = cust.length;
				if(len==0) {
					pw.println("Didn't find the customer");
					System.out.println("Didn't find the customer");
				}
				else if(len!=1) {
					pw.println("Find multiply customers : ");
					System.out.println("Find multiply customers : ");
					break;
				}
			}
			else {
				pw.println("Input here:(don't support parentheses)\n example input: balance>=100.0\n  balance<=50&&balance>10\n:");
				System.out.println("Input here:(don't support parentheses)\n example input: balance>=100.0\n  balance<=50&&balance>10\n:");
				input.nextLine();
				String ss = input.nextLine();
				cust = bank.searchCustomers(ss);
				if(cust.length==0) {
					pw.println("Didn't find the customer");
					System.out.println("Didn't find the customer");
				}
				else {
					break;
				}
			}
		}
		input.close();
		print(cust);
		pw.close();
	}
	public static void main(String[] args) throws IOException {
		
		Bank bank = Bank.getBank();
	    File file = new File("input.txt");
	    Scanner in = new Scanner (file);
	    String s;
	    StringBuffer sb1 = new StringBuffer();
	    StringBuffer sb2 = new StringBuffer();
	    if(in.hasNextLine()) {
	    	s = in.nextLine();
	    	s = in.nextLine();
	    	while(!s.equals("transaction") && in.hasNextLine()) {
	    		sb1.append(s);
	    		s = in.nextLine();
	    	}
	    	if(in.hasNextLine()) {
	    		s = in.nextLine();
	    		sb2.append(s);
	    		while(in.hasNextLine()) {
	    			s = in.nextLine();
	    			sb2.append(s);
	    		}
	    	}
	    }
	    in.close();
	    
	// Analyze the first part of input
	    String []total = sb1.toString().split(";");
	    for(int i=0; i<total.length ; i++) {
	    	String []tem = total[i].split(",");
	    	String []name = tem[0].split(" ");
	    	Customer cuss = new Customer(name[0], name[1]);
	    	Transaction tran = new Transaction("Customer", cuss.getID(),true,"add",0,"");
	    	cuss.addTransaction(tran);
	    	bank.addTransaction(tran);
	    	for(int j=1 ;j<tem.length ; j++) {
	    		String [] t = tem[j].split(" ");
	        	double balance=0;
	        	switch(t[0]) {
	        	case "c":
	        		balance=0;
	        		double overdraftProtection=0;
	        		boolean flagc=false;
	        		CheckingAccount ca = null;
	        		if(1<t.length&&(t[1].equals("share"))) {
	        			ca = (CheckingAccount) bank.getCustomer(t[2], t[3]).getAccount(true);
	        			flagc = true;
	        		}
	        		if(1<t.length&&(!t[1].equals("share"))) {
	        			balance = Double.valueOf(t[1]);
	        		}
	        		if(2<t.length&&t[2].equals("o")) {
	        			overdraftProtection = Double.valueOf(t[3]);
	        		}
	        		if(!flagc)
	        			ca= new CheckingAccount(balance,overdraftProtection);
	        		Transaction actran = new Transaction("Checking account",ca.getID(),true,"add",ca.getBalance(),flagc==true?"Sharing account":""+" "+cuss.getFirstName()+" "+cuss.getLastName());
	        		ca.addTransaction(actran);
	        		cuss.setAccount(ca);
	        		cuss.addTransaction(actran);
	        		bank.addTransaction(actran);
	        		break;
	        	case "s":
	        		balance=0;
	        		double interesting=0;
	        		boolean flags=false;
	        		SavingAccount sa = null;
	        		if(1<t.length&&(t[1].equals("share"))) {
	        			sa = (SavingAccount) (bank.getCustomer(t[2], t[3]).getAccount(false));
	        			flags = true;
	        		}
	        		if(1<t.length&&(!t[1].equals("share"))) {
	        			balance = Double.valueOf(t[1]);
	        		}
	        		if(2<t.length&&t[2].equals("i")) {
	        			interesting = Double.valueOf(t[3]);
	        		}
	        		if(!flags)
	        			sa = new SavingAccount(balance ,interesting);
	        		Transaction satran = new Transaction("Saving account",sa.getID(),true,"add",sa.getBalance(),flags==true?"Sharing account":""+" "+cuss.getFirstName()+" "+cuss.getLastName());
	        		sa.addTransaction(satran);
	        		cuss.setAccount(sa);
	        		cuss.addTransaction(satran);
	        		bank.addTransaction(satran);
	        		break;
	        	}
	    	}
	    	bank.addCustomer(cuss);
	    }
	    
	 // Analyze the second part of input
	    String [] transaction = sb2.toString().split(";");
		for(int i=0; i<transaction.length ; i++) {
			String[] tem = transaction[i].split(",");
			String [] name= tem[0].split(" ");
			Customer cust = bank.getCustomer(name[0], name[1]);
			int j =1;
			boolean maxn = false;
			if(tem[1].equals("*")) {
				j=2;
				maxn = true;
			}
			Account ac = maxn==false?cust.getAccount(0):cust.getAccount(cust.getMax());
			boolean check = ac instanceof CheckingAccount;
			String out =String.format("\nRetrieving the customer %s %s with %s account",name[0],name[1],check?"Checking Account":"Saving Account");
			String out1 = "";
			if(check) {
				if(((CheckingAccount) ac).getOverdraftProtection()==0)
					out1 = " with no overdraft protection.";
				else
					out1 = " that has overdraft protection.";
			}
			System.out.println(out+out1);
			
			for( ; j<tem.length ; j++) {
				String [] tran = tem[j].split(" ");
				out = String.format("Checking Acct [%s %s] : ",cust.getLastName(),cust.getFirstName());
				System.out.println(out);
				//  account withdraw
				if(tran[0].equals("w")) {
					out = String.format("Withdraw %.2f:", Double.valueOf(tran[1]));
					System.out.println(out);
					Transaction withtran = null;
					try {
						ac.withdraw(Double.valueOf(tran[1]));
						withtran = new Transaction(ac.getClass().getSimpleName(), ac.getID() , true, "withdraw", Double.valueOf(tran[1]), "");
					} catch (OverdraftException e) {
						System.out.println(e);
						withtran = new Transaction(ac.getClass().getSimpleName(), ac.getID() , false, "withdraw", Double.valueOf(tran[1]), e.getMessage());
					}
					ac.addTransaction(withtran);
					cust.addTransaction(withtran);
					bank.addTransaction(withtran);
				}
				// account deposit
				else if(tran[0].equals("d")){
					Transaction detran = null;
					out = String.format("Deposit %.2f:", Double.valueOf(tran[1]));
					System.out.println(out);
					ac.deposit(Double.valueOf(tran[1]));
					detran = new Transaction(ac.getClass().getSimpleName(), ac.getID() , true, "deposit", Double.valueOf(tran[1]), "");
					ac.addTransaction(detran);
					cust.addTransaction(detran);
					bank.addTransaction(detran);
				}
			}
			out = String.format("Customer [%s %s] has a checking balance of %.2f", name[1], name[0],bank.getCustomer(name[0], name[1]).getAccount(0).getBalance());
			System.out.println(out);
		}
	    
	   if( args.length==0 || args[0]!="1") 
		   generateReport();
	    
		
	}
}
