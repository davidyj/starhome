package com.example.sample_map.map;

import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

import org.cocos2d.layers.ColorLayer;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.types.CCColor4B;

public class CSampleMap extends ColorLayer{
	
	public static CSampleMap create(){
		return new CSampleMap(new CCColor4B(255,255,255,255));
	}
	
	public CSampleMap(CCColor4B color){
		super(color);
		
		for(int i = 0;i<7;i++)
		{
			CSampleMapLayer layer = CSampleMapLayer.create();
			layers.add(layer);
		}
		
		//Sprite node = Sprite.sprite("img/Map/Obj/tutorial_jp.img/common.tile.0.0.png");
		CSampleMapObj obj = CSampleMapObj.create();
		obj.setTexture("img/Map/Obj/tutorial_jp.img/common.tile.0.0.png");
		obj.setPosition(10.0f,10.0f);
		this.addChild(obj);
	}
	
	private ArrayList<CSampleMapLayer> layers = new ArrayList<CSampleMapLayer>();	
	
	public void addObj(int layerid,CSampleMapObj obj){		
		CSampleMapLayer layer = layers.get(layerid);
		if(layer != null){			
			layer.addObj(obj);			
			this.addChild(obj);
		}
	}
	
	public void addTile(int layerid,CSampleMapTile tile){
		CSampleMapLayer layer = layers.get(layerid);
		if(layer != null){
			layer.addTile(tile);
			this.addChild(tile);
		}
	}
	
	@Override
	public void draw(GL10 gl){
		super.draw(gl);
		//this.setPosition(this.getPositionX() + 0.01f, this.getPositionY() + 0.01f);
	}
	
}
