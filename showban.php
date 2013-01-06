<?
include('scripts/common.inc');
$id=$_GET['id'];
if(is_numeric($id))
{
  $sql='select id,img_type from banners where id="'.$id.'"';
  //echo $sql;
  $result=sql($sql);
  if(mysql_num_rows($result))
  {
    $row=mysql_fetch_array($result);
    if(isset($local))
      readfile('/uni/banners/imgs/img_'.$row['id'].'.'.$row['img_type']);
    else
    {
      $mirror=get_mirror();
      Header('Location: '.$mirror['url'].'banners/imgs/img_'.$row['id'].'.'.$row['img_type']);
    }
  }
  else echo '0';
}?>
