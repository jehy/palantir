
Md=document;Mnv=navigator;
Mrn=Math.random();Mn=(Mnv.appName.substring(0,2)=="Mi")?0:1;

Mp=0;Mz="p="+Mp+"&amp";
Ms=screen;Mz+="wh="+Ms.width+'x'+Ms.height;

My="<img src='http://top.2s.ru/cnt?cid=jehy&amp;cntsize=88x31";
My+="&amp;cntc=none&amp;rand="+Mrn+"&amp;"+Mz+"&amp;referer="+escape(Md.referrer)+'&amp;pg='+escape(window.location.href);
My+="' border=0 width=1 height=1 alt='top.2s.ru' title=&quot;Участник&nbsp;RHC&#039;s&nbsp;top&quot;>";
Md.write(My);