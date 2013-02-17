package org.cocos2d.tests;

import android.app.Activity;
import android.app.AlertDialog;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import org.cocos2d.layers.Layer;
import org.cocos2d.menus.Menu;
import org.cocos2d.menus.MenuItemImage;
import org.cocos2d.nodes.*;
import org.cocos2d.opengl.CCGLSurfaceView;
import org.cocos2d.transitions.*;
import org.cocos2d.types.CCColor3B;
import org.cocos2d.types.CCSize;

import java.lang.reflect.Constructor;

public class TransitionsTest extends Activity {
    private static final String LOG_TAG = TransitionsTest.class.getSimpleName();
    private CCGLSurfaceView mGLSurfaceView;

    private static final float TRANSITION_DURATION = 1.2f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        new AlertDialog.Builder(this)
                .setTitle("Warning")
                .setMessage("There are known problems with this demo.")
                .setPositiveButton("Ok", null)
                .show();

        
        mGLSurfaceView = new CCGLSurfaceView(this);
        setContentView(mGLSurfaceView);
    }

    @Override
    public void onStart() {
        super.onStart();

        // attach the OpenGL view to a window
        Director.sharedDirector().attachInView(mGLSurfaceView);

        // set landscape mode
        Director.sharedDirector().setLandscape(true);

        // show FPS
        Director.sharedDirector().setDisplayFPS(true);

        // frames per second
        Director.sharedDirector().setAnimationInterval(1.0f / 60);

        Scene scene = Scene.node();
        scene.addChild(new TestLayer1());
        // Make the Scene active
        Director.sharedDirector().runWithScene(scene);

    }

    @Override
    public void onPause() {
        super.onPause();

        Director.sharedDirector().pause();
    }

    @Override
    public void onResume() {
        super.onResume();

        Director.sharedDirector().resume();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        TextureManager.sharedTextureManager().removeAllTextures();
    }

    static class FadeWhiteTransition extends FadeTransition {
        public FadeWhiteTransition(float t, Scene s) {
            super(t, s, new CCColor3B(255, 255, 255));
        }
    }

    static class FlipXLeftOverTransition extends FlipXTransition {
        public FlipXLeftOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationLeftOver);
        }
    }

    static class FlipXRightOverTransition extends FlipXTransition {
        public FlipXRightOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationRightOver);
        }
    }

    static class FlipYUpOverTransition extends FlipYTransition {
        public FlipYUpOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationUpOver);
        }
    }

    static class FlipYDownOverTransition extends FlipYTransition {
        public FlipYDownOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationDownOver);
        }
    }

    static class FlipAngularLeftOverTransition extends FlipAngularTransition {
        public FlipAngularLeftOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationLeftOver);
        }
    }

    static class FlipAngularRightOverTransition extends FlipAngularTransition {
        public FlipAngularRightOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationRightOver);
        }
    }

    static class ZoomFlipXLeftOverTransition extends ZoomFlipXTransition {
        public ZoomFlipXLeftOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationLeftOver);
        }
    }

    static class ZoomFlipXRightOverTransition extends ZoomFlipXTransition {
        public ZoomFlipXRightOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationRightOver);
        }
    }

    static class ZoomFlipYUpOverTransition extends ZoomFlipYTransition {
        public ZoomFlipYUpOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationUpOver);
        }
    }

    static class ZoomFlipYDownOverTransition extends ZoomFlipYTransition {
        public ZoomFlipYDownOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationDownOver);
        }
    }

    static class ZoomFlipAngularLeftOverTransition extends ZoomFlipAngularTransition {
        public ZoomFlipAngularLeftOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationLeftOver);
        }
    }

    static class ZoomFlipAngularRightOverTransition extends ZoomFlipAngularTransition {
        public ZoomFlipAngularRightOverTransition(float t, Scene s) {
            super(t, s, Orientation.kOrientationRightOver);
        }
    }

    static int sceneIdx = 0;
    static Class transitions[] = {
            JumpZoomTransition.class,
//            FadeTRTransition.class,
//            FadeBLTransition.class,
//            FadeUpTransition.class,
//            FadeDownTransition.class,
//            TurnOffTilesTransition.class,
//            SplitRowsTransition.class,
//            SplitColsTransition.class,
            FadeTransition.class,
            FadeWhiteTransition.class,
            FlipXLeftOverTransition.class,
            FlipXRightOverTransition.class,
            FlipYUpOverTransition.class,
            FlipYDownOverTransition.class,
            FlipAngularLeftOverTransition.class,
            FlipAngularRightOverTransition.class,
            ZoomFlipXLeftOverTransition.class,
            ZoomFlipXRightOverTransition.class,
            ZoomFlipYUpOverTransition.class,
            ZoomFlipYDownOverTransition.class,
            ZoomFlipAngularLeftOverTransition.class,
            ZoomFlipAngularRightOverTransition.class,
            ShrinkGrowTransition.class,
            RotoZoomTransition.class,
            MoveInLTransition.class,
            MoveInRTransition.class,
            MoveInTTransition.class,
            MoveInBTransition.class,
            SlideInLTransition.class,
            SlideInRTransition.class,
            SlideInTTransition.class,
            SlideInBTransition.class,
    };

    static TransitionScene nextTransition(float d, Scene s) {
        sceneIdx++;
        sceneIdx = sceneIdx % transitions.length;

        return restartTransition(d, s);
    }

    static TransitionScene backTransition(float d, Scene s) {
        sceneIdx--;
        int total = transitions.length;
        if (sceneIdx < 0)
            sceneIdx += total;

        return restartTransition(d, s);
    }

    static TransitionScene restartTransition(float d, Scene s) {
        try {
            Class c = transitions[sceneIdx];
            Class partypes[] = new Class[2];
            partypes[0] = Float.TYPE;
            partypes[1] = s.getClass();
            Constructor ctor = c.getConstructor(partypes);
            Object arglist[] = new Object[2];
            arglist[0] = d;
            arglist[1] = s;
            return (TransitionScene) ctor.newInstance(arglist);
        } catch (Exception e) {
            return null;
        }
    }

    static class TestLayer1 extends Layer {

        public TestLayer1() {

            CCSize s = Director.sharedDirector().winSize();
            float x = s.width;
            float y = s.height;

            Sprite bg1 = Sprite.sprite("background1.jpg");
            bg1.setAnchorPoint(0, 0);
            addChild(bg1, -1);

            Label label = Label.label("SCENE 1", "DroidSans", 64);

            label.setPosition(x / 2, y / 2);
            addChild(label);

            // menu
            MenuItemImage item1 = MenuItemImage.item("b1.png", "b2.png", this, "backCallback");
            MenuItemImage item2 = MenuItemImage.item("r1.png", "r2.png", this, "restartCallback");
            MenuItemImage item3 = MenuItemImage.item("f1.png", "f2.png", this, "nextCallback");

            Menu menu = Menu.menu(item1, item2, item3);
            menu.setPosition(0, 0);
            item1.setPosition(s.width / 2 - 100, 30);
            item2.setPosition(s.width / 2, 30);
            item3.setPosition(s.width / 2 + 100, 30);
            addChild(menu, 1);
        }

        public void nextCallback() {
            Scene scene = Scene.node();
            scene.addChild(new TestLayer2());
            Director.sharedDirector().replaceScene(nextTransition(TRANSITION_DURATION, scene));
        }

        public void backCallback() {
            Scene scene = Scene.node();
            scene.addChild(new TestLayer2());
            Director.sharedDirector().replaceScene(backTransition(TRANSITION_DURATION, scene));
        }

        public void restartCallback() {
            Scene scene = Scene.node();
            scene.addChild(new TestLayer2());
            Director.sharedDirector().replaceScene(restartTransition(TRANSITION_DURATION, scene));
        }
    }

    static class TestLayer2 extends Layer {

        public TestLayer2() {

            CCSize s = Director.sharedDirector().winSize();
            float x = s.width;
            float y = s.height;

            Sprite bg2 = Sprite.sprite("background2.jpg");
            bg2.setAnchorPoint(0, 0);
            addChild(bg2, -1);

            Label label = Label.label("SCENE 2", "DroidSans", 64);

            label.setPosition(x / 2, y / 2);
            addChild(label);

            // menu
            MenuItemImage item1 = MenuItemImage.item("b1.png", "b2.png", this, "backCallback");
            MenuItemImage item2 = MenuItemImage.item("r1.png", "r2.png", this, "restartCallback");
            MenuItemImage item3 = MenuItemImage.item("f1.png", "f2.png", this, "nextCallback");

            Menu menu = Menu.menu(item1, item2, item3);
            menu.setPosition(0, 0);
            item1.setPosition(s.width / 2 - 100, 30);
            item2.setPosition(s.width / 2, 30);
            item3.setPosition(s.width / 2 + 100, 30);
            addChild(menu, 1);

        }

        public void nextCallback() {
            Scene scene = Scene.node();
            scene.addChild(new TestLayer1());
            Director.sharedDirector().replaceScene(nextTransition(TRANSITION_DURATION, scene));
        }

        public void backCallback() {
            Scene scene = Scene.node();
            scene.addChild(new TestLayer1());
            Director.sharedDirector().replaceScene(backTransition(TRANSITION_DURATION, scene));
        }

        public void restartCallback() {
            Scene scene = Scene.node();
            scene.addChild(new TestLayer1());
            Director.sharedDirector().replaceScene(restartTransition(TRANSITION_DURATION, scene));

        }
    }


}
