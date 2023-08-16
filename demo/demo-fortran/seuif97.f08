!
! The interface of libseuif97 
!
! License: this code is in the public domain
!
! Author:   Cheng Maohua
! Email:    cmh@seu.edu.cn
!
! Last modified: 2019.01.05
!
module seuif97
implicit none
Interface
    real(c_double) function pt(p,t,wid) bind (C,name="pt")
        use iso_c_binding
        real(c_double), value :: p,t
         integer(c_int), value ::wid
    end function pt 

    real(c_double) function ph(p,h,wid) bind (C,name="ph")
        use iso_c_binding
        real(c_double), value :: p,h 
        integer(c_int), value ::wid
    end function ph 

    real(c_double) function ps(p,s,wid) bind (C,name="ps")
        use iso_c_binding
        real(c_double), value :: p,s
        integer(c_int), value ::wid
    end function ps 

    real(c_double) function pv(p,v,wid) bind (C,name="pv")
        use iso_c_binding
        real(c_double), value :: p,v
        integer(c_int), value ::wid
    end function pv

    real(c_double) function th(t,h,wid) bind (C,name="th")
        use iso_c_binding
        real(c_double), value :: t,h 
        integer(c_int), value ::wid
    end function th 

    real(c_double) function ts(t,s,wid) bind (C,name="ts")
        use iso_c_binding
        real(c_double), value :: t,s
        integer(c_int), value ::wid
    end function ts 

    real(c_double) function tv(t,v,wid) bind (C,name="tv")
        use iso_c_binding
        real(c_double), value :: t,v
        integer(c_int), value ::wid
    end function tv

    real(c_double) function hs(h,s,wid) bind (C,name="hs")
        use iso_c_binding
        real(c_double), value :: h,s
        integer(c_int), value ::wid
    end function hs 

    real(c_double) function px(p,x,wid) bind (C,name="px")
        use iso_c_binding
        real(c_double), value :: p,x
        integer(c_int), value ::wid
    end function px

    real(c_double) function tx(t,x,wid) bind (C,name="tx")
        use iso_c_binding
        real(c_double), value :: t,x
        integer(c_int), value ::wid
    end function tx

    real(c_double) function hx(h,x,wid) bind (C,name="hx")
        use iso_c_binding
        real(c_double), value :: h,x
        integer(c_int), value ::wid
    end function hx

    real(c_double) function sx(s,x,wid) bind (C,name="sx")
        use iso_c_binding
        real(c_double), value :: s,x
        integer(c_int), value ::wid
    end function sx

    real(c_double) function ishd(pi,ti,pe) bind (C,name="ishd")
        use iso_c_binding
        real(c_double), value :: pi,ti,pe
    end function ishd

    real(c_double) function ief(pi,ti,pe,te) bind (C,name="ief")
        use iso_c_binding
        real(c_double), value :: pi,ti,pe,te
    end function ief

End Interface


end module
