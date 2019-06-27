package com.example.fangxi1998.update.backup;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.RectF;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.example.fangxi1998.update.R;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MonitorActivity extends AppCompatActivity {

    private SurfaceView surface;
    private SurfaceHolder holder;
    public static String url;
    private boolean thread;
    HttpURLConnection conn;

    private Handler handler;
    private Canvas canvas;
    URL videoUrl;
    Bitmap bmp;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_monitor);
        surface=findViewById(R.id.surface1);
        surface.setKeepScreenOn(true);  //视频
        holder = surface.getHolder();
    }

    @Override
    protected void onResume() {
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

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        Intent intent = new Intent(MonitorActivity.this,MainzigActivity.class);

        startActivity(intent);
        MonitorActivity.this.finish();
    }

    private void draw() {
        // TODO Auto-generated method stub
        try {
            InputStream inputstream = null;
            //创建一个URL对象

            url = "http://192.168.137.184:8080/?action=snapshot";
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
