#  Excel VBA with Libseuif97.dll  

## 1 Copy `libseuif97.dll` to the default path of Windows's dll

    C:/Windows/system

## 2 Excel workbook with macro enabled on Excel Add-in Macro to Libseuif97.dll

### 2.1 Excel Add-in Macro to Libseuif97.dll

copy [SEUIF97.xlam](./SEUIF97.xlam) to the path `\XLStart` to load the add-in automatically when Excel starts up
   
   For Example: `C:\Program Files\Microsoft Office\root\Office16\XLSTART`

### 2.2 Using Add-in Macro in the  Excel workbook with macro enabled 

[demo_addin_seuif97.xlsm](./demo_addin_seuif97.xlsm)

![demo_addin](./img/demo_addin.jpg)

## 3 Excel add-in UDF path issue

https://stackoverflow.com/questions/24925424/excel-add-in-udf-path-issue

### 3.1 Introduction

Excel has a host of built-in functions to help you do your computations. But sometimes you need to write your own functions using VBA. These functions are called "User Defined Functions" (UDF). UDFs typically are placed in add-ins. As long as the add-in is installed, the UDFs work as expected. `You get into trouble when the location of the add-in changes`, for example because you have distributed the Add-in to your co-workers and they have installed it to their local user addin folder (which is different for each user!).

As soon as a file which uses the UDF is opened on a system that uses a different addin path, all cells that use your UDF show `#NAME! errors`. Also, the complete path to the original location of the add-in is shown in each formula:

For Example: [demo_addin_SEUIF97.xlsm](./demo_addin_SEUIF97.xlsm)

```vb
='C:\Program Files\Microsoft Office\root\Office16\XLSTART\SEUIF97xlam!if97pt(A1,A2,4)
```

### 3.2 Methods to Fix `#Name! Errors`

#### 3.2.1 Use fixed location

The simplest way to avoid the problem is by fixing the location of your addin in **`the same absolute path`**.  for example **`C:\program files\addins\xxxx.xlam`**

Tell all your users where the add-in should be installed. Your `#Name! errors` will not resurface.

### 3.2.2 Don't use an add-in

But instead of keeping your UDF code inside the add-in, you import the UDF routine [seuif97.bas](./seuif97.bas)into each workbook that uses it.

For Example: [demo_SEUIF97.xlsm](./demo_SEUIF97.xlsm)

This is a neat solution.

### 3.2.3 Running VBA in the worksheet to delete the path reference to the add-in,

Put the following codes in the worksheet

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
 ='if97pt(...)
```
