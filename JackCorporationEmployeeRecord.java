//Author: JackTorpas, 2018

import java.util.*;
import java.sql.*;

public class JackCorporationEmployeeRecord {
	public static String sql;
	public static Connection con;
	public static PreparedStatement ps;
	public static String DB_Driver = "net.ucanaccess.jdbc.UcanaccessDriver";
	public static String DB = "Jack Corporation Employee Record.accdb";
	public static String DB_Connection = "jdbc:ucanaccess://"+DB;
	static JackCorporationEmployeeRecord obj = new JackCorporationEmployeeRecord();
	
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
	
	public static void main(String[] args) throws SQLException {
		System.out.println("This program modifies a database regarding the personal information of employees of Jack Corporation.");
		System.out.println("Choose from the menu below: ");
		obj.menu();
	}
	
	public void menu() throws SQLException {
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("\n");
			System.out.println("\t1 - Add a record");
			System.out.println("\t2 - Retrieve all records");
			System.out.println("\t3 - Search for a specific employee by field");
			System.out.println("\t4 - Delete record");
			System.out.println("\t5 - Update record by specific field");
			System.out.println("\t6 - Delete all records (WARNING: DON'T DO THIS IF YOU ARE CURIOUS)");
			System.out.println("\t7 - Exit program");
			System.out.print("Enter the corresponding number here- ");
			int choice = s.nextInt();
			switch(choice){
				case(1):{
					obj.addData();
					break;
				}case(2):{
					obj.searchAll();
					break;
				}case(3):{
					obj.search();
					break;
				}case(4):{
					obj.delete();
					break;
				}case(5):{
					obj.update();
					break;
				}case(6):{
					obj.deleteAll();
					break;
				}case(7):{
					System.out.println("Thanks for using this program xD");
					break;
				}default:{
					System.out.println("Invalid input.");
					obj.menu();
				}
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
			System.out.print("Enter the employee's name: ");
			String n = s.nextLine();
			System.out.print("Enter the address: ");
			String add = s.nextLine();
			System.out.print("Enter the date of birth, format must be MM/DD/YYYY: ");
			String dob = s.nextLine();
			System.out.print("Enter if MALE or FEMALE: ");
			String sex = s.nextLine();
			System.out.print("Enter where the employee studied in elementary: ");
			String prim = s.nextLine();
			System.out.print("Enter where the employee studied in high school: ");
			String sec = s.nextLine();
			System.out.print("Enter where the employee studied in college: ");
			String ter = s.nextLine();
			System.out.print("Enter other professional skills the employee has: ");
			String pro = s.nextLine();
			System.out.print("Enter the employee's Social Security number: ");
			String sss = s.nextLine();
			System.out.print("Enter the employee's TIN: ");
			int tin = s.nextInt();
			s.nextLine();
			System.out.println("Enter if that employee has any disabilities.");
			System.out.print("Perfectly normal, no disabilities, mentally disabled, or handicapped: ");
			String dis = s.nextLine();
			System.out.print("Enter his/her contact number: ");
			String conctnum = s.nextLine();
			System.out.print("Enter his/her working hours (e.g. 6:30 to 14:30 - 24-hour format): ");
			String hours = s.nextLine();
			System.out.print("Enter his/her working days (e.g. Monday to Friday or Tuesday to Wednesday): ");
			String days = s.nextLine();
			System.out.print("Enter the employee's benefits (e.g. bonuses), if he/she has any: ");
			String ben = s.nextLine();
			
			sql = "insert into EmployeeRecord(EmployeeName, Address, DateOfBirth, Sex, PrimaryEd, SecondaryEd, TertiaryEd, ProSkills, SSSNUm, TIN, Disabilities, EmergencyContactNum, WorkingHours, WorkingDays, Benefits)values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, n);
			ps.setString(2, add);
			ps.setString(3, dob);
			ps.setString(4, sex);
			ps.setString(5, prim);
			ps.setString(6, sec);
			ps.setString(7, ter);
			ps.setString(8, pro);
			ps.setString(9, sss);
			ps.setInt(10, tin);
			ps.setString(11, dis);
			ps.setString(12, conctnum);
			ps.setString(13, hours);
			ps.setString(14, days);
			ps.setString(15, ben);
			ps.execute();
			System.out.println("Info successfully added to the database.");
			obj.menu();	
		}catch(InputMismatchException e){
				System.out.println("Invalid input!");
				addData();
		}catch(SQLException e){
				System.out.println(e.getMessage());
				addData();
		}finally{
			if(con != null){
				con.close();
			}
			if(ps != null){
				ps.close();
			}
	    }
	}
	
