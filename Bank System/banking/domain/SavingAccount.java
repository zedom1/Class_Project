package banking.domain;

import java.util.ArrayList;

public class SavingAccount extends Account {
	
	private double interestRate;
	
	public SavingAccount(double balance, double interest_rate) {
		super(balance,String.format("interest rate :%f%%", interest_rate*100));
		this.interestRate = interest_rate*100;
		// TODO Auto-generated constructor stub
	}
	public SavingAccount(double balance, double rate, int accountID) {
		super(balance,accountID,String.format("interest rate :%f%%", rate*100));
		this.interestRate = rate*100;
	}
	public double getRate() {
		return interestRate;
	}
	public void setRate(double rate) {
		if(rate>0)
			interestRate=rate;
	}
	public int setData(ArrayList<Object>array, int m) {
		m = super.setData(array, m);
		interestRate = (double)array.get(m++);
		return m;
	}
	public ArrayList<Object> writeData(ArrayList<Object> array){
		super.writeData(array);
		array.add(interestRate);
		return array;
	}
}
