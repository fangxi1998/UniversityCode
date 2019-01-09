package com.example.fangxi.door;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {
    public static final String ACTION = "com.example.Activity";

    MyReceiver receiver = new MyReceiver();
    IntentFilter filter = new IntentFilter(ACTION);
    Myservice carService=new Myservice();
    private Button open;
    private Handler handler;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
          open = findViewById(R.id.open);


        open.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showSystemParameter();

                if(Util.Do){
                Message msg = handler.obtainMessage();
                msg.obj="o";
                handler.sendMessage(msg);}


            }
        });
        Intent in = new Intent(MainActivity.this,Myservice.class);
        startService(in);
        this.registerReceiver(receiver, filter); //开启广播
        CarSendThread carSendThread = new CarSendThread();
        carSendThread.start();


    }

public void up(){
        String user = SystemUtil.getSystemModel();

    String url = "http://39.106.50.90/login/register.php?username=" + user;
    Log.e("message", "url：" + url);
    HttpURLConnection conn;

    try {
        conn = (HttpURLConnection) new URL(url).openConnection();
        conn.setRequestMethod("GET");
        conn.connect();
        int a =conn.getResponseCode();
        Log.e("message", "res：" + a);

conn.disconnect();
    }
    catch (Exception e) {
        e.printStackTrace();
    }

}

    private void showSystemParameter() {
        String TAG = "系统参数：";
        Log.e(TAG, "手机厂商：" + SystemUtil.getDeviceBrand());
        Log.e(TAG, "手机型号：" + SystemUtil.getSystemModel());
        Log.e(TAG, "手机当前系统语言：" + SystemUtil.getSystemLanguage());
        Log.e(TAG, "Android系统版本号：" + SystemUtil.getSystemVersion());

    }
    public class MyReceiver extends BroadcastReceiver {
        // 接收SocketService发送过来的广播，更新主界面UI
        @Override
        public void onReceive(Context context, Intent intent) {
            String dataReceiver = intent.getStringExtra("str");
            if("ok".equals(dataReceiver)){
                Toast.makeText(MainActivity.this,"联网成功！！！",Toast.LENGTH_LONG).show();





            }else{
                Toast.makeText(MainActivity.this,"联网失败 请重启app！！！",Toast.LENGTH_LONG).show();



            }


        }
    }


    class CarSendThread extends Thread{
        @SuppressLint("HandlerLeak")
        public void run(){

            Looper.prepare();
            handler=new Handler(){
                @Override
                public void handleMessage(Message msg) {
                    up();
                    super.handleMessage(msg);
                    String s = (String) msg.obj;

                    carService.sendDate(s);
                    Toast.makeText(MainActivity.this,"芝麻开门",Toast.LENGTH_LONG).show();
                }
            };
            Looper.loop();



        }




    }
}



