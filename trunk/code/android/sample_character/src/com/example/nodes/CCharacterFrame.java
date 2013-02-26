package com.example.nodes;

import java.util.ArrayList;
import java.util.HashMap;

import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.opengl.Texture2D;

import android.graphics.Bitmap;

public class CCharacterFrame {	 

	public static CCharacterFrame create(){
		return new CCharacterFrame();
	}
		
	private CocosNode layer;
	private String name;
	private byte frame = 0;
	public CCharacterSprite sprites = null;
	
	public void addSprites(CCharacterSprite sprites){
		this.sprites = sprites;
	}
	
}
