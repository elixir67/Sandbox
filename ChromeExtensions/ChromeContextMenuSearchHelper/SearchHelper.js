// Copyright (c) 2012 Dan Lin. All rights reserved.
// A customized search helper in google chrome context menu.

function searchByDoubanMovie(info, tab) {
  console.log("Text " + info.selectionText + " was selected");
  window.open ("http://movie.douban.com/subject_search?search_text="+encodeURI(info.selectionText) ) 
}

function searchByBaidu(info, tab) {
  console.log("Text " + info.selectionText + " was selected");
  window.open ("http://www.baidu.com/s?wd="+encodeURI(info.selectionText) ) 
}

function searchByBing(info, tab) {
  console.log("Text " + info.selectionText + " was selected");
  // Copy the search string from google search engine manager
  // http://www.bing.com/search?setmkt=en-US&q=%s
  window.open ("http://www.bing.com/search?setmkt=en-US&q="+encodeURI(info.selectionText) ) 
}

var cmMovie = chrome.contextMenus.create(
  {"title": "用豆瓣电影搜索 \"%s\"", "contexts": ["selection"],"onclick": searchByDoubanMovie});
  
var cmBaidu = chrome.contextMenus.create(
  {"title": "用百度搜索 \"%s\"", "contexts": ["selection"],"onclick": searchByBaidu});
  
var cmBaidu = chrome.contextMenus.create(
  {"title": "用Bing搜索 \"%s\"", "contexts": ["selection"],"onclick": searchByBing});