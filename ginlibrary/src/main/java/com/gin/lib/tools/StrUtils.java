package com.gin.lib.tools;

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
     * 获得单例
     *
     * @return
     */
    public static StrUtils getInstance() {
        return InstanceHolder.INSTANCE;
    }

    /**
     * 单例持有器
     */
    private static final class InstanceHolder {
        private static final StrUtils INSTANCE = new StrUtils();
    }

    /**
     * 禁止构造
     */
    private StrUtils() {
    }
    
    public native String getMD5(String md);
    
}
