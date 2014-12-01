var express = require('express');
var fs = require('fs');
var session = require('express-session');

exports.form = function(req, res) {
	console.log("received upload get request")
	res.render('upload', {
		title: 'Web Exercise 101 - Calculator with session'
	});
};

exports.submit = function(req, res) {
	var sess = req.session
	console.log(sess)
	var a, b
	if(sess.a && sess.b){
		a = sess.a
		b = sess.b
	}
	else{
		console.log("No data in session or session expired")
		a = Math.round(Math.random()*100)
		b = Math.round(Math.random()*100)
		sess.a = a
		sess.b = b
	}

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