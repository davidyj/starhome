package com.example.nodes;


import java.util.ArrayList;

import org.cocos2d.nodes.CocosNode;

public class CCharacterAnimation implements CocosNode.CocosAnimation {
	
	private String name;
	private ArrayList<Object> frames= new ArrayList<Object>();
	private float delay = 5;		
	
	public CCharacterAnimation(String name) {
		// TODO Auto-generated constructor stub
		this.name = name;
	}

	public static CCharacterAnimation create(String name){
		return new CCharacterAnimation(name);
	}	
	
	public void setDelay(int delay){
		this.delay = delay;
	}
	
	public void addFrame(CCharacterFrame frame){
		frames.add(frame);
	}
	
	public ArrayList<Object>  frames(){
		return frames;
	}	
	
	public Object getFrame(String frame){
		int index = Integer.parseInt(frame);
		return frames.get(index);		
	}		
	public float delay(){
		return delay;
	}

	@Override
	public String name() {		
		return name;
	}	
}
