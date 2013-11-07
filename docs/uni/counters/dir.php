<?
$exc=array(
           '2_1.png','3_1.png','3_2.png','5_1.png','5_2.png','5_3.png',
           '5_4.png','6_1.png','6_2.png','6_3.png','6_4.png','7_1.png',
           '7_2.png','8_1.png','9_2.png','10_6.png','11_1.png',
           '12_1.png','12_2.png','12_3.png','12_4.png','12_5.png',
           '14_1.png','15_1.png','15_2.png','15_3.png','17_1.png',
           '16_1.png','16_2.png','16_3.png','16_4.png'
           );

function echo_dir_filenames($dirr)
{
  global $exc;
  $dir = opendir($dirr);
  $contents = array();
  while ($contents[] = trim(readdir($dir))){;}
  closedir($dir);
  $images = '';
  natcasesort ($contents);
  foreach ($contents as $line){
   if(!(in_array($line,$exc)&&$dirr='standart'))
   {
#        if($line=='2_1.png')print_r($exc);
    $filename = substr($line,0,(strlen($line)-strlen(strrchr($line,'.'))));
    $extension = substr(strrchr($line,'.'), 1);
    //if (strcasecmp($extension,'png')==0 ){
    //  $n++;
    //  if ($n==4){$images.='<br>';$n=0;}
    //if(($line!='.')and($line!='..'))if(!$images)$images=$filename;else $images.='|'.$filename;
    if(($line!='.')and($line!='..')and($line!='')){if(!$images)$images=$line;else $images.='|'.$line;}
   }
  }
echo $images;
}
echo_dir_filenames('standard');
echo'/';
echo_dir_filenames('numeric');
echo'/';
echo_dir_filenames('hit');
?>
