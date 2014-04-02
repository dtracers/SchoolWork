<html>

	<head>
		<title>Project 3</title>
	</head>
	
	<body>		
		<div id="main">
		<?php
			if (isset($_GET['events'])) {
				include('events.php');
			}
			else if (isset($_GET['calendar'])) {
				include('calendar.php');
			}
			else if (isset($_GET['signup'])) {
				include('signup.php');
			}
			else if (isset($_GET['login'])) {
				include('login.php');
			}
			else if (isset($_GET['about'])) {
				include('about.php');
			}
			else {
				include 'home.php';
			}
		?>
		</div>
	</body>

</html>