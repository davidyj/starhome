package com.example.nodes;

import java.util.ArrayList;
import java.util.HashMap;

import com.example.core.CCore;

public class CCharacterFace {

	public CCharacterFace() {		
	}	
	
	private static CCharacterFace instance=null;
	
	public static synchronized CCharacterFace getInstance(){ 
		if(instance==null){ 
			instance=new CCharacterFace(); 
		} 
		return instance;			
	}	
	private HashMap<String,ArrayList<CCharacterPart>> facemap = new HashMap<String,ArrayList<CCharacterPart>>();
	
	public CCharacterPart getNext(String state,CCharacterPart part){		
		ArrayList<CCharacterPart> fl= facemap.get(state);
		
		if(part == null)
			return fl.get(0);
		
		if(fl.size() == 1){
			return fl.get(0);
		}
		else if(fl.size() == 2){		
			if(fl.get(0) == part)
				return fl.get(1);
			return fl.get(0);
		}
		else{
			if(fl.get(0) == part)
				return fl.get(1);
			if(fl.get(1) == part)
				return fl.get(2);
			return fl.get(0);
		}		
	}
	
	public void addFace(String state,CCharacterPart part){
		ArrayList<CCharacterPart> fl= facemap.get(state);
		if(fl == null){
			fl = new ArrayList<CCharacterPart>();		
			facemap.put(state,fl);
		}
		fl.add(part);				
	}
}
