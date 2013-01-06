<?
$to=str_replace(array("\r","\n","\t"),' ',$_GET['to']);
header('location: ' . $to);
die();
?>

