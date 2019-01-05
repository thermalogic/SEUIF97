module seuif97
implicit none
Interface
    real(c_double) function seupt(p,t,wid) bind (C,name="seupt")
        use iso_c_binding
        real(c_double), value :: p,t
         integer(c_int), value ::wid
    end function seupt 

    real(c_double) function seuph(p,h,wid) bind (C,name="seuph")
        use iso_c_binding
        real(c_double), value :: p,h 
        integer(c_int), value ::wid
    end function seuph 

    real(c_double) function seups(p,s,wid) bind (C,name="seups")
        use iso_c_binding
        real(c_double), value :: p,s
        integer(c_int), value ::wid
    end function seups 

    real(c_double) function seupv(p,v,wid) bind (C,name="seupv")
        use iso_c_binding
        real(c_double), value :: p,v
        integer(c_int), value ::wid
    end function seupv

    real(c_double) function seuth(t,h,wid) bind (C,name="seuth")
        use iso_c_binding
        real(c_double), value :: t,h 
        integer(c_int), value ::wid
    end function seuth 

    real(c_double) function seuts(t,s,wid) bind (C,name="seuts")
        use iso_c_binding
        real(c_double), value :: t,s
        integer(c_int), value ::wid
    end function seuts 

    real(c_double) function seutv(t,v,wid) bind (C,name="seutv")
        use iso_c_binding
        real(c_double), value :: t,v
        integer(c_int), value ::wid
    end function seutv

    real(c_double) function seuhs(h,s,wid) bind (C,name="seuhs")
        use iso_c_binding
        real(c_double), value :: h,s
        integer(c_int), value ::wid
    end function seuhs 

    real(c_double) function seupx(p,x,wid) bind (C,name="seupx")
        use iso_c_binding
        real(c_double), value :: p,x
        integer(c_int), value ::wid
    end function seupx

    real(c_double) function seutx(t,x,wid) bind (C,name="seutx")
        use iso_c_binding
        real(c_double), value :: t,x
        integer(c_int), value ::wid
    end function seutx

    real(c_double) function seuishd(pi,ti,pe) bind (C,name="seuishd")
        use iso_c_binding
        real(c_double), value :: pi,ti,pe
    end function seuishd

    real(c_double) function seuief(pi,ti,pe,te) bind (C,name="seuief")
        use iso_c_binding
        real(c_double), value :: pi,ti,pe,te
    end function seuief

End Interface


end module
