package banking.domain;

import java.util.ArrayList;

public class Account implements Comparable<Account>{
	static public int nextAccountID=0;
	
	protected double balance;
	protected int accountID;
	protected ArrayList<Transaction> transaction = new ArrayList<>();
	
	public Account(double init_balance,String des) {
		balance = init_balance;
		boolean flag = false;
	   	while(!flag) {
	   		int i=0;
	   		for(; i<Bank.getBank().getNumOfCustomers(); i++) {
	   			Customer cust = Bank.getBank().getCustomer(i);
	   			int j=0;
		   		for(; j<cust.getNumOfAccounts(); j++)
		   			if(nextAccountID==cust.getAccount(j).getID()) {
		   				nextAccountID ++;
		   				break;
	   				}
		   		if(j<cust.getNumOfAccounts())
		   			break;
		   	}
	   		if(i==Bank.getBank().getNumOfCustomers())
	   			flag=true;
	   	}
		accountID = nextAccountID++;
	}
	public Account(double init_balance, int accountID,String des) {
		balance = init_balance;
		boolean flag = false;
	   	while(!flag) {
	   		int i=0;
	   		for(; i<Bank.getBank().getNumOfCustomers(); i++) {
	   			Customer cust = Bank.getBank().getCustomer(i);
	   			int j=0;
		   		for(; j<cust.getNumOfAccounts(); j++)
		   			if(accountID==cust.getAccount(j).getID()) {
		   				accountID++;
		   				break;
	   				}
		   		if(j<cust.getNumOfAccounts())
		   			break;
		   	}
	   		if(i==Bank.getBank().getNumOfCustomers())
	   			flag=true;
	   	}
		this.accountID = accountID;
	}
	public double getBalance() {
		return balance;
	}
	public void deposit(double amt) {
		balance += amt;
	}
	public void withdraw(double amt) throws OverdraftException {
		if(balance < amt) {
			throw new OverdraftException("Insufficient funds  Deficit : ",amt-balance);
		}
		balance -= amt;
	}
	public int getID() {
		return accountID;
	}
	@Override
	public int compareTo(Account o) {
		// TODO Auto-generated method stub
		return -(int) (balance-o.balance);
	}
	public void addTransaction(Transaction tran) {
		transaction.add(tran);
	}
	public Transaction getTransaction(int index) {
		return transaction.get(index);
	}
	public String getTransactionString() {
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<transaction.size(); i++) {
			sb.append(transaction.get(i).toString());
			sb.append('\n');
		}
		return "Transaction:\n"+sb.toString();
	}
	public boolean setID(int id){
		boolean flag = true;
		for(int i=0; i<Bank.getBank().getNumOfCustomers(); i++) {
   			Customer cust = Bank.getBank().getCustomer(i);
	   		for(int j=0; j<cust.getNumOfAccounts(); j++)
	   			if(id==cust.getAccount(j).getID()) {
	   				flag=false;
	   				break;
   				}
	   	}
   		if(flag==true) {
   			accountID = id;
   			return true;
   		}
   		else 
   			return false;
	}
	public void setBalance(double balance) {
		this.balance = balance;
	}
	public int getNumOfTransaction() {
		return transaction.size();
	}
	public int setData(ArrayList<Object>array, int m) {
		balance = (double)array.get(m++);
		accountID = (int)array.get(m++);
		return m;
	}
	public ArrayList<Object> writeData(ArrayList<Object> array){
		array.add(balance);
		array.add(accountID);
		return array;
	}
}
