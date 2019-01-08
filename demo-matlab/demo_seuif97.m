% The demo using libseuif97 in MATLAB for Windows 64
%
%  1 Put the following files in the path `\extern\seuif97` of the installed MATLAB
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

myfuns = seuif97;
p=18.0;
t=535;
h=myfuns.pt(p,t,4);
s=myfuns.pt(p,t,5);
v=myfuns.pt(p,t,3);
fprintf('(p,t),h,s,v: %.2f,%.2f,%.2f,%.4f,%.4f\n',p,t,h,s,v);
