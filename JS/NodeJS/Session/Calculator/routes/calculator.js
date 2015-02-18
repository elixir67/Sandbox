var express = require('express');
var fs = require('fs');
var session = require('express-session');

var ops = ['+','-','*','/']

var getSessionData = function(req)
{
	var sess = req.session
	console.log(sess)
	var a, b, op
	if(sess.a && sess.b){
		a = sess.a
		b = sess.b
		op = sess.op
	}
	else{
		// console.log("No data in session or session expired")
		a = Math.random()*100
		b = Math.random()*100
		op = ops[Math.floor(Math.random()*4)]
		sess.a = a
		sess.b = b
		sess.op = op
	}
	return {
		a: a,
		b: b,
		op: op
	};
}

var getCaluculteResult = function(req)
{
	var sessData = getSessionData(req)
	var a = sessData.a
	var b = sessData.b
	var op = sessData.op

	var out = a
	out += op
	out += b
	out += "=" + eval(out) + "\n"

	return out
}

var setHeader = function(req, res) {
	var sessData = getSessionData(req)
	var a = sessData.a
	var b = sessData.b
	var op = sessData.op

	// set fields to the header
	res.set("Num1", a)
	res.set("Num2", b)
	res.set("Op", op)
}

exports.form = function(req, res) {
	console.log("received upload get request")

	setHeader(req, res)

	res.render('upload', {
		title: 'Web Exercise 101 - Calculator with session'
	});
};

exports.submit = function(req, res) {
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

	setHeader(req, res)
	//var out = getCaluculteResult(req)
	//console.log("calculate send " + out);
	res.send(200);
}