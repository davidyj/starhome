package com.example.sample_map.map;

import org.cocos2d.nodes.TextureNode;
import org.cocos2d.types.CCVertex3D;

public class CSampleMapTile extends TextureNode{
	
	public static CSampleMapTile create(){
		return new CSampleMapTile();
	}
	
	public String name = null;
	public String os = null;
	public String l0 = null,l1 = null,l2 = null;
	public CCVertex3D position = null;
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
		}
		else if("x".equals(key)){
			position.x = Float.valueOf(value);
		}
		else if("y".equals(key)){
			position.y = Float.valueOf(value);
		}
		else if("z".equals(value)){
			position.z = Float.valueOf(value);
			
			this.setPosition(position.x, position.y);
		}
		else if("f".equals(key)){
			f = Integer.valueOf(value);
		}
		else if("zM".equals(key)){
			zm = Integer.valueOf(value);
		}
	}
}


