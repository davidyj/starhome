package com.example.sample_map.map;

import org.cocos2d.nodes.TextureManager;
import org.cocos2d.nodes.TextureNode;
import org.cocos2d.opengl.Texture2D;
import org.cocos2d.types.CCPoint;
import org.cocos2d.types.CCVertex3D;

import android.util.Log;

public class CSampleMapTile extends TextureNode{
	
	public static CSampleMapTile create(){
		return new CSampleMapTile();
	}
	
	public String name = null;
	public String os = null,u=null,no=null,ts=null;
	public String l0 = null,l1 = null,l2 = null,path = null,img = null;
	public CCPoint point = CCPoint.ccp(0.0f, 0.0f);
	public CCPoint origin = CCPoint.ccp(0.0f, 0.0f); 
	public int f = 0,zm = 0,z=0;
	
	public void initTexture(String ts){		
		this.ts = ts;
		path = String.format("img/Map/Tile/%s.img/%s.%s.png",ts,u,no);			
		img = String.format("%s.%s.png", u,no);		
		Log.i("set texture",path);
		Texture2D t = TextureManager.sharedTextureManager().addImage(path); 
		setTexture(t);			
	}
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
		}
		else if("x".equals(key)){
			point.x = Float.valueOf(value);
		}
		else if("y".equals(key)){
			point.y = Float.valueOf(value);
		}
		else if("z".equals(key)){
			z = Integer.valueOf(value);
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
			origin.y = Float.valueOf(value);
		}		
		else if("img".equals(key)){
			img = value;
		}
		else if("no".equals(key)){
			no = value;			
		}
		else if("u".equals(key)){
			u = value;
		}
		else if("tS".equals(key)){
			ts = value;
		}
	}
}


