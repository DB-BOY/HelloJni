package com.gin.lib.tools;

import java.io.File;

/**
 * Created by wang.lichen on 2016/12/26.
 */

public class StrUtils {
    //    private native void accessJavaRandomNumberMethod() ;

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    //    public native String stringFromJNI();


    /**
     * 禁止构造
     */
    private StrUtils() {
    }

    /**
     * 获得单例
     *
     * @return
     */
    public static StrUtils getInstance() {
        return InstanceHolder.INSTANCE;
    }

    public native String getMD5(String md);

    public native File openFileFromC(String path);

    public native int copeFile(String oldPath, String newPath);
    
    /**
     * 单例持有器
     */
    private static final class InstanceHolder {
        private static final StrUtils INSTANCE = new StrUtils();
    }
}
