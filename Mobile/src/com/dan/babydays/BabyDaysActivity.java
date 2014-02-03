package com.dan.babydays;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import android.os.Bundle;
import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.DatePickerDialog.OnDateSetListener;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.Toast;

public class BabyDaysActivity  extends Activity implements OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_baby_days);
        Button btnDate = (Button)findViewById(R.id.btnDate);
        btnDate.setOnClickListener(this);
        
        init();
    }

    private void init() {
    	String nickName = "瑞宝";
    	String birthDate = "2013-06-30";
    	  	
    	TextView tvDays = (TextView)findViewById(R.id.textViewDays);
    	try{
    		Calendar c = Calendar.getInstance();
    		SimpleDateFormat dfDate = new SimpleDateFormat("yyyy-mm-dd");  
    		Date dBirth = dfDate.parse(birthDate);
    		Date dToday = dfDate.parse(dfDate.format(c.getTime()));
    		int diffInDays = (int) ((dToday.getTime() - dBirth.getTime())/ (1000 * 60 * 60 * 24));
    		
        	String sOutputFormat = getResources().getString(R.string.ouput_days);
        	String sOutputFinal = String.format(sOutputFormat, nickName, diffInDays);
        	
        	tvDays.setText(sOutputFinal);
    	}catch(java.text.ParseException ex)
    	{
    		ex.printStackTrace();
    		tvDays.setText(getResources().getString(R.string.require_input));
    	}
     	//tvDays.setText("218天了");
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.baby_days, menu);
        return true;
    }

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch(v.getId()){
		case R.id.btnDate:
			DatePickerDialog datePicker=new DatePickerDialog(BabyDaysActivity.this, new OnDateSetListener() {
			    
			    @Override
			    public void onDateSet(DatePicker view, int year, int monthOfYear,
			            int dayOfMonth) {
			        // TODO Auto-generated method stub
			       Toast.makeText(BabyDaysActivity.this, year+"year "+(monthOfYear+1)+"month "+dayOfMonth+"day", Toast.LENGTH_SHORT).show();
			       //TextView tvDate = (TextView)findViewById(R.id.textViewDate);
			       //tvDate.setText(text)
			    }
			}, 2013, 4, 30);
			datePicker.show();
		}
	}
    
}
