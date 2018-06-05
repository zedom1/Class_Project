package banking.domain;

public class OverdraftException extends Exception {
	
	private double deficit;
	public OverdraftException(String message , double deficit) {
		super(message+deficit);
		this.deficit = deficit;
	}
	public double getDeficit() {
		return deficit;
	}
	
}
