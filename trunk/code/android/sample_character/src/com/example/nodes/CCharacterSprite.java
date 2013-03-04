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
	
	private String 		  expresion = null;
	public CCharacterPart body = null;
	public CCharacterPart arm = null;	
	public CCharacterPart lhand = null;
	public CCharacterPart rhand = null;
	public CCharacterPart head = null;
	public CCharacterPart hair = null;
	public CCharacterPart face = null;
	public CCharacterPart tempFace = null;
	
	public void Init(){
		expresion = new String("blink");
		body = CCharacterPart.create("body","img/Character/00002000/alert.0.body.png");
		arm = CCharacterPart.create("arm","img/Character/00002000/alert.0.arm.png");	
		lhand = CCharacterPart.create("lhand","img/Character/00002000/alert.0.lHand.png");
		rhand = CCharacterPart.create("rhand","img/Character/00002000/alert.0.rHand.png");
		head = CCharacterPart.create("head","img/Character/00012000/front.head.png");
		hair = CCharacterPart.create("hair","img/Character/Hair/00030000/default.hairOverHead.png");
		face = CCharacterPart.create("face","img/Character/Face/00020000/default.face.png");
		
		this.addChild(body);	
		this.addChild(arm);
		this.addChild(lhand);
		this.addChild(rhand);
		this.addChild(head);
		this.addChild(hair);
		this.addChild(face);
		
		body.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		arm.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		lhand.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		rhand.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		head.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		hair.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		face.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
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
		if(null != rhand){
			rhand.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.rhand.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.rhand.Navel().y );
		}
		if(null != head){			
			head.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x, 
							 0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y);
		}		
		if(null != face){
			tempFace = CCharacterFace.getInstance().getNext(expresion, tempFace);
			face.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x + sprites.head.Brow().x - tempFace.Brow().x,
							 0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y + sprites.head.Brow().y - tempFace.Brow().y);
		}
		if(null != hair)
		{
			hair.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x + sprites.head.Brow().x - sprites.hair.Brow().x ,
							 0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y + sprites.head.Brow().y - sprites.hair.Brow().y);
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
		else if("head".equals(name))
			head = sprite;	
		else if("hair".equals(name))
			hair = sprite;
		
	}	
	
	
	public void setDisplayFrame(CCharacterSprite sprites){		
		this.body.setDisplayFrame(sprites.body);
		this.arm.setDisplayFrame(sprites.arm);		
		this.lhand.setDisplayFrame(sprites.lhand);
		this.rhand.setDisplayFrame(sprites.rhand);
		this.head.setDisplayFrame(sprites.head);
		this.hair.setDisplayFrame(sprites.hair);
		if(tempFace != null)
			this.face.setDisplayFrame(tempFace);
	}
	
	public void setExpresion(String expresion){
		this.expresion = expresion;
	}
}
