package skyline;

import java.util.ArrayList;

public class Skyline {
	private Building[] buildings;
	private int buildingCount;
	
	public Skyline(int size) {
		buildings = new Building[size];
	}
	
	public void addBuilding(int left, int height, int right) {
		buildings[buildingCount++] = new Building(left, height, right);
	}
	
	public void printSkyline() {
		ArrayList<Node> skyline = findSkyline(buildings, 0, buildings.length - 1);
		StringBuffer buf = new StringBuffer(skyline.get(0).x + "," + skyline.get(1).y);
		
		for(int i = 1; i < skyline.size(); i++) {
			if(skyline.get(i).y == skyline.get(i - 1).y) {
				continue;
			}
			
			buf.append("," + skyline.get(i).x + "," + skyline.get(i).y);
		}
		
		System.out.println(buf);
	}

	public ArrayList<Node> findSkyline(Building[] buildings, int start, int end) {
		if(start == end) {
			ArrayList<Node> skyline = new ArrayList<Node>();
			skyline.add(new Node(buildings[start].left, buildings[start].height));
			skyline.add(new Node(buildings[end].right, 0));
			return skyline;
		}
		
		int mid = (start + end) / 2;
		ArrayList<Node> sky1 = findSkyline(buildings, start, mid);
		ArrayList<Node> sky2 = findSkyline(buildings, mid + 1, end);
		return mergeSkyline(sky1, sky2);
	}
	
	private ArrayList<Node> mergeSkyline(ArrayList<Node> sky1, ArrayList<Node> sky2) {
		int currentH1 = 0;
		int currentH2 = 0;
		int currentX = 0;
		int maxH = 0;
		ArrayList<Node> skyline = new ArrayList<Node>();
		
		while((sky1.size() > 0) && (sky2.size() > 0)) {
			if(sky1.get(0).x < sky2.get(0).x) {
				currentX = sky1.get(0).x;
				currentH1 = sky1.get(0).y;
				maxH = currentH1;
				
				if(currentH2 > maxH) {
					maxH = currentH2;
				}
				
				skyline.add(new Node(currentX, maxH));
				sky1.remove(0);
			}
			
			else {
				currentX = sky2.get(0).x;
				currentH2 = sky2.get(0).y;
				maxH = currentH1;
				
				if(currentH2 > maxH) {
					maxH = currentH2;
				}
				
				skyline.add(new Node(currentX, maxH));
				sky2.remove(0);
			}
		}
		
		while(sky1.size() > 0) {
			skyline.add(sky1.get(0));
			sky1.remove(0);
		}
		
		while(sky2.size() > 0) {
			skyline.add(sky2.get(0));
			sky2.remove(0);
		}
		
		return skyline;
	}
	
	private class Node {
		int x;
		int y;
		
		public Node(int x, int y) {
			super();
			this.x = x;
			this.y = y;
		}
	}

	private class Building {
		int left;
		int height;
		int right;
		
		public Building(int left, int height, int right) {
			super();
			this.left = left;
			this.height = height;
			this.right = right;
		}
	}
}
