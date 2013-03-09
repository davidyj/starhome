package com.example.sample_map;

import org.cocos2d.nodes.Director;
import org.cocos2d.opengl.CCGLSurfaceView;

import com.example.sample_map.map.CSampleMap;

import android.content.Context;
import android.view.MotionEvent;

public class CSampleMapView extends CCGLSurfaceView {

	public CSampleMapView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
	}

	public CSampleMapView(MainActivity context) {
		// TODO Auto-generated constructor stub
		super(context);
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {		
		int id = event.getAction();
		switch (id) 
		{
          case MotionEvent.ACTION_CANCEL:              
              break;
          case MotionEvent.ACTION_DOWN:        	 
        	  float x = event.getX();
        	  float y = event.getY();
        	  
        	  map.move(x - 512, y - 400);
              break;
          case MotionEvent.ACTION_MOVE:              
              break;
          case MotionEvent.ACTION_UP:              
              break;
	    }		  
		return super.onTouchEvent(event);	       
    }
	
	private CSampleMap map = null;
	public void setMap(CSampleMap map){
		this.map = map;
	}

}
