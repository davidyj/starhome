package com.example.sample_map.map;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.microedition.khronos.opengles.GL10;
import javax.xml.parsers.ParserConfigurationException;

import org.box2d.collision.shapes.BBPolygonShape;
import org.box2d.common.BBVec2;
import org.box2d.dynamics.BBBody;
import org.box2d.dynamics.BBWorld;
import org.box2d.dynamics.BBBody.BBBodyDef;
import org.box2d.dynamics.BBFixture.BBFixtureDef;
import org.box2d.dynamics.BBWorldCallbacks.BBDebugDraw;
import org.cocos2d.actions.interval.MoveTo;
import org.cocos2d.actions.interval.RotateTo;
import org.cocos2d.box2d.GLESDebugDraw;
import org.cocos2d.events.TouchDispatcher;
import org.cocos2d.layers.ColorLayer;
import org.cocos2d.nodes.AtlasSprite;
import org.cocos2d.nodes.AtlasSpriteManager;
import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.Director;
import org.cocos2d.nodes.Scene;
import org.cocos2d.nodes.Sprite;
import org.cocos2d.nodes.TextureManager;
import org.cocos2d.types.CCColor4B;
import org.cocos2d.types.CCMacros;
import org.cocos2d.types.CCPoint;
import org.cocos2d.types.CCRect;
import org.cocos2d.types.CCSize;
import org.cocos2d.types.CCVertex3D;
import org.jbox2d.collision.AABB;
import org.jbox2d.collision.shapes.EdgeChainDef;
import org.jbox2d.collision.shapes.PolygonDef;
import org.jbox2d.common.Vec2;
import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.BodyDef;
import org.jbox2d.dynamics.World;
import org.xml.sax.SAXException;

import android.util.Log;
import android.view.MotionEvent;

import com.example.core.CCore;
import com.example.sample_map.xml.CSampleMapXml;

public class CSampleMap extends ColorLayer{
	
	 public static final int kTagSpriteManager = 1;
 	
		// Pixel to meters ratio. Box2D uses meters as the unit for measurement.
		// This ratio defines how many pixels correspond to 1 Box2D "meter"
		// Box2D is optimized for objects of 1x1 meter therefore it makes sense
		// to define the ratio so that your most common object type is 1x1 meter.
     protected static final float PTM_RATIO = 32.0f;
     
     // Simulation space should be larger than window per Box2D recommendation.
     protected static final float BUFFER = 1.0f;
     
     protected final World bxWorld;
     private Scene baseScene = Scene.node();
	public static CSampleMap create(){
		return new CSampleMap(new CCColor4B(255,255,255,255));
	}
	
	public CSampleMap(CCColor4B color){
		super(color);
		CCore.getInstance();
		this.addChild(baseScene);
		
		baseScene.setPosition(100.0f, 1492.0f); 
		baseScene.setAnchorPoint(CCore.ORIGIN_LEFT_BOTTOM.x, CCore.ORIGIN_LEFT_BOTTOM.y);
		
		this.isTouchEnabled_ = true;
     	this.isAccelerometerEnabled_ = true;    	
		
     	CCSize s = Director.sharedDirector().winSize();
        float scaledWidth = s.width/PTM_RATIO;
        float scaledHeight = s.height/PTM_RATIO;

    	Vec2 lower = new Vec2(-BUFFER, -BUFFER);
    	Vec2 upper = new Vec2(scaledWidth+BUFFER, scaledHeight+BUFFER);
    	Vec2 gravity = new Vec2(0.0f, -10.0f);
    	
    	bxWorld = new World(new AABB(lower, upper), gravity, true);     	
    	
        BodyDef bxGroundBodyDef = new BodyDef();
        bxGroundBodyDef.position.set(0.0f, 0.0f);
        
        Body bxGroundBody = bxWorld.createBody(bxGroundBodyDef);

        EdgeChainDef bxGroundOutsideEdgeDef = new EdgeChainDef();
        bxGroundOutsideEdgeDef.addVertex(new Vec2(0f,9f));
        bxGroundOutsideEdgeDef.addVertex(new Vec2(0f,scaledHeight));
        bxGroundOutsideEdgeDef.addVertex(new Vec2(scaledWidth,scaledHeight));
        bxGroundOutsideEdgeDef.addVertex(new Vec2(scaledWidth,9f));            
        bxGroundOutsideEdgeDef.addVertex(new Vec2(0f,9f));
        bxGroundBody.createShape(bxGroundOutsideEdgeDef);
        
        AtlasSpriteManager mgr = new AtlasSpriteManager("blocks.png", 150);
        baseScene.addChild(mgr, 0, kTagSpriteManager);        
        mgr.setAnchorPoint(CCore.ORIGIN_LEFT_BOTTOM.x, CCore.ORIGIN_LEFT_BOTTOM.y);
        
        //add layer
		//for(int i = 0;i<8;i++)
		//{
		//	CSampleMapLayer layer = CSampleMapLayer.create();
		//	layers.add(layer);
		//}	
		
		//addNewSpriteWithCoords(CCPoint.ccp(s.width / 2.0f, s.height / 2.0f));
		
		//schedule("tick");
		
	}
	
