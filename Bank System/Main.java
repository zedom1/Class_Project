
	
import java.io.IOException;

import banking.domain.*;
import banking.reports.CustomerReport;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ContentDisplay;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

public class Main extends Application {
	
	private static Bank bank = Bank.getBank();
	
	private static String[] customer_name;
	private static String[][] account_name;
	
	
	static Button add = new Button("Add");
	static Button edit = new Button("Edit");
	static Button delete_ac = new Button("Delete Account");
	static Button delete_co = new Button("Delete Customer");
	static Button sort = new Button("Sort");
	static Button leftac = new Button("<- account");
	static Button rightac = new Button("account ->");
	static Button leftco = new Button("<- customer");
	static Button rightco = new Button("customer ->");
	
	static TextField firstName_text = new TextField();
	static Label firstName_label = new Label("First Name",firstName_text);
	static TextField lastName_text = new TextField();
	static Label lastName_label = new Label("Last Name",lastName_text);
	static TextField customerID_text = new TextField();
	static Label customerID_label = new Label("Customer ID",customerID_text);
	static TextField accountID_text = new TextField();
	static Label accountID_label = new Label("Account ID",accountID_text);
	static TextField accountType_text = new TextField();
	static Label accountType_label = new Label("Account Type",accountType_text);
	static TextField balance_text = new TextField();
	static Label balance_label = new Label("Balance",balance_text);
	static TextField over_text = new TextField();
	static Label over_label = new Label("Overdraft Protection",over_text);
	static TextField rate_text = new TextField();
	static Label rate_label = new Label("Interest Rate",rate_text);
	
	static TextArea transaction = new TextArea("Transaction:");
	
	static TextField amount_text = new TextField();
	static Button deposit = new Button("deposit");
	static Button withdraw = new Button("withdraw");
	
	static Label hint = new Label(null);
	
	static ComboBox<String> search_combo = new ComboBox<>();
	static TextField search_text = new TextField();
	static Button search_btn = new Button("Search");
	
	static ListView<String> customer_list=null;
	static ListView<String> account_list=null;
	
	public static void displayData(int customerIndex, int accountIndex) {
		
		customerIndex = customerIndex>0?customerIndex:0;
		accountIndex = accountIndex >0?accountIndex:0;
		if(bank.getNumOfCustomers()<=customerIndex || bank.getCustomer(customerIndex).getNumOfAccounts()<=accountIndex) {
			displayNull();
			return;
		}
		Customer customer = bank.getCustomer(customerIndex);
		Account account = customer.getAccount(accountIndex);
		boolean ca = account.getClass().getSimpleName().equals("SavingAccount")?false:true;
		firstName_text.setText(customer.getFirstName());
		lastName_text .setText(customer.getLastName());
		customerID_text .setText(Integer.toString(customer.getID()));
		accountID_text.setText(Integer.toString(account.getID()));
		accountType_text.setText(ca?"Checking Account":"Saving Account");
		balance_text .setText(Double.toString(account.getBalance()));
		over_text.setText(ca?Double.toString(((CheckingAccount)account).getOverdraftProtection()):"None");
		rate_text.setText(ca?"None":Double.toString( (( (SavingAccount)account).getRate())));
		transaction.setText(account.getTransactionString());
	}
	public static void displayNull() {
		firstName_text.setText(null);
		lastName_text .setText(null);
		customerID_text .setText(null);
		accountID_text.setText(null);
		accountType_text.setText(null);
		balance_text.setText(null);
		over_text.setText(null);
		rate_text.setText(null);
		transaction.setText(null);
	}
	public static void search(String s , int mod) {
		//"First Name"     "Last Name"     "First Name and Last Name"    "Balance","Customer ID"     "Account ID" 
		Customer [] custarr = null;
		int custIndex = -1;
		int accountIndex = -1;
		switch(mod) {
		case 0:
		case 1: 
			custarr = bank.searchCustomers(s,mod); 
			if(custarr.length>0) {
				custIndex = bank.getIndex(custarr[0]);
				accountIndex=0;
			}
			break;
		case 2: 
			String [] ss = s.split(" ");
			if(ss.length!=2) {
				hint.setText("Didn't find");
				return;
			}
			custarr = bank.searchCustomers(ss[0],ss[1]);
			if(custarr!=null) {
				custIndex = bank.getIndex(custarr[0]);
				accountIndex=0;
			}
			break;
		case 3:
			custarr = bank.searchCustomers(s);
			if(custarr!=null) {
				custIndex = bank.getIndex(custarr[0]);
				accountIndex=0;
			}
			break;
		case 4:
			custarr = new Customer[1];
			custarr[0] = null;
			int custID = Integer.valueOf(s);
			for(int i=0; i<bank.getNumOfCustomers(); i++) {
				if(custID == bank.getCustomer(i).getID()) {
					custIndex = i;
					accountIndex = 0;
					break;
				}
			}
			break;
		case 5:
			custarr = new Customer[1];
			custarr[0] = null;
			int accID = Integer.valueOf(s);
			for(int i=0; i<bank.getNumOfCustomers(); i++) {
				for(int j=0; j<bank.getCustomer(i).getNumOfAccounts(); j++) {
					if(accID == bank.getCustomer(i).getAccount(j).getID()) {
						custIndex = i;
						accountIndex = j;
						break;
					}
				}
				if(custIndex!=-1)
					break;
			}
			break;
		}
		if(custIndex==-1) {
			hint.setText("Didn't find");
		}
		refresh(custIndex, accountIndex);
	}
	public static boolean check(int mod) {
		if(mod==0) {
			return bank.getNumOfCustomers()>0;
		}
		if(mod==1) {
			if(bank.getNumOfCustomers()>0) {
				int index = customer_list.getSelectionModel().getSelectedIndex();
				return bank.getCustomer(index).getNumOfAccounts()>0;
			}
			else
				return false;
		}
		return false;
	}
	
