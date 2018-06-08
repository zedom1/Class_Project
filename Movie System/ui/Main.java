package ui;

import java.io.IOException;
import java.util.ArrayList;

import info.BookItem;
import info.Cinema;
import info.Movie;
import info.Session;
import javafx.application.Application;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Main extends Application {

	
	@Override
	public void start(Stage primaryStage) throws Exception {
		Cinema.main(null);
		
		VBox mainPane = new VBox();
		VBox textPane = new VBox();
		Scene scene = new Scene(mainPane,500,850);
		FlowPane searchPane = new FlowPane();
		
		Label search_label = new Label("Search:");
		TextField search_text = new TextField();
		//Button search_btn = new Button("Search");
		
		searchPane.setPadding(new Insets(50,60,10,10));
		searchPane.setHgap(30);
		searchPane.setAlignment(Pos.TOP_CENTER);
		
		searchPane.getChildren().add(search_label);
		searchPane.getChildren().add(search_text);
		
		displayFullMovie(textPane,null);
		
		search_text.setOnKeyReleased(e->{
			if(search_text.getText().equals("")) {
				displayFullMovie(textPane,null);
			}
			else {
				displayFullMovie(textPane,Cinema.search(search_text.getText()));
			}
		});
		
		mainPane.getChildren().add(searchPane);
		mainPane.getChildren().add(textPane);
		
		primaryStage.setTitle("Cinema");
		primaryStage.setScene(scene);
		primaryStage.show();
		primaryStage.setOnCloseRequest(e->{
		});
	}
	
	public static void displayFullMovie(VBox textPane, int[]index) {
		textPane.getChildren().clear();
		for(int i=0; i<Cinema.movielist.size(); i ++) {
			Movie movie;
			if(index == null)
				movie = Cinema.movielist.get(i);
			else
				movie = Cinema.movielist.get(index[i]);
			TextArea mText = new TextArea();
			mText.setEditable(false);
			mText.setPrefRowCount(6);
			mText.setFont(new Font(15));
			mText.setPrefColumnCount(28);
			mText.setText(movie.getDesc());
			mText.setWrapText(true);
			HBox  moviePane = new HBox();
			moviePane.setPadding(new Insets(5,10,5,10));
			Button btn = new Button("Select");
			btn.setOnAction(e->{
				selectSession(movie);
			});
			moviePane.getChildren().add(mText);
			moviePane.getChildren().add(btn);
			moviePane.setAlignment(Pos.CENTER);
			textPane.getChildren().add(moviePane);
		}
	}
	
	public static void selectSession(Movie movie) {
		
		Stage stage = new Stage();
		VBox mainPane = new VBox();
		VBox titlePane = new VBox();
		VBox textPane = new VBox();
		Scene scene = new Scene(mainPane,480,400);
		
		Text title = new Text("\n电影信息\n");
		title.setFont(new Font(20));
		
		Label moviedesc = new Label(movie.getDesc()+"\n");
		moviedesc.setFont(new Font(15));
		moviedesc.setWrapText(true);
		
		Text title_s = new Text("场次信息\n");
		title_s.setFont(new Font(20));
		
		titlePane.setAlignment(Pos.CENTER);
		titlePane.getChildren().add(title);
		titlePane.getChildren().add(moviedesc);
		titlePane.getChildren().add(title_s);
		
		for(int i=0; i<movie.session.size(); i ++) {
			Session session =movie.session.get(i);
			TextArea mText = new TextArea();
			mText.setEditable(false);
			mText.setPrefRowCount(3);
			mText.setPrefColumnCount(32);
			mText.setText(session.getDesc());
			
			HBox  moviePane = new HBox();
			moviePane.setPadding(new Insets(10,10,5,10));
			Button btn = new Button("Select");
			btn.setOnAction(e->{
				selectSeats(Cinema.makeNewItem(1,movie.id,session.id,0),session,movie);
			});
			moviePane.getChildren().add(mText);
			moviePane.getChildren().add(btn);
			textPane.getChildren().add(moviePane);
		}
		
		mainPane.getChildren().add(titlePane);
		mainPane.getChildren().add(textPane);
		stage.setTitle("Session");
		stage.setScene(scene);
		stage.show();
		stage.setOnCloseRequest(e->{});
		
	}
	
	public static void selectSeats(BookItem book, Session session,Movie movie) {
		Stage stage = new Stage();
		VBox mainPane = new VBox();
		VBox titlePane = new VBox();
		Scene scene = new Scene(mainPane,480,600);
		
		Text title = new Text("\n场次信息\n");
		title.setFont(new Font(20));
		
		Label sessiondesc = new Label(session.getDesc()+"\n");
		sessiondesc.setFont(new Font(15));
		sessiondesc.setWrapText(true);
		
		Text titles = new Text("\n选择座位\n");
		titles.setFont(new Font(25));
		
		Text screen = new Text("\n---屏幕---\n");
		screen.setFont(new Font(20));
		
		titlePane.getChildren().add(title);
		titlePane.getChildren().add(sessiondesc);
		titlePane.getChildren().add(titles);
		titlePane.getChildren().add(screen);
		titlePane.setAlignment(Pos.CENTER);
		
	
		Text price = new Text("\nTotal price = 0");
		price.setFill(Color.RED);
		
		GridPane seatsPane = new GridPane();
		seatsPane.setAlignment(Pos.CENTER);
		seatsPane.setHgap(20);
		seatsPane.setVgap(20);
		int[] seatSize= session.getSeatSize();
		boolean[][] booked = session.getBook();
		for(int i=0; i<seatSize[0]; i++) {
			for(int j=0; j<seatSize[1]; j++) {
				CheckBox seat = new CheckBox();
				if (booked[i][j]==true) {
					seat.setSelected(true);
					seat.setDisable(true);
				}
				seat.setOnAction(e->{
					if(seat.isSelected()) {
						String[] list = price.getText().split(" ");
						int p = Integer.parseInt(list[3]) + movie.getPrice();
						String s = "";
						for(int k=0; k<list.length-1; k++)
							s = s+" "+list[k];
						s = s + " " + p;
						price.setText("\n"+s.trim());
					}
					else {
						String[] list = price.getText().split(" ");
						int p = Integer.parseInt(list[3]) - movie.getPrice();
						String s = "";
						for(int k=0; k<list.length-1; k++)
							s = s+" "+list[k];
						s = s + " " + p;
						price.setText("\n"+s.trim());
					}
				});
				seatsPane.add(seat, i , j );
			}
		}
		
		HBox btnBox = new HBox();
		Button clear = new Button("Clear");
		Button confirm = new Button("Confirm");
		Button exit = new Button("Exit");
		btnBox.getChildren().add(clear);
		btnBox.getChildren().add(confirm);
		btnBox.getChildren().add(exit);
		btnBox.setAlignment(Pos.CENTER);
		btnBox.setPadding(new Insets(20,20,20,20));
		btnBox.setSpacing(20);
		
		clear.setOnMouseClicked(e->{
			for(int i=0; i<seatSize[0]; i++)
				for(int j=0; j<seatSize[1]; j++) {
					if(booked[i][j]!=true) {
						ObservableList<Node> child = seatsPane.getChildren();
						for(Node node : child) {
							 if(seatsPane.getRowIndex(node) == j && seatsPane.getColumnIndex(node) == i)
							 ((CheckBox)node).setSelected(false);
						}
					}
				}
			String[] list = price.getText().split(" ");
			String s = "";
			for(int k=0; k<list.length-1; k++)
				s = s+" "+list[k];
			s = s + " " + 0;
			price.setText("\n"+s.trim());
		});
		
		confirm.setOnMouseClicked(e->{
			int p = Integer.parseInt(price.getText().split(" ")[3]);
			//System.out.println(p);
			if (p ==0)
				return;
			for(int i=0; i<seatSize[0]; i++)
				for(int j=0; j<seatSize[1]; j++) {
					if(booked[i][j]!=true) {
						ObservableList<Node> child = seatsPane.getChildren();
						for(Node node : child) {
							if(seatsPane.getRowIndex(node) == j && seatsPane.getColumnIndex(node) == i && ((CheckBox)node).isSelected()==true) {
								book.addSeat(new int[] {i,j},movie.getPrice());
								session.addBook(i, j);
							}
						}
					}
				}
			try {
				Cinema.addNewItem(book);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			stage.close();
			confirmScene(book);
		});
		
		exit.setOnMouseClicked(e->stage.close());
		
		mainPane.setAlignment(Pos.TOP_CENTER);
		mainPane.getChildren().add(titlePane);
		mainPane.getChildren().add(seatsPane);
		mainPane.getChildren().add(price);
		mainPane.getChildren().add(btnBox);
		
		stage.setTitle("Seats");
		stage.setScene(scene);
		stage.show();
		stage.setOnCloseRequest(e->{});
	}
	
	public static void confirmScene(BookItem book) {
		Stage stage = new Stage();
		VBox mainPane = new VBox();
		Scene scene = new Scene(mainPane,480,400);
		
		Text title = new Text("\n订票成功！\n");
		title.setFont(new Font(40));
		
		TextArea text = new TextArea();
		text.setText(book.getDesc());
		text.setEditable(false);
		text.setFont(new Font(18));
		
		Button confirm = new Button("确定");
		confirm.setOnMouseClicked(e->stage.close());
		
		mainPane.setAlignment(Pos.TOP_CENTER);
		mainPane.setSpacing(20);
		
		mainPane.getChildren().add(title);
		mainPane.getChildren().add(text);
		mainPane.getChildren().add(confirm);
		
		stage.setTitle("Book");
		stage.setScene(scene);
		stage.show();
		stage.setOnCloseRequest(e->{});
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
