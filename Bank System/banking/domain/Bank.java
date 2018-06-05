package banking.domain;

import java.util.ArrayList;

public class Bank
{
	static private Bank bankInstance;
	private ArrayList<Customer> customer = new ArrayList<>();
	private Bank()
	{}
	protected ArrayList<Transaction> transaction = new ArrayList<>();
	
	public int getNumOfTransaction() {
		return transaction.size();
	}
	public void addCustomer(String first, String last)
	{
		Customer cust = new Customer(first, last);
		customer.add(cust);
		for(int j=0; j<cust.getNumOfAccounts(); j++) {
			Account acc = cust.getAccount(j);
			for(int k=0 ; k<acc.getNumOfTransaction(); k++) {
				cust.addTransaction(acc.getTransaction(k));
				Bank.getBank().addTransaction(acc.getTransaction(k));
			}
		}
	}
	public void addCustomer(Customer cust) {
		customer.add(cust);
		for(int j=0; j<cust.getNumOfAccounts(); j++) {
			Account acc = cust.getAccount(j);
			for(int k=0 ; k<acc.getNumOfTransaction(); k++) {
				cust.addTransaction(acc.getTransaction(k));
				Bank.getBank().addTransaction(acc.getTransaction(k));
			}
		}
	}
	public void deleteCustomer(int index) {
		//String clas, int id , boolean isOK, String operation, double amount, String description
		transaction.add(new Transaction("Customer",customer.get(index).getID(),true,"delete",0,""));
		customer.remove(index);
	}
	public int getNumOfCustomers()
	{
		return customer.size();
	}
	public Customer getCustomer(int index)
	{
		return customer.get(index);
	}
	public Customer getCustomer(String firstName, String lastName) {
		for(int i=0 ; i<getNumOfCustomers(); i++) {
			if(getCustomer(i).getFirstName().equals(firstName)&&getCustomer(i).getLastName().equals(lastName))
				return getCustomer(i);
		}
		return null;
	}
	public static Bank getBank() {
		if(bankInstance == null)
			return bankInstance=new Bank();
		else
			return bankInstance;
	}
	public void sortCustomers() {
		customer.sort(null);
	}
	public Customer[] searchCustomers(String name, int type) {
		ArrayList<Customer> cust = new ArrayList<Customer>();
		for(int i=0; i<customer.size() ; i++) {
			if(type==0 && name.equals(customer.get(i).getFirstName()))
				cust.add(customer.get(i));
			if(type==1 && name.equals(customer.get(i).getLastName()) )
				cust.add(customer.get(i));
		}
		Customer [] cc = new Customer[cust.size()];
		return cust.toArray(cc);
	}
	public Customer[] searchCustomers(String firstName,String lastName) {
		ArrayList<Customer> cust = new ArrayList<Customer>();
		for(int i=0; i<customer.size() ; i++) {
			if(firstName.equals(customer.get(i).getFirstName()) &&lastName.equals(customer.get(i).getLastName()) )
				cust.add(customer.get(i));
		}
		Customer [] cc = new Customer[cust.size()];
		return cust.toArray(cc);
	}
	public Customer[] searchCustomers(String input) {
		ArrayList<Customer> cust = new ArrayList<Customer>();
		StringBuilder str = new StringBuilder();
		
		while(input.contains("&&")||input.contains("||")) {
			String[] ss=null;
			if((input.contains("&&")&&!input.contains("||"))||(input.indexOf("&&")<input.indexOf("||"))) {
				ss= input.split("&&");
				str.append(ss[0]);
				str.append("!");
				StringBuilder str1 = new StringBuilder();
				for(int i=1; i<ss.length;i++) {
					str1.append(ss[i]);
					str.append("!");
				}	
				input = str1.toString();
			}
			else {
				ss= input.split("||");
				str.append(ss[0]);
				str.append("!");
				StringBuilder str1 = new StringBuilder();
				for(int i=1; i<ss.length;i++) {
					str1.append(ss[i]);
				}
				input = str1.toString();
			}
		}
		str.append(input);
		boolean [] bol = new boolean[getNumOfCustomers()];
		for(int i=0; i<bol.length ; i++)
			bol[i]=true;
		String []s1 = str.toString().split("!");
		for(int i=0; i<s1.length; i++){
			if(s1[i].contains(">=")) {
				int ii=s1[i].indexOf(">=");
				String pre = s1[i].substring(0,ii).trim();
				double num = Double.valueOf(s1[i].substring(ii+2, s1[i].length()).trim());
				if(pre.equals("balance")) {
					for(int j=0; j<customer.size(); j++) {
						double nn =0;
						for(int k=0; k<customer.get(j).getNumOfAccounts();k++) {
							nn += customer.get(j).getAccount(k).getBalance();
						}
						if(nn<num)
							bol[j]=false;
					}
				}
			}
			else if(s1[i].contains(">")) {
				int ii=s1[i].indexOf(">");
				String pre = s1[i].substring(0,ii).trim();
				double num = Double.valueOf(s1[i].substring(ii+1, s1[i].length()).trim());
				if(pre.equals("balance")) {
					for(int j=0; j<customer.size(); j++) {
						double nn =0;
						for(int k=0; k<customer.get(j).getNumOfAccounts();k++) {
							nn += customer.get(j).getAccount(k).getBalance();
						}
						if(nn<=num)
							bol[j]=false;
					}
				}
			}
			else if(s1[i].contains("<=")) {
				int ii=s1[i].indexOf("<=");
				String pre = s1[i].substring(0,ii).trim();
				double num = Double.valueOf(s1[i].substring(ii+2, s1[i].length()).trim());
				if(pre.equals("balance")) {
					for(int j=0; j<customer.size(); j++) {
						double nn =0;
						for(int k=0; k<customer.get(j).getNumOfAccounts();k++) {
							nn += customer.get(j).getAccount(k).getBalance();
						}
						if(nn>num)
							bol[j]=false;
					}
				}
			}
			else if(s1[i].contains("<")) {
				int ii=s1[i].indexOf("<");
				String pre = s1[i].substring(0,ii).trim();
				double num = Double.valueOf(s1[i].substring(ii+1, s1[i].length()).trim());
				if(pre.equals("balance")) {
					for(int j=0; j<customer.size(); j++) {
						double nn =0;
						for(int k=0; k<customer.get(j).getNumOfAccounts();k++) {
							nn += customer.get(j).getAccount(k).getBalance();
						}
						if(nn>=num)
							bol[j]=false;
					}
				}
			}
		}
		for(int i=0; i<customer.size() ; i++) {
			if(bol[i])
				cust.add(customer.get(i));
		}
		Customer [] cc = new Customer[cust.size()];
		return cust.toArray(cc);
	}
	public void addTransaction(Transaction tran) {
		transaction.add(tran);
	}
	public Transaction getTransaction(int index) {
		return transaction.get(index);
	}
	public int getIndex(Customer cust) {
		return customer.indexOf(cust);
	}
	public Customer getCustomerByID(int id) {
		Customer cust = null;
		for(int i=0; i<customer.size(); i++)
			if(customer.get(i).getID()==id) {
				cust = customer.get(i);
				break;
			}
				
		return cust;
	}
	public Customer getCustomerByAccountID(int id) {
		for(int i=0; i<customer.size(); i++)
			for(int j=0; j<customer.get(i).getNumOfAccounts(); j++)
				if(customer.get(i).getAccount(j).getID()==id)
					return customer.get(i);
		return null;
	}
	public boolean detectSameTran(Transaction tran) {
		for(int i=0; i<transaction.size(); i++)
			if(tran.equals(transaction.get(i)))
				return true;
		return false;
	}
}