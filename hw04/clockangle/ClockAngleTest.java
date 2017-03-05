package clockangle;

import java.util.Scanner;

public class ClockAngleTest {
	public static void main(String[] args) {
		ClockAngle ca = new ClockAngle();
		Scanner sc = new Scanner(System.in);
		
		System.out.print("hour : ");
		int hour = sc.nextInt();
		System.out.print("minute : ");
		int minute = sc.nextInt();
		
		System.out.println("angle : " + ca.calculate_angle(hour, minute));
		
		sc.close();
	}

}
