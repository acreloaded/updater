Imports System.IO

Public Class Options
    Dim appdata As String = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)
    Public Function IsConnectionAvailable() As Boolean
        ' Returns True if connection is available 
        ' Replace www.yoursite.com with a site that
        ' is guaranteed to be online - perhaps your 
        ' corporate site, or microsoft.com
        Dim objUrl As New System.Uri("http://www.google.com/")
        ' Setup WebRequest
        Dim objWebReq As System.Net.WebRequest
        objWebReq = System.Net.WebRequest.Create(objUrl)
        Dim objResp As System.Net.WebResponse
        Try
            ' Attempt to get response and return True
            objResp = objWebReq.GetResponse
            objResp.Close()
            objWebReq = Nothing
            Return True
        Catch
            objWebReq = Nothing
            Return False
        End Try
    End Function
    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click

        Me.Close()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If (System.IO.Directory.Exists(Application.StartupPath & "\data\config\")) Then
            System.IO.Directory.Delete(Application.StartupPath & "\data\config", True)
            MsgBox("Data has been reset!")
        End If
    End Sub
    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        
        Try
            If My.Computer.FileSystem.DirectoryExists(Application.StartupPath) Then

                If (System.IO.Directory.Exists(Application.StartupPath & "\bin_win32")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\bin_win32", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\bot")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\bot", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\config")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\config", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\data")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\data", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\demos")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\demos", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\docs")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\docs", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\locale")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\locale", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\packages")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\packages", True)
                End If
                If (System.IO.Directory.Exists(Application.StartupPath & "\versions")) Then
                    System.IO.Directory.Delete(Application.StartupPath & "\versions", True)
                End If
                SetAttr(Application.StartupPath & "\Client.bat", FileAttribute.Normal)
                SetAttr(Application.StartupPath & "\Server.bat", FileAttribute.Normal)
                Kill(Application.StartupPath & "\*.bat*")
                Kill(Application.StartupPath & "\*.dat*")
                Kill(Application.StartupPath & "\*.txt*")
            End If
        Catch ex As Exception
        End Try
        MsgBox("AssaultCube Reloaded has been uninstalled!", MsgBoxStyle.Information, "Uninstalled")
        Form1.reload()
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        If IsConnectionAvailable() = True Then
            Try
                If My.Computer.FileSystem.DirectoryExists(Application.StartupPath) Then

                    If (System.IO.Directory.Exists(Application.StartupPath & "\bin_win32")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\bin_win32", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\bot")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\bot", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\config")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\config", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\data")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\data", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\demos")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\demos", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\docs")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\docs", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\locale")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\locale", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\packages")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\packages", True)
                    End If
                    If (System.IO.Directory.Exists(Application.StartupPath & "\versions")) Then
                        System.IO.Directory.Delete(Application.StartupPath & "\versions", True)
                    End If
                    SetAttr(Application.StartupPath & "\Client.bat", FileAttribute.Normal)
                    SetAttr(Application.StartupPath & "\Server.bat", FileAttribute.Normal)
                    Kill(Application.StartupPath & "\*.bat*")
                    Kill(Application.StartupPath & "\*.dat*")
                    Kill(Application.StartupPath & "\*.txt*")
                End If
            Catch ex As Exception
            End Try


            Me.Hide()
            Form1.reinstall()
            Me.Close()
        Else
            MsgBox("You must be connected to the Internet to be able to reinstall ACR.")
        End If
    End Sub
    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        If IsConnectionAvailable() = True Then
            Extra.Show()
        Else
            MsgBox("You are not connect to Internet to get this feature.")
        End If
    End Sub

    Private Sub Options_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        If IsConnectionAvailable() = True Then
            Changes.Show()
        Else
            MsgBox("You are not connect to Internet to get this feature.")
        End If
    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        Try
            Kill(Application.StartupPath & "\*.txt*")
            MsgBox("All server log files have been removed!")
        Catch ex As Exception
        End Try
    End Sub

    Private Sub Button8_Click(sender As Object, e As EventArgs) Handles Button8.Click
        If File.Exists(Application.StartupPath & "\data\config\saved.cfg") = True Then
            Name_Changer.Show()
        Else
            MsgBox("There is no nickname set. Please start the client.", MsgBoxStyle.Information)
        End If
    End Sub
End Class