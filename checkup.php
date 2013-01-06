<?
$sql='select url,id from mirrors where ((status=0)or(status=1)) order by priority desc';
$result=sql($sql);
while(0)#($row=mysql_fetch_array($result))
{
  #$res=@file_get_contents($row['check_url']);
  $res=1;
  if($res!=1)
  {
    $sql='update mirrors set status=0 where id="'.$row['id'].'"';
    sql($sql);
    $date=date("Y-m-d H:m:s");
    $sql='insert into revision values("",'.$row['id'].',"'.$date.'",0)';
    sql($sql);
  }
  else
  {
    $sql='update mirrors set status=1 where id="'.$row['id'].'"';
    sql($sql);
    $date=date("Y-m-d H:m:s");
    $sql='insert into revision values("",'.$row['id'].','.$date.',1)';
    sql($sql);
    break;
  }
}
mysql_free_result($result);
?>
