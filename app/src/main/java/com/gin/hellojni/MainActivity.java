package com.gin.hellojni;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    EditText et;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    final TextView tv = (TextView) findViewById(R.id.sample_text);
        et = (EditText) findViewById(R.id.edit);
        Button btn = (Button) findViewById(R.id.btn);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String md =et.getText().toString();
                if(TextUtils.isEmpty(md)){
                    return ;
                }
                
                String result = Utils.getMD5(md);
                tv.setText(result);
            }
        });
    }

}
