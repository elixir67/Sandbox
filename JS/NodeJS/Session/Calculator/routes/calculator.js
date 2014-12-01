var express = require('express');
var fs = require('fs');

exports.form = function(req, res) {
	console.log("received upload get request")
	res.render('upload', {
		title: 'Web Exercise 101 - Calculator with session'
	});
};

exports.submit = function(req, res) {
	var a = Math.round(Math.random()*100)
	var b = Math.round(Math.random()*100)


	console.log("req.files:" + req.files)
	var filePath = req.files.script.path
	console.log("filePath:" + filePath)
	//read content from temporary file  
	fs.readFile(filePath, function(err, data) {
		if (err) {
			res.send(err);
			return;
		}
		console.log("content:" + data)
		var out = "Num 1: " + a
		out += " + "
		out += "Num 2: " + b
		out += "=" + (a + b) + "\n"
		out += "script content is: \n" + data + "\n"
		res.send(out)
	});
};