	public void searchAll() throws SQLException {
		sql = "select * from EmployeeRecord";
		try{
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			if(!rs.isBeforeFirst()){
				System.out.println("This database is devoid of records.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
            } 
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchAll();
		}
	}
	
	public void search() throws SQLException {
		try{
			Scanner s = new Scanner(System.in);
			System.out.println("Search for a specific employee by: ");
			System.out.println("1 - Name");
			System.out.println("2 - Sex");
			System.out.println("3 - Address");
			System.out.println("4 - Professional skill/s");
			System.out.println("5 - SSS Number");
			System.out.println("6 - TIN");
			System.out.print("Enter the corresponding number here - ");
			int x = s.nextInt();
			if(x == 1){
				searchName();
			}else if(x == 2){
				searchSex();
			}else if(x == 3){
				searchAdd();
			}else if(x == 4){
				searchSkill();
			}else if(x == 5){
				searchSSS();
			}else if(x == 6){
				searchTIN();
			}else if(x < 1 || x > 6){
				System.out.println("Invalid input!");
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			search();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			search();
		}
	}
	
	public void searchName() throws SQLException {
		sql = "select * from EmployeeRecord where EmployeeName like ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employee's name: ");
			String n = s.nextLine();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" +n+ "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String e_name = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			searchName();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchName();
		}
	}
	
