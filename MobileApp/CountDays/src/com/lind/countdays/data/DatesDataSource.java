package com.lind.countdays.data;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.SortedSet;
import java.util.TreeSet;

import android.content.Context;
import android.content.SharedPreferences;

public class DatesDataSource {

	private static final String PREFKEY = "dates";
	private SharedPreferences notePrefs;
	
	public DatesDataSource(Context context) {
		notePrefs = context.getSharedPreferences(PREFKEY, Context.MODE_PRIVATE);
	}
	
	public List<DateItem> findAll() {
		
		Map<String, ?> notesMap = notePrefs.getAll();
		
		SortedSet<String> keys = new TreeSet<String>(notesMap.keySet());
		
		List<DateItem> noteList = new ArrayList<DateItem>();
		for (String key : keys) {
			DateItem note = new DateItem();
			note.setKey(key);
			note.setText((String) notesMap.get(key));
			noteList.add(note);
		}
		
		return noteList;
		
	}
	
	public boolean update(DateItem note) {
		
		SharedPreferences.Editor editor = notePrefs.edit();
		editor.putString(note.getKey(), note.getText());
		editor.commit();
		return true;
	}
	
	public boolean remove(DateItem note) {
		
		if (notePrefs.contains(note.getKey())) {
			SharedPreferences.Editor editor = notePrefs.edit();
			editor.remove(note.getKey());
			editor.commit();
		}
		
		return true;
	}
	
	
}
