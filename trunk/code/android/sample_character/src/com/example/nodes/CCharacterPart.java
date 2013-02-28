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

public class CCharacterPart extends TextureNode  {
	
    public static CCharacterPart create(String filename) {    	
        return new CCharacterPart(TextureManager.sharedTextureManager().addImage(filename));
    }    
	   
	public CCharacterPart(Texture2D tex) {			
		setTexture(tex);
	}
	
	private String z;		
	private CCPoint origin 	= null,neck = null,navel =null,hand = null,handmove = null;	
	private boolean neckflag = false,handflag = false,navelflag = false,handmoveflag = false;

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
