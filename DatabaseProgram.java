import java.util.*;
import java.sql.*;

public class DatabaseProgram {
	public static String sql;
	public static Connection con;
	public static PreparedStatement ps;
	public static String DB_Driver = "net.ucanaccess.jdbc.UcanaccessDriver";
	public static String BasicDatabase = "BasicDatabase.accdb";
	public static String DB_Connection = "jdbc:ucanaccess://"+BasicDatabase;
	static DatabaseProgram obj = new DatabaseProgram();
	
	public static void main(String[] args) throws SQLException {
		System.out.println("This program modifies a database regarding personal information. Choose from the menu below:");
		obj.menu();
	}
	
	public void menu() throws SQLException {
		try{
			Scanner s = new Scanner(System.in);
			System.out.println("\n1 - Add data");
			System.out.println("2 - Search a specific record");
			System.out.println("3 - Search all records");
			System.out.println("4 - Delete a record");
			System.out.println("5 - Update a record");
			System.out.println("6 - Exit program");
			System.out.print("Enter the corresponding number here: ");
			int choice = s.nextInt();
			if(choice == 1){
				obj.addData();
			}if(choice == 2){
				obj.search();
			}if(choice == 3){
				obj.searchAll();
			}if(choice == 4){
				obj.delete();
			}if(choice == 5){
				obj.update();
			}if(choice < 1 || choice > 6){
				System.out.println("Invalid input.");
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			obj.menu();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			obj.menu();
		}
	}
	
	public void addData() throws SQLException {
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
			
			sql = "insert into Person(LastName, FirstName, Address, Age)values(?, ?, ?, ?)";
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, ln);
			ps.setString(2, fn);
			ps.setString(3, add);
			ps.setInt(4, age);
			ps.execute();
			System.out.println("Data successfully saved.");
			obj.menu();
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			obj.menu();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			obj.menu();
		}finally{
			if(con != null){
				con.close();
			}
			if(ps != null){
				ps.close();
			}
		}
	}
	
	public void search() throws SQLException {
		sql = "select * from Person where LastName like ? order by Age desc";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter a family name: ");
			String a = s.nextLine();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" +a+ "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("ID");
					String ln = rs.getString("LastName");
					String fn = rs.getString("FirstName");
					String add = rs.getString("Address");
					int age = rs.getInt("Age");
					
					System.out.print("\tID no. " + id + " - " + ln + ", " + fn + " - " + add + " - " + age + " yrs. old");
				}
				obj.menu();
			}
		}catch(SQLException e){
			System.out.println(e.getMessage());
			obj.menu();
		}
	}
	
	public void searchAll() throws SQLException {
		sql = "select * from Person";
		try{
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("ID");
					String ln = rs.getString("LastName");
					String fn = rs.getString("FirstName");
					String add = rs.getString("Address");
					int age = rs.getInt("Age");
					
					System.out.println("\tID no. " + id + " - " + ln + ", " + fn + " - " + add + " - " + age + " yrs. old");
				}
				obj.menu();
			}
		}catch(SQLException e){
			System.out.println(e.getMessage());
			obj.menu();
		}
	}
	
	public void delete() throws SQLException {
		try{
			sql = "select * from Person where LastName like ? order by LastName";
			Scanner s = new Scanner(System.in);
			System.out.print("Enter a last name: ");
			String ln = s.nextLine();
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" +ln+ "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("ID");
					String ln2 = rs.getString("LastName");
					String fn = rs.getString("FirstName");
					String add = rs.getString("Address");
					int age = rs.getInt("Age");
					
					System.out.println("\tID no. " + id + " - " + ln2 + ", " + fn + " - " + add + " - " + age + " yrs. old");
			    }
			}
			System.out.print("Enter an ID to delete: ");
			int id2 = s.nextInt();
            sql = "delete * from Person where ID = ?";
			ps = con.prepareStatement(sql);
			ps.setInt(1, id2);
			ps.execute();
			System.out.println("Record successfully deleted.");
			obj.menu();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			obj.menu();
		}
	}
	
	public void update() throws SQLException {
		try{
			sql = "select * from Person where LastName like ? order by LastName";
			Scanner s = new Scanner(System.in);
			System.out.print("Enter a last name: ");
			String ln = s.nextLine();
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" +ln+ "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("ID");
					String ln2 = rs.getString("LastName");
					String fn = rs.getString("FirstName");
					String add = rs.getString("Address");
					int age = rs.getInt("Age");
					
					System.out.println("\tID no. " + id + " - " + ln2 + ", " + fn + " - " + add + " - " + age + " yrs. old");
			    }
			}
			System.out.println("Enter new last name: ");
			String updtln = s.nextLine();
			System.out.println("Enter new first name: ");
			String updtfn = s.nextLine();
			System.out.println("Enter new address: ");
			String updtadd = s.nextLine();
			System.out.println("Enter new age: ");
			int updtage = s.nextInt();
			System.out.println("Enter the ID: ");
			int id2 = s.nextInt();
			sql = "update Person set LastName = ?, FirstName = ?, Address = ?, Age = ? where ID = ?";
			ps = con.prepareStatement(sql);
			ps.setString(1, updtln);
			ps.setString(2, updtfn);
			ps.setString(3, updtadd);
			ps.setInt(4, updtage);
			ps.setInt(5, id2);
			ps.execute();
			System.out.println("Record successfully updated.");
			obj.menu();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			obj.menu();
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