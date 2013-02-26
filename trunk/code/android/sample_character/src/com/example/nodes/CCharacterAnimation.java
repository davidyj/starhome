package com.example.nodes;


import java.util.ArrayList;

import org.cocos2d.nodes.CocosNode;

public class CCharacterAnimation implements CocosNode.CocosAnimation {
	
	private String name;
	private ArrayList<Object> frames= new ArrayList<Object>();
	private float delay = 5;		
	
	public static CCharacterAnimation create(){
		return new CCharacterAnimation();
	}
	public void setName(String name){
		this.name = name;
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
		
	public float delay(){
		return delay;
	}

	@Override
	public String name() {		
		return name;
	}	
}
