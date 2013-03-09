package com.example.sample_map;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import org.cocos2d.nodes.Director;
import org.cocos2d.nodes.Scene;
import org.xml.sax.SAXException;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {

	protected CSampleMapView _glSurfaceView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		_glSurfaceView = new CSampleMapView(this);
		
		setContentView(_glSurfaceView);
		
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public void onStart()
	{
		super.onStart();
		
		Director.sharedDirector().attachInView(_glSurfaceView);
		
		Director.sharedDirector().setDeviceOrientation(Director.CCDeviceOrientationPortrait);
		
		Director.sharedDirector().setDisplayFPS(true);
		
		Director.sharedDirector().setAnimationInterval(1.0f / 60.0f);
		
		Scene scene = null;
		try {
			scene = CGameLayer.scene(_glSurfaceView);
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
			Log.i("io error",e.getMessage());
		}
		Director.sharedDirector().runWithScene(scene);	
		
	}
	
	@Override
	public void onPause()
	{
		super.onPause();
		
		Director.sharedDirector().pause();
	}
	
	@Override
	public void onResume()
	{
		super.onResume();
		
		Director.sharedDirector().resume();
	}
	
	@Override
	public void onStop()
	{
		super.onStop();
		
		Director.sharedDirector().end();
	}


}
