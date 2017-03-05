package floor;

import java.math.BigInteger;

public class Floor {
	public int log2Floor(BigInteger inputNumber) {
		int k = 0;
		BigInteger n = new BigInteger("1");
		
		while(n.compareTo(inputNumber) != 1) {
			k += 1;
			n = n.multiply(new BigInteger("2"));
		}
		
		return k - 1;
	}
	
	public int log2FloorFast(BigInteger inputNumber) {
		int k = 1;
		BigInteger n = new BigInteger("2");
		
		while(n.compareTo(inputNumber) != 1) {
			k *= 2;
			n = n.multiply(n);
		}
		
		return binarySearch(inputNumber, k);
	}

	private int binarySearch(BigInteger inputNumber, int k) {
		int i = k / 2;
		int j = k;
		int m;
		
		while((i + 1) != j) {
			m = (i + j) / 2;
			
			if(inputNumber.compareTo(new BigInteger("2").pow(m)) != 1) {
				j = m;
			}
			
			else {
				i = m;
			}
			
		}
		return i;
	}
}
