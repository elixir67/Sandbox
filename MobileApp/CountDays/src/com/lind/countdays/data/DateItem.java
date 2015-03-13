package com.lind.countdays.data;

import android.annotation.SuppressLint;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class DateItem {

	private String key; // Key is date now
	private String text;
	
	public static final String TEXT = "text";
	public static final String KEY = "key";
	
	public String getKey() {
		return key;
	}
	public void setKey(String key) {
		this.key = key;
	}
	public String getText() {
		return text;
	}
	public void setText(String text) {
		this.text = text;
	}
	
	@SuppressLint("SimpleDateFormat")
	public static DateItem getNew() {
	
		Locale locale = new Locale("en_US");
		Locale.setDefault(locale);

		String pattern = "yyyy-MM-dd HH:mm:ss Z";
		SimpleDateFormat formatter = new SimpleDateFormat(pattern);
		String key = formatter.format(new Date());
		
		DateItem note = new DateItem();
		note.setKey(key);
		note.setText("");
		return note;
		
	}
	
	@Override
	public String toString() {
		return this.getText();
	}
	
}
