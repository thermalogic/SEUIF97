!  
! SEUIF97 Library:
! 
!  1 Windows: C:/Windows/system/libseuif97.dll
!  2 Linux:  /usr/lib/libseuif97.so
!  3 The Module: ./seuif97.f08

! Build：
! Windows with MinGW-W64
!  >gfortran -fno-underscoring -c seuif97.f08 -LC:/Windows/system/ -lseuif97
!  >gfortran -fno-underscoring -o demo demo_fortran_module.f08 -LC:/Windows/system/ -lseuif97
!
! Linux：
!  $gcc  -fno-underscoring -c seuif97.f08 -L/usr/lib/ -lseuif97 -lm
!  $gcc  -fno-underscoring -o demo demo_fortran_module.f08 seuif97.f08 -L/usr/lib/ -lseuif97 -lm
!
! Run:
! ./demo
!
! Author: Cheng Maohua
!

program demo
  use iso_c_binding
  use seuif97
  implicit none
  real(c_double) :: p,t,h,s,v
  p = 16.13;
  t = 535.0;

  h = seupt(p, t, 4);
  s = seupt(p, t, 5);
  v = seupt(p, t, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(p,t),h,s,v",p,t,h,s,v 

  t = seuph(p, h, 1);
  s = seuph(p, h, 5);
  v = seuph(p, h, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(p,h),t,s,v",p,h,t,s,v 

  t = seuph(p, h, 1);
  s = seuph(p, h, 5);
  v = seuph(p, h, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(p,h),t,s,v",p,h,t,s,v 

  p = seuth(t, h, 0);
  s = seuth(t, h, 5);
  v = seuth(t, h, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(t,h),p,s,v",t,h,p,s,v 

end program demo