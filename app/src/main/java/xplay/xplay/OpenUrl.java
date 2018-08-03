package xplay.xplay;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;

public class OpenUrl extends AppCompatActivity {

    private Button btfile;
    private Button btrtmp;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        setContentView( R.layout.openurl );
        btfile = findViewById(R.id.playvideo);
        btfile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EditText t = findViewById(R.id.fileurl);
                Open(t.getText().toString());

                finish();
            }
        });

        btrtmp = findViewById(R.id.playrtmp);
        btrtmp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EditText t = findViewById(R.id.rtmpurl);
                Open(t.getText().toString());

                finish();
            }
        });
    }
    public native void Open(String url);
}
