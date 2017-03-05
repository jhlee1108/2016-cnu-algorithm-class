package fibonacci;

import java.util.Scanner;

public class FibonacciSequenceTest {
	public static void main(String[] args) {
		FibonacciSequence fs = new FibonacciSequence();
		Scanner sc = new Scanner(System.in);
		
		System.out.print("n = ");
		int n = sc.nextInt();
		
		System.out.println("1 : Recursion");
		System.out.println("2 : Array");
		System.out.println("3 : Recursive squaring");
		int state = sc.nextInt();
		
		switch(state) {
		case 1:
			fs.startFibonacciRecursion(n);
			break;
			
		case 2:
			fs.startFibonacciArray(n);
			break;
			
		case 3:
			fs.startFibonacciRecursiveSquaring(n);
			break;
			
		default:
			break;	
		}
		
		sc.close();
	}
}
