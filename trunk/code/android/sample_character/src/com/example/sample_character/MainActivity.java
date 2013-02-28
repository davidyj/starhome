package com.example.sample_character;

import org.cocos2d.nodes.Scene;
import org.cocos2d.nodes.Director;
import org.cocos2d.opengl.CCGLSurfaceView;


import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {

	protected CCGLSurfaceView _glSurfaceView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		_glSurfaceView = new CCGLSurfaceView(this);
		
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
		
		Director.sharedDirector().setDisplayFPS(false);
		
		Director.sharedDirector().setAnimationInterval(1.0f / 60.0f);
		
		Scene scene = CGameLayer.scene();
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
