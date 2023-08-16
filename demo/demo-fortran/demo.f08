!  
! SEUIF97 Library:
! 
!  1 Windows: C:/Windows/system/libseuif97.dll
!  2 Linux:  /usr/lib/libseuif97.so
!  3 The Module: ./seuif97.f08

! Build：
! Windows with MinGW-W64
!  >gfortran -fno-underscoring -c seuif97.f08 -LC:/Windows/system/ -lseuif97
!  >gfortran -fno-underscoring -o demo demo.f08 -LC:/Windows/system/ -lseuif97
!
! Linux：
!  $gfortran  -fno-underscoring -c seuif97.f08 -L/usr/lib/ -lseuif97 -lm
!  $gfortran  -fno-underscoring -o demo demo.f08 seuif97.f08 -L/usr/lib/ -lseuif97 -lm
!
! Run:
! ./demo
!
! Author: Cheng Maohua
! Email:  cmh@seu.edu.cn
!
! Last modified: 2019.01.05
!

program demo
  use iso_c_binding
  use seuif97
  implicit none
  real(c_double) :: p,t,h,s,v
  p = 16.13;
  t = 535.0;

  h = pt(p, t, 4);
  s = pt(p, t, 5);
  v = pt(p, t, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(p,t),h,s,v",p,t,h,s,v 

  t = ph(p, h, 1);
  s = ph(p, h, 5);
  v = ph(p, h, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(p,h),t,s,v",p,h,t,s,v 

  t = ps(p, s, 1);
  h = ps(p, s, 4);
  v = ps(p, s, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(p,s),t,h,v",p,s,t,h,v 

  p = th(t, h, 0);
  s = th(t, h, 5);
  v = th(t, h, 3);
  write (*,'(A,F10.2,F10.2,F10.2,F10.4,F10.4)') "(t,h),p,s,v",t,h,p,s,v 

end program demo