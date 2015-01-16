console.log("Uploaded js is running on client side");
var myRequest;
//create a new instance of the object
myRequest = new XMLHttpRequest();
myRequest.open("GET", "http://localhost:3000/calculate", true);
myRequest.send();
//attach a function to handle onreadystatechange,
//that is, the response from the server:
myRequest.onreadystatechange = function()
{
	console.log("getData begin")
	console.log("getData begin:" + myRequest.readyState)
	console.log("myRequest.status:" + myRequest.status)
	if (myRequest.readyState ===4 && myRequest.status === 200)
	{
		var text = myRequest.responseText;
		console.log("getData text:" + text)
		alert(text);
	}
}

