package com.example.fangxi1998.update.backup;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.example.fangxi1998.update.R;
import com.iflytek.cloud.SpeechConstant;
import com.iflytek.cloud.SpeechError;
import com.iflytek.cloud.SpeechSynthesizer;
import com.iflytek.cloud.SpeechUtility;
import com.iflytek.cloud.SynthesizerListener;

import ser.ZigbeeService;

public class MainzigActivity extends AppCompatActivity {
    static  int count=0,count1=0,count2=0;
    static  int count00=0,count11=0,count22=0;
    public static final String ACTION = "com.example.Zigbee";

    IntentFilter filter = new IntentFilter(ACTION);
    ZigbeeReceiver zigbeeReceiver = new ZigbeeReceiver();
    ZigbeeService zigbeeService = new ZigbeeService();
    ZigSendThread zigSendThread = new ZigSendThread();

    private TextView wen2,wen4;
    private TextView light,light2;
    private TextView fire,people,smog;
    private TextView fire1,people1,smog1;
    private Button jump;
    private Button beep1,beep2;
    MySynthesizerListener mTtsListener;
    private SpeechSynthesizer mTts ;
    private Handler handler;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mainzig);
        wen2=findViewById(R.id.wen2);
        wen4=findViewById(R.id.wen4);
        light=findViewById(R.id.light);
        light2=findViewById(R.id.light2);
        fire=findViewById(R.id.fire);
        people=findViewById(R.id.people);
        smog=findViewById(R.id.smog);
        fire1=findViewById(R.id.fire1);
        people1=findViewById(R.id.people1);
        smog1=findViewById(R.id.smog1);

        beep1=findViewById(R.id.beep1);
        beep2=findViewById(R.id.beep2);

        initSpeech();
        speekText();
        zigSendThread.start();


       // mTts.startSpeaking("欢迎使用",mTtsListener);

        final Intent intent = new Intent(MainzigActivity.this, ZigbeeService.class);
        startService(intent);
        this.registerReceiver(zigbeeReceiver, filter);
        jump.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent1 = new Intent(MainzigActivity.this,MonitorActivity.class);
                startActivity(intent1);
                MainzigActivity.this.finish();
            }
        });
        beep1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Message msg = handler.obtainMessage();
                msg.obj="BEEP01";
                handler.sendMessage(msg);

            }
        });

        beep2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Message msg = handler.obtainMessage();
                msg.obj="BEEP02";
                handler.sendMessage(msg);

            }
        });
    }
    class ZigSendThread extends Thread{
        @SuppressLint("HandlerLeak")
        public void run(){

            Looper.prepare();
            handler=new Handler(){
                @Override
                public void handleMessage(Message msg) {
                    super.handleMessage(msg);
                    String s = (String) msg.obj;
                    Log.d("send",s);
                    zigbeeService.sendDate(s);
                }
            };
            Looper.loop();
        }
    }
    public class ZigbeeReceiver extends BroadcastReceiver {

        // 接收SocketService发送过来的广播，更新主界面UI
        @Override
        public void onReceive(Context context, Intent intent) {

            String dataReceiver = intent.getStringExtra("str");
            Log.d("receiver",dataReceiver);
            String dat[]=dataReceiver.split(",");
            try{


                Log.d("一号教室人",dat[8]);
                Log.d("二号教室人",dat[18]);

                if(Integer.parseInt(dat[0])==49){
                   // Log.d("dat[0]",dat[0]);

                   // Log.d("data",""+(d*10+e)+"."+f);
                    wen2.setText(cal(Integer.parseInt(dat[1])-48,Integer.parseInt(dat[2])-48,Integer.parseInt(dat[3])-48));
                    light.setText(cal(Integer.parseInt(dat[4])-48,Integer.parseInt(dat[5])-48,Integer.parseInt(dat[6])-48));
                    if((Integer.parseInt(dat[7])-48)==1){
                        fire.setText("有火焰");
                        fire.setTextColor(Color.rgb(255, 0, 0));
                        count1++;
                        Log.d("count1",String.valueOf(count1));
                        if(count1==1){
                            mTts.startSpeaking("1号教室有火焰，请及时处理~",mTtsListener);}
                        if(count1==2){
                            count1=0;
                        }

                    }else
                        fire.setText("");

                    if((Integer.parseInt(dat[8])-48)==0){
                        count++;
                        people.setText("有人");

                        people.setTextColor(Color.rgb(255, 0, 0));
                        if(count==1){
                            mTts.startSpeaking("1号教室有人",mTtsListener);

                        }
                        if(count==2){
                            count=0;
                        }

                    }else if((Integer.parseInt(dat[8])-48)==1){

                        people.setText("");
                    }

                    if((Integer.parseInt(dat[9])-48)==1){
                        count2++;
                        smog.setText("有烟雾");
                        smog.setTextColor(Color.rgb(255, 0, 0));
                        if(count2==1){
                            mTts.startSpeaking("1号教室有烟雾",mTtsListener);}
                        if(count2==2){
                            count2=0;
                        }

                    }else
                        smog.setText("");





                }
                 if(Integer.parseInt(dat[10])==50){
               ;

                    wen4.setText(cal(Integer.parseInt(dat[11])-48,Integer.parseInt(dat[12])-48,Integer.parseInt(dat[13])-48));
                    light2.setText(cal(Integer.parseInt(dat[14])-48,Integer.parseInt(dat[15])-48,Integer.parseInt(dat[16])-48));
                     if((Integer.parseInt(dat[17])-48)==1){

                        count11++;
                         fire1.setText("有火焰");
                         fire1.setTextColor(Color.rgb(255, 0, 0));
                         if(count11==1){
                             mTts.startSpeaking("2号教室有火焰",mTtsListener);}
                         if(count11==2){
                             count11=0;
                         }

                     }else
                         fire1.setText("");
                     if((Integer.parseInt(dat[18])-48)==0){
                         count00++;
                         people1.setText("有人");
                         people1.setTextColor(Color.rgb(255, 0, 0));
                         if(count00==1){
                             mTts.startSpeaking("2号教室有人",mTtsListener);}
                         if(count00==2){
                             count00=0;
                         }

                     }else if((Integer.parseInt(dat[18])-48)==1){

                         people1.setText("");
                     }
                     if((Integer.parseInt(dat[19])-48)==1){
                         count22++;
                         smog1.setText("有烟雾");
                         smog1.setTextColor(Color.rgb(255, 0, 0));
                         if(count22==1){
                             mTts.startSpeaking("2号教室有烟雾",mTtsListener);}
                         if(count22==2){
                             count22=0;
                         }

                     }else
                         smog1.setText("");
                }

            }
            catch (Exception g){


            }




        }

    }




    String cal(int a, int b,int c){


        return (a*10+b+"."+c);
    }


    private void speekText() {
        //1. 创建 SpeechSynthesizer 对象 , 第二个参数： 本地合成时传 InitListener
        mTts = SpeechSynthesizer.createSynthesizer( this, null);
        //2.合成参数设置，详见《 MSC Reference Manual》 SpeechSynthesizer 类
        //设置发音人（更多在线发音人，用户可参见 附录 13.2
        mTts.setParameter(SpeechConstant. VOICE_NAME, "vixy" ); // 设置发音人
        mTts.setParameter(SpeechConstant. SPEED, "50" );// 设置语速
        mTts.setParameter(SpeechConstant. VOLUME, "80" );// 设置音量，范围 0~100
        mTts.setParameter(SpeechConstant. ENGINE_TYPE, SpeechConstant. TYPE_CLOUD); //设置云端
        //设置合成音频保存位置（可自定义保存位置），保存在 “./sdcard/iflytek.pcm”
        //保存在 SD 卡需要在 AndroidManifest.xml 添加写 SD 卡权限
        //仅支持保存为 pcm 和 wav 格式， 如果不需要保存合成音频，注释该行代码
        // mTts.setParameter(SpeechConstant. TTS_AUDIO_PATH, "./sdcard/iflytek.pcm" );
        //3.开始合成
    }
    private void initSpeech() {
        // 将“12345678”替换成您申请的 APPID，申请地址： http://www.xfyun.cn
        // 请勿在 “ =”与 appid 之间添加任务空字符或者转义符
        SpeechUtility. createUtility( this, SpeechConstant. APPID + "=5b0424f1" );
    }
    class MySynthesizerListener implements SynthesizerListener {


        @Override
        public void onSpeakBegin() {
            //  showTip(" 开始播放 ");
        }

        @Override
        public void onSpeakPaused() {
            //   showTip(" 暂停播放 ");
        }

        @Override
        public void onSpeakResumed() {
            // showTip(" 继续播放 ");
        }

        @Override
        public void onBufferProgress(int percent, int beginPos, int endPos ,
                                     String info) {
            // 合成进度
        }

        @Override
        public void onSpeakProgress(int percent, int beginPos, int endPos) {
            // 播放进度
        }

        @Override
        public void onCompleted(SpeechError error) {
            if (error == null) {
                //showTip("播放完成 ");
            } else if (error != null ) {
                showTip(error.getPlainDescription( true));
            }
        }

        @Override
        public void onEvent(int eventType, int arg1 , int arg2, Bundle obj) {

        }
    }

    private void showTip (String data) {
        Toast.makeText( this, data, Toast.LENGTH_SHORT).show() ;
    }



}
