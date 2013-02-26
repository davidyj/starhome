package com.example.nodes;

import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.opengl.Texture2D;
import org.cocos2d.types.CCPoint;

import android.graphics.Bitmap;

public class CCharacterSprite extends CocosNode {
  public static CCharacterSprite create() {    	
        return new CCharacterSprite();
    }  
 
    
	protected CCharacterSprite() {		
		this.addChild(body);
		this.addChild(arm);
		this.addChild(lhand);
	}
	
	public CCharacterPart body = CCharacterPart.create("img/character/00002000/alert.0.body.png");
	public CCharacterPart arm = CCharacterPart.create("img/character/00002000/alert.0.arm.png");	
	public CCharacterPart lhand = CCharacterPart.create("img/character/00002000/alert.0.lhand.png");
	
	@Override
	public void setPosition(float x,float y){
		super.setPosition(x, y);	
	}

	public void resetPosition(CCharacterSprite sprites){
		
		if(sprites == null)
			return;			
		
		//
		if(null != body)
			body.setPosition(0, 0);
		
		if(null != arm){
			arm.setPosition(0 + sprites.body.Origin().x + sprites.body.Navel().x - sprites.arm.Navel().x - sprites.arm.Origin().x ,
								  0 + sprites.body.Origin().y + sprites.body.Navel().y - sprites.arm.Navel().y - sprites.arm.Origin().y);
		}
		
		if(null != lhand){
			lhand.setPosition(0,0);
		}
				
	}

	
	public void addSprite(String name,CCharacterPart sprite){
		if(name.equals("body"))
			body = sprite;
		else if(name.equals("arm"))
			arm = sprite;
		else if(name.equals("lhand"))
			lhand = sprite;
	}	
	
	
	public void setDisplayFrame(CCharacterSprite sprites){
		this.body.setDisplayFrame(sprites.body);
		this.arm.setDisplayFrame(sprites.arm);
		this.lhand.setDisplayFrame(sprites.lhand);
	}
	
}
