package com.example.sample_map.map;

import java.util.ArrayList;

public class CSampleMapLayer {
	public static CSampleMapLayer create(){
		return new CSampleMapLayer();
	}
	
	private String ts = null;
	private ArrayList<CSampleMapObj> objs = new ArrayList<CSampleMapObj>();
	private ArrayList<CSampleMapTile> tiles = new ArrayList<CSampleMapTile>();
	
	public void addObj(CSampleMapObj obj){
		objs.add(obj);
	}
	
	public void addTile(CSampleMapTile tile){
		tiles.add(tile);
	}
	
	public ArrayList<CSampleMapObj> objs(){
		return objs;
	}
	
	public ArrayList<CSampleMapTile> tiles(){
		return tiles;
	}
	
	public void setValue(String key,String value){
		if("tS".equals(key)){
			ts = value;
		}
	}
}
