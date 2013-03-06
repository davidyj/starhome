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
	public CCharacterPart cap = null;
	public CCharacterPart cape = null;
	public CCharacterPart mail = null;
	public CCharacterPart mailarm = null;
	public CCharacterPart lglove = null;
	public CCharacterPart rglove = null;
	public CCharacterPart pant = null;
	public CCharacterPart shield = null;
	public CCharacterPart shoes = null;
	public CCharacterPart weapon = null;
	
	public void Init(){
		expresion = new String("blink");
		body = CCharacterPart.create("body","img/Character/00002000/alert.0.body.png");
		arm = CCharacterPart.create("arm","img/Character/00002000/alert.0.arm.png");	
		lhand = CCharacterPart.create("lhand","img/Character/00002000/alert.0.lHand.png");
		rhand = CCharacterPart.create("rhand","img/Character/00002000/alert.0.rHand.png");
		head = CCharacterPart.create("head","img/Character/00012000/front.head.png");
		hair = CCharacterPart.create("hair","img/Character/Hair/00030000/default.hairOverHead.png");
		face = CCharacterPart.create("face","img/Character/Face/00020000/default.face.png");
		cap = CCharacterPart.create("cap","img/Character/Cap/01000000/default.default.png");
		cape = CCharacterPart.create("cape","img/Character/Cape/01102000/alert.0.cape.png");
		mail = CCharacterPart.create("mail","img/Character/Coat/01040000/alert.0.mail.png");
		mailarm = CCharacterPart.create("mailArm","img/Character/Coat/01040000/alert.0.mailArm.png");
		lglove = CCharacterPart.create("lGrove","img/Character/Glove/01080000/alert.0.lGlove.png");
		rglove = CCharacterPart.create("rGlove","img/Character/Glove/01080000/alert.0.rGlove.png");
		pant = CCharacterPart.create("pant","img/Character/Pants/01060000/alert.0.pants.png");
		shield = CCharacterPart.create("shield","img/Character/Shield/01092000/alert.0.shield.png");
		shoes= CCharacterPart.create("shoes","img/Character/Shoes/01070000/alert.0.shoes.png");
		weapon= CCharacterPart.create("weapon","img/Character/Weapon/01302000/alert.0.weapon.png");
	
		
		this.addChild(cape);
		this.addChild(body);	
		this.addChild(arm);		
		this.addChild(head);
		this.addChild(hair);
		this.addChild(face);
		this.addChild(cap);
		this.addChild(mail);
		this.addChild(mailarm);
		this.addChild(weapon);
		this.addChild(lhand);
		this.addChild(rhand);
		this.addChild(lglove);
		this.addChild(rglove);
		this.addChild(pant);
		this.addChild(shield);
		this.addChild(shoes);
		
		
		
		body.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		arm.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		lhand.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		rhand.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		head.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		hair.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		face.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		cap.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		cape.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		mail.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		mailarm.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		lglove.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		rglove.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		pant.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		shield.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		shoes.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
		weapon.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_TOP.x,CCore.getInstance().ORIGIN_LEFT_TOP.y);
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
		if(null != cap){
			cap.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x + sprites.head.Brow().x - sprites.cap.Brow().x ,
							0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y + sprites.head.Brow().y - sprites.cap.Brow().y);
		}
		if(null != mail){
			mail.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.mail.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.mail.Navel().y );
		}
		if(null != mailarm){
			mailarm.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.mailarm.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.mailarm.Navel().y );
		}
		if(null != cape){
			cape.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.cape.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.cape.Navel().y );
		}
		if(null != lglove){
			if(sprites.lglove.HandMove().x != 0.0f || sprites.lglove.HandMove().y != 0.0f){
				lglove.setPosition(0 - sprites.lhand.Origin().x, 0 - sprites.lhand.Origin().y);
			}
			else{
				lglove.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.lglove.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.lglove.Navel().y );
			}
		}
		if(null != rglove){
			if(sprites.rglove.HandMove().x != 0.0f || sprites.rglove.HandMove().y != 0.0f){
				lglove.setPosition(0 - sprites.lhand.Origin().x, 0 - sprites.lhand.Origin().y);
			}
			else{
				rglove.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.rglove.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.rglove.Navel().y );
			}
		}		
		if(null != pant){
			pant.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.pant.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.pant.Navel().y );
		}
		if(null != shield){
			shield.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.shield.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.shield.Navel().y );
		}
		if(null != shoes){
			shoes.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.shoes.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.shoes.Navel().y );
		}
		if(null != weapon){
			if(sprites.weapon.Hand().x != 0.0f | sprites.weapon.Hand().y != 0.0f){
				weapon.setPosition( 0 - sprites.body.Origin().x - sprites.arm.Navel().x + sprites.body.Navel().x + sprites.arm.Hand().x - sprites.weapon.Hand().x ,
									0 - sprites.body.Origin().y - sprites.arm.Navel().y + sprites.body.Navel().y + sprites.arm.Hand().y - sprites.weapon.Hand().y );
			}
			else{
				weapon.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.weapon.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.weapon.Navel().y );
			}
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
		else if("cap".equals(name))
			cap = sprite;
		else if("cape".equals(name))
			cape = sprite;
		else if("mail".equals(name))
			mail = sprite;
		else if("mailArm".equals(name))
			mailarm = sprite;
		else if("lGlove".equals(name))
			lglove = sprite;
		else if("rGlove".equals(name))
			rglove = sprite;
		else if("pant".equals(name))
			pant = sprite;
		else if("shield".equals(name))
			shield = sprite;
		else if("shoes".equals(name))
			shoes = sprite;
		else if("weapon".equals(name))
			weapon = sprite;
		
	}		
	
	public void setDisplayFrame(CCharacterSprite sprites){
		if( null == sprites )
			return;
		if(sprites.cape != null)
			this.cape.setDisplayFrame(sprites.cape);
		
		if(sprites.body != null)
			this.body.setDisplayFrame(sprites.body);
		
		if(sprites.arm != null)
			this.arm.setDisplayFrame(sprites.arm);
		
		if(sprites.lhand != null)
			this.lhand.setDisplayFrame(sprites.lhand);
		
		if(sprites.rhand != null)
			this.rhand.setDisplayFrame(sprites.rhand);
		
		if( sprites.head != null)
			this.head.setDisplayFrame(sprites.head);
		
		if(sprites.hair != null)
			this.hair.setDisplayFrame(sprites.hair);
		
		if(tempFace != null)
			this.face.setDisplayFrame(tempFace);
		
		if(sprites.cap != null)
			this.cap.setDisplayFrame(sprites.cap);
		
		if(sprites.mail != null)
			this.mail.setDisplayFrame(sprites.mail);
		
		if(sprites.mailarm != null)
			this.mailarm.setDisplayFrame(sprites.mailarm);
		
		if(sprites.lglove != null )
			this.lglove.setDisplayFrame(sprites.lglove);
		
		if(sprites.rglove != null)
			this.rglove.setDisplayFrame(sprites.rglove);
		
		if(sprites.pant != null)
			this.pant.setDisplayFrame(sprites.pant);
		
		if(sprites.shield != null )
			this.shield.setDisplayFrame(sprites.shield);
		
		if(sprites.shoes != null )
			this.shoes.setDisplayFrame(sprites.shoes);
		
		if(sprites.weapon != null )
			this.weapon.setDisplayFrame(sprites.weapon);
	}
	
	public void setExpresion(String expresion){
		this.expresion = expresion;
	}
}
