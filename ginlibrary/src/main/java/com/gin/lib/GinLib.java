package com.gin.lib;

import android.content.Context;

/**
 * Created by wang.lichen on 2016/12/26.
 */

public class GinLib {
    
    public static GinLib init(Context contx) {
        GinLib ginLib = new GinLib();
        System.loadLibrary("native-lib");
        return ginLib;
    }
}
