package com.gin.hellojni.activity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;

import com.gin.hellojni.R;
import com.gin.lib.tools.StrUtils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;

/**
 * Created by wang.lichen on 2016/12/28.
 */

public class FileActivity extends Activity {
    Runnable runnable = new Runnable() {
        public void run() {
            copyFile();
        }
    };

    public static Intent getIntent(Context ctx) {
        return new Intent(ctx, FileActivity.class);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file);
    }

    public void click(View view) {
        switch (view.getId()) {
            case R.id.file_copy:
                new Thread(runnable).start();
                break;
        }
    }

    private void copyFile() {
        Log.i("-----wang.lichen", "1:" + System.currentTimeMillis());
        int ss = StrUtils.getInstance().copeFile("/sdcard/upload.jpg", "/sdcard/upload1.jpg");
        Log.i("-----wang.lichen", "2:" + ss + "   " + System.currentTimeMillis());
        //        copyFile("/sdcard/upload.jpg", "/sdcard/upload2.jpg");
        //        Log.i("-----wang.lichen", "3:" + System.currentTimeMillis());

    }

    /**
     * 使用文件通道的方式复制文件
     *
     * @param oldPath
     *         源文件
     * @param newPath
     *         复制到的新文件
     */
    private void copyFile(String oldPath, String newPath) {

        FileInputStream fi = null;

        FileOutputStream fo = null;

        FileChannel in = null;

        FileChannel out = null;

        try {

            fi = new FileInputStream(new File(oldPath));

            fo = new FileOutputStream(new File(newPath));

            in = fi.getChannel();//得到对应的文件通道

            out = fo.getChannel();//得到对应的文件通道

            Log.i("-----wang.lichen", "4:");
            in.transferTo(0, in.size(), out);//连接两个通道，并且从in通道读取，然后写入out通道

        } catch (IOException e) {

            e.printStackTrace();

        } finally {

            try {

                if (fi != null) {
                    fi.close();
                }

                if (in != null) {
                    in.close();
                }

                if (fo != null) {
                    fo.close();
                }
                if (out != null) {
                    out.close();
                }

            } catch (IOException e) {

                e.printStackTrace();

            }

        }
    }
}
