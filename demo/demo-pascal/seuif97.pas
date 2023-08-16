unit seuif97;

Interface
  const IF97LIB= 'libseuif97';
  const IF97P=0;  const  IF97T=1;  const IF97D=2; const  IF97V=3;  const IF97H=4;
  const IF97S=5;  const  IF97E=6;  const IF97U=7; const IF97CP=8;  const IF97CV=9;

  const IF97W=10; const IF97KS=11; const IF97F=12; const IF97G=13;  const    IF97Z=14;
  const IF97X=15; const  IF97R=16; const IF97EC=17; const IF97KT=18; const IF97DVDT=19;

  const IF97DVDP=20; const IF97DPDT=21; const IF97IJTC=22; const IF97JTC=23;
  const IF97DV=24;   const IF97KV=25;   const IF97TC=26;   const IF97TD=27;
  const IF97PR=28; const IF97ST=29;

  function pt( p,t:double; param:integer):double;external IF97LIB;// Windows stdcall : stdcall;external IF97LIB;
  function ph( p,h:double; param:integer):double;external IF97LIB;
  function ps( p,s:double; param:integer):double;external IF97LIB;
  function pv( p,v:double; param:integer):double;external IF97LIB;

  function th( t,h:double; param:integer):double;external IF97LIB;
  function ts( t,s:double; param:integer):double;external IF97LIB;
  function tv( t,v:double; param:integer):double;external IF97LIB;

  function px( p,v:double; param:integer):double;external IF97LIB;
  function tx( t,x:double; param:integer):double;external IF97LIB;

  function hx( h,v:double; param:integer):double;external IF97LIB;
  function sx( s,x:double; param:integer):double;external IF97LIB;

  function hs( p,v:double; param:integer):double;external IF97LIB;
  
  function ishd( pi,ti,pe:double):double;external IF97LIB;
  function ief( pi,ti,pe,te:double):double;external IF97LIB;

implementation

end.
