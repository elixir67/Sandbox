package com.lind.countdays;

import com.lind.countdays.data.DateItem;

import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.DatePickerDialog.OnDateSetListener;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.InputType;
import android.view.MenuItem;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.text.ParseException;
import java.text.SimpleDateFormat;

public class EditorActivity extends Activity {

	private DateItem date;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_note_editor);
		getActionBar().setDisplayHomeAsUpEnabled(true);
				
		Intent intent = this.getIntent();
		
		// Date is key at the moment
		String key = intent.getStringExtra("key");
		String note = intent.getStringExtra("text");
		date = new DateItem();
		date.setKey(key);
		date.setText(note);
		
		EditText et = (EditText) findViewById(R.id.noteText);
		et.setText(note);
		//et.setSelection(note.length());
		
//		if(note.isEmpty())
//			return;
		
		EditText dt = (EditText) findViewById(R.id.dateText);
		dt.setText(key);
		
		TextView tv = (TextView) findViewById(R.id.summaryText);
		String summary;
		
		diffDate(key, tv);

		dt.setOnClickListener(new View.OnClickListener() {  
		    public void onClick(View v) {  
				DatePickerDialog datePicker=new DatePickerDialog(EditorActivity.this, new OnDateSetListener() {
				    
				    @Override
				    public void onDateSet(DatePicker view, int year, int monthOfYear,
				            int dayOfMonth) {       
				       Calendar c = Calendar.getInstance();
				       c.set(year, monthOfYear, dayOfMonth);
				       Date d = c.getTime();
				       SimpleDateFormat formatter = new SimpleDateFormat(DateItem.DatePattern);
				       String newDate = formatter.format(d);
				       EditText dt = (EditText) findViewById(R.id.dateText);
				       dt.setText(newDate);	
				       TextView tv = (TextView) findViewById(R.id.summaryText);
				       diffDate(newDate, tv);
				    }
				}, 2013, 5, 30);
				datePicker.show();
		    }             
		});
		// Hide soft keys
		InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(dt.getWindowToken(), 0);
		//dt.setInputType(InputType.TYPE_NULL);
	}

	private void diffDate(String date, TextView tv) {
		String summary;
		Locale locale = new Locale("en_US");
		Locale.setDefault(locale);
		SimpleDateFormat formatter = new SimpleDateFormat(DateItem.DatePattern);
		try {
			Date memorialDay = formatter.parse(date);
			Calendar c = Calendar.getInstance();
			Date dToday = c.getTime();			
    		int diffDays = (int) ((dToday.getTime() - memorialDay.getTime())/ (1000 * 60 * 60 * 24));
    		if(diffDays > 0)
    			summary = diffDays + " days passed";
    		else
    			summary = -diffDays + " days left";
    		tv.setText(summary);

		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void saveAndFinish() {
		EditText et = (EditText) findViewById(R.id.noteText);
		String noteText = et.getText().toString();
		EditText dt = (EditText) findViewById(R.id.dateText);
		String memorialDay =dt.getText().toString();  
		Intent intent = new Intent();
		intent.putExtra("oldkey", date.getKey());
		intent.putExtra("key", memorialDay);
		intent.putExtra("text", noteText);
		setResult(RESULT_OK, intent);
		finish();
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		if (item.getItemId() == android.R.id.home) {
			saveAndFinish();
		}
		return false;
	}
	
	@Override
	public void onBackPressed() {
		saveAndFinish();
	}
	
}
