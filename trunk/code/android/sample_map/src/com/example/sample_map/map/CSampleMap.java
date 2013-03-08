package com.example.sample_map.map;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.microedition.khronos.opengles.GL10;
import javax.xml.parsers.ParserConfigurationException;

import org.cocos2d.layers.ColorLayer;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.types.CCColor4B;
import org.xml.sax.SAXException;

import android.util.Log;

import com.example.core.CCore;
import com.example.sample_map.xml.CSampleMapXml;

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
	}
	
	private ArrayList<CSampleMapLayer> layers = new ArrayList<CSampleMapLayer>();	
	private HashMap<String,CSampleMapObj> objs = new HashMap<String,CSampleMapObj>();
	private CSampleMapObj currentObj = null;
	private int map_top = 0,map_bottom = 0,map_left = 0,map_right = 0,map_width=0,map_height = 0,map_centerX = 0,map_centerY = 0;
	
	public void addObj(int layerid,CSampleMapObj obj) throws SAXException, ParserConfigurationException, IOException{		
		CSampleMapLayer layer = layers.get(layerid);
		if(layer != null){			
			layer.addObj(obj);		
			
			obj.setAnchorPoint(CCore.getInstance().ORIGIN_LEFT_BOTTOM.x, CCore.getInstance().ORIGIN_LEFT_BOTTOM.y);
			
			currentObj = objs.get(obj.img);
			if(currentObj == null){
				String path = String.format("xml/Map/Obj/%s.xml",obj.os);
				CSampleMapXml.getInstance().readObj(objs, path);
			}
			currentObj = objs.get(obj.img);
			if(currentObj == null){
				Log.i("error add obj",obj.path);
				return;
			}
			
			if(obj.f == 0){
				obj.setPosition(obj.position.x + map_centerX - currentObj.origin.x,
								obj.position.y + map_centerY - currentObj.origin.y);
			}
			else{
				
			}
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
	
	public void setValue(String key,String value){
		if("VRTop".equals(key)){
			map_top = -Integer.valueOf(value);
		}
		else if("VRLeft".equals(key)){
			map_left = Integer.valueOf(value);
		}
		else if("VRBottom".equals(key)){
			map_bottom = -Integer.valueOf(value);
		}
		else if("VRRight".equals(key)){
			map_right = Integer.valueOf(value);
		}
	}
	
	public void setValueEnd(){
		map_width = map_right - map_left;
		map_height = map_top - map_bottom;
		map_centerX = -map_left;
		map_centerY = -map_top;
	}
	
	@Override
	public void draw(GL10 gl){
		super.draw(gl);
		//this.setPosition(this.getPositionX() + 0.01f, this.getPositionY() + 0.01f);
	}
	
}
