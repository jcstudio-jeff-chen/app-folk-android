package com.folk.folk;

import android.app.Application;
import android.content.Context;
import android.os.AsyncTask;
import android.support.annotation.NonNull;
import android.util.Log;

/**
 * Created by jeffrey on 2017/4/20.
 *
 * 全域變數
 */

public class AppDelegate extends Application {

    public native void initialize();
    private OnInitializedListener onInitializedListener;

    static {
        System.loadLibrary("native-lib");
    }

    public static AppDelegate getInstance(@NonNull Context context){
        if(context instanceof AppDelegate){
            return (AppDelegate) context;
        }
        Context appContext = context.getApplicationContext();
        if(appContext instanceof AppDelegate){
            return (AppDelegate) appContext;
        }
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        new AsyncTask<Void, Void, Double>() {
            @Override
            protected Double doInBackground(Void... params) {
                long startTime = System.nanoTime();
                initialize();
                long endTime = System.nanoTime();
                return (endTime-startTime)/1000000000.0;
            }

            @Override
            protected void onPostExecute(Double aDouble) {
                super.onPostExecute(aDouble);
                Log.d("訊息", "初始化耗費 " + aDouble + "秒");
                if(onInitializedListener != null){
                    onInitializedListener.onInitFinish();
                }
            }
        }.execute();
    }

    public void setOnInitializedListener(OnInitializedListener listener){
        onInitializedListener = listener;
    }

    interface OnInitializedListener{
        void onInitFinish();
    }
}
