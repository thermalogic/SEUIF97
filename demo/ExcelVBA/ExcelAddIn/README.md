# Excel VBA with Add-in Macro to libseuif97.dll   

## 1 Copy `libseuif97.dll` to the default path of Windows's dll

    C:/Windows/system

## 2 Excel workbook(macro enabled) on Excel Add-in Macro to Libseuif97.dll

### 2.1 Excel Add-in Macro to libseuif97.dll

copy [SEUIF97.xlam](./SEUIF97.xlam) to the path `\XLStart` to load the add-in automatically when Excel starts up
   
   For Example: `C:\Program Files\Microsoft Office\root\Office16\XLSTART`

### 2.2 Using Add-in Macro in the  Excel workbook with macro enabled 

[demo_addin_seuif97.xlsm](./demo_addin_seuif97.xlsm)

In Excel VBA, using syntax like `=if97pt(p, t, 4)`

* first,second input parameters: the input properties(double)
* third input parameter: the propertyID of the calculated property(int, 0-29), see `Properties in libseuif97`
* the return: the calculated property value(double)

![demo_addin](./img/demo_addin.jpg)

## 3 The Path Reference Issue to Excel Add-in 

Sometimes,we write our own functions using VBA placed in add-ins. As long as the add-in is installed, the functions work as expected. 

But. You get into trouble when **the location of the add-in changes**.

As soon as a file which uses the function is opened on a system that uses a **different** add-in path, all cells that use your function show **`#NAME! errors`**. Also, the complete path to the original location of the add-in is shown in each formula:

For Example: [demo_addin_SEUIF97.xlsm](./demo_addin_SEUIF97.xlsm)

```vb
='C:\Program Files\Microsoft Office\root\Office16\XLSTART\SEUIF97xlam!if97pt(A1,A2,4)
```

### Methods to Fix `#Name! Errors`

#### 3.1 Use fixed location

The simplest way to avoid the problem is by fixing the location of your addin in **`the same absolute path`**.  for example **`C:\program files\addins\xxxx.xlam`**

Tell all your users where the add-in should be installed. Your `#Name! errors` will not resurface.

#### 3.2 Running VBA in the worksheet to delete the path reference to the add-in,

Put the following codes in the worksheet using the add-in

```vb
Sub RemoveXlaPath()
'
' Goal: delete the path reference to the add-in, i.e. everything before and including the '!'
' ='C:\Program Files\Microsoft Office\root\Office16\XLSTART\SEUIF97xlam!if97pt(...)'
'
    Cells.Replace What:="'C:\*xla*'!", Replacement:="", _
                    LookAt:=xlPart, SearchOrder:=xlByRows, MatchCase:=False, _
                    SearchFormat:=False, ReplaceFormat:=False
End Sub
```

Run the sub `RemoveXlaPath` to delete the path reference to the add-in, i.e. everything before and including the '!'

```vb
 ='C:\Program Files\Microsoft Office\root\Office16\XLSTART\SEUIF97xlam!if97pt(...)'
```
to 

```vb
 ='if97pt(...)'
```
