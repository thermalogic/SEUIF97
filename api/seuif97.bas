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

    Declare PtrSafe Function if97pt Lib "libseuif97" Alias "seupt" (ByVal p As Double, ByVal t As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function if97ph Lib "libseuif97" Alias "seuph" (ByVal p As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function if97ps Lib "libseuif97" Alias "seups" (ByVal p As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function if97pv Lib "libseuif97" Alias "seupv" (ByVal p As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function if97th Lib "libseuif97" Alias "seuth" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function if97ts Lib "libseuif97" Alias "seuts" (ByVal t As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function if97tv Lib "libseuif97" Alias "seutv" (ByVal t As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function if97px Lib "libseuif97" Alias "seupx" (ByVal p As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function if97tx Lib "libseuif97" Alias "seutx" (ByVal t As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    
    Declare PtrSafe Function if97hs Lib "libseuif97" Alias "seuhs" (ByVal h As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    
    ' Thermodynamic Process of Steam Turbine
    Declare PtrSafe Function if97ishd Lib "libseuif97" Alias "seuishd" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
    Declare PtrSafe Function if97ief Lib "libseuif97" Alias "seuief" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
    
    ' Exergy
    Declare PtrSafe Function pt2eu Lib "libseuif97" (ByVal p As Double, ByVal t As Double, ByVal Tu As Double) As Double
    Declare PtrSafe Function ph2eu Lib "libseuif97" (ByVal p As Double, ByVal h As Double, ByVal Tu As Double) As Double
    Declare PtrSafe Function ps2eu Lib "libseuif97" (ByVal p As Double, ByVal s As Double, ByVal Tu As Double) As Double
    Declare PtrSafe Function pv2eu Lib "libseuif97" (ByVal p As Double, ByVal v As Double, ByVal Tu As Double) As Double
    
    Declare PtrSafe Function th2eu Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal Tu As Double) As Double
    Declare PtrSafe Function ts2eu Lib "libseuif97" (ByVal t As Double, ByVal s As Double, ByVal Tu As Double) As Double
    Declare PtrSafe Function tv2eu Lib "libseuif97" (ByVal t As Double, ByVal v As Double, ByVal Tu As Double) As Double
    
    Declare PtrSafe Function px2eu Lib "libseuif97" (ByVal p As Double, ByVal x As Double, ByVal Tu As Double) As Double
    Declare PtrSafe Function tx2eu Lib "libseuif97" (ByVal t As Double, ByVal x As Double, ByVal Tu As Double) As Double
    
    Declare PtrSafe Function hs2eu Lib "libseuif97" (ByVal h As Double, ByVal s As Double, ByVal Tu As Double) As Double
    
    '
    Declare PtrSafe Function if97thHi Lib "libseuif97" Alias "thHi" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare PtrSafe Function th2euHi Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal Tu As Double) As Double

#Else


    Declare Function if97pt Lib "libseuif97" Alias "seupt" (ByVal p As Double, ByVal t As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function if97ph Lib "libseuif97" Alias "seuph" (ByVal p As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function if97ps Lib "libseuif97" Alias "seups" (ByVal p As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare Function if97pv Lib "libseuif97" Alias "seupv" (ByVal p As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function if97th Lib "libseuif97" Alias "seuth" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function if97ts Lib "libseuif97" Alias "seuts" (ByVal t As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    Declare Function if97tv Lib "libseuif97" Alias "seutv" (ByVal t As Double, ByVal v As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function if97px Lib "libseuif97" Alias "seupx" (ByVal p As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    Declare Function if97tx Lib "libseuif97" Alias "seutx" (ByVal t As Double, ByVal x As Double, ByVal OutWhat As Integer) As Double
    
    Declare Function if97hs Lib "libseuif97" Alias "seuhs" (ByVal h As Double, ByVal s As Double, ByVal OutWhat As Integer) As Double
    
    ' Thermodynamic Process of Steam Turbine
    Declare Function if97ishd Lib "libseuif97"  Alias "seuishd" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
    Declare Function if97ief Lib "libseuif97" Alias "seuief" (ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
    
    ' Exergy
    Declare Function pt2eu Lib "libseuif97" (ByVal p As Double, ByVal t As Double, ByVal Tu As Double) As Double
    Declare Function ph2eu Lib "libseuif97" (ByVal p As Double, ByVal h As Double, ByVal Tu As Double) As Double
    Declare Function ps2eu Lib "libseuif97" (ByVal p As Double, ByVal s As Double, ByVal Tu As Double) As Double
    Declare Function pv2eu Lib "libseuif97" (ByVal p As Double, ByVal v As Double, ByVal Tu As Double) As Double
    
    Declare Function th2eu Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal Tu As Double) As Double
    Declare Function ts2eu Lib "libseuif97" (ByVal t As Double, ByVal s As Double, ByVal Tu As Double) As Double
    Declare Function tv2eu Lib "libseuif97" (ByVal t As Double, ByVal v As Double, ByVal Tu As Double) As Double
    
    Declare Function px2eu Lib "libseuif97" (ByVal p As Double, ByVal x As Double, ByVal Tu As Double) As Double
    Declare Function tx2eu Lib "libseuif97" (ByVal t As Double, ByVal x As Double, ByVal Tu As Double) As Double
    
    Declare Function hs2eu Lib "libseuif97" (ByVal h As Double, ByVal s As Double, ByVal Tu As Double) As Double
    
    '
    Declare Function if97thHi Lib "libseuif97" Alias "thHi" (ByVal t As Double, ByVal h As Double, ByVal OutWhat As Integer) As Double
    Declare Function th2euHi Lib "libseuif97" (ByVal t As Double, ByVal h As Double, ByVal Tu As Double) As Double


#End If

Public Function pt(ByVal p As Double, ByVal t As Double, ByVal wp As Integer) As Double
   pt = if97pt(p, t, wp)
End Function

Public Function ph(ByVal p As Double, ByVal h As Double, ByVal wp As Integer) As Double
   ph = if97ph(p, h, wp)
End Function

Public Function ps(ByVal p As Double, ByVal s As Double, ByVal wp As Integer) As Double
   ps = if97ps(p, s, wp)
End Function

Public Function pv(ByVal p As Double, ByVal v As Double, ByVal wp As Integer) As Double
   pv = if97pv(p, v, wp)
End Function

Public Function th(ByVal t As Double, ByVal h As Double, ByVal wp As Integer) As Double
   th = if97th(t, h, wp)
End Function

Public Function ts(ByVal t As Double, ByVal s As Double, ByVal wp As Integer) As Double
   ts = if97th(t, s, wp)
End Function

Public Function tv(ByVal t As Double, ByVal v As Double, ByVal wp As Integer) As Double
   tv = if97tv(t, v, wp)
End Function

Public Function hs(ByVal h As Double, ByVal s As Double, ByVal wp As Integer) As Double
   hs = if97tv(h, s, wp)
End Function

Public Function px(ByVal p As Double, ByVal x As Double, ByVal wp As Integer) As Double
   px = if97pt(p, x, wp)
End Function

Public Function tx(ByVal t As Double, ByVal x As Double, ByVal wp As Integer) As Double
   tx = if97tx(t, x, wp)
End Function


Public Function ishd(ByVal pi As Double, ByVal ti As Double, ByVal pe As Double) As Double
   ishd = if97ishd(pi, ti, pe)
End Function


Public Function ief(ByVal pi As Double, ByVal ti As Double, ByVal pe As Double, ByVal te As Double) As Double
   ief = if97ief(pi, ti, pe, te)
End Function

