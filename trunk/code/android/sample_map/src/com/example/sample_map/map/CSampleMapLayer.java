package com.example.sample_map.map;

import java.util.ArrayList;

public class CSampleMapLayer {
	public static CSampleMapLayer create(){
		return new CSampleMapLayer();
	}
	
	private ArrayList<CSampleMapObj> objlist = new ArrayList<CSampleMapObj>();
	private ArrayList<CSampleMapTile> tilelist = new ArrayList<CSampleMapTile>();
	
	public void addObj(CSampleMapObj obj){
		objlist.add(obj);
	}
	
	public void addTile(CSampleMapTile tile){
		tilelist.add(tile);
	}
}
