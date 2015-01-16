console.log("Uploaded js is running on client side");
var myRequest;
//create a new instance of the object 
//it ignore IE ActiveXObject for simple exercise
myRequest = new XMLHttpRequest();
myRequest.open("head", "http://localhost:3000/upload", true);
myRequest.send();
//attach a function to handle onreadystatechange,
//that is, the response from the server:
myRequest.onreadystatechange = function()
{
	if (myRequest.readyState ===4 && myRequest.status === 200)
	{
		var a = myRequest.getResponseHeader("Num1");
		var b = myRequest.getResponseHeader("Num2");
		var op = myRequest.getResponseHeader("Op");

		var out = a
		out += op
		out += b
		out += "=" + eval(out) + "\n"
		
		alert(out);
	}
	else
	{
		console.log("myRequest.readyState:" + myRequest.readyState)
		console.log("myRequest.status:" + myRequest.status)
	}
}

