package com.gin.hellojni;

import com.gin.lib.tools.StrUtils;

/**
 * Created by wang.lichen on 2016/12/26.
 */

public class Utils {

    public static  String getMD5(String str){
        return StrUtils.getInstance().getMD5(str);
 
    }
    
}
