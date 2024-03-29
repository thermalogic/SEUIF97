
% The interface of libseuif97 to MATLAB for Windows 64
%
%  1 Put the following files in the path `\extern\seuif97` of the installed MATLAB%    
%   
%    libseuif97.dll
%    seuif97.h
%    seuif97.m
%
%  2 Add the path to the Search Path of MATLAB
%
%  License: this code is in the public domain
%
%  Author:   Cheng Maohua
%  Email:    cmh@seu.edu.cn
%
% Last modified: 2019.01.08
%

function funs = seuif97
if ~libisloaded('libseuif97')
   loadlibrary('libseuif97.dll','if97.h')
end
funs.pt=@pt;
funs.ph=@ph;
funs.ps=@ps;
funs.pv=@pv;

funs.th=@th;
funs.ts=@ts;
funs.tv=@tv;

funs.hs=@hs;

funs.px=@px;
funs.tx=@tx;

funs.hx=@hx;
funs.sx=@sx;

funs.ishd=@ishd;
funs.ief=@ief;

end

function f=pt(p,t,wid)
f=calllib('libseuif97', 'pt', p,t,wid);
end

function f=ph(p,h,wid)
f=calllib('libseuif97', 'ph', p,h,wid);
end

function f=ps(p,s,wid)
f=calllib('libseuif97', 'ps', p,s,wid);
end

function f=pv(p,v,wid)
f=calllib('libseuif97', 'ph', p,v,wid);
end

function f=th(t,h,wid)
f=calllib('libseuif97', 'th', t,h,wid);
end

function f=ts(t,s,wid)
f=calllib('libseuif97', 'ts', t,s,wid);
end

function f=tv(t,v,wid)
f=calllib('libseuif97', 'th', t,v,wid);
end

function f=hs(h,s,wid)
f=calllib('libseuif97', 'hs', h,s,wid);
end

function f=px(p,x,wid)
f=calllib('libseuif97', 'px', p,x,wid);
end

function f=tx(t,x,wid)
f=calllib('libseuif97', 'tx', t,x,wid);
end

function f=hx(h,x,wid)
f=calllib('libseuif97', 'hx', t,x,wid);
end

function f=sx(s,x,wid)
f=calllib('libseuif97', 'sx', t,x,wid);
end

function f=ishd(pi,ti,pe)
f=calllib('libseuif97', 'ishd', pi,ti,pe);
end

function f=ief(pi,ti,pe,te)
f=calllib('libseuif97', 'ief', pi,ti,pe,te);
end



