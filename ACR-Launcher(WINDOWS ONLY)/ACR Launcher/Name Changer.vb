Imports System.IO

Public Class Name_Changer

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

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Me.Close()
    End Sub

    Private Sub Name_Changer_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim line As String = File.ReadAllLines(Application.StartupPath & "\data\config\saved.cfg").FirstOrDefault(Function(s As String) s.StartsWith("name"))
        Dim text As String = line.Replace("name", "")
        Dim text1 As String = text.Replace(" ", "")
        Dim text2 As String = text1.Replace("""", "")
        TextBox1.Text = text2
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim line As String = File.ReadAllLines(Application.StartupPath & "\data\config\saved.cfg").FirstOrDefault(Function(s As String) s.StartsWith("name"))
        Dim text As String = line.Replace("name", "")
        My.Computer.FileSystem.WriteAllText(Application.StartupPath & "\data\config\saved.cfg", My.Computer.FileSystem.ReadAllText(Application.StartupPath & "\data\config\saved.cfg").Replace(text, " """ + TextBox1.Text + """"), False)
        MsgBox("Your nickname has been changed to " + TextBox1.Text + ".")
        If IsConnectionAvailable() = True Then
            Form1.message_file()
        Else
            Form1.offline_message_file()
        End If
        Me.Close()
    End Sub
End Class