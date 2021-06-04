import java.util.*;

public class ArrayExercise {
	static Integer[] array;
	static int size, i, val = 1, nd = 0, n, checker = 0;
	public static void menu(){
		try{
			Scanner s = new Scanner(System.in);
			System.out.println("\n\nChoose from the menu below: ");
			System.out.println("1 - Input data for the array \n2 - Get the index of a value \n3 - Get the duplicates of a value \n4 - Sort in ascending order \n5 - Sort in descending order \n6 - Exit program");
			System.out.print("Input here: ");
			int choice = s.nextInt();
			if(choice == 1){
				inputData();
			}else if(choice == 2){
				getIndex();
			}else if(choice == 3){
				getDuplicates();
			}else if(choice == 4){
				sortUp();
			}else if(choice == 5){
				sortDown();
			}else if(choice < 1 || choice > 6){
				System.out.println("Choices are from 1-6.");
				menu();
			}
		}catch(InputMismatchException d){
			System.out.println("You did not input a number.");
			menu();
		}
	}
	public static void inputData(){
		try{
			Scanner s = new Scanner(System.in);
			System.out.println("Input the size for the array: ");
			size = s.nextInt();
			array = new Integer[size];
			for(i = 0; i < size; i++){
				System.out.println("Enter value #" + val + ": ");
				if(s.hasNextInt()){
					array[i] = s.nextInt();
					val ++;
				}else{
					System.out.println("You did not input a number.");
					i--;
					s.next();
				}
			}
			checker ++;
			val = 1;
			menu();
		}catch(InputMismatchException d){
			System.out.println("You did not input a number.");
			menu();
		}
	}
	public static void getIndex(){
		try{
			if(checker != 0){
				Scanner s = new Scanner(System.in);
				System.out.println("Input an array value: ");
				n = s.nextInt();
				for(i = 0; i < size; i++){
					if(n == array[i]){
						System.out.println("This number is in index " + i + ". ");
					}
				}
				menu();
			}else{
				System.out.println("Array has no values.");
				menu();
			}
		}catch(InputMismatchException d){
			System.out.println("You did not input a number.");
			menu();
		}
	}
	public static void getDuplicates(){
		try{
			Scanner s = new Scanner(System.in);
			System.out.println("Input an array value: ");
			n = s.nextInt();
			for(i = 0; i < size; i++){
				if(n == array[i]){
					nd ++;
				}
			}
			if(nd == 1){
				System.out.println("This value has " + nd + " duplicate.");
			}else if(!(nd == 0)){
				System.out.println("This value has " + nd + " duplicates.");
			}else{
				System.out.println("Either the array has no values, or the value you input isn't part of the array.");
			}
			nd = 0;
			menu();
		}catch(InputMismatchException d){
			System.out.println("You did not input a number.");
			menu();
		}
	}
	public static void sortUp(){
		try{
			Arrays.sort(array);
			System.out.println("Sorted values: ");
			for(i = 0; i < size; i++){
				System.out.print(array[i] + " ");
			}
			menu();
		}catch(NullPointerException e){
			System.out.println("Array has no values.");
			menu();
		}
	}
	public static void sortDown(){
		try{
			Arrays.sort(array, Collections.reverseOrder());
			System.out.println("Sorted values: ");
			for(i = 0; i < size; i++){
				System.out.print(array[i] + " ");
			}
			menu();
		}catch(NullPointerException e){
			System.out.println("Array has no values.");
			menu();
		}
	}
	public static void main(String[] args){
		menu();
	}
}