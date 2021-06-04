import java.util.*;
import java.sql.*;

public class BasicDatabase {
	public static String sql;
	public static Connection con;
	public static PreparedStatement ps;
	public static String DB_Driver = "net.ucanaccess.jdbc.UcanaccessDriver";
	public static String BasicDatabase = "BasicDatabase.accdb";
	public static String DB_Connection = "jdbc: ucanaccess://"+BasicDatabase;
	static BasicDatabase g = new BasicDatabase();
	
	public static void main(String[] args){
		try{
			Scanner s = new Scanner(System.in);
			System.out.println("Enter last name: ");
			String ln = s.nextLine();
			System.out.println("Enter first name: ");
			String fn = s.nextLine();
			System.out.println("Enter address: ");
			String add = s.nextLine();
			System.out.println("Enter age: ");
			int age = s.nextInt();
			g.addToDB(ln, fn, add, age);
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
		}catch(SQLException e){
			System.out.println(e.getMessage());
		}
	}
	
	public void addToDB(String ln, String fn, String add, int age) throws SQLException {
		sql = "insert into Person(LastName, FirstName, Address, Age)values(?, ?, ?, ?)";
		try{
			con = g.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, ln);
			ps.setString(2, fn);
			ps.setString(3, add);
			ps.setInt(4, age);
			ps.execute();
			System.out.println("Data successfully saved.");
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
		}catch(SQLException e){
			System.out.println(e.getMessage());
		}finally{
			if(con != null){
				con.close();
			}
			if(ps != null){
				ps.close();
			}
		}
	}
	public Connection getDBConnection(){
		try{
			Class.forName(DB_Driver);
		}catch(ClassNotFoundException e){
			System.out.println(e.getMessage());
		}
		try{
			con = DriverManager.getConnection(DB_Connection, "", "");
		}catch(SQLException e){
			System.out.println(e.getMessage());
		}
		return con;
	}
}