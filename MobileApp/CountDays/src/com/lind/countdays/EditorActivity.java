package com.lind.countdays;

import com.lind.countdays.data.DateItem;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.EditText;

public class EditorActivity extends Activity {

	private DateItem date;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_note_editor);
		getActionBar().setDisplayHomeAsUpEnabled(true);
				
		Intent intent = this.getIntent();
		date = new DateItem();
		date.setKey(intent.getStringExtra("key"));
		date.setText(intent.getStringExtra("text"));
		
		EditText et = (EditText) findViewById(R.id.noteText);
		et.setText(date.getText());
		et.setSelection(date.getText().length());
	}
	
	private void saveAndFinish() {
		EditText et = (EditText) findViewById(R.id.noteText);
		String noteText = et.getText().toString();
		
		Intent intent = new Intent();
		intent.putExtra("key", date.getKey());
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
