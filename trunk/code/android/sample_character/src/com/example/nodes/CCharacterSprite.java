package com.example.nodes;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.opengl.Texture2D;
import org.cocos2d.types.CCPoint;
import org.xml.sax.SAXException;

import com.example.core.CCore;
import com.example.xml.CCharacterXML;

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
	public CCharacterPart coat = null;
	public CCharacterPart mail = null;
	public CCharacterPart mailarm = null;
	public CCharacterPart lglove = null;
	public CCharacterPart rglove = null;
	public CCharacterPart pant = null;
	public CCharacterPart shield = null;
	public CCharacterPart shoes = null;
	public CCharacterPart weapon = null;
	
	public void init(){		
		expresion = new String("blink");		
		body = CCharacterPart.create();
		
		arm = CCharacterPart.create();	
		lhand = CCharacterPart.create();
		rhand = CCharacterPart.create();
		head = CCharacterPart.create();
		face = CCharacterPart.create("face","img/Character/Face/00020000/blink.0.face.png");		
		cap = CCharacterPart.create();
		cape = CCharacterPart.create();
		coat = CCharacterPart.create();
		mail = CCharacterPart.create();
		mailarm = CCharacterPart.create();
		lglove = CCharacterPart.create();
		rglove = CCharacterPart.create();
		pant = CCharacterPart.create();
		shield = CCharacterPart.create();
		shoes = CCharacterPart.create();
		weapon = CCharacterPart.create();	
			
		setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
	}
	
	public void setPart(){			
		if(null !=body)
			this.addChild(body);
		if(null != cape)
			this.addChild(cape);		
		if(null != coat)
			this.addChild(coat);
		if(null != arm)
			this.addChild(arm);
		if(null != head)
			this.addChild(head);
		if(null != hair)
			this.addChild(hair);
		if(null != face)
			this.addChild(face);		
		if(null != cap)
			this.addChild(cap);
		if(null != pant)
			this.addChild(pant);
		if(null != mail)
			this.addChild(mail);
		if(null != mailarm)
			this.addChild(mailarm);
		if(null != weapon)
			this.addChild(weapon);
		if(null != lhand)
			this.addChild(lhand);
		if(null != rhand)
			this.addChild(rhand);
		if(null != lglove)
			this.addChild(lglove);
		if(null != rglove)
			this.addChild(rglove);		
		if(null != shield)
			this.addChild(shield);
		if(null != shoes)
			this.addChild(shoes);			
	}
	public void unsetPart()
	{		
		if(null != body)
			this.removeChild(body,true);
		if(null != cape)
			this.removeChild(cape,true);
		if(null != coat)
			this.removeChild(coat,true);
		if(null != arm)
			this.removeChild(arm,false);
		if(null != head)
			this.removeChild(head,false);
		if(null != hair)
			this.removeChild(hair,false);
		if(null != face)
			this.removeChild(face,false);
		if(null != cap)
			this.removeChild(cap,true);		
		if(null != pant)
			this.removeChild(pant,true);
		if(null != mail)
			this.removeChild(mail,true);
		if(null != mailarm)
			this.removeChild(mailarm,true);
		if(null != weapon)
			this.removeChild(weapon,true);
		if(null != lhand)
			this.removeChild(lhand,true);
		if(null != rhand)
			this.removeChild(rhand,true);
		if(null != lglove)
			this.removeChild(lglove,true);
		if(null != rglove)
			this.removeChild(rglove,true);	
		if(null != shield)
			this.removeChild(shield,true);
		if(null != shoes)
			this.removeChild(shoes,true);			
	}
	
	public void setPart(CCharecter character,String part ,String img) throws ParserConfigurationException, SAXException, IOException{
		if("Hat".equals(part)){		
			CCharacterXML.getInstance().readCap(character, String.format("xml/%s.xml",img));
		}
		else if("Top".equals(part)){
			CCharacterXML.getInstance().readCoat(character, String.format("xml/%s.xml",img));
		}
		else if("Bottom".equals(part)){
			CCharacterXML.getInstance().readPant(character,  String.format("xml/%s.xml",img));
		}
		else if("Gloves".equals(part)){
			CCharacterXML.getInstance().readGlove(character, String.format("xml/%s.xml",img));
		}
		else if("Shield".equals(part)){
			CCharacterXML.getInstance().readShield(character, String.format("xml/%s.xml",img));
		}
		else if("Shoes".equals(part)){
			CCharacterXML.getInstance().readShoes(character, String.format("xml/%s.xml",img));
		}
		else if("Overall".equals(part)){
			CCharacterXML.getInstance().readCoat(character, String.format("xml/%s.xml",img));
		}
		
	}
	
	
	public void setAnchorPoint(float x,float y)
	{
		if(null != body)
			body.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != arm)
			arm.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != lhand)
			lhand.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != rhand)
			rhand.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != head)
			head.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != hair)
			hair.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != face)
			face.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != cap)
			cap.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != cape)
			cape.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != coat)
			coat.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != mail)
			mail.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != mailarm)
			mailarm.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != lglove)
			lglove.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != rglove)
			rglove.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != pant)
			pant.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != shield)
			shield.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != shoes)
			shoes.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		if(null != weapon)
			weapon.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x,CCore.ORIGIN_LEFT_TOP.y);
		
	}
	
	public void resetPosition(CCharacterSprite sprites){
		
		if(sprites == null || sprites.body == null)
			return;
		
		
		//
		if(null != body ){
			body.setPosition(0 - sprites.body.Origin().x , 0 - sprites.body.Origin().y);			
		}		
		
		
		if(null != arm && null != sprites.arm){
			arm.setPosition(0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.arm.Navel().x  ,
							0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.arm.Navel().y );
			
		}		
		if(null != lhand && null != sprites.lhand){
			lhand.setPosition(0  - sprites.lhand.Origin().x , 0 - sprites.lhand.Origin().y);
		}						
		if(null != rhand && null != sprites.rhand){
			rhand.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.rhand.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.rhand.Navel().y );
		}
		if(null != head && null != sprites.head){			
			head.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x, 
							 0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y);
		}		
		if(null != face && null != sprites.head ){
			tempFace = CCharacterFace.getInstance().getNext(expresion, tempFace);
			face.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x + sprites.head.Brow().x - tempFace.Brow().x,
							 0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y + sprites.head.Brow().y - tempFace.Brow().y);
		}
		if(null != hair && null != sprites.head && null != sprites.hair)
		{
			hair.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x + sprites.head.Brow().x - sprites.hair.Brow().x ,
							 0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y + sprites.head.Brow().y - sprites.hair.Brow().y);
		}
		if(null != cap && null != sprites.head  && null != sprites.cap){
			cap.setPosition(0 - sprites.body.Origin().x - sprites.head.Neck().x + sprites.body.Neck().x + sprites.head.Brow().x - sprites.cap.Brow().x ,
							0 - sprites.body.Origin().y - sprites.head.Neck().y + sprites.body.Neck().y + sprites.head.Brow().y - sprites.cap.Brow().y);
		}
		if(null != mail && null != sprites.mail){
			mail.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.mail.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.mail.Navel().y );
		}
		if(null != mailarm && null != sprites.mailarm){
			mailarm.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.mailarm.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.mailarm.Navel().y );
		}
		if(null != cape && null != sprites.cape){
			cape.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.cape.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.cape.Navel().y );
		}
		if(null != lglove && null != sprites.lhand && null != sprites.lglove){
			if(sprites.lglove.HandMove().x != 0.0f || sprites.lglove.HandMove().y != 0.0f){
				lglove.setPosition(0 - sprites.lhand.Origin().x, 0 - sprites.lhand.Origin().y);
			}
			else{
				lglove.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.lglove.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.lglove.Navel().y );
			}
		}
		if(null != rglove && null != sprites.rglove){
			if(sprites.rglove.HandMove().x != 0.0f || sprites.rglove.HandMove().y != 0.0f){
				lglove.setPosition(0 - sprites.lhand.Origin().x, 0 - sprites.lhand.Origin().y);
			}
			else{
				rglove.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.rglove.Navel().x  ,
									0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.rglove.Navel().y );
			}
		}		
		if(null != pant && null != sprites.pant){
			pant.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.pant.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.pant.Navel().y );
		}
		if(null != shield && null != sprites.shield){
			shield.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.shield.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.shield.Navel().y );
		}
		if(null != shoes && null != sprites.shoes){
			shoes.setPosition(	0 - sprites.body.Origin().x + sprites.body.Navel().x - sprites.shoes.Navel().x  ,
								0 - sprites.body.Origin().y + sprites.body.Navel().y - sprites.shoes.Navel().y );
		}
		if(null != weapon && null != sprites.weapon){
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
			this.body = sprite;		
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
		else if("coat".equals(name))
			coat = sprite;
		else if("pant".equals(name))
			pant = sprite;
		else if("mail".equals(name))
			mail = sprite;
		else if("mailArm".equals(name))
			mailarm = sprite;
		else if("lGlove".equals(name))
			lglove = sprite;
		else if("rGlove".equals(name))
			rglove = sprite;		
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
		
		if(null != this.body && sprites.body != null)
			this.body.setDisplayFrame(sprites.body);		
		if(sprites.cape != null)
			this.cape.setDisplayFrame(sprites.cape);
		
		if(sprites.coat != null)
			this.coat.setDisplayFrame(sprites.coat);			
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
