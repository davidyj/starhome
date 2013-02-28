package com.example.core;

import org.cocos2d.types.CCPoint;

public class CCore {
	
	private static CCore instance=null;
	
	public static synchronized CCore getInstance(){ 
		if(instance==null){ 
			instance=new CCore(); 
		} 
			return instance;			
		} 	
	
	public CCPoint GamePoint = new CCPoint();
	
	public static CCPoint ORIGIN_LEFT_TOP = CCPoint.ccp(0.0f,1.0f);  
	public static CCPoint ORIGIN_RIGHT_TOP = CCPoint.ccp(1.0f, 1.0f);  
	public static CCPoint ORIGIN_RIGHT_BOTTOM = CCPoint.ccp(1.0f, 0.0f);  
	public static CCPoint ORIGIN_LEFT_BOTTOM = CCPoint.ccp(0.0f, 0.0f);
	public static CCPoint ORIGIN_MIDDLE = CCPoint.ccp(0.5f, 0.5f);
	  
}
