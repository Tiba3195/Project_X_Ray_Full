Imports System.IO
Imports System.Runtime.InteropServices
Imports Insight
Imports Insight.Core

Public Class NativeTools

    Public Shared AGSWrapper As New AGS.NativeWrapper
    Public Shared initialiseError As TextWriter
    Public Shared initialiseOut As TextWriter
    Private Shared ThisConsole As Console

    Class GuiRedirect

        Private Shared hWndConsole As IntPtr
        Private Declare Auto Function ShowWindow Lib "user32.dll" (ByVal hWnd As IntPtr, ByVal nCmdShow As Integer) As Boolean
        Private Declare Auto Function GetConsoleWindow Lib "kernel32.dll" () As IntPtr

        <DllImport("kernel32.dll", SetLastError:=True)>
        Private Shared Function AttachConsole(dwProcessId As Integer) As Boolean
        End Function
        <DllImport("kernel32.dll", SetLastError:=True)>
        Private Shared Function GetStdHandle(nStdHandle As StandardHandle) As IntPtr
        End Function
        <DllImport("kernel32.dll", SetLastError:=True)>
        Private Shared Function SetStdHandle(nStdHandle As StandardHandle, handle As IntPtr) As Boolean
        End Function
        <DllImport("kernel32.dll", SetLastError:=True)>
        Private Shared Function GetFileType(handle As IntPtr) As FileType
        End Function
        <DllImport("kernel32.dll", SetLastError:=True)>
        Private Shared Function AllocConsole() As <MarshalAs(UnmanagedType.Bool)> Boolean
        End Function
        <DllImport("kernel32.dll", SetLastError:=True)>
        Private Shared Function FreeConsole() As <MarshalAs(UnmanagedType.Bool)> Boolean
        End Function

        Private Enum StandardHandle As Integer
            Input = CType(-10, Integer)
            Output = CType(-11, Integer)
            [Error] = CType(-12, Integer)
        End Enum

        Private Enum FileType As UInteger
            Unknown = &H0
            Disk = &H1
            [Char] = &H2
            Pipe = &H3
        End Enum

        Private Shared Function IsRedirected(handle As IntPtr) As Boolean
            Dim fileType__1 As FileType = GetFileType(handle)

            Return (fileType__1 = FileType.Disk) OrElse (fileType__1 = FileType.Pipe)
        End Function
        Public Shared Sub Close()
            FreeConsole()
        End Sub

        Public Shared Sub Redirect()
            'Alloc()
            '    FreeConsole()

            If Not AttachConsole(-1) Then
                AllocConsole()
            End If

            If IsRedirected(GetStdHandle(StandardHandle.Output)) Then
                SetStdHandle(StdHandle.Output, GetConsoleStandardOutput())
                initialiseOut = Console.Out
            End If

            Dim errorRedirected As Boolean = IsRedirected(GetStdHandle(StandardHandle.Output))
            If errorRedirected Then
                SetStdHandle(StdHandle.Input, GetConsoleStandardInput())
                initialiseError = Console.[Error]
            End If


            ' If Not errorRedirected Then
            ' SetStdHandle(StandardHandle.Output, GetStdHandle(StandardHandle.Output))
            '   End If

            hWndConsole = GetConsoleWindow()

            ShowWindow(hWndConsole, 1)

        End Sub


    End Class
    Public Shared Sub CloseAGS()

        GuiRedirect.Close()
    End Sub
    Public Shared Sub Redirect()
        GuiRedirect.Redirect()
        Console.WriteLine("Console Attached")
    End Sub
    Public Shared Sub Setup()


    End Sub
    ''' <summary>
    ''' Allocates a console and resets the standard stream handles.
    ''' </summary>
    Public Shared Sub Alloc()
        If Not AllocConsole() Then

        End If
        SetStdHandle(StdHandle.Output, GetConsoleStandardOutput())
        SetStdHandle(StdHandle.Input, GetConsoleStandardInput())
    End Sub

    Private Shared Function GetConsoleStandardInput() As IntPtr
        Dim handle As Object = CreateFile("CONIN$", DesiredAccess.GenericRead Or DesiredAccess.GenericWrite, FileShare.ReadWrite, IntPtr.Zero, FileMode.Open, FileAttributes.Normal,
            IntPtr.Zero)
        If handle = InvalidHandleValue Then
            ' Throw New Win32Exception()
        End If
        Return handle
    End Function

    Private Shared Function GetConsoleStandardOutput() As IntPtr
        Dim handle As Object = CreateFile("CONOUT$", DesiredAccess.GenericWrite Or DesiredAccess.GenericWrite, FileShare.ReadWrite, IntPtr.Zero, FileMode.Open, FileAttributes.Normal,
            IntPtr.Zero)
        If handle = InvalidHandleValue Then
            'Throw New Win32Exception()
        End If
        Return handle
    End Function

    <DllImport("kernel32.dll", SetLastError:=True)>
    Private Shared Function AllocConsole() As Boolean
    End Function

    <DllImport("kernel32.dll")>
    Private Shared Function SetStdHandle(nStdHandle As StdHandle, hHandle As IntPtr) As Boolean
    End Function

    <DllImport("kernel32.dll", SetLastError:=True, CharSet:=CharSet.Auto)>
    Private Shared Function CreateFile(lpFileName As String, <MarshalAs(UnmanagedType.U4)> dwDesiredAccess As DesiredAccess, <MarshalAs(UnmanagedType.U4)> dwShareMode As FileShare, lpSecurityAttributes As IntPtr, <MarshalAs(UnmanagedType.U4)> dwCreationDisposition As FileMode, <MarshalAs(UnmanagedType.U4)> dwFlagsAndAttributes As FileAttributes,
        hTemplateFile As IntPtr) As IntPtr
    End Function

    <Flags>
    Enum DesiredAccess As UInteger
        GenericRead = &H80000000UI
        GenericWrite = &H40000000
        GenericExecute = &H20000000
        GenericAll = &H10000000
    End Enum

    Private Enum StdHandle As Integer
        Input = -10
        Output = -11
        [Error] = -12
    End Enum

    Private Shared ReadOnly InvalidHandleValue As New IntPtr(-1)

End Class
