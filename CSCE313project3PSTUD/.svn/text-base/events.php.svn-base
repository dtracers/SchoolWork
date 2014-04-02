<html>

	<head>
		<title>Project 3 Events Page</title>
		<link rel="stylesheet" href="style.css" type="text/css" media="screen" />

    	<script src="http://maps.google.com/maps?file=api&amp;v=2&amp;key=AIzaSyA6AU4ySiAUhWnmb_a5FPUDm474gdTJYKE"
            type="text/javascript"></script>		
	</head>
	
	<body>
		<?php include 'header.php'; ?>
		
		<div id="container">
		<div id="content">
		<div id="events">
		<p>Events<p>	
		<div id="map" style="width: 500px; height: 400px"></div>
		<script type="text/javascript">
		    //<![CDATA[
		    window.onload = showMap;
		    function showMap()
			{
			    var map = new GMap(document.getElementById("map"));
			    map.addControl(new GSmallMapControl());
			    map.centerAndZoom(new GPoint(-122.1419, 37.4419), 4);
		    }
		    //]]>
		</script>
		</div><!-- events -->
		
		<?php include 'sidebar.php'; ?>
		
		</div><!-- content -->
		</div><!-- container -->
		
		<?php include 'footer.php'; ?>
	</body>

</html>