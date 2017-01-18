package com.gin.hellojni.activity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.gin.hellojni.R;
import com.gin.hellojni.tools.Constant;
import com.gin.hellojni.tools.SecretUtils;
import com.gin.hellojni.tools.Utils;

/**
 * Created by wang.lichen on 2016/12/28.
 */

public class MD5Activity extends Activity {

    EditText et;

    public static Intent getIntent(Context mainActivity) {

        return new Intent(mainActivity, MD5Activity.class);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_md5);

        final TextView tv = (TextView) findViewById(R.id.sample_text);
        et = (EditText) findViewById(R.id.edit);
        Button btn = (Button) findViewById(R.id.btn);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String md = et.getText().toString();
                if (TextUtils.isEmpty(md)) {
                    return;
                }

                String result = Utils.getMD5(md);
                tv.setText(result);

                Log.i("---lichen Utils： ", Utils.getMD5("admin"));
                Log.i("---lSecretUtils： ", SecretUtils.MD5("adminhelloworld!"));
                matchMd5();


            }
        });

    }

    private void matchMd5() {
        //        new Thread(new Runnable(){
        //
        //            @Override
        //            public void run() {
        //                long start = System.currentTimeMillis();
        //                Log.i("------wang.lichen1",start+"");
        //                for (String ss:Constant.ConstantStrings) {
        //                    String result = SecretUtils.MD5(ss+"helloworld!");
        //                }
        //                Log.i("------wang.lichen1",System.currentTimeMillis()-start+"");
        //            }
        //        }).start();

        //        new Thread(new Runnable(){
        //
        //            @Override
        //            public void run() {
        //                long start = System.currentTimeMillis();
        //                Log.i("------wang.lichen2",start+"");
        //                for (String ss: Constant.ConstantStrings) {
        //                    String result = Utils.getMD5(ss);
        //                }
        //                Log.i("------wang.lichen2",System.currentTimeMillis()-start+"");
        //            }
        //        }).start();

        new Thread(new Runnable() {

            @Override
            public void run() {
                long start = System.currentTimeMillis();
                Log.i("------wang.lichen3", start + "");
                String sResult;
                String uResult;
                for (String ss : Constant.ConstantStrings) {
                    uResult = Utils.getMD5(ss);
                    sResult = SecretUtils.MD5(ss + "helloworld!");
                    if (!uResult.equals(sResult)) {
                        Log.i("------wang.lichen3", ss);
                    }
                }
                Log.i("------wang.lichen3", System.currentTimeMillis() - start + "");
            }
        }).start();


    }
}
