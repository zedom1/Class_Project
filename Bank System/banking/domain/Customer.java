package banking.domain;

import java.util.ArrayList;

public class Customer implements Comparable<Customer>
{
	public static int nextCustomerID=0;
	private String firstName;
	private String lastName;
	private boolean sorted = false;
	private int customerID;
	private int maxAccount=0;
	public int numCA = 0;
	public int numSA = 0;
	ArrayList<Account> account = new ArrayList<>();
	protected ArrayList<Transaction> transaction = new ArrayList<>();
	
	static public int FIRSTNAME_SIZE = 10;
	static public int LASTNAME_SIZE = 10;
	
	public int setData(ArrayList<Object> array , int i) {
		firstName = (String)array.get(i++);
		lastName = (String)array.get(i++);
		sorted = ((int)array.get(i++))==1?true:false;
		customerID = (int)array.get(i++);
		numCA = (int)array.get(i++);
		numSA = (int)array.get(i++);
		return i;
	}
	public ArrayList<Object> writeData(ArrayList<Object> array){
		array.add(firstName);
		array.add(lastName);
		array.add(sorted==true?1:0);
		array.add(customerID);
		numCA =0;
		numSA = 0;
		for(int i=0; i<account.size(); i++)
			if(account.get(i).getClass().getSimpleName().equals("CheckingAccount"))
				numCA++;
			else
				numSA++;
		array.add(numCA);
		array.add(numSA);
		return array;
	}
	
	public Customer( String first,String last)
	{
		firstName = first;
	   	lastName = last;
	   	boolean flag = false;
	   	while(!flag) {
	   		int i=0;
	   		for(; i<Bank.getBank().getNumOfCustomers(); i++) {
		   		if(nextCustomerID == Bank.getBank().getCustomer(i).getID()) {
		   			nextCustomerID++;
		   			break;
		   		}
		   	}
	   		if(i==Bank.getBank().getNumOfCustomers())
	   			flag=true;
	   	}
	   	
	   	customerID = nextCustomerID++;
	}
	public Customer( String first,String last,int customerID)
	{
	   firstName = first;
	   lastName = last;
	   boolean flag = false;
	   while(!flag) {
	   		int i=0;
	   		for(; i<Bank.getBank().getNumOfCustomers(); i++) {
		   		if(customerID == Bank.getBank().getCustomer(i).getID()) {
		   			customerID++;
		   			break;
		   		}
		   	}
	   		if(i==Bank.getBank().getNumOfCustomers())
	   			flag=true;
	   	}
	   this.customerID = customerID;
	}
	public String getFirstName()
	{
		return firstName;
	}
	public String getLastName()
	{
		return lastName;
	}	
	public Account getAccount(int index)
	{
		return account.get(index);
	}
	public Account getAccount(boolean check) {
		for(int i=0; i<account.size() ; i++) {
			if(check==true ) {
				if(account.get(i) instanceof CheckingAccount)
					return account.get(i);
			}
			else {
				if(account.get(i) instanceof SavingAccount)
					return account.get(i);
			}
		}
		return null;
	}
	public void setFirstName(String s) {
		firstName = s;
	}
	public void setLastName(String s) {
		lastName =s;
	}
	public boolean setID(int id) {
		boolean flag = true;
   		for(int i=0; i<Bank.getBank().getNumOfCustomers(); i++) {
	   		if(id == Bank.getBank().getCustomer(i).getID()) {
	   			flag=false;
	   			break;
	   		}
	   	}
   		if(flag==true) {
   			customerID = id;
   			return true;
   		}
   		else 
   			return false;
	}
	public void setAccount( Account a)
	{
		account.add(a);
		sorted = false;
		if(a.getBalance()>getAccount(maxAccount).getBalance())
			maxAccount = getNumOfAccounts()-1;
	}
	public void deleteAccount( int index) {
		//String clas, int id , boolean isOK, String operation, double amount, String description
		Account acc = account.get(index);
		Transaction tran = new Transaction(acc.getClass().getSimpleName(),acc.getID(),true,"delete",acc.balance,"");
		transaction.add(tran);
		Bank.getBank().addTransaction(tran);
		account.remove(index);
	}
	public int getNumOfAccounts() {
		return account.size();
	}
	@Override
	public int compareTo(Customer customer) {
		// TODO Auto-generated method stub
		if(sorted == false) {
			account.sort(null);
			sorted = true;
		}
		if(customer.sorted==false) {
			customer.account.sort(null);
			customer.sorted = true;
		}
		int c = getLastName().compareTo(customer.getLastName());
		if(c!=0)
			return c;
		c = getFirstName().compareTo(customer.getFirstName());
		if(c!=0)
			return c;
		double sum1= 0,sum2=0;
		for(int i=0 ; i<account.size(); i++)
			sum1+=account.get(i).getBalance();
		for(int i=0 ; i<customer.account.size(); i++)
			sum2+=customer.account.get(i).getBalance();
		return ((int)(sum1-sum2));
	}
	public int getID() {
		return customerID;
	}
	public void addTransaction(Transaction tran) {
		transaction.add(tran);
	}
	public Transaction getTransaction(int index) {
		return transaction.get(index);
	}
	public int getMax() {
		return maxAccount;
	}
	public int getIndex(Account acc) {
		return account.indexOf(acc);
	}
	public Account getAccountByID(int id) {
		for(int i=0; i<account.size(); i++)
			if(account.get(i).getID()==id) {
				return account.get(i);
			}
		return null;
	}
	
};