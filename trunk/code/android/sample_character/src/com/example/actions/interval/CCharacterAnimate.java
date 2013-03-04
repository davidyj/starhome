package com.example.actions.interval;

import org.cocos2d.actions.interval.Animate;
import org.cocos2d.actions.interval.IntervalAction;
import org.cocos2d.nodes.CocosNode;
import org.cocos2d.nodes.CocosNode.CocosAnimation;
import org.cocos2d.nodes.Sprite;


import com.example.nodes.CCharacterPart;
import com.example.nodes.CCharacterAnimation;
import com.example.nodes.CCharacterFrame;
import com.example.nodes.CCharacterSprite;

public class CCharacterAnimate extends IntervalAction {
		
		private CocosNode.CocosAnimation animation = null;	    
	    
	    public static CCharacterAnimate action(CocosNode.CocosAnimation anim) {
	        assert anim != null : "Animate: argument Animation must be non-null";
	        return new CCharacterAnimate(anim, true);
	    }

	    public static CCharacterAnimate action(CocosNode.CocosAnimation anim, boolean restore) {
	        assert anim != null : "Animate: argument Animation must be non-null";
	        return new CCharacterAnimate(anim, restore);
	    }
	    
	    protected CCharacterAnimate(CocosAnimation anim, boolean restore) {
	        super(anim.frames().size() * anim.delay());
	        animation = anim;	        
	    }			    
	    
	    public CocosNode.CocosAnimation getAnimation(){
	    	return animation;
	    }
	    
	    // aTarge is CCharacterSprite
	    @Override
	    public void start(CocosNode aTarget) {
	    	 super.start(aTarget);
	    }

	    @Override
	    public void stop() {
	         super.stop();
	    }

	    private byte frameindex = 0;
	    
	    @Override
	    public void update(float t) {
	    	
          if (frameindex >= animation.frames().size()) {
        	  frameindex = 0;
          }

          //sprite is CCharacterSprite;
          CCharacterSprite sprites = (CCharacterSprite) target;
          
          CCharacterFrame frame = (CCharacterFrame) animation.frames().get(frameindex);
          sprites.resetPosition(frame.sprites);
          
          //animation.frames is CCharacterSpriteFraem ArrayList          
          sprites.setDisplayFrame(frame.sprites);         
          
          frameindex++;
	    }
}
