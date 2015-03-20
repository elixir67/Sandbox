package com.lind.countdays;

import java.util.List;

//import com.actionbarsherlock.view.MenuItem;
//import com.davidgassner.plainolnotes.NoteEditorActivity;
//import com.davidgassner.plainolnotes.R;
//import com.davidgassner.plainolnotes.data.DateItem;
import com.lind.countdays.data.*;

import android.os.Bundle;
import android.app.ListActivity;
import android.content.Intent;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.AdapterView.AdapterContextMenuInfo;

public class MainActivity extends ListActivity{

	private static final int EDITOR_ACTIVITY_REQUEST = 1001;
	private static final int MENU_DELETE_ID = 1002;
	private int currentNoteId;
	private DatesDataSource datasource;
	List<DateItem> datesList;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);		
		registerForContextMenu(getListView());
		datasource = new DatesDataSource(this);		
		refreshDisplay();
	}
	
	private void refreshDisplay() {
		datesList = datasource.findAll();
		ArrayAdapter<DateItem> adapter =
				new ArrayAdapter<DateItem>(this, R.layout.list_item_layout, datesList);
		setListAdapter(adapter);		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {

		if (item.getItemId() == R.id.action_create) {
			createNote();
		}
		
		return super.onOptionsItemSelected(item);
	}

	private void createNote() {
		DateItem note = DateItem.getNew();
		Intent intent = new Intent(this, EditorActivity.class);
		intent.putExtra(DateItem.KEY, note.getKey());
		intent.putExtra(DateItem.TEXT, note.getText());
		startActivityForResult(intent, EDITOR_ACTIVITY_REQUEST);
	}

	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		
		DateItem note = datesList.get(position);
		Intent intent = new Intent(this, EditorActivity.class);
		intent.putExtra(DateItem.KEY, note.getKey());
		intent.putExtra(DateItem.TEXT, note.getText());
		startActivityForResult(intent, EDITOR_ACTIVITY_REQUEST);
		
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == EDITOR_ACTIVITY_REQUEST && resultCode == RESULT_OK) {
			String key = data.getStringExtra(DateItem.KEY);
			String text = data.getStringExtra(DateItem.TEXT);
			String oldkey = data.getStringExtra("oldkey");
			if(!text.isEmpty())
			{				
				
				DateItem note = new DateItem();
				note.setKey(key);
				note.setText(text);
				datasource.update(note);
				if(!oldkey.equals(key))
					datasource.remove(oldkey);
				
				refreshDisplay();
			}
		}
	}
	
	@Override
	public void onCreateContextMenu(ContextMenu menu, View v,
			ContextMenuInfo menuInfo) {
		
		AdapterContextMenuInfo info = (AdapterContextMenuInfo) menuInfo;
		currentNoteId = (int)info.id;
		menu.add(0, MENU_DELETE_ID, 0, R.string.delete);
	}
	
	@Override
	public boolean onContextItemSelected(android.view.MenuItem item) {
		
		if (item.getItemId() == MENU_DELETE_ID) {
			DateItem note = datesList.get(currentNoteId);
			datasource.remove(note);
			refreshDisplay();
		}
		
		return super.onContextItemSelected(item);
	}

}
