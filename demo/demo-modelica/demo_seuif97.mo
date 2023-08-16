model demo_seuif97 "Model of seuif97"

function pt
    input Real p;
    input Real t;
    input Integer w;
    output Real result;
external"C" result = pt(
        p,
        t,
        w);
    annotation (Library="libseuif97");
end pt;

Real h;
parameter Real p=16;
parameter Real t=542;
parameter Integer w=4;

equation
  h = pt(
    p,
    t,
    w);
end demo_seuif97;
