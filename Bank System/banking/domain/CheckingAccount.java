package banking.domain;

import java.util.ArrayList;

public class CheckingAccount extends Account {

	private double overdraftProtection;
	
	public CheckingAccount(double balance) {
		super(balance,"");
	}
	public CheckingAccount(double balance , double protect) {
		super(balance,String.format("overdraftProtection:%f", protect));
		overdraftProtection = protect;
	}
	public CheckingAccount(double balance, double protect, int accountID) {
		super(balance,accountID,String.format("overdraftProtection:%f", protect));
		overdraftProtection = protect;
		this.accountID = accountID;
	}
	public void withdraw(double amt) throws OverdraftException{
		if(overdraftProtection == 0) {
			throw new OverdraftException("No overdraft protection  Deficit : ",amt);
		}
		if(amt >= overdraftProtection+balance) {
			throw new OverdraftException("Insufficient funds for overdraft protection  Deficit : ",amt - overdraftProtection+balance);
		}
		if(balance >= amt) {
			balance-=amt;
		}
		else if(overdraftProtection+balance-amt>=0) {
			overdraftProtection += balance-amt;
			balance =0;
		}
	}
	public double getOverdraftProtection(){
		return overdraftProtection;
	}
	public void setOverdraftProtection(double over) {
		overdraftProtection = over;
	}
	public int setData(ArrayList<Object>array, int m) {
		m = super.setData(array, m);
		overdraftProtection = (double)array.get(m++);
		return m;
	}
	public ArrayList<Object> writeData(ArrayList<Object> array){
		super.writeData(array);
		array.add(overdraftProtection);
		return array;
	}
}
