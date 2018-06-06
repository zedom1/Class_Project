package info;

import java.io.IOException;
import java.util.ArrayList;

import support.DataInterface;

public class Book {
	public ArrayList<BookItem> booklist = new ArrayList<>();

	public void makeNewBook(BookItem book) throws IOException {
		booklist.add(book);
		DataInterface.saveNewBook(book);
	}
	
}