	public void start(Stage primaryStage) throws IOException {
		
		TestRAF.initData();
		HBox mainPane = new HBox();
		VBox context  = new VBox();
		getCustomerName();
		
		customer_list = new ListView<>(FXCollections.observableArrayList(customer_name));
		customer_list.setPrefSize(130, 450);
		customer_list.getSelectionModel().select(0);
		customer_list.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
		
		
		account_list = new ListView<>(FXCollections.observableArrayList(account_name[0]));
		account_list.setPrefSize(130, 450);
		account_list.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
		
		ScrollPane customerListPane = new ScrollPane(customer_list);
		ScrollPane accountListPane = new ScrollPane(account_list);
		
		FlowPane imagePane = new FlowPane(10,10);
		BorderPane pane = new BorderPane();
		HBox hbox = new HBox(1);
		
		hbox.getChildren().add(customerListPane);
		hbox.getChildren().add(accountListPane);
		
		pane.setLeft(hbox);
		pane.setCenter(imagePane);
		customer_list.setOnMouseClicked(
				e->{
					hint.setText(null);
					account_list.setItems(FXCollections.observableArrayList(account_name[customer_list.getSelectionModel().getSelectedIndex()]));
					account_list.getSelectionModel().select(0);
					displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
				}
			);
		account_list.setOnMouseClicked(
				e->{
					hint.setText(null);
					displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
				}
		);
		
// ===========    attribute  begin   ================= //
		GridPane attribute = new GridPane();
		attribute.setAlignment(Pos.TOP_CENTER);
		attribute.setPadding(new Insets(10,10,10,10));
		attribute.setHgap(5);
		attribute.setVgap(5);
		
		FlowPane changeFlow = new FlowPane();
		
		changeFlow.getChildren().add(amount_text);
		changeFlow.getChildren().add(deposit);
		changeFlow.getChildren().add(withdraw);
		
		
		firstName_label.setContentDisplay(ContentDisplay.RIGHT);
		lastName_label.setContentDisplay(ContentDisplay.RIGHT);
		customerID_label.setContentDisplay(ContentDisplay.RIGHT);
		accountID_label.setContentDisplay(ContentDisplay.RIGHT);
		accountType_label.setContentDisplay(ContentDisplay.RIGHT);
		balance_label.setContentDisplay(ContentDisplay.RIGHT);
		over_label.setContentDisplay(ContentDisplay.RIGHT);
		rate_label.setContentDisplay(ContentDisplay.RIGHT);
		
		transaction.setEditable(false);
		transaction.setPrefRowCount(5);
		transaction.setPrefColumnCount(45);
		ScrollPane scrollTransaction = new ScrollPane(transaction);
		
		attribute.add(firstName_label,0,0);
		attribute.add(lastName_label,1,0);
		attribute.add(customerID_label,0,1);
		attribute.add(accountID_label,1,1);
		attribute.add(accountType_label, 0,2);
		attribute.add(changeFlow,1, 2);
		attribute.add(balance_label,0,3);
		attribute.add(over_label,0,4);
		attribute.add(rate_label,1,4);
		
// ===========    attribute end     ================= //		
		
		
		
// ===========   search  begin     ================= //			
		
		FlowPane searchPane = new FlowPane();
		searchPane.setPadding(new Insets(10,10,10,10));
		searchPane.setHgap(30);
		searchPane.setAlignment(Pos.TOP_CENTER);
		
		
		search_combo.getItems().addAll("First Name","Last Name","First Name and Last Name","Balance","Customer ID","Account ID");
		search_combo.setValue("First Name");
		
		search_text.setPrefColumnCount(20);
		
		searchPane.getChildren().add(search_text);
		searchPane.getChildren().add(search_combo);
		searchPane.getChildren().add(search_btn);
		
		search_btn.setOnAction(e->{
			hint.setText(null);
			if(bank.getNumOfCustomers()==0) {
				hint.setText("No customer to search!");
				return;
			}
			int mod = search_combo.getSelectionModel().getSelectedIndex();
			String s = search_text.getText();
			if(s==null)
				return;
			search(s,mod);
		});
		
// ===========   search  end       ================= //	
		
// ===========   button  begin     ================= //			
		FlowPane buttonPane1 = new FlowPane();
		buttonPane1.setPadding(new Insets(10,10,10,10));
		buttonPane1.setHgap(15);
		buttonPane1.setVgap(15);
		buttonPane1.setAlignment(Pos.TOP_CENTER);
		FlowPane buttonPane2 = new FlowPane();
		buttonPane2.setPadding(new Insets(10,10,10,10));
		buttonPane2.setHgap(15);
		buttonPane2.setVgap(15);
		buttonPane2.setAlignment(Pos.TOP_CENTER);
		
		buttonPane1.getChildren().add(add);
		buttonPane1.getChildren().add(edit);
		buttonPane1.getChildren().add(delete_ac);
		buttonPane1.getChildren().add(delete_co);
		buttonPane1.getChildren().add(sort);
		
		buttonPane2.getChildren().add(leftac);
		buttonPane2.getChildren().add(rightac);
		buttonPane2.getChildren().add(leftco);
		buttonPane2.getChildren().add(rightco);
		
		delete_ac.setOnAction(e->{
			hint.setText(null);
			if(bank.getNumOfCustomers()>0) {
				int customerIndex = customer_list.getSelectionModel().getSelectedIndex();
				
				if(bank.getCustomer(customerIndex).getNumOfAccounts()>0) {
					int accountIndex = account_list.getSelectionModel().getSelectedIndex()>0?account_list.getSelectionModel().getSelectedIndex():0;
					bank.getCustomer(customerIndex).deleteAccount(accountIndex);
					getCustomerName();
					account_list.setItems(FXCollections.observableArrayList(account_name[customerIndex]));
					account_list.getSelectionModel().select(0);
					if(bank.getCustomer(customerIndex).getNumOfAccounts()>0)
						displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
					else
						displayNull();
				}
				else {
					hint.setText("No account!");
				}
			}
			else {
				hint.setText("No customer!");
			}
		});
		
		delete_co.setOnAction(e->{
			hint.setText(null);
			if(bank.getNumOfCustomers()>0) {
				int customerIndex = customer_list.getSelectionModel().getSelectedIndex();
				bank.deleteCustomer(customerIndex);
				if(bank.getNumOfCustomers()>0) {
					customerIndex = customerIndex%bank.getNumOfCustomers();
					getCustomerName();
					customer_list.setItems(FXCollections.observableArrayList(customer_name));
					customer_list.getSelectionModel().select(customerIndex);
					if(bank.getNumOfCustomers()>customerIndex && bank.getCustomer(customerIndex).getNumOfAccounts()>0) {
						account_list.setItems(FXCollections.observableArrayList(account_name[customerIndex]));
						account_list.getSelectionModel().select(0);
						if(bank.getCustomer(customerIndex).getNumOfAccounts()>0)
							displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
						else
							displayNull();
					}
				}
				else {
					customer_list.setItems(null);
					account_list.setItems(null);
					displayNull();
				}
					
			}
			else {
				hint.setText("No customer!");
			}
		});
		
		sort.setOnAction(e->{
			hint.setText(null);
			if(bank.getNumOfCustomers()>0) {
				bank.sortCustomers();
				refresh(-1,-1);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				hint.setText("No customer to sort!");
			}
		});
		
		leftac.setOnAction(e->{
			hint.setText(null);
			if(bank.getNumOfCustomers()==0) {
				hint.setText("No customer!");
				return;
			}
			int numac = bank.getCustomer(customer_list.getSelectionModel().getSelectedIndex()>0?customer_list.getSelectionModel().getSelectedIndex():0).getNumOfAccounts();
			if(numac>0) {
				account_list.getSelectionModel().select((account_list.getSelectionModel().getSelectedIndex()-1+numac)%numac);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				displayNull();
				hint.setText("No available account");;
			}
			
		});
		
		rightac.setOnAction(e->{
			hint.setText(null);
			if(bank.getNumOfCustomers()==0) {
				hint.setText("No customer!");
				return;
			}
			int numac = bank.getCustomer(customer_list.getSelectionModel().getSelectedIndex()>0?customer_list.getSelectionModel().getSelectedIndex():0).getNumOfAccounts();
			if(numac>0) {
				account_list.getSelectionModel().select((account_list.getSelectionModel().getSelectedIndex()+1)%numac);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				displayNull();
				hint.setText("No available account");;
			}
		});
		
		leftco.setOnAction(e->{
			hint.setText(null);
			int numcu = bank.getNumOfCustomers();
			if(numcu>0) {
				customer_list.getSelectionModel().select((customer_list.getSelectionModel().getSelectedIndex()-1+bank.getNumOfCustomers())%bank.getNumOfCustomers());
				account_list.setItems(FXCollections.observableArrayList(account_name[customer_list.getSelectionModel().getSelectedIndex()]));
				account_list.getSelectionModel().select(0);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				displayNull();
				hint.setText("No available customer");;
			}
			
		});
		rightco.setOnAction(e->{
			hint.setText(null);
			int numcu = bank.getNumOfCustomers();
			if(numcu>0) {
				customer_list.getSelectionModel().select((customer_list.getSelectionModel().getSelectedIndex()+1)%bank.getNumOfCustomers());
				account_list.setItems(FXCollections.observableArrayList(account_name[customer_list.getSelectionModel().getSelectedIndex()]));
				account_list.getSelectionModel().select(0);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				displayNull();
				hint.setText("No available customer!");;
			}
		});
		
		deposit.setOnAction(e->{
			hint.setText(null);
			if(check(1)) {
				Double amt = Double.valueOf(amount_text.getText());
				int cuIndex = customer_list.getSelectionModel().getSelectedIndex();
				int acIndex = account_list.getSelectionModel().getSelectedIndex();
				Customer cust = bank.getCustomer(cuIndex);
				Account ac = cust.getAccount(acIndex);
				ac.deposit(amt);
				Transaction detran = new Transaction(ac.getClass().getSimpleName(), ac.getID() , true, "deposit", amt, "");
				ac.addTransaction(detran);
				cust.addTransaction(detran);
				bank.addTransaction(detran);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				hint.setText("No available account!");
			}
		});
		withdraw.setOnAction(e->{
			hint.setText(null);
			if(check(1)) {
				Double amt = Double.valueOf(amount_text.getText());
				int cuIndex = customer_list.getSelectionModel().getSelectedIndex();
				int acIndex = account_list.getSelectionModel().getSelectedIndex();
				Customer cust = bank.getCustomer(cuIndex);
				Account ac = cust.getAccount(acIndex);
				Transaction withtran = null;
				try {
					ac.withdraw(amt);
					withtran = new Transaction(ac.getClass().getSimpleName(), ac.getID() , true, "withdraw", amt, "");
				} catch (OverdraftException ee) {
					hint.setText(ee.toString());
					withtran = new Transaction(ac.getClass().getSimpleName(), ac.getID() , false, "withdraw", amt, ee.getMessage());
				}
				ac.addTransaction(withtran);
				cust.addTransaction(withtran);
				bank.addTransaction(withtran);
				displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
			}
			else {
				hint.setText("No available account!");
			}
		});
		add.setOnAction(e->{
			addData();
			refresh(-1,-1);
		});
		edit.setOnAction(e->{
			if(check(1)) {
				editData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
				refresh(-1,-1);
			}
			else {
				hint.setText("No available account!");
			}
		});
		
// ===========   button  end       ================= //		
		
		StackPane labelPane = new StackPane(hint);
		hint.setFont(new Font(16));
		hint.setTextFill(Color.RED);
	
		context.getChildren().add(attribute);
		context.getChildren().add(scrollTransaction);
		context.getChildren().add(searchPane);
		context.getChildren().add(buttonPane1);
		context.getChildren().add(buttonPane2);
		context.getChildren().add(labelPane);
		
		Scene scene = new Scene(mainPane,1000,460);
		mainPane.getChildren().add(hbox);
		mainPane.getChildren().add(context);
		
		
		primaryStage.setTitle("Bank");
		primaryStage.setScene(scene);
		primaryStage.show();
		primaryStage.setOnCloseRequest(e->{
				try {
					TestRAF.saveData();
					CustomerReport.generateReport();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			
		});
	}
	
	public static void main(String[] args) {
		launch(args);
	}
	public static void getCustomerName() {
		customer_name = new String[bank.getNumOfCustomers()];
		for(int i=0; i<bank.getNumOfCustomers() ; i++) {
			StringBuilder sb = new StringBuilder();
			sb.append(bank.getCustomer(i).getFirstName());
			sb.append(" ");
			sb.append(bank.getCustomer(i).getLastName());
			customer_name[i]=sb.toString();
		}
		getAccountName();
	}
	public static void getAccountName() {
		account_name = new String[bank.getNumOfCustomers()][];
		for(int i=0; i<bank.getNumOfCustomers() ; i++) {
			account_name[i] = new String[bank.getCustomer(i).getNumOfAccounts()];
			for(int j=0; j<bank.getCustomer(i).getNumOfAccounts(); j++)
				account_name[i][j]=Integer.toString(bank.getCustomer(i).getAccount(j).getID());
		}
	}
	public static void editData(int coIndex, int acIndex) {
		if(firstName_text.getLength()==0 || lastName_text.getLength()==0|| customerID_text.getLength()==0|| accountID_text.getLength()==0|| accountType_text.getLength()==0|| balance_text.getLength()==0) {
			hint.setText("Empty Input");
			return;
		}
		if( !( accountType_text.getText().equals("Checking Account")||accountType_text.getText().equals("Saving Account") ) ) {
			hint.setText("Invalid account type!");
			return;
		}
		if(accountType_text.getText().equals("Saving Account")&&(!over_text.getText().equals("None"))) {
			hint.setText("Saving account doesn't have overdraft protection!");
			return;
		}
		if(accountType_text.getText().equals("Saving Account")&&rate_text.getLength()==0) {
			hint.setText("Empty interest rate");
			return;
		}
		Customer cust = bank.getCustomer(coIndex);
		Account account = cust.getAccount(acIndex);
		
		String accountType = account.getClass().getSimpleName().equals("CheckingAccount")?"Checking Account":"Saving Account";
		if(!accountType.equals(accountType_text.getText())) {
			hint.setText("Unmatched account type!");
			return;
		}
		
		int coID = Integer.valueOf(customerID_text.getText());
		int acID = Integer.valueOf(accountID_text.getText());
		double over = 0;
		if(accountType.equals("Checking Account"))
			over = Double.valueOf(over_text.getText());
		double rate = 0;
		if(accountType.equals("Saving Account"))
			rate = Double.valueOf(rate_text.getText());
		double balance = Double.valueOf(balance_text.getText());
		
		if(balance<0 || over<0) {
			hint.setText("Invalid balance or overdraft protection!");
			return;
		}
		
		
		if(cust.getID()!=coID)
			if(!cust.setID(coID)) {
				hint.setText("Customer ID exists!");
				return;
			}
		if(account.getID()!=acID)
			if(!account.setID(acID)) {
				hint.setText("Account ID exists!");
			}
		
		cust.setFirstName(firstName_text.getText());
		cust.setLastName(lastName_text.getText());
		if(accountType.equals("Checking Account"))
			((CheckingAccount)account).setOverdraftProtection(over);
		if(accountType.equals("Saving Account"))
			((SavingAccount)account).setRate(rate);
		double diff = balance - account.getBalance();
		Transaction tran = null;
		if(diff>0)
			tran = new Transaction(account.getClass().getSimpleName(), account.getID() , true, "deposit", diff, "");
		else if(diff<0)
			tran = new Transaction(account.getClass().getSimpleName(), account.getID() , true, "withdraw", diff, "");
		if(tran!=null) {
			account.addTransaction(tran);
			cust.addTransaction(tran);
			bank.addTransaction(tran);
		}
		
		account.setBalance(balance);
		
	}
	public static void refresh(int custIndex, int accountIndex) {
		getCustomerName();
		int cuIndex = custIndex==-1?customer_list.getSelectionModel().getSelectedIndex():custIndex;
		int acIndex = accountIndex==-1?account_list.getSelectionModel().getSelectedIndex():accountIndex;
		customer_list.setItems(FXCollections.observableArrayList(customer_name));
		customer_list.getSelectionModel().select(cuIndex);
		account_list.setItems(FXCollections.observableArrayList(account_name[customer_list.getSelectionModel().getSelectedIndex()]));
		account_list.getSelectionModel().select(acIndex);
		displayData(customer_list.getSelectionModel().getSelectedIndex(),account_list.getSelectionModel().getSelectedIndex());
	}
	public static void addData() {
		if(firstName_text.getLength()==0 || lastName_text.getLength()==0|| balance_text.getLength()==0 ||accountType_text.getLength()==0) {
			hint.setText("Empty Input");
			return;
		}
		if( !( accountType_text.getText().equals("Checking Account")||accountType_text.getText().equals("Saving Account") ) ) {
			hint.setText("Invalid account type!");
			return;
		}
		if(accountType_text.getText().equals("Saving Account")&&(!over_text.getText().equals("None"))) {
			hint.setText("Saving account doesn't have overdraft protection!");
			return;
		}
		
		Customer[] custarr = bank.searchCustomers(firstName_text.getText(), lastName_text.getText());
		Customer cust = null;
		if(custarr==null) {
			if(customerID_text.getLength()==0)
				cust = new Customer(firstName_text.getText(), lastName_text.getText());
			else
				cust = new Customer(firstName_text.getText(), lastName_text.getText(),Integer.valueOf(customerID_text.getText()));
			bank.addCustomer(cust);
		}
		else {
			if(customerID_text.getLength()==0) {
				cust = new Customer(firstName_text.getText(), lastName_text.getText());
				bank.addCustomer(cust);
			}
			else {
				int custID = Integer.valueOf(customerID_text.getText());
				int i=0;
				for(; i<custarr.length; i++) {
					if(custID == custarr[i].getID()) {
						cust = custarr[i];
						break;
					}
				}
				if(i==custarr.length) {
					cust = new Customer(firstName_text.getText(), lastName_text.getText(),custID);
					bank.addCustomer(cust);
				}
			}
		}
		Account account = null;
		
		boolean ca = accountType_text.getText().equals("Checking Account")?true:false;
		if(ca==true) {
			if(accountID_text.getLength()==0)
				account = new CheckingAccount(Double.valueOf(balance_text.getText()));
			else
				account = new CheckingAccount(Double.valueOf(balance_text.getText()),Integer.valueOf(accountID_text.getText()));
			if(over_text.getLength()==0 || over_text.getText().equals("None"))
				((CheckingAccount)account).setOverdraftProtection(0);
			else
				((CheckingAccount)account).setOverdraftProtection(Double.valueOf(over_text.getText()));
		}
		else {
			double rate = 0;
			rate = Double.valueOf(rate_text.getText());
			if(accountID_text.getLength()==0)
				account = new SavingAccount(Double.valueOf(balance_text.getText()),rate/100.0);
			else
				account = new SavingAccount(Double.valueOf(balance_text.getText()),rate/100.0,Integer.valueOf(accountID_text.getText()));
		}
		cust.setAccount(account);
		Transaction tran = new Transaction(account.getClass().getSimpleName(), account.getID() , true, "add", 0, "");
		account.addTransaction(tran);
		cust.addTransaction(tran);
		bank.addTransaction(tran);
	}
}