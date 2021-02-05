program demo;
uses seuif97;

var p,t,h,s:double;

begin
   p:=16.0;
   t:=535.0;
   h:=seupt(p,t,IF97H);
   s:=seupt(p,t,IF97S);
   writeln('(h,s)',h,s);
end.