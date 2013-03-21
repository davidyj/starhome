package com.example.nodes;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

import javax.xml.parsers.ParserConfigurationException;


import org.cocos2d.actions.base.RepeatForever;
import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.types.CCPoint;
import org.xml.sax.SAXException;

import com.example.actions.interval.CCharacterAnimate;
import com.example.core.CSuitMgr;
public class CCharecter  {	
	
	public static CCharecter create(){
		return new CCharecter();
	}
	
	public CCharecter() {		
	}
	
	public void init() {	
		sprites.init();
	}	
	
	public void setPosition(float x,float y){
		sprites.setPosition(x, y);				
	}	
	
	public static CCPoint gameOrigin = new CCPoint();
	public CCharacterSprite sprites = CCharacterSprite.create();	
	private String CurrentAction = new String();
	private HashMap<String, CCharacterAnimate> animates = new HashMap<String, CCharacterAnimate>();	
	
	
	public void addAnimate(CCharacterAnimation animation){
		CCharacterAnimate animate = CCharacterAnimate.action(animation);
		animates.put(animation.name(), animate);
	}
	
	public void SetAction(String action){		
		
		if(action.isEmpty() || CurrentAction.equals(action))
			return;
		
		if(!CurrentAction.isEmpty() && animates.get(CurrentAction) != null)
			sprites.stopAction(animates.get(CurrentAction));		
				
		CurrentAction = action;		
		
		if(animates.get(CurrentAction) !=null ){
			sprites.runAction(RepeatForever.action(animates.get(CurrentAction)));
		}		
	}	
	
	public void setSuit(String name) throws ParserConfigurationException, SAXException, IOException{
		sprites.unsetPart();
		HashMap<String, String> suit = CSuitMgr.getInstance().suits(name);
		if(suit != null){
			  Set<Entry<String, String>> set = suit.entrySet();  
			  Iterator<Entry<String, String>> itor = set.iterator();  
			  while(itor.hasNext())  {  
				  Entry<String, String> entry = itor.next();   
				  sprites.setPart(this,entry.getKey(),entry.getValue());  
			  }
		}			
		sprites.setPart();
	}
	
	public void SetExpresion(String expresion){		
		
	}
	
	public CCharacterAnimation getAnimation(String name){		
		CCharacterAnimate animate = animates.get(name);
		if(animate != null)
			return (CCharacterAnimation) animate.getAnimation();
		return null;
	}
	
	public CCharacterFrame getFrame(String name,String frame){
		CCharacterAnimation ani = getAnimation(name);
		if(ani != null)
			return (CCharacterFrame) ani.getFrame(frame);
		return null;
	}
	
}
