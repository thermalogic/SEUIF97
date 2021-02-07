model seuif97 "Model of seuif97"

function pt
    input Real p;
    input Real t;
    input Integer w;
    output Real result;
external"C" result = seupt(
        p,
        t,
        w);
    annotation (Library="libseuif97");
end pt;

end seuif97;
