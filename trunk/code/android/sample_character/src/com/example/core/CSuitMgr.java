package com.example.core;

import java.util.ArrayList;
import java.util.HashMap;

public class CSuitMgr {

	private static CSuitMgr instance=null;
	
	public static synchronized CSuitMgr getInstance(){ 
		if(instance==null){ 
			instance=new CSuitMgr(); 
		} 
			return instance;			
		} 	
	
	private HashMap<String,HashMap<String,String>> suits = new HashMap<String,HashMap<String,String>>();
	
	public void add(String name,String part,String path){
		HashMap<String,String> suit = suits.get(name);
		if(suit == null){
			suit = new HashMap<String,String>();
			suits.put(name, suit);
		}
		suit.put(part, path);			
	}
	
	public HashMap<String,String> suits(String name){
		return suits.get(name);
	}
}
