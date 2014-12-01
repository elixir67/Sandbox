var express = require('express');
//var fs = require('fs');

exports.form = function(req, res) {
	console.log("received upload get request")
	res.render('upload', {
		title: 'Web Exercise 101 - Calculator with session'
	});
};

exports.submit = function(req, res) {
	console.log("received upload post request")
	console.log("req.files:" + req.files)
	var filePath = req.files.script.path;
	onsole.log("filePath:" + filePath)
	// read content from temporary file  
	// fs.readFile(filePath, function(err, data) {
	// 	if (err) {
	// 		res.send(err);
	// 		return;
	// 	}
	// 	console.log("content:" + data)
	// 	res.send("script content is: \n" + data);
	// }
};