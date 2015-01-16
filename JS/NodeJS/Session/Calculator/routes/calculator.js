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
	  //console.log("content:" + data)

	  res.writeHead(200, { 'Content-Type': 'text/html' });
	  res.write('<!DOCTYPE html><html ><head>');
	  res.write('<meta charset="utf-8">');
	  res.write('<title>' + 'Web101' + '</title>');
	  res.write('</head><body onload="runScript()">');

	  res.write('<h1><tt>' + "hello web 101: Calculator with session" +'</tt></h1>');
	  res.write('<script type="text/javascript"> function runScript() {' + data + '}; </script>')
	  res.write('</body></html>');

	  res.end();
	});
};

exports.calculate = function(req, res) {
	console.log("calculate begin ");
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

	var out = a
	out += " + "
	out += b
	out += "=" + (a + b) + "\n"
	console.log("calculate send " + out);
	res.status(200).send(out);
}