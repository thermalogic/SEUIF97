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

    Declare PtrSafe Function pt Lib "libseuif97" (ByVal p As Double, ByVal t As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function ph Lib "libseuif97" (ByVal p As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function ps Lib "libseuif97" (ByVal p As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function pv Lib "libseuif97" (ByVal p As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function th Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function ts Lib "libseuif97" (ByVal t As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function tv Lib "libseuif97" (ByVal t As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function px Lib "libseuif97" (ByVal p As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function tx Lib "libseuif97" (ByVal t As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    
   Declare PtrSafe Function hx Lib "libseuif97" (ByVal h As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
   Declare PtrSafe Function sx Lib "libseuif97" (ByVal s As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
   
    Declare PtrSafe Function hs Lib "libseuif97" (ByVal h As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    
    'Thermodynamic Process of Steam Turbine
    Declare PtrSafe Function ishd Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
    Declare PtrSafe Function ief Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
    
    

#Else

    Declare Function pt Lib "libseuif97" (ByVal p As Double, ByVal t As Double, ByVal OutWhat As Integer) As Double
    Declare Function ph Lib "libseuif97" (ByVal p As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function ps Lib "libseuif97" (ByVal p As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare Function pv Lib "libseuif97" (ByVal p As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function th Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function ts Lib "libseuif97" (ByVal t As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare Function tv Lib "libseuif97" (ByVal t As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function px Lib "libseuif97" (ByVal p As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare Function tx Lib "libseuif97" (ByVal t As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function hx Lib "libseuif97" (ByVal h As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare Function sx Lib "libseuif97" (ByVal s As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double

    Declare Function hs Lib "libseuif97" (ByVal h As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    
    'Thermodynamic Process of Steam Turbine
    Declare Function ishd Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
    Declare Function ief Lib "libseuif97" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
 
#End If

Public Function if97pt(ByVal p As Double, ByVal t As Double, ByVal wp As Integer) As Double
   if97pt = pt(p, t, wp)
End Function

Public Function if97ph(ByVal p As Double, ByVal h As Double, ByVal wp As Integer) As Double
   if97ph = ph(p, h, wp)
End Function

Public Function if97ps(ByVal p As Double, ByVal s As Double, ByVal wp As Integer) As Double
   if97ps = ps(p, s, wp)
End Function

Public Function if97pv(ByVal p As Double, ByVal v As Double, ByVal wp As Integer) As Double
   if97pv = pv(p, v, wp)
End Function

Public Function if97th(ByVal t As Double, ByVal h As Double, ByVal wp As Integer) As Double
   if97th = th(t, h, wp)
End Function

Public Function if97ts(ByVal t As Double, ByVal s As Double, ByVal wp As Integer) As Double
   if97ts = ts(t, s, wp)
End Function

Public Function if97tv(ByVal t As Double, ByVal v As Double, ByVal wp As Integer) As Double
   if97tv = tv(t, v, wp)
End Function

Public Function if97hs(ByVal h As Double, ByVal s As Double, ByVal wp As Integer) As Double
   if97hs = hs(h, s, wp)
End Function

Public Function if97px(ByVal p As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97px = px(p, x, wp)
End Function

Public Function if97tx(ByVal t As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97tx = tx(t, x, wp)
End Function

Public Function if97hx(ByVal h As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97hx = hx(h, x, wp)
End Function

Public Function if97sx(ByVal s As Double, ByVal x As Double, ByVal wp As Integer) As Double
   if97sx = sx(s, x, wp)
End Function


Public Function if97ishd(ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
   if97ishd = ishd(pi, ti, pe)
End Function


Public Function if97ief(ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
   if97ief = ief(pi, ti, pe, te)
End Function

