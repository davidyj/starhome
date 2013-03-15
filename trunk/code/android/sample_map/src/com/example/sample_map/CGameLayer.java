package com.example.sample_map;

import java.io.IOException;
import javax.xml.parsers.ParserConfigurationException;

import org.cocos2d.layers.ColorLayer;
import org.cocos2d.nodes.Scene;
import org.cocos2d.types.CCColor4B;
import org.xml.sax.SAXException;

import com.example.sample_map.map.CSampleMap;
import com.example.sample_map.xml.CSampleMapXml;


public class CGameLayer extends ColorLayer {
	
	protected CGameLayer(CCColor4B color) throws SAXException, ParserConfigurationException, IOException {
		super(color);
		this.setIsTouchEnabled(true);
		
	}
	
	public static Scene scene() throws SAXException, ParserConfigurationException, IOException
	{
		Scene scene = Scene.node();
		CSampleMap map = CSampleMapXml.getInstance().read("xml/105040400.xml");
		
		//map.setPosition(-2848.0f,-5.0f);
		map.init();
		
		scene.addChild(map);		
		
		return scene;
	}	

}
