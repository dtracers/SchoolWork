<html>

	<head>
		<title>Project 3 Home Page</title>
		<link rel="stylesheet" href="style.css" type="text/css" media="screen" />
	</head>
	
	<body>
		<?php include 'header.php'; ?>
		
		<div id="container">
		<div id="content">
		<div id="home">
		<p>Home<p>
		<?php
		$doc = new DOMDocument();
		$doc->load( 'events.xml' );
		  
		$employees = $doc->getElementsByTagName( "event" );
		foreach( $events as $event )
		{
			$names = $event->getElementsByTagName( "name" );
			$name = $names->item(0)->nodeValue;
		  
			$dates= $event->getElementsByTagName( "date" );
			$date= $dates->item(0)->nodeValue;
		  
			$locations = $event->getElementsByTagName( "location" );
			$location = $locations->item(0)->nodeValue;
		  
			echo "<b>$name - $date - $location\n</b><br>";
		}
		?> 
		
		<?php
	    $books = array();
	  	$books [] = array(
	  	'title' => 'PHP Hacks',
	  	'author' => 'Jack Herrington',
	  	'publisher' => "O'Reilly"
	  	);
	  	$books [] = array(
	  	'title' => 'Podcasting Hacks',
	  	'author' => 'Jack Herrington',
	  	'publisher' => "O'Reilly"
	  	);
	  
	  	$doc = new DOMDocument();
	  	$doc->formatOutput = true;
	  
	  	$r = $doc->createElement( "books" );
	  	$doc->appendChild( $r );
	  
	  	foreach( $books as $book )
	  	{
	  	$b = $doc->createElement( "book" );
	  
	  	$author = $doc->createElement( "author" );
	  	$author->appendChild(
	  	$doc->createTextNode( $book['author'] )
	  	);
	  	$b->appendChild( $author );
	  
	  	$title = $doc->createElement( "title" );
	  	$title->appendChild(
	  	$doc->createTextNode( $book['title'] )
	  	);
	  	$b->appendChild( $title );
	  
	  	$publisher = $doc->createElement( "publisher" );
	  	$publisher->appendChild(
	  	$doc->createTextNode( $book['publisher'] )
	  	);
	  	$b->appendChild( $publisher );
	  
	  	$r->appendChild( $b );
	  	}
	  
	  	echo $doc->saveXML();
	  	?>	
		
		</div><!-- home -->
		
		<?php include 'sidebar.php'; ?>
		
		</div><!-- content -->
		</div><!-- container -->
		
		<?php include 'footer.php'; ?>
	</body>

</html>