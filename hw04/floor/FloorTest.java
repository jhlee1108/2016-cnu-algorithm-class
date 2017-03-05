package floor;

import java.math.BigInteger;
import java.util.Scanner;

public class FloorTest {	
	public static void main(String[] args) {
		Floor f = new Floor();
		Scanner sc = new Scanner(System.in);
		
		System.out.print("input number : ");
		String input = sc.nextLine();
		BigInteger inputNumber = new BigInteger(input);
		
		System.out.println("log2Floor : " + f.log2Floor(inputNumber));
		System.out.println("log2FloorFast : " + f.log2FloorFast(inputNumber));
		
		sc.close();
	}
}
