package Support.Interface;

public class Factory {
	
	private static DatabaseInterface database;
	private static UserBase userinterface;
	
	private static Factory factory;
	
	private Factory() {
	}
	
	public static synchronized Factory getFactory() {
		if(factory==null)
			factory = new Factory();
		return factory;
	}
	
	public DatabaseInterface getDataBase() throws InstantiationException, IllegalAccessException, ClassNotFoundException {
		if(database == null) {
			String databaseName = System.getProperty("database.class.name");
			database = (DatabaseInterface) Class.forName(databaseName).newInstance();
		}
		return database;
	}
	public UserBase getUserBase() throws InstantiationException, IllegalAccessException, ClassNotFoundException {
		if(userinterface == null) {
			String userbaseName = System.getProperty("userbase.class.name");
			userinterface = (UserBase) Class.forName(userbaseName).newInstance();
		}
		return userinterface;
	}
}
