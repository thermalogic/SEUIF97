Attribute VB_Name = "seuif97"
' SEUIF97
'   The VBA Module to access libseuif97.dll
'
'   License: this code is in the public domain
'
'   Author:   Cheng Maohua
'   Email:    cmh@seu.edu.cn
'
' Last modified: 2016.4.20
'
Option Explicit

' API declarations
#If Win64 Then

    Declare PtrSafe Function seupt Lib "libseuif97" (ByVal p As Double, ByVal t As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function seuph Lib "libseuif97" (ByVal p As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function seups Lib "libseuif97" (ByVal p As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function seupv Lib "libseuif97" (ByVal p As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function seuth Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function seuts Lib "libseuif97" (ByVal t As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function seutv Lib "libseuif97" (ByVal t As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function seupx Lib "libseuif97" (ByVal p As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function seutx Lib "libseuif97" (ByVal t As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    
   Declare PtrSafe Function seuhx Lib "libseuif97" (ByVal h As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
   Declare PtrSafe Function seusx Lib "libseuif97" (ByVal s As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
   
    Declare PtrSafe Function seuhs Lib "libseuif97" (ByVal h As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    
    'Thermodynamic Process of Steam Turbine
    Declare PtrSafe Function seuishd Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
    Declare PtrSafe Function seuief Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
    
    

#Else

    Declare Function seupt Lib "libseuif97" (ByVal p As Double, ByVal t As Double, ByVal OutWhat As Integer) As Double
    Declare Function seuph Lib "libseuif97" (ByVal p As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function seups Lib "libseuif97" (ByVal p As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare Function seupv Lib "libseuif97" (ByVal p As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function seuth Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function seuts Lib "libseuif97" (ByVal t As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare Function seutv Lib "libseuif97" (ByVal t As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function seupx Lib "libseuif97" (ByVal p As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare Function seutx Lib "libseuif97" (ByVal t As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function seuhx Lib "libseuif97" (ByVal h As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare Function seusx Lib "libseuif97" (ByVal s As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double

    Declare Function seuhs Lib "libseuif97" (ByVal h As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    
    'Thermodynamic Process of Steam Turbine
    Declare Function seuishd Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
    Declare Function seuief Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
 
#End If

Public Function if97pt(ByVal p As Double, ByVal t As Double, ByVal wp As Integer) As Double
   if97pt = seupt(p, t, wp)
End Function

Public Function if97ph(ByVal p As Double, ByVal h As Double, ByVal wp As Integer) As Double
   if97ph = seuph(p, h, wp)
End Function

Public Function if97ps(ByVal p As Double, ByVal s As Double, ByVal wp As Integer) As Double
   if97ps = seups(p, s, wp)
End Function

Public Function if97pv(ByVal p As Double, ByVal v As Double, ByVal wp As Integer) As Double
   if97pv = seupv(p, v, wp)
End Function

Public Function if97th(ByVal t As Double, ByVal h As Double, ByVal wp As Integer) As Double
   if97th = seuth(t, h, wp)
End Function

Public Function if97ts(ByVal t As Double, ByVal s As Double, ByVal wp As Integer) As Double
   if97ts = seuts(t, s, wp)
End Function

Public Function if97tv(ByVal t As Double, ByVal v As Double, ByVal wp As Integer) As Double
   if97tv = seutv(t, v, wp)
End Function

Public Function if97hs(ByVal h As Double, ByVal s As Double, ByVal wp As Integer) As Double
   if97hs = seuhs(h, s, wp)
End Function

Public Function if97px(ByVal p As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97px = seupx(p, x, wp)
End Function

Public Function if97tx(ByVal t As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97tx = seutx(t, x, wp)
End Function

Public Function if97hx(ByVal h As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97hx = seuhx(h, x, wp)
End Function

Public Function if97sx(ByVal s As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97sx = seusx(s, x, wp)
End Function


Public Function if97ishd(ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
   if97ishd = seuishd(pi, ti, pe)
End Function


Public Function if97ief(ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
   if97ief = seuief(pi, ti, pe, te)
End Function

