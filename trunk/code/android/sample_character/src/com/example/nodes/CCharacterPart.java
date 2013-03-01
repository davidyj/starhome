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
	
	public static CCharacterPart create() {    	
        return new CCharacterPart();
    }
	
    public static CCharacterPart create(String name,String filename) {    	
        return new CCharacterPart(name,TextureManager.sharedTextureManager().addImage(filename));
    }    
	
    public CCharacterPart() {		
	}
    
	public CCharacterPart(String name,Texture2D tex) {
		this.name = name;
		setTexture(tex);
	}
	
	private String name = new String();
	private String z;		
	private CCPoint origin 	= new CCPoint(),neck = new CCPoint(),navel = new CCPoint(),hand = new CCPoint(),handmove = new CCPoint();	
	private boolean neckflag = false,handflag = false,navelflag = false,handmoveflag = false;

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
			String path = "img/character/00002000/".concat(value);
			Texture2D tex = TextureManager.sharedTextureManager().addImage(path);
			if(null == tex){
				Log.i("character set image error",value);
				return;
			}
			setTexture(tex);
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
		else if("handmove_x".equals(key)){
			handmove.x = Integer.parseInt(value) + origin.x;
		}
		else if("handmove_y".equals(key)){
			handmove.y = -Integer.parseInt(value) + origin.y;
		}
		
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
	public void setOrigin(CCPoint origin) {
		this.origin = CCPoint.ccp(origin.x, -origin.y);
	}
	public CCPoint Neck() {
		return neck;
	}
	public void setNeck(CCPoint neck) {
		if(neckflag == false){
			this.neck = CCPoint.ccp(neck.x,neck.y);
			neckflag = true;
		}
	}
	public CCPoint Navel() {
		return navel;
	}
	public void setNavel(CCPoint navel) {		
		if( false == navelflag ){
			this.navel = CCPoint.ccp( navel.x + origin.x,-navel.y + origin.y);
			navelflag = true;
		}
		
	}
	public CCPoint Hand() {
		return hand;
	}
	public void setHand(CCPoint hand) {		
		if( false == handflag){
			this.hand = CCPoint.ccp(hand.x,hand.y);
			handflag = true;
		}
	}		
	
	public CCPoint HandMove(){
		return handmove;
	}
	
	public void setHandmove(CCPoint handmove){
		if( false == handmoveflag){
			this.handmove = CCPoint.ccp(handmove.x,handmove.y);
			handmoveflag = true;
		}	
	}
	
    public boolean isFrameDisplayed(Object frame) {
        return getTexture() == (((CCharacterPart)frame).getTexture());
    }
	
	
	 public void setDisplayFrame(Object frame) {
	        setTexture(((CCharacterPart)frame).getTexture());
	 }
	
}
