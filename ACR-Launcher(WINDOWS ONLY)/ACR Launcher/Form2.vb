Imports System.Net
Imports System
Imports System.IO
Public Class Form2
    Public Shared WithEvents httpclient As WebClient
    Dim WithEvents WC As New WebClient
    Dim appdata As String = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)
    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Interval = 2000
        Timer1.Start()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            WC.DownloadFileAsync(New Uri("http://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/Downloader.exe"), Application.StartupPath & "\Downloader.exe")
            Do While WC.IsBusy
                Application.DoEvents()
            Loop
            Shell(Application.StartupPath & "\Downloader.exe")
            Form1.Close()
            Me.Close()
        Catch ex As Exception
        End Try
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Form1.Hide()
    End Sub
    Private Sub Form2_FormClosing(sender As System.Object, e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
        Form1.Close()
    End Sub
End Class