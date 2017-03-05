package fibonacci;

import java.math.BigInteger;

public class FibonacciSequence {
	private BigInteger[] fiboArray;
	private BigInteger[][] matrix;
	
	public BigInteger fibonacciRecursion(int n) {
		if(n < 2) {
			return new BigInteger(n + "");
		}
		
		else {
			return fibonacciRecursion(n - 1).add(fibonacciRecursion(n - 2));
		}
	}
	
	public BigInteger fibonacciArray(int n) {
		if(n < 2) {
			fiboArray[n] = new BigInteger(n + "");
			return fiboArray[n];
		}
		
		else {
			fiboArray[n] =  fiboArray[n - 1].add(fiboArray[n - 2]);
			return fiboArray[n];
		}
	}
	
	public BigInteger fibonacciRecursiveSquaring(int n) {
		if(n < 2) {
			return new BigInteger(n + "");
		}
		
		else {
			return powMatrix(n - 1)[0][0];
		}
	}
	
	private BigInteger[][] powMatrix(int n) {
		if(n == 1) {
			return matrix;
		}
		
		else {
			if(n % 2 == 0) {
				return multMatrix(powMatrix(n / 2), powMatrix(n / 2));
			}
			
			else {
				return multMatrix(multMatrix(powMatrix((n - 1) / 2), powMatrix((n - 1) / 2)), matrix);
			}
		}
	}

	private BigInteger[][] multMatrix(BigInteger[][] a, BigInteger[][] b) {
		BigInteger[][] resultMatrix = new BigInteger[2][2];
		resultMatrix[0][0] = new BigInteger("0");
		resultMatrix[0][1] = new BigInteger("0");
		resultMatrix[1][0] = new BigInteger("0");
		resultMatrix[1][1] = new BigInteger("0");
		
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j< 2; j++) {
				for(int k = 0; k < 2; k++) {
					resultMatrix[i][j] = resultMatrix[i][j].add(a[i][k].multiply(b[k][j]));
				}
			}
		}
		
		return resultMatrix;
	}

	public void startFibonacciRecursion(int max) {
		long start, end;
		
		for(int i = 0; i <= max; i++) {
			start = System.nanoTime();
			BigInteger fibo = fibonacciRecursion(i);
			end = System.nanoTime();
			print(i, fibo, end - start);
		}
	}
	
	public void startFibonacciArray(int max) {
		long start, end;
		long total = 0;
		fiboArray = new BigInteger[max + 1];
		
		for (int j = 0; j <= max; j++) {
			BigInteger fibo = new BigInteger("0");
			for (int i = 0; i <= j; i++) {
				start = System.nanoTime();
				fibo = fibonacciArray(i);
				end = System.nanoTime();
				total = total + (end - start);
			}
			print(j, fibo, total);
		}
	}
	
	public void startFibonacciRecursiveSquaring(int max) {
		long start, end;
		matrix = new BigInteger[2][2];
		matrix[0][0] = new BigInteger("1");
		matrix[0][1] = new BigInteger("1");
		matrix[1][0] = new BigInteger("1");
		matrix[1][1] = new BigInteger("0");
		
		for(int i = 0; i <= max; i++) {
			start = System.nanoTime();
			BigInteger fibo = fibonacciRecursiveSquaring(i);
			end = System.nanoTime();
			print(i, fibo, end - start);
		}
	}
	
	private void print(int i, BigInteger fibo, long time) {
		System.out.println(String.format("f<%2d> = %-25s %.9fsec", i, fibo, time / 1000000000.0));
	}
}
