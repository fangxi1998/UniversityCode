package com.example.fangxi.door;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.charset.Charset;

public class Myservice extends Service {
    String IP="192.168.1.166";
    int Port=1200;
    private Socket socket;
    private OutputStream outputStream = null;
    static PrintWriter printWriter = null;
    Context context;
    @Override
    public IBinder onBind(Intent intent) {
        Log.v("Myserivce","on bind");
        return null;
    }
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

       socketconnect(this);
        return super.onStartCommand(intent, flags, startId);
    }
    public void socketconnect(Context context){
        this.context = context;
        new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    socket = new Socket(IP,Port);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                try {
                    outputStream= socket.getOutputStream();
                    printWriter = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream, Charset.forName("gb2312"))));
                    showToast("ok");
                    Util.Do = true;
                    } catch (Exception e) {
                 showToast("er");
                 Util.Do = false;
                    e.printStackTrace();
                }
            }
        }).start();
        }
        public void showToast(String str){

        Intent intent = new Intent();
        intent.putExtra("str",str);
        intent.setAction("com.example.Activity");
        sendBroadcast(intent);


    }
    public void sendDate(String str){
        printWriter.print(str);
        printWriter.flush();



    }
}
