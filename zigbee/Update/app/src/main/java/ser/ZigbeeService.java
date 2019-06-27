package ser;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.util.Log;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.charset.Charset;

public class ZigbeeService extends Service {
    String IP="192.168.137.91";
    int Port=1200;
    private Socket socket;
    private OutputStream outputStream = null;
    private InputStream inputStream = null;
    static byte RxBuf[] = new byte[256];
    int len;
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
        // showToast("正在连接网关");
        new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    socket = new Socket(IP,Port);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                try {

                    inputStream = socket.getInputStream();
                    outputStream= socket.getOutputStream();
                    printWriter = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream, Charset.forName("gb2312"))));

                    //showToast("网关连接成功");
                    getData();



                } catch (Exception e) {
                    // showToast("网管连接失败");
                    e.printStackTrace();
                }
            }
        }).start();







    }
    public void getData() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                setTimerTask();
                while (socket.isConnected()) {
                    try {
                        len = inputStream.read(RxBuf);
                        //Log.d("length",String.valueOf(len));
                    } catch (IOException e1) {
                        // TODO Auto-generated catch block
                        e1.printStackTrace();
                    }
                    if (len > 0) {
                        //Log.d("2", String.valueOf(RxBuf[0])+","+String.valueOf(RxBuf[1]));

                        showToast(RxBuf[0]+","+RxBuf[1]+","+RxBuf[2]+","+RxBuf[3]+","+RxBuf[4]+","+RxBuf[5]+","+RxBuf[6]+","+RxBuf[7]+","+RxBuf[8]+","+RxBuf[9]+
                                ","+RxBuf[10]+","+RxBuf[11]+","+RxBuf[12]+","+RxBuf[13]+","+RxBuf[14]+","+RxBuf[15]+","+RxBuf[16]+","+RxBuf[17]+","+RxBuf[18]+","+RxBuf[19]+
                                ","+RxBuf[20]+","+RxBuf[21]);



                        // System.out.println(RxBuf[11]);

                    }

                }
            }
        }).start();
    }
    public  void setTimerTask() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    sendDate("s");
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }
    public void showToast(String str){

        Intent intent = new Intent();
        intent.putExtra("str",str);
        intent.setAction("com.example.Zigbee");
        sendBroadcast(intent);


    }
    public void sendDate(String str){
        printWriter.print(str);
        printWriter.flush();



    }
}
