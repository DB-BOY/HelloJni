package com.gin.hellojni;

import android.app.Application;

import com.gin.lib.GinLib;

/**
 * Created by wang.lichen on 2016/12/26.
 */

public class GinApplication extends Application {


    @Override
    public void onCreate() {
        super.onCreate();
        GinLib.init(this);
    }
}
