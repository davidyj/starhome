package com.example.nodes;

import java.util.ArrayList;
import java.util.HashMap;

import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.opengl.Texture2D;

import android.graphics.Bitmap;

public class CCharacterFrame {	 

	public CCharacterFrame(String frame) {
		this.frame = frame;
	}

	public static CCharacterFrame create(String frame){
		return new CCharacterFrame(frame);
	}
		
	private CocosNode layer;	
	private String frame = null;
	public CCharacterSprite sprites = CCharacterSprite.create();
	
}