	public void searchSex(){
		sql = "select * from EmployeeRecord where Sex = ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employees' sex: (MALE OR FEMALE)");
			String e_sex = s.nextLine();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, e_sex);
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			searchSex();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchSex();
		}
	}
	
	public void searchAdd() throws SQLException {
		sql = "select * from EmployeeRecord where Address like ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employee's address: ");
			String a = s.nextLine();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" + a + "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			searchAdd();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchAdd();
		}
	}
	
	public void searchSkill() throws SQLException {
		sql = "select * from EmployeeRecord where ProSkills like ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employee's professional skill/s: ");
			String skill = s.nextLine();
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" + skill + "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			searchSkill();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchSkill();
		}
	}
	
	public void searchSSS() throws SQLException {
		sql = "select * from EmployeeRecord where SSSNUm like ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employee's SSS number: ");
			String sssnum = s.nextLine();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" + sssnum + "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			searchSSS();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchSSS();
		}
	}
	
	public void searchTIN() throws SQLException {
		sql = "select * from EmployeeRecord where TIN like ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employee's TIN: ");
			int taxid = s.nextInt();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setInt(1, taxid);
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				obj.menu();
			}
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			searchTIN();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			searchTIN();
		}
	}
	
	public void delete() throws SQLException {
		sql = "select * from EmployeeRecord where EmployeeName like ? order by EmployeeID";
		try{
			Scanner s = new Scanner(System.in);
			System.out.print("Enter the employee's name: ");
			String e_name = s.nextLine();
			
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ps.setString(1, "%" +e_name+ "%");
			ResultSet rs = ps.executeQuery();
			
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
			}
			System.out.print("Enter an EmployeeID to delete: ");
			int id2 = s.nextInt();
			sql = "delete * from EmployeeRecord where EmployeeID = ?";
			ps = con.prepareStatement(sql);
			ps.setInt(1, id2); 
			ps.execute();
			System.out.println("Record successfully deleted.");
			obj.menu();
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			delete();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			delete();
		}
	}
	
	public void update() throws SQLException {
		sql = "select * from EmployeeRecord";
		try{
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			if(!rs.isBeforeFirst()){
				System.out.println("This record does not exist.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				Scanner s = new Scanner(System.in);
				System.out.print("Enter the EmployeeID to update: ");
				int id2 = s.nextInt();
				System.out.println("What would you like to update?");
				System.out.println("1 - Name");
				System.out.println("2 - Sex");
				System.out.println("3 - Address");
				System.out.println("4 - Professional skill/s");
				System.out.println("5 - SSS Number");
				System.out.println("6 - TIN");
				System.out.println("7 - Date of  birth");
				System.out.println("8 - Elementary education");
				System.out.println("9 - Secondary education");
				System.out.println("10 - Tertiary education");
				System.out.println("11 - Disabilities");
				System.out.println("12 - Contact number");
				System.out.println("13 - Working hours");
				System.out.println("14 - Working days");
				System.out.println("15 - Benefits");
				System.out.print("Enter the corresponding number here - ");
				int x = s.nextInt();
				if(x == 1){
					s.nextLine();
					System.out.print("Enter the new EmployeeName: ");
					String newName = s.nextLine();
					sql = "update EmployeeRecord set EmployeeName = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newName);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 2){
					s.nextLine();
					System.out.print("Revise the employee's sex: ");
					String newSex = s.nextLine();
					sql = "update EmployeeRecord set Sex = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newSex);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 3){
					s.nextLine();
					System.out.print("Revise the employee's address: ");
					String newAdd = s.nextLine();
					sql = "update EmployeeRecord set Address = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newAdd);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 4){
					s.nextLine();
					System.out.print("Revise the employee's skill/s: ");
					String newSkills = s.nextLine();
					sql = "update EmployeeRecord set ProSkills = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newSkills);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 5){
					s.nextLine();
					System.out.print("Revise the employee's SSS number: ");
					String newSSS = s.nextLine();
					sql = "update EmployeeRecord set SSSNUm = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newSSS);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 6){
					s.nextLine();
					System.out.print("Revise the employee's TIN: ");
					int newTIN = s.nextInt();
					sql = "update EmployeeRecord set TIN = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setInt(1, newTIN);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x < 1 || x > 15){
					System.out.println("Invalid input!");
					obj.menu();
				}else if(x == 7){
					s.nextLine();
					System.out.print("Revise the employee's date of birth: ");
					String newDOB = s.nextLine();
					sql = "update EmployeeRecord set DateOfBirth = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newDOB);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 8){
					s.nextLine();
					System.out.print("Revise the employee's elementary education: ");
					String newPrim = s.nextLine();
					sql = "update EmployeeRecord set PrimaryEd = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newPrim);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 9){
					s.nextLine();
					System.out.print("Revise the employee's secondary education: ");
					String newSec = s.nextLine();
					sql = "update EmployeeRecord set SecondaryEd = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newSec);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu();
				}else if(x == 10){
					s.nextLine();
					System.out.print("Revise the employee's tertiary education: ");
					String newTer = s.nextLine();
					sql = "update EmployeeRecord set TertiaryEd = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newTer);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu(); 
				}else if(x == 11){
					s.nextLine();
					System.out.print("Revise the employee's disabilities, if any: ");
					String newDis = s.nextLine();
					sql = "update EmployeeRecord set Disabilities = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newDis);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu(); 
				}else if(x == 12){
					s.nextLine();
					System.out.print("Revise the employee's contact number: ");
					String newNum = s.nextLine();
					sql = "update EmployeeRecord set EmergencyContactNum = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newNum);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu(); 
				}else if(x == 13){
					s.nextLine();
					System.out.print("Revise the employee's working hours: ");
					String newHour = s.nextLine();
					sql = "update EmployeeRecord set WorkingHours = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newHour);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu(); 
				}else if(x == 14){
					s.nextLine();
					System.out.print("Revise the employee's working days: ");
					String newDay = s.nextLine();
					sql = "update EmployeeRecord set WorkingDays = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newDay);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu(); 
				}else if(x == 15){
					s.nextLine();
					System.out.print("Revise the employee's benefits: ");
					String newBen = s.nextLine();
					sql = "update EmployeeRecord set Benefits = ? where EmployeeID = ?";
					ps = con.prepareStatement(sql);
					ps.setString(1, newBen);
					ps.setInt(2, id2);
					ps.execute();
					System.out.println("Record successfully updated.");
					obj.menu(); 
				}
			}	
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			update();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			update();
		}
	}
	
	public void deleteAll() throws SQLException {
		sql = "select * from EmployeeRecord";
		try{
			con = obj.getDBConnection();
			ps = con.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			if(!rs.isBeforeFirst()){
				System.out.println("This database is devoid of records.");
				obj.menu();
			}else{
				while(rs.next()){
					int id = rs.getInt("EmployeeID");
					String n = rs.getString("EmployeeName");
					String add = rs.getString("Address");
					String dob = rs.getString("DateOfBirth");
					String sex = rs.getString("Sex");
					String prim = rs.getString("PrimaryEd");
					String sec = rs.getString("SecondaryEd");
					String ter = rs.getString("TertiaryEd");
					String pro = rs.getString("ProSkills");
					String sss = rs.getString("SSSNUm");
					int tin = rs.getInt("TIN");
					String dis = rs.getString("Disabilities");
					String conctnum = rs.getString("EmergencyContactNum");
					String hours = rs.getString("WorkingHours");
					String days = rs.getString("WorkingDays");
					String ben = rs.getString("Benefits");
					
					System.out.println("\tID no. " + id + " || Name : " + n + " || Address : " + add + " || Born : " + dob + " || Sex : " + sex + " || Elementary : " + prim + " || High school :" + sec + " || College : " + ter);
					System.out.println("\tProfessional skills : " + pro + " || SSS # : " + sss + " || TIN : " + tin + " || Any disabilities : " + dis + " || Contact # : " + conctnum + " || Working hours : " + hours + " || Working days : " + days + " || Benefits : " + ben);
					System.out.print("\n");
				}
				Scanner s = new Scanner(System.in);
				System.out.println("Are you sure you want to delete all the records of this database? (1 - YES, 2 - NO)");
				int ans = s.nextInt();
				if(ans == 1){
					sql = "delete * from EmployeeRecord";
					ps = con.prepareStatement(sql);
					ps.execute();
					System.out.println("All records have been deleted.");
					obj.menu();
				}else{
					obj.menu();
				}
			}	
		}catch(InputMismatchException e){
			System.out.println("Invalid input!");
			update();
		}catch(SQLException e){
			System.out.println(e.getMessage());
			update();
		}
	}
}
