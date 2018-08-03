package xplay.xplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback,GLSurfaceView.Renderer{


    public XPlay(Context context, AttributeSet attrs) {

        super(context, attrs);
        //android 8.0 需要设置
        setRenderer(this);
    }
    @Override
    public void surfaceCreated(SurfaceHolder holder){
        //初始化OPENGL EGL显示
        InitView(holder.getSurface());



    }
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height){

    }
    @Override
    public void surfaceDestroyed(SurfaceHolder holder){

    }

    public native  void InitView(Object surface);

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }
}