	private HashMap<Integer,CSampleMapLayer> layers = new HashMap<Integer,CSampleMapLayer>();	
	private HashMap<String,CSampleMapObj> objs = new HashMap<String,CSampleMapObj>();
	private HashMap<String,CSampleMapTile> tiles = new HashMap<String,CSampleMapTile>();
	private CSampleMapObj currentObj = null;
	private CSampleMapTile currentTile = null;
	private CCPoint movePoint = CCPoint.ccp(0.0f, 0.0f);
	private int map_top = 0,map_bottom = 0,map_left = 0,map_right = 0,map_width=0,map_height = 0,map_centerX = 0,map_centerY = 0;
	
	public CSampleMapLayer getLayer(int index){
		CSampleMapLayer layer = layers.get(index);
		if(null == layer){
			layer = CSampleMapLayer.create();
			layers.put(index,layer);		
		}
		return layer;
	}
	
	public void addObj(int layerIndex,CSampleMapObj obj) throws SAXException, ParserConfigurationException, IOException{
		obj.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x, CCore.ORIGIN_LEFT_TOP.y);
		
		currentObj = objs.get(obj.img);
		if(currentObj == null){
			String path = String.format("xml/Map/Obj/%s.xml",obj.os);
			CSampleMapXml.getInstance().readObj(objs, path);
		}
		currentObj = objs.get(obj.img);
		if(currentObj == null){
			Log.e("error add obj",obj.path);
			return;
		}
		
		if(obj.f == 0){
			obj.setPosition(obj.point.x + map_centerX - currentObj.origin.x,-(obj.point.y + map_centerY - currentObj.origin.y));
		}
		else{
			obj.setPosition(obj.point.x + map_centerX - obj.getWidth() , obj.point.y - map_centerY + currentObj.origin.y);
		}			
		
