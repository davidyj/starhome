package com.example.sample_character;

import java.util.ArrayList;

import org.cocos2d.actions.base.RepeatForever;
import org.cocos2d.actions.interval.Animate;
import org.cocos2d.layers.ColorLayer;
import org.cocos2d.nodes.Animation;
import org.cocos2d.nodes.Director;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.Scene;
import org.cocos2d.layers.Layer;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.types.CCColor4B;
import org.cocos2d.types.CCPoint;
import org.cocos2d.types.CCSize;


import android.content.Context;


public class CGameLayer extends ColorLayer {

	private CPlayerSprite player;
	private Animate alter;
	
	protected CGameLayer(CCColor4B color) {
		super(color);
		
		// TODO Auto-generated constructor stub		
		this.setIsTouchEnabled(true);		
			
		CCSize winSize = Director.sharedDirector().displaySize();		
		player = new CPlayerSprite("character_00002000_alert_0_body.png");			
		player.sprite.setPosition( winSize.width / 2.0f, winSize.height / 2.0f);		
		
		addChild(player.sprite);					
		
		player.SetAction("fly");
		
		//Animation player_action_alter = new Animation("alter",1.0f / 2.0f);		
		//alter = Animate.action(player_action_alter);		
		//player.runAction(RepeatForever.action(alter));
		
		
		this.schedule("gameLogic", 1.0f);
		this.schedule("update");
	}

	protected ArrayList<Sprite> _targets;
	protected ArrayList<Sprite> _projectiles;
	protected int _projectilesDestroyed;

	public static Scene scene()
	{
		Scene scene = Scene.node();
		ColorLayer layer = new CGameLayer(new CCColor4B(255, 255, 255, 255));
		
		scene.addChild(layer);
		
		return scene;
	}
	
	public void gameLogic(float dt)
	{
		
	}	
	
	public void update(float dt)
	{
	}
	
}
