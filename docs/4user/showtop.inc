<?

if((!isset($frompage))||($frompage<1))
  $frompage=1;
$from2=($frompage-1)*TOP;

if(!isset($katid)){$katid=13;}

$sql='select `name`,`name_eng` from `types` where id="'.$katid.'" limit 1';
$result=sql($sql);
$row=mysql_fetch_row($result);
$katname=$row[1];
$Kat_Name_Rus=$row[0];

$s_num=CountPages($katid);
$kats=GetKats($katid,1);
$sql='select sources.id,sources.name,sources.url,sources.description,sources.today_hosts,today_hits,sources.hide_flags from sources where sources.parent in('.$kats.') order by today_hosts desc,sources.name limit '.$from2.','.TOP;
$num=$from2+1;
#echo $sql;
$result=sql($sql);
$showpages='';
$srcblock='';
if($frompage-10>1)
	$showpages.='<a href="'.COMMON_URL.'top/'.$katname.'/1.html">1</a>';
if($frompage-10>2)
	 $showpages.=' ...';
for ($i=$frompage-10; $i<=$frompage+10; $i++)
{
  if($i<1 || $i>$s_num)
  	  continue;	
  if ($i==$frompage)
    $showpages.=' &nbsp;<strong><font size="-1" color="white">['.$i.']</font></strong>';
  else
    $showpages.=' &nbsp;<a href="'.COMMON_URL.'top/'.$katname.'/'.$i.'.html">'.$i.'</a>';
 }
if($s_num-$frompage>11)
	$showpages.='... ';

if($s_num-$frompage>10)
	$showpages.=' &nbsp;<a href="'.COMMON_URL.'top/'.$katname.'/'.$s_num.'.html">'.$s_num.'</a>';
$showpages='<b>Страницы рейтинга:</b> '.$showpages;
if(!mysql_num_rows($result))
{
  $srcblock='<tr><td></td><td colspan="5" align="center"><font size="+1">Ресурсов в этом каталоге не зарегестрировано!</font></td></tr>';
}
$a=1;
while($all=mysql_fetch_array($result))
{
    $hide_pages=$all['hide_flags'][0];
    $hide_referers=$all['hide_flags'][1];

$a=-$a;
if($a!=1){$bg_im='dark';}else{$bg_im='white';}
$srcblock.='<tr align="center" class="bg'.$bg_im.'" id="Row'.$all['id'].'">
<td style="padding-left:20px;" class="nobg" height="40">'.$num.'</td>
<td class="nobg"><a rel="nofollow" href="'.MaskLink($all['url']).'">'.masktags($all['name']).'</a></td>
<td class="nobg">'.masktags($all['description']).'</td>
<td class="nobg">'.$all['today_hosts'].'</td>
<td class="nobg">';

if($all['today_hosts'])
{
    if(!$hide_pages)
    {
	$sql2='select count(*) from addition where site_id="'.$all['id'].'" and referer<>""';
	$result2=mysql_query($sql2);
	$row=mysql_fetch_row($result2);
	$ref1=$row[0];

	if($ref1>0)
		$srcblock.='<a href="'.COMMON_URL.'index.php?page=stats&ac=vispages&site_id='.$all['id'].'"><img border="0" src="'.COMMON_URL.'graphic/what.gif" title="Посещённые страницы сайта"></a>';
    }
    if(!$hide_referers)
    {	
	$sql2='select count(*) from addition where site_id="'.$all['id'].'" and referer2<>""';
	$result2=mysql_query($sql2);
	$row=mysql_fetch_row($result2);
	$ref2=$row[0];
	
	if($ref2>0)
		$srcblock.='<a href="'.COMMON_URL.'index.php?page=stats&ac=referers&site_id='.$all['id'].'"><img border="0" src="'.COMMON_URL.'graphic/from.gif" title="Откуда посещали сайт"></a>';
    }
}
$srcblock.='</td>
</tr>';
$num++;
}
?>
<table class="tab_all" border="0" width="100%" align="center" cellpadding="0" cellspacing="0">

<tr><td style="padding-left:20px;" colspan="5" align="center" id="KatName">Каталог "<?=$Kat_Name_Rus;?>"</td></tr>
<tr><td style="padding-left:20px;" colspan="5" align="center"><?=$showpages;?></td></tr>
<tr><td style="padding-left:20px;" colspan="5"><br></td></tr>
<?=$srcblock;?><tr class="bgdark"><td colspan="5" align="center"><?=$showpages;?></td></tr></table>
<script type="text/javascript">
// if it is from #some site
SetSite("<?=$Kat_Name_Rus;?>");
</script>
<?unset($srcblock,$all,$showpages,$uprowtitle);?>