		//CSampleMapLayer layer = getLayer((int) (obj.z));
		CSampleMapLayer layer = getLayer(layerIndex);
		if(layer != null){			
			layer.addObj(obj);		
			//Log.i("add obj id",String.format("z = %d,zm = %d,z = %d",obj.z,obj.zm,currentObj.z));			
		}
	}
	
	public void addTile(int layerIndex,CSampleMapTile tile) throws SAXException, ParserConfigurationException, IOException{
		
		tile.setAnchorPoint(CCore.ORIGIN_LEFT_TOP.x, CCore.ORIGIN_LEFT_TOP.y);
		
		currentTile = tiles.get(tile.path);
		if(currentTile == null){
			String path = String.format("xml/Map/Tile/%s.xml",tile.ts);
			CSampleMapXml.getInstance().readTile(tiles, path,tile.ts);
		}
		currentTile = tiles.get(tile.path);
		if(currentTile == null){
			Log.e("error tile obj",tile.path);
			return;
		}
		
		if(tile.f == 0){
			tile.setPosition(tile.point.x + map_centerX - currentTile.origin.x,-(tile.point.y + map_centerY - currentTile.origin.y));				
		}
		else{
			tile.setPosition(tile.point.x + map_centerX - tile.getWidth(),-(tile.point.y + map_centerY - currentTile.origin.y));
		}	
		 
		
		//CSampleMapLayer layer = getLayer((int)(tile.zm + currentTile.z));
		CSampleMapLayer layer = getLayer(layerIndex);
		if(layer != null){
			layer.addTile(tile);		
			//Log.i("add tile id",String.format("z = %d,zm = %d,z = %d",tile.z,tile.zm,currentTile.z));		
		}
	}
	
	public void setValue(String key,String value){
		if("VRTop".equals(key)){
			map_top = Integer.valueOf(value);
		}
		else if("VRLeft".equals(key)){
			map_left = Integer.valueOf(value);
		}
		else if("VRBottom".equals(key)){
			map_bottom = Integer.valueOf(value);
		}
		else if("VRRight".equals(key)){
			map_right = Integer.valueOf(value);
		}
		else if("width".equals(key)){
			map_width = Integer.valueOf(value);
		}
		else if("height".equals(key)){
			map_height = Integer.valueOf(value);
			this.setContentSize(map_width, map_height);
			baseScene.setContentSize(map_width, map_height);
		}
		else if("centerX".equals(key)){
			map_centerX = Integer.valueOf(value);
		}
		else if("centerY".equals(key)){
			map_centerY = Integer.valueOf(value);
			baseScene.setPosition(map_centerX, map_centerY);
		}
	}
	
	public void setValueEnd(){
		map_width = map_right - map_left;
		map_height = -(map_top - map_bottom);
		map_centerX = -map_left;
		map_centerY = -map_top;
		
		
		this.setContentSize(map_width, map_height);
		//baseScene.setContentSize(map_width, map_height);
		baseScene.setPosition(map_centerX, map_centerY); 
	}	
	
	public void move(float x ,float y){
		this.setPosition(this.getPositionX() + x, this.getPositionY() - y);		
	}
	
	
	public void init(){
		for(int i=-10;i<50;i++){			
			CSampleMapLayer layer = layers.get(i);
			if(null != layer){
				for(CSampleMapObj obj : layer.objs()){
					baseScene.addChild(obj);		
					Log.i("CSampleMap add obj",String.format("layer = %d path = %s [%f,%f]",i,obj.path,obj.getPositionX(),obj.getPositionY()));
				}
				for(CSampleMapTile tile : layer.tiles()){
					baseScene.addChild(tile);
					Log.i("CSampleMap" ,String.format("layer = %d path = %s [%f %f]",i,tile.path,tile.getPositionX(),tile.getPositionY()));
				}					
			}
		}
		/*
		for(CSampleMapLayer layer:layers){
			for(CSampleMapTile tile : layer.tiles()){
				baseScene.addChild(tile);
			}					
		}
		*/		
	}
	
	private void addNewSpriteWithCoords(CCPoint pos) {
        AtlasSpriteManager mgr = (AtlasSpriteManager) baseScene.getChild(kTagSpriteManager);

    	// We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    	// just randomly picking one of the images
    	int idx = (CCMacros.CCRANDOM_0_1() > 0.5f ? 0:1);
    	int idy = (CCMacros.CCRANDOM_0_1() > 0.5f ? 0:1);
        AtlasSprite sprite = AtlasSprite.sprite(CCRect.make(idx * 32f, idy * 32f, 32f, 32f), mgr);
        mgr.addChild(sprite);
        Log.i("sprite tag",String.valueOf(sprite.getTag()));
        sprite.setAnchorPoint(CCore.ORIGIN_LEFT_BOTTOM.x, CCore.ORIGIN_LEFT_BOTTOM.y);
        sprite.setPosition(pos.x, pos.y);
        Log.i("add sprite",CCPoint.ccp(sprite.getPositionX(),sprite.getPositionY()).toString());
        Log.i("mgr point",CCPoint.ccp(mgr.getPositionX(),mgr.getPositionY()).toString());

    	// Define the dynamic body.
    	// Set up a 1m squared box in the physics world
    	BodyDef bxSpriteBodyDef = new BodyDef();
    	bxSpriteBodyDef.userData = sprite;
    	bxSpriteBodyDef.position.set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
    	bxSpriteBodyDef.linearDamping = 0.3f;
    	
    	// Define another box shape for our dynamic body.
    	PolygonDef bxSpritePolygonDef = new PolygonDef();
    	bxSpritePolygonDef.setAsBox(0.5f, 0.5f);
    	bxSpritePolygonDef.density = 1.0f;
    	bxSpritePolygonDef.friction = 0.3f;

    	synchronized (bxWorld) {
    		// Define the dynamic body fixture and set mass so it's dynamic.
    		Body bxSpriteBody = bxWorld.createBody(bxSpriteBodyDef);
    		bxSpriteBody.createShape(bxSpritePolygonDef);
    		bxSpriteBody.setMassFromShapes();
    	}
    }
	
	 public synchronized void tick(float delta) {
     	// It is recommended that a fixed time step is used with Box2D for stability
     	// of the simulation, however, we are using a variable time step here.
     	// You need to make an informed choice, the following URL is useful
     	// http://gafferongames.com/game-physics/fix-your-timestep/
     	
     	// Instruct the world to perform a simulation step. It is
     	// generally best to keep the time step and iterations fixed.
     	synchronized (bxWorld) {
     		bxWorld.step(delta, 10);
     	}
	        	
     	// Iterate over the bodies in the physics world
     	for (Body b = bxWorld.getBodyList(); b != null; b = b.getNext()) {
     		Object userData = b.getUserData();
     		
     		if (userData != null && userData instanceof AtlasSprite) {
     			// Synchronize the AtlasSprite position and rotation with the corresponding body
     			AtlasSprite sprite = (AtlasSprite)userData;
     			sprite.setPosition(b.getPosition().x * PTM_RATIO, b.getPosition().y * PTM_RATIO);
     			sprite.setRotation(-1.0f * CCMacros.CC_RADIANS_TO_DEGREES(b.getAngle()));     			
     		}	
     	}
     }
	@Override
    public void ccAccelerometerChanged(float accelX, float accelY, float accelZ) {
		// no filtering being done in this demo (just magnify the gravity a bit)
		Vec2 gravity = new Vec2( accelX * -2.00f, accelY * -2.00f );
		bxWorld.setGravity( gravity );
	}	
	@Override
	public boolean ccTouchesBegan(MotionEvent event){
	   int action = event.getActionMasked();
       switch (action) {
       case MotionEvent.ACTION_DOWN:
           Log.i("TAG", "ccTouchesBegan.ACTION_DOWN");
           movePoint.x = movePoint.y = 0.0f;
           break;
       case MotionEvent.ACTION_MOVE:
           Log.i("TAG", "ccTouchesBegan.ACTION_MOVE");
           Log.i("position",CCPoint.ccp(event.getX(), event.getY()).toString());
           break;
       case MotionEvent.ACTION_CANCEL:
       case MotionEvent.ACTION_UP:
           Log.i("TAG", "ccTouchesBegan.ACTION_UP");
           break;		           
       }
       return true;
	}
	
	@Override
	public boolean ccTouchesMoved(MotionEvent event){
	   int action = event.getActionMasked();
       switch (action) {
       case MotionEvent.ACTION_DOWN:
           Log.i("TAG", "ccTouchesMoved.ACTION_DOWN");
           break;
       case MotionEvent.ACTION_MOVE:
           Log.i("TAG", "ccTouchesMoved.ACTION_MOVE");
           Log.i("position",CCPoint.ccp(event.getX(), event.getY()).toString());
           if(movePoint.x == 0.0f && movePoint.y == 0.0f){
        	   movePoint.x = event.getX();
        	   movePoint.y = event.getY();
           }
           else{	        	   
        	   move(event.getX() - movePoint.x,event.getY() - movePoint.y);	        	   
        	   movePoint.x = event.getX();
        	   movePoint.y = event.getY();	        	   
           }	           
           break;
       case MotionEvent.ACTION_CANCEL:
       case MotionEvent.ACTION_UP:
           Log.i("TAG", "ccTouchesMoved.ACTION_UP");
           break;		           
       }
       return true;	
	}
		
		
}
