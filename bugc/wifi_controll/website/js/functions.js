$( document ).ready(function() {
	console.log("ready");
	$("button").click(function() {
		var direction = "";
		switch ($(this).attr("id")){
			case "topBtn": direction = "forward"; break;
			case "bottomBtn": direction = "backward"; break;
			case "leftBtn": direction = "left"; break;
			case "rightBtn": direction = "right"; break;
			case "stopBtn": direction = "stop"; break;
		}
		console.log("move BugC to: " + direction);
		moveBugC(direction);
	});
});

function moveBugC(direction){
	var url = "http://"+ipAdresse+"/move?direction=" + direction;
	console.log("call: " + url);
	$.get(url);
}