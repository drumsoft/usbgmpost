main();

function main() {
	var objShell = WScript.CreateObject("WScript.Shell");
	var objExec = objShell.Exec(usbgmdata);

	while(!objExec.StdOut.AtEndOfStream){
		var strLine = objExec.StdOut.ReadLine();
		if (/,\d+,\d+/.test(strLine)){
			var data = strLine.split(/,/g);
			send(data[1], data[2]);
		}
	}
}

function send(gCount, gTime){
	var measuredtime = Math.floor((new Date()).getTime()/1000);
	send = {
		action : "Post",
		id     : param["id"],
		measured_time : measuredtime,
		count  : gCount,
		time   : gTime,
		hash   : createhash([param["id"],measuredtime,gCount,gTime], param["key"])
	};
	var url = postto + "?" + encodeparameters(send);
	
	xmlHttp = WScript.CreateObject("MSXML2.XMLHTTP");
	xmlHttp.open("GET", url, false);
	xmlHttp.send();
	var re = xmlHttp.responseText;
	if (! /^ok/.test(re)) {
		WScript.Echo(re);
	}
}

function encodeparameters(p) {
	var a = new Array();
	for(i in p) {
		a.push(encodeURIComponent(i) + "=" + encodeURIComponent(p[i]));
	}
	return a.join("&");
}

function createhash(arr, secretkey) {
	return CybozuLabs.SHA1.calc(arr.join(":")+":"+secretkey);
}
