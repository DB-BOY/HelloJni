package com.gin.hellojni;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.gin.hellojni.activity.FileActivity;
import com.gin.hellojni.activity.MD5Activity;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        View view = findViewById(R.id.iview);

        view.setLayerType(View.LAYER_TYPE_SOFTWARE, null);
    }


    public void click(View view) {
        Intent intent;
        switch (view.getId()) {
            case R.id.md5:
                intent = MD5Activity.getIntent(MainActivity.this);
                break;

            case R.id.file:
                intent = FileActivity.getIntent(MainActivity.this);
                break;
            default:
                intent = MD5Activity.getIntent(MainActivity.this);
                break;

        }
        startActivity(intent);
    }

}
