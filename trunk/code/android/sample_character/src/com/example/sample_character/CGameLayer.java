package com.example.sample_character;

import java.io.IOException;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;
import javax.xml.parsers.ParserConfigurationException;

import org.cocos2d.layers.ColorLayer;
import org.cocos2d.nodes.Director;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.Scene;
import org.cocos2d.opengl.Primitives;
import org.cocos2d.types.CCColor4B;
import org.cocos2d.types.CCPoint;
import org.cocos2d.types.CCSize;
import org.xml.sax.SAXException;

import com.example.core.CCore;
import com.example.nodes.CCharecter;
import com.example.xml.CCharacterXML;


public class CGameLayer extends ColorLayer {
	private CCSize winSize;
	protected CGameLayer(CCColor4B color) throws SAXException, ParserConfigurationException, IOException {
		super(color);
		
		// TODO Auto-generated constructor stub		
		this.setIsTouchEnabled(true);		
			
		winSize = Director.sharedDirector().displaySize();
		CCore.getInstance().GamePoint.x = 0;
		CCore.getInstance().GamePoint.x = -winSize.height;
		
		CCharacterXML.getInstance().readSuit("xml/suit.xml");
		CCharacterXML.getInstance().readFace( "xml/Character/Face/00020000.xml");
		
		//CCharecter player = CCharecter.create();		
		CCharecter player = CCharacterXML.getInstance().readBody( "xml/Character/00002000.xml");
		CCharacterXML.getInstance().readHead( player, "xml/Character/00012000.xml");
		
		player.init();		
		player.setSuit("11");			
		player.setPosition( winSize.width / 2.0f, winSize.height / 2.0f);
		
		this.addChild(player.sprites);		
		
		player.SetAction("alert");		
		
		this.schedule("gameLogic", 1.0f);
		this.schedule("update");
	}

	private CCharecter CCharecter() {
		// TODO Auto-generated method stub
		return null;
	}

	protected ArrayList<Sprite> _targets;
	protected ArrayList<Sprite> _projectiles;
	protected int _projectilesDestroyed;

	public static Scene scene() throws SAXException, ParserConfigurationException, IOException
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
	
	 @Override
	 public void draw(GL10 gl) {
		 super.draw(gl);
		 
		  gl.glEnable(GL10.GL_LINE_SMOOTH);
		  gl.glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		  gl.glLineWidth(0.5f);		     
          Primitives.drawLine(gl, CCPoint.ccp(0,winSize.height/2), CCPoint.ccp(winSize.width, winSize.height/2));
          Primitives.drawLine(gl, CCPoint.ccp(winSize.width/2,0), CCPoint.ccp(winSize.width/2, winSize.height));
	 
	 }
	
}
