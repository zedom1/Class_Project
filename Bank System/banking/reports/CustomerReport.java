package banking.reports;

import java.io.FileNotFoundException;
import java.io.PrintWriter;

import banking.domain.*;

public class CustomerReport {

	public static void generateReport() throws FileNotFoundException {
		Bank bank = Bank.getBank();
		PrintWriter print = new PrintWriter("output.txt");
		String out = "\t\t\tCUSTOMERS REPORT\n\t\t\t=================\n";
		print.println(out);
    	System.out.println(out);
		bank.sortCustomers();
    	for(int i=0; i<bank.getNumOfCustomers() ; i++) {
	    	Customer customer = bank.getCustomer(i);
	    	out = String.format("ID: %d ; Customer: %s, %s",customer.getID(),customer.getLastName(),customer.getFirstName());
	    	print.println(out);
	    	System.out.println(out);
	    	for(int j=0; j<customer.getNumOfAccounts(); j++) {
	    		Account account = customer.getAccount(j);
	    		boolean account_type = account instanceof CheckingAccount;
	    		out = String.format("ID: %d ; %s: current balance is %.2f \n",account.getID(),account_type?"Checking Account":"Saving Account",account.getBalance());
	    		print.print(out);
	        	System.out.print(out);
	        	out = account.getTransactionString();
        		print.println(out);
	        	System.out.println(out);
	    	}
	    	System.out.println("");
	    }
		
	    print.close();
	}
}
