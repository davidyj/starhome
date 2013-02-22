package com.example.sample_character;

import java.util.ArrayList;

import org.cocos2d.layers.ColorLayer;
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

	protected CGameLayer(CCColor4B color) {
		super(color);
		
		// TODO Auto-generated constructor stub		
		this.setIsTouchEnabled(true);
		
		_targets = new ArrayList<Sprite>();
		_projectiles = new ArrayList<Sprite>();
		_projectilesDestroyed = 0;
		
		CCSize winSize = Director.sharedDirector().displaySize();
		Sprite player = Sprite.sprite("character_00002000_alert_0_body.png");
		
		player.setPosition( player.getWidth() / 2.0f, winSize.height / 2.0f);
		
		addChild(player);
		
		// Handle sound
		Context context = Director.sharedDirector().getActivity();		
		
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
