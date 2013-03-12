package com.example.sample_map.map;

import org.cocos2d.nodes.TextureManager;
import org.cocos2d.nodes.TextureNode;
import org.cocos2d.opengl.Texture2D;
import org.cocos2d.types.CCPoint;
import org.cocos2d.types.CCVertex3D;

import android.util.Log;

public class CSampleMapObj extends TextureNode{
	
	public static CSampleMapObj create(){
		return new CSampleMapObj();
	}
	
	public String name = null;
	public String os = null;
	public String l0 = null,l1 = null,l2 = null,path = null,img = null;
	public CCVertex3D position = new CCVertex3D(0.0f, 0.0f, 0.0f);
	public CCVertex3D origin = new CCVertex3D(0.0f, 0.0f, 0.0f); 
	public int f = 0,zm = 0;
	
	public void setValue(String key,String value){
		if("name".equals(key)){
			name = value;
		}
		else if("oS".equals(key)){
			os = value;
		}
		else if("l0".equals(key)){
			l0 = value;
		}
		else if("l1".equals(key)){
			l1 = value;
		}
		else if("l2".equals(key)){
			l2 = value;			
			path = String.format("img/Map/Obj/%s.img/%s.%s.%s.0.png",os,l0,l1,l2);			
			img = String.format("%s.%s.%s.0.png", l0,l1,l2);
			Log.i("load img",path);
			Texture2D t = TextureManager.sharedTextureManager().addImage(path); 
			setTexture(t);			
		}
		else if("x".equals(key)){
			position.x = Float.valueOf(value);
		}
		else if("y".equals(key)){
			position.y = -Float.valueOf(value);		
		}
		else if("z".equals(value)){
			position.z = Float.valueOf(value);
		}
		else if("f".equals(key)){
			f = Integer.valueOf(value);
		}
		else if("zM".equals(key)){
			zm = Integer.valueOf(value);
		}
		else if("origin_x".equals(key)){
			origin.x = Float.valueOf(value);
		}
		else if("origin_y".equals(key)){
			origin.y = -Float.valueOf(value);
		}
		else if("origin_z".equals(key)){
			origin.z = Float.valueOf(value);
		}
		else if("img".equals(key)){
			img = value;
		}
	}
	public void setTexture(String filepath){
		setTexture(TextureManager.sharedTextureManager().addImage(filepath));
	}
}
