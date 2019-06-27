package com.example.fangxi1998.update.ZigbeeDemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.RectF;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;

import com.example.fangxi1998.update.R;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MonitorActivity extends Fragment {

    private SurfaceView surface;
    private SurfaceHolder holder;
    public static String url;
    private boolean thread;
    HttpURLConnection conn;

    private Handler handler;
    private Canvas canvas;
    URL videoUrl;
    Bitmap bmp;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view =inflater.inflate(R.layout.activity_monitor,container,false);
        surface=view.findViewById(R.id.surface1);
        surface.setKeepScreenOn(true);  //视频
        holder = surface.getHolder();

        return  view;
    }
    @Override
    public void onResume() {
        // TODO Auto-generated method stub
        thread=true;
        new gotoLoginAct().start();
        super.onResume();
    }
    class gotoLoginAct extends Thread{
        @Override
        public void run() {
            super.run();
            while(thread){
                draw();
            }
        }
    }
    private void draw() {
        // TODO Auto-generated method stub
        try {
            InputStream inputstream = null;
            //创建一个URL对象

            url = "http://192.168.137.114:8080/?action=snapshot";
            videoUrl=new URL(url);
            //利用HttpURLConnection对象从网络中获取网页数据
            conn = (HttpURLConnection)videoUrl.openConnection();
            //设置输入流
            conn.setDoInput(true);
            //连接
            conn.connect();
            //得到网络返回的输入流
            inputstream = conn.getInputStream();
            //创建出一个bitmap
            bmp = BitmapFactory.decodeStream(inputstream);
            canvas = holder.lockCanvas();
            canvas.drawColor(Color.WHITE);
            RectF rectf = new RectF(0, 0, 1100, 750);
            canvas.drawBitmap(bmp, null, rectf, null);
            holder.unlockCanvasAndPost(canvas);
            //关闭HttpURLConnection连接
            conn.disconnect();
        } catch (Exception ex) {
        } finally {
        }
    }
}
