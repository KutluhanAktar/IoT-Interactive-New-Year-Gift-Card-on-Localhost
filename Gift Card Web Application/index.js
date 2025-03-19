
setInterval(() => {
	$.ajax({
	  url: "convey.php?print=true",
	  type: "GET",
	  dataType: "json",
	  success: (response) => {
		  let data = response;
		  let audio = document.getElementById("jingle");
		  
		  if(data["block"] == "true") window.location.assign("https://www.theamplituhedron.com/");
		  $(".circle").css("fill", data["color"]);
		  if(data["audio"] == "true"){ audio.play(); }else{ audio.pause(); audio.currentTime = 0; }
	    }
    });
}, 500);