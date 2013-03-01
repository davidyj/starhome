package com.example.nodes;

import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.opengl.Texture2D;
import org.cocos2d.types.CCPoint;

import com.example.core.CCore;

import android.graphics.Bitmap;
import android.util.Log;

public class CCharacterSprite extends CocosNode {
  public static CCharacterSprite create() {    	
        return new CCharacterSprite();
    }  
 
    
	protected CCharacterSprite() {				
		
	}
	
	public CCharacterPart body = null;
	public CCharacterPart arm = null;	
	public CCharacterPart lhand = null;
	public CCharacterPart rhand = null;	
	
	public void Init(){
		body = CCharacterPart.create("body","img/character/00002000/alert.0.body.png");
		arm = CCharacterPart.create("arm","img/character/00002000/alert.0.arm.png");	
		lhand = CCharacterPart.create("lhand","img/character/00002000/alert.0.lHand.png");
		rhand = CCharacterPart.create("lhand","img/character/00002000/alert.0.rHand.png");
		
		this.addChild(body);	
		this.addChild(arm);
		this.addChild(lhand);
		this.addChild(rhand);
		
		body.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		arm.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		lhand.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		rhand.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
	}

	public void resetPosition(CCharacterSprite sprites){
		
		if(sprites == null)
			return;
		
		//
		if(null != body){
			body.setPosition(0 - sprites.body.Origin().x , 0 - sprites.body.Origin().y);			
		}
		
		
		if(null != arm){
			arm.setPosition(0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.arm.Navel().x  ,
							0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.arm.Navel().y );
			
		}
		
		if(null != lhand){
			lhand.setPosition(0  - sprites.lhand.Origin().x , 0 - sprites.lhand.Origin().y);
		}				
		
		if(null != rhand)
		{
			rhand.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.rhand.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.rhand.Navel().y );
		}
	}
	
	
	public void addSprite(String name,CCharacterPart sprite){
		if("body".equals(name))
			body = sprite;
		else if("arm".equals(name))
			arm = sprite;
		else if("lHand".equals(name))
			lhand = sprite;
		else if("rHand".equals(name))
			rhand = sprite;
	}	
	
	
	public void setDisplayFrame(CCharacterSprite sprites){		
		this.body.setDisplayFrame(sprites.body);
		this.arm.setDisplayFrame(sprites.arm);		
		this.lhand.setDisplayFrame(sprites.lhand);
	}
	
}
