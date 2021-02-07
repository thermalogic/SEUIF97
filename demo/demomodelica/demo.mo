within demomodelica;

model demo "demo of seuif97"

Real h;
parameter Real p=16;
parameter Real t=542;
parameter Integer w=4;

equation
  h = seuif97.pt(
    p,
    t,
    w);
end demo;
