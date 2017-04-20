package com.folk.folk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity implements AppDelegate.OnInitializedListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        AppDelegate global = AppDelegate.getInstance(this);
        if(global != null) {
            global.setOnInitializedListener(this);
        }
    }

    @Override
    public void onInitFinish() {
        Log.d("訊息", "初始化完成，執行換頁");
    }
}
