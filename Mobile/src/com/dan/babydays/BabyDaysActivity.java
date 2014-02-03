package com.dan.babydays;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import android.os.Bundle;
import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.DatePickerDialog.OnDateSetListener;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class BabyDaysActivity  extends Activity implements OnClickListener {

	private static String MY_PREFS = "BABY_INFO";
	private SimpleDateFormat m_dfDate;
	private String m_name;
	private String m_date;
	
	public void save()
	{
		SharedPreferences sharedPreferences = getSharedPreferences(MY_PREFS, Activity.MODE_PRIVATE);
		Editor editor = sharedPreferences.edit();
		editor.putString("name", m_name);
		editor.putString("date", m_date);
		editor.commit();
	}
	
	public void Load()
	{
		SharedPreferences mySharedPreferences = getSharedPreferences(MY_PREFS, Activity.MODE_PRIVATE);		
		m_name = mySharedPreferences.getString("name", "");
		m_date = mySharedPreferences.getString("date", "");
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_baby_days);
        Button btnDate = (Button)findViewById(R.id.btnDate);
        btnDate.setOnClickListener(this);
        
        m_dfDate = new SimpleDateFormat("yyyy-MM-dd");  
        Load();
        refresh();
    }

    private void refresh() {
    	TextView tvDays = (TextView)findViewById(R.id.textViewDays);   	
    	EditText edName = (EditText)findViewById(R.id.editTextName);
    	TextView tvDate = (TextView)findViewById(R.id.textViewDate);
    	edName.setText(m_name);
    	tvDate.setText(m_date);
    	if(m_name.isEmpty() || m_date.isEmpty())
    	{
    		tvDays.setText(getResources().getString(R.string.require_input));
    		return;
    	}
    	
    	// Compute the days
    	try{
    		Calendar c = Calendar.getInstance();
    		
    		Date dBirth = m_dfDate.parse(m_date);
    		Date dToday = m_dfDate.parse(m_dfDate.format(c.getTime()));
    		int diffInDays = (int) ((dToday.getTime() - dBirth.getTime())/ (1000 * 60 * 60 * 24));
    		
        	String sOutputFormat = getResources().getString(R.string.ouput_days);
        	String sOutputFinal = String.format(sOutputFormat, m_name, diffInDays);
        	
        	tvDays.setText(sOutputFinal);
    	}catch(java.text.ParseException ex)
    	{
    		ex.printStackTrace();
    	}
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
			       Calendar c = Calendar.getInstance();
			       c.set(year, monthOfYear, dayOfMonth);
			       Date d = c.getTime();
			       m_date = m_dfDate.format(d);
			       TextView tvDate = (TextView)findViewById(R.id.textViewDate);
			       tvDate.setText(m_date);
			       
			       // TODO: better handle it maybe in another event listener
			       EditText edName = (EditText)findViewById(R.id.editTextName);
			       m_name = edName.getText().toString();
			       
			       save();
			       refresh();
			    }
			}, 2013, 5, 30);	// TODO avoid the magic number
			datePicker.show();
		}
	}
    
}
