package com.example.nodes;

import java.util.HashMap;

import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureNode;
import org.cocos2d.nodes.CocosNode.CocosAnimation;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.opengl.Texture2D;
import org.cocos2d.types.CCPoint;

import android.graphics.Bitmap;
import android.util.Log;

public class CCharacterPart extends TextureNode  {
	
	public static CCharacterPart create(String path) {    	
        return new CCharacterPart(path);
    }	
    public static CCharacterPart create(String name,String filename) {    	
        return new CCharacterPart(name,TextureManager.sharedTextureManager().addImage(filename));
    }    
    public static CCharacterPart create(CCharacterPart part) {    	
        return new CCharacterPart(part);
    }
	
    public CCharacterPart(String path) {
    	this.path = path;
	}    
	public CCharacterPart(String name,Texture2D tex) {
		this.name = name;		
		setTexture(tex);
	}
	public CCharacterPart(CCharacterPart part){		
		this.name = part.name;
		this.path = part.path;
		this.z    = part.getZ();	
		
		this.setTexture(part.getTexture());
		
		this.origin.x = part.Origin().x;
		this.origin.y = part.Origin().y;
		
		this.neck.x   = part.Neck().x;
		this.neck.y   = part.Neck().y;
		
		this.navel.x  = part.Navel().x;
		this.navel.y  = part.Navel().y;
		
		this.hand.x   = part.Hand().x;
		this.hand.y   = part.Hand().y;
		
		this.handmove.x = part.HandMove().x;
		this.handmove.y = part.HandMove().y;
		
		this.brow.x	  = part.Brow().x;
		this.brow.y   = part.Brow().y;		
	}
	
	private String path = new String();
	private String name = new String();
	private String z = new String();		
	private CCPoint origin 	= new CCPoint(),neck = new CCPoint(),navel = new CCPoint(),hand = new CCPoint(),handmove = new CCPoint(),brow = new CCPoint();	
	

	public String name(){
		return name;
	}
	
	public void setValue(String key,String value){		
		if(null == value){
			return;
		}
		if("name".equals(key)){
			this.name = value;
		}
		else if("image".equals(key)){			
			Texture2D tex = TextureManager.sharedTextureManager().addImage(path.concat(value));
			if(null == tex){
				Log.i("character set image error",value);
				return;
			}
			setTexture(tex);
		}
		else if("z".equals(key)){
			this.z = value;
		}
		else if("origin_x".equals(key)){
			origin.x = Integer.parseInt(value);
		}
		else if("origin_y".equals(key)){
			origin.y = -Integer.parseInt(value);			
		}
		else if("neck_x".equals(key)){
			neck.x = Integer.parseInt(value) + origin.x;
		}
		else if("neck_y".equals(key)){
			neck.y = -Integer.parseInt(value) + origin.y;
		}
		else if("navel_x".equals(key)){
			navel.x = Integer.parseInt(value) + origin.x;
		}
		else if("navel_y".equals(key)){
			navel.y = -Integer.parseInt(value) + origin.y;
		}
		else if("hand_x".equals(key)){
			hand.x = Integer.parseInt(value) + origin.x;
		}
		else if("hand_y".equals(key)){
			hand.y = -Integer.parseInt(value) + origin.y;
		}
		else if("handMove_x".equals(key)){
			handmove.x = Integer.parseInt(value) + origin.x;
		}
		else if("handMove_y".equals(key)){
			handmove.y = -Integer.parseInt(value) + origin.y;
		}
		else if("brow_x".equals(key)){
			brow.x = Integer.parseInt(value) + origin.x;
		}
		else if("brow_y".equals(key)){
			brow.y = -Integer.parseInt(value) + origin.y;
		}		
	}
	
	public void setName(String name){
		this.name = name;
	}
	public String getZ() {
		return z;
	}
	public void setZ(String string) {
		this.z = string;
	}
	public CCPoint Origin() {
		return origin;
	}	
	public CCPoint Neck() {
		return neck;
	}
	public CCPoint Navel() {
		return navel;
	}	
	public CCPoint Hand() {
		return hand;
	}		
	public CCPoint HandMove(){
		return handmove;
	}
	public CCPoint Brow(){
		return brow;
	}
	
    public boolean isFrameDisplayed(Object frame) {
        return getTexture() == (((CCharacterPart)frame).getTexture());
    }	
	 public void setDisplayFrame(Object frame) {
	        setTexture(((CCharacterPart)frame).getTexture());
	 }
	
}
