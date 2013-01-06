function ScrollToElement(theElement){

  var selectedPosX = 0;
  var selectedPosY = 0;

  while(theElement != null){
    selectedPosX += theElement.offsetLeft;
    selectedPosY += theElement.offsetTop;
    theElement = theElement.offsetParent;
  }

 window.scrollTo(selectedPosX,selectedPosY);
}
function SetSite(KatName)
{
var strHref = window.location.href;
if(strHref.indexOf("#")!=-1)
{

 var k=document.getElementById("KatName");
 var strQueryString = strHref.substr(strHref.indexOf("#")+1).toLowerCase();
 var a='Row'+strQueryString;
 //alert(a);
 var e=document.getElementById(a);
  e.bgColor='navy';

  var tds = e.getElementsByTagName("td");
  e.className="selected";
 // for(i=0;i<tds.length;i++)
    //tds[i].className="selected";

  k.innerHTML="Рейтинг сайта "+'"'+tds[1].innerHTML+'"'+' в каталоге '+'"'+KatName+'"';
  ScrollToElement(e);

 // alert(tds[1].innerHTML);
}
}