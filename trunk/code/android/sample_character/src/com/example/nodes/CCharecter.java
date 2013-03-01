package com.example.nodes;

import java.util.ArrayList;
import java.util.HashMap;


import org.cocos2d.actions.base.RepeatForever;
import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.types.CCPoint;
import com.example.actions.interval.CCharacterAnimate;
public class CCharecter  {	
	
	public static CCharecter create(){
		return new CCharecter();
	}
	
	public CCharecter() {		
	}
	
	public void init() {	
		sprites.Init();
		//<p name="body"  origin_x="16" origin_y="29" neck_x="-4"   neck_y="-29" navel_x="-3" navel_y="-18" z="body" image="alert.0.body.png"/>
		//<p name="body" origin_x="16" origin_y="30" neck_x="-4" neck_y="-30" navel_x="-3" navel_y="-19" z="body" image="alert.1.body.png"/>
		//<p name="body" origin_x="16" origin_y="31" neck_x="-4" neck_y="-31" navel_x="-3" navel_y="-20" z="body" image="alert.2.body.png"/>
		
		//<p name="arm"   origin_x="6"  origin_y="8"  navel_x="-11" navel_y="1"  hand_x="-5" hand_y="5" z="armOverHair" image="alert.0.arm.png"/>
		//<p name="arm"   origin_x="7" origin_y="8" navel_x="-11" navel_y="1" hand_x="-6" hand_y="6" z="armOverHair" image="alert.1.arm.png"/>
		//<p name="arm"   origin_x="6" origin_y="10" navel_x="-11" navel_y="-1" hand_x="-5" hand_y="5" z="armOverHair" image="alert.2.arm.png"/>
		
		//<p name="lHand" origin_x="15" origin_y="24" handMove_x="-11" handMove_y="-20" z="handBelowWeapon" image="alert.0.lHand.png"/>
		//<p name="lHand" origin_x="15" origin_y="23" handMove_x="-13" handMove_y="-19" z="handBelowWeapon" image="alert.1.lHand.png"/>
		//<p name="lHand" origin_x="15" origin_y="22" handMove_x="-15" handMove_y="-17" z="handBelowWeapon" image="alert.2.lHand.png"/>
		/*
		//body 24 * 29
		CCharacterPart bodySprite1 = CCharacterPart.create("body","img/character/00002000/alert.0.body.png");
		bodySprite1.setOrigin(CCPoint.make(16.0f,29.0f));
		bodySprite1.setNeck(CCPoint.make(-4.0f,-29.0f));
		bodySprite1.setNavel(CCPoint.make(-3.0f,-18.0f));
		bodySprite1.setZ("body");
		
		
		// 24 * 30
		CCharacterPart bodySprite2 = CCharacterPart.create("body","img/character/00002000/alert.1.body.png");
		bodySprite2.setOrigin(CCPoint.make(16.0f,30.0f));
		bodySprite2.setNeck(CCPoint.make(-4.0f,-30.0f));
		bodySprite2.setNavel(CCPoint.make(-3.0f,-19.0f));
		bodySprite2.setZ("body");
		
		// 24 * 31
		CCharacterPart bodySprite3 = CCharacterPart.create("body","img/character/00002000/alert.2.body.png");
		bodySprite3.setOrigin(CCPoint.make(16.0f,31.0f));
		bodySprite3.setNeck(CCPoint.make(-4.0f,-31.0f));
		bodySprite3.setNavel(CCPoint.make(-3.0f,-20.0f));
		bodySprite3.setZ("body");
		
		//arm 8 * 14
		CCharacterPart armSprite1 = CCharacterPart.create("arm","img/character/00002000/alert.0.arm.png");
		armSprite1.setOrigin(CCPoint.make(6.0f,8.0f));		
		armSprite1.setNavel(CCPoint.make(-11.0f,1.0f));
		armSprite1.setHand(CCPoint.make(-5.0f,5.0f));
		armSprite1.setZ("armOverHair");
		//armSprite1.setAnchorPoint(1,0);
		
		// 8 * 15
		CCharacterPart armSprite2 = CCharacterPart.create("arm","img/character/00002000/alert.1.arm.png");
		armSprite2.setOrigin(CCPoint.make(7.0f,8.0f));		
		armSprite2.setNavel(CCPoint.make(-11.0f,1.0f));
		armSprite2.setHand(CCPoint.make(-6.0f,6.0f));
		armSprite2.setZ("armOverHair");
		//armSprite2.setAnchorPoint(1,0);
		
		// 7 * 16
		CCharacterPart armSprite3 = CCharacterPart.create("arm","img/character/00002000/alert.2.arm.png");
		armSprite3.setOrigin(CCPoint.make(6.0f,10.0f));		
		armSprite3.setNavel(CCPoint.make(-11.0f,-1.0f));
		armSprite3.setHand(CCPoint.make(-5.0f,5.0f));
		armSprite3.setZ("armOverHair");
		//armSprite3.setAnchorPoint(1,0);
		
		//hand 8 * 9
		CCharacterPart lhandSprite1 = CCharacterPart.create("hand","img/character/00002000/alert.0.lhand.png");
		assert lhandSprite1 != null : "add img/character/00002000/alert.0.lhand.png failed";
		lhandSprite1.setOrigin(CCPoint.make(15.0f,24.0f));		
		lhandSprite1.setHandmove(CCPoint.make(-11.0f,-20.0f));		
		lhandSprite1.setZ("handBelowWeapon");
		
		CCharacterPart lhandSprite2 = CCharacterPart.create("hand","img/character/00002000/alert.1.lhand.png");
		lhandSprite2.setOrigin(CCPoint.make(15.0f,23.0f));		
		lhandSprite2.setHandmove(CCPoint.make(-13.0f,-19.0f));		
		lhandSprite2.setZ("handBelowWeapon");
		
		CCharacterPart lhandSprite3 = CCharacterPart.create("hand","img/character/00002000/alert.2.lhand.png");
		lhandSprite3.setOrigin(CCPoint.make(15.0f,22.0f));		
		lhandSprite3.setHandmove(CCPoint.make(-15.0f,-17.0f));		
		lhandSprite3.setZ("handBelowWeapon");
		
		
		//frame
		CCharacterSprite sprites1 = CCharacterSprite.create();		
		sprites1.addSprite("body",bodySprite1);
		sprites1.addSprite("arm",armSprite1);		
		sprites1.addSprite("lhand", lhandSprite1);
		
		CCharacterSprite sprites2 = CCharacterSprite.create();		
		sprites2.addSprite("body",bodySprite2);
		sprites2.addSprite("arm",armSprite2);
		sprites2.addSprite("lhand", lhandSprite2);
		
		CCharacterSprite sprites3 = CCharacterSprite.create();		
		sprites3.addSprite("body",bodySprite3);
		sprites3.addSprite("arm",armSprite3);
		sprites3.addSprite("lhand", lhandSprite3);
		
		
		CCharacterFrame frames1 = CCharacterFrame.create("0");
		frames1.addSprites(sprites1);
		CCharacterFrame frames2 = CCharacterFrame.create("1");
		frames2.addSprites(sprites2);
		CCharacterFrame frames3 = CCharacterFrame.create("2");
		frames3.addSprites(sprites3);	
		
		//animation
		CCharacterAnimation animation = CCharacterAnimation.create("alter");		
		animation.addFrame(frames1);
		animation.addFrame(frames2);
		animation.addFrame(frames3);			
		
		//				
		addAnimate(animation);		
		*/
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
	
}
