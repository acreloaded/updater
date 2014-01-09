Imports System.Net
Imports System
Imports System.IO
Imports ComponentAce.Compression.ZipForge
Imports ComponentAce.Compression.Archiver
Public Class Form1
    Public Shared WithEvents httpclient As WebClient
    Dim WithEvents WC As New WebClient
    Dim appdata As String = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        If (System.IO.File.Exists(Application.StartupPath & "\Downloader.exe")) Then
            System.IO.File.Delete(Application.StartupPath & "\Downloader.exe")
        End If
        If (System.IO.File.Exists(Application.StartupPath & "\ZipForge.dll")) Then
            System.IO.File.Delete(Application.StartupPath & "\ZipForge.dll")
        End If
        CheckForInternet()
    End Sub
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

    Public Sub CheckForInternet()
        If IsConnectionAvailable() = True Then
            Timer2.Start()
            message_file()
            If (Not System.IO.File.Exists(Application.StartupPath & "\versions\data.dat")) Then
                data_file()
            End If
            If (Not System.IO.Directory.Exists(Application.StartupPath & "\bin_win32")) Then
                Button4.Visible = True
                Label1.Visible = True
                Label2.Visible = True
                Dim s As Size = Me.Size
                s.Height = 305
                Me.Size = s
            End If
            If (Not System.IO.File.Exists(Application.StartupPath & "\Client.bat")) Then
                Button1.Visible = False
            End If
            If (Not System.IO.File.Exists(Application.StartupPath & "\Server.bat")) Then
                Button2.Visible = False
            End If
            imagebox()
            CheckForUpdates()

        Else
            MsgBox("Your computer is not connected to Internet!", MsgBoxStyle.Critical, "Please connect to Internet")
            Timer3.Start()
        End If
    End Sub
    Public Sub imagebox()
        PictureBox1.ImageLocation = "https://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/logo.png"
    End Sub
    Public Sub message_file()

        Dim request As System.Net.HttpWebRequest = System.Net.HttpWebRequest.Create("https://dl.dropbox.com/s/gtei1lwtgp8l8gd/news.dat?dl=1")

        Dim response As System.Net.HttpWebResponse = request.GetResponse()
        Dim sr As System.IO.StreamReader = New System.IO.StreamReader(response.GetResponseStream())
        Dim message As String = sr.ReadToEnd()
        If File.Exists(Application.StartupPath & "\data\config\saved.cfg") = True Then
            Dim line As String = File.ReadAllLines(Application.StartupPath & "\data\config\saved.cfg").FirstOrDefault(Function(s As String) s.StartsWith("name"))
            Dim text As String = line.Replace("name", "")
            Dim text1 As String = text.Replace("""", "")
            Dim user As String = text1
            Label5.Text = "Welcome back" + user + "! " + message
        Else
            Label5.Text = message
        End If
    End Sub
    Private Sub data_file()
        'replace example.com with address to data.txt'
        My.Computer.Network.DownloadFile("https://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/data.dat", Application.StartupPath & "\versions\data.dat")
    End Sub
    Public Sub CheckForUpdates()



        Dim request As System.Net.HttpWebRequest = System.Net.HttpWebRequest.Create("https://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/launcher.dat")

        Dim response As System.Net.HttpWebResponse = request.GetResponse()
        Dim sr As System.IO.StreamReader = New System.IO.StreamReader(response.GetResponseStream())
        Dim newestversion As String = sr.ReadToEnd()
        Dim currentversion As String = Application.ProductVersion
        If newestversion.Contains(currentversion) Then

        Else
            Form2.Show()
            MsgBox("Launcher Update Available")
        End If






        'Checks for updates for the data'
        Try
            Dim urlfile As String = (Application.StartupPath & "\url.dat")
            Dim datafile As String = (Application.StartupPath & "\data.dat")
            Dim MyVer As String = My.Computer.FileSystem.ReadAllText(Application.StartupPath & "\versions\data.dat")

            If My.Computer.FileSystem.FileExists(datafile) Then
                My.Computer.FileSystem.DeleteFile(datafile)
            End If
            If My.Computer.FileSystem.FileExists(urlfile) Then
                My.Computer.FileSystem.DeleteFile(urlfile)
            End If

            My.Computer.Network.DownloadFile("https://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/data.dat", datafile)
            My.Computer.Network.DownloadFile("https://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/url.dat", urlfile)
            Dim LastVer As String = My.Computer.FileSystem.ReadAllText(datafile)

            If Not MyVer = LastVer Then
                MsgBox("Game Update Available")
                Button3.Visible = True
                Label1.Visible = True
                Label2.Visible = True
                Dim s As Size = Me.Size
                s.Height = 305
                Me.Size = s
            End If
        Catch
        End Try
    End Sub
    Public Sub install_once_data()
        Try
            Dim url As String = My.Computer.FileSystem.ReadAllText(Application.StartupPath & "\url.dat")
            Label2.Text = "Status: Downloading ACR..."
            Timer1.Start()
            ProgressBar1.Value = ProgressBar1.Minimum
            ProgressBar1.Visible = True
            'Dim filepath As String = appdata "\ACR\versions\data.dat"'
            WC.DownloadFileAsync(New Uri(url), Application.StartupPath & "\data.zip")
            My.Computer.Network.DownloadFile("http://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/ZipForge.dll", Application.StartupPath & "\ZipForge.dll")
            If ProgressBar1.Value = ProgressBar1.Minimum Then
                Label1.Visible = False
                Button1.Visible = False
                Button2.Visible = False
                Button5.Visible = False
            End If
            Do While WC.IsBusy
                Application.DoEvents()
            Loop
            unzip_data()
        Catch
        End Try
    End Sub
    Private Sub download_data()
        Try
            Dim url As String = My.Computer.FileSystem.ReadAllText(Application.StartupPath & "\url.dat")
            Label2.Text = "Status: Updating ACR..."
            Timer1.Start()
            ProgressBar1.Value = ProgressBar1.Minimum
            ProgressBar1.Visible = True
            'Dim filepath As String = appdata "\ACR\versions\data.dat"'
            WC.DownloadFileAsync(New Uri(url), Application.StartupPath & "\data.zip")
            My.Computer.Network.DownloadFile("http://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/ZipForge.dll", Application.StartupPath & "\ZipForge.dll")
            If ProgressBar1.Value = ProgressBar1.Minimum Then
                Label1.Visible = False
                Button1.Visible = False
                Button2.Visible = False
                Button5.Visible = False
            End If
            Do While WC.IsBusy
                Application.DoEvents()
            Loop

            Button3.Visible = False
            Kill(Application.StartupPath & "\versions\data.dat")
            unzip_data()
            after_unzip()
        Catch
        End Try
    End Sub
    Private Sub unzip_data()
        If (Not System.IO.File.Exists(Application.StartupPath & "\ZipForge.dll")) Then
            My.Computer.Network.DownloadFile("http://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/ZipForge.dll", Application.StartupPath & "\ZipForge.dll")
        Else
            Try
                Dim archiver As New ZipForge()
                ' The name of the ZIP file to unzip
                archiver.FileName = Application.StartupPath & "\data.zip"
                ' Open an existing archive
                archiver.OpenArchive(System.IO.FileMode.Open)
                ' Default path for all operations                
                archiver.BaseDir = Application.StartupPath & "\"
                ' Extract all files from the archive to C:\Temp folder
                archiver.ExtractFiles("*.*")
                ' Close archive
                archiver.CloseArchive()
                ' Catch all exceptions of the ArchiverException type
            Catch ae As ArchiverException
                Console.WriteLine("Message: {0} Error code: {1}", ae.Message, ae.ErrorCode)
                ' Wait for keypress
                Console.ReadLine()
            End Try
            after_unzip()
        End If
    End Sub
    Public Sub after_unzip()
        Kill(Application.StartupPath & "\versions\data.dat")
        My.Computer.Network.DownloadFile("https://assaultcuber-updater.googlecode.com/svn/trunk/updateinfo/data.dat", Application.StartupPath & "\versions\data.dat")
        Try
            Dim Client As String = "Client.bat"
            Dim Server As String = "Server.bat"
            Dim c As New FileInfo(Client)
            Dim s As New FileInfo(Server)
            c.Attributes = FileAttributes.Hidden
            s.Attributes = FileAttributes.Hidden
            Console.WriteLine("File's Hidden")
        Catch ex As Exception
            ' handle ex
        End Try
        Label3.Visible = False
        Button1.Visible = True
        Button2.Visible = True
        Button5.Visible = True

        Kill(Application.StartupPath & "\data.zip")
        Kill(Application.StartupPath & "\ZipForge.dll")
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        If ProgressBar1.Value = 98 Then
            Label3.Visible = True
        End If
        Label6.Text = ProgressBar1.Value & (" %")
        If ProgressBar1.Value = ProgressBar1.Maximum Then
            Label2.Text = "Status: Done!"
        End If
        If ProgressBar1.Value = ProgressBar1.Maximum Then
            Timer1.Stop()
            Dim s As Size = Me.Size
            s.Height = 250
            Me.Size = s
        End If

    End Sub
    Private Sub WC_DownloadProgressChanged(ByVal sender As Object, ByVal e As DownloadProgressChangedEventArgs) Handles WC.DownloadProgressChanged
        ProgressBar1.Value = e.ProgressPercentage
    End Sub
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim p As New System.Diagnostics.Process()
        p.StartInfo.FileName = "Client.bat"
        p.Start()
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Dim p As New System.Diagnostics.Process()
        p.StartInfo.FileName = "Server.bat"
        p.Start()
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Dim s As Size = Me.Size
        s.Height = 380
        Me.Size = s
        Button3.Visible = False
        Button1.Visible = False
        Button2.Visible = False
        download_data()
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        Dim s As Size = Me.Size
        s.Height = 380
        Me.Size = s
        Button4.Visible = False
        Label1.Visible = False
        install_once_data()
    End Sub
    Private Sub Form1_FormClosing(sender As System.Object, e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
        If (System.IO.File.Exists(Application.StartupPath & "\url.dat")) Then
            My.Computer.FileSystem.DeleteFile(Application.StartupPath & "\url.dat")
        End If
        If (System.IO.File.Exists(Application.StartupPath & "\data.dat")) Then
            My.Computer.FileSystem.DeleteFile(Application.StartupPath & "\data.dat")
        End If
        Try
            Kill(Application.StartupPath & "\data.zip")
            Kill(Application.StartupPath & "\ZipForge.dll")
        Catch ex As Exception
        End Try
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        Options.Show()
    End Sub
    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick

        Label5.Left -= 5
        If Label5.Right < 0 Then
            Label5.Left = Width
        End If

    End Sub
    Public Sub reinstall()
        If (Not System.IO.File.Exists(Application.StartupPath & "\versions\data.dat")) Then
            data_file()
        End If
        Button1.Visible = False
        Button2.Visible = False
        CheckForUpdates()
        Dim s As Size = Me.Size
        s.Height = 380
        Me.Size = s
        Button4.Visible = False
        Label1.Visible = False
        install_once_data()
    End Sub
    Public Sub reload()
        If (Not System.IO.File.Exists(Application.StartupPath & "\versions\data.dat")) Then
            data_file()
        End If
        If (Not System.IO.Directory.Exists(Application.StartupPath & "\bin_win32")) Then
            Button4.Visible = True
            Label1.Visible = True
            Label2.Visible = True
            Dim s As Size = Me.Size
            s.Height = 305
            Me.Size = s
        End If
        Button1.Visible = False
        Button2.Visible = False
        CheckForUpdates()
    End Sub
    Private Sub Timer3_Tick(sender As Object, e As EventArgs) Handles Timer3.Tick

        Label5.Left -= 5
        If Label5.Right < 0 Then
            Label5.Left = Width
        End If
        offline_message_file()
    End Sub
    Public Sub offline_message_file()
        If File.Exists(Application.StartupPath & "\data\config\saved.cfg") = True Then
            Dim line As String = File.ReadAllLines(Application.StartupPath & "\data\config\saved.cfg").FirstOrDefault(Function(s As String) s.StartsWith("name"))
            Dim text As String = line.Replace("name", "")
            Dim text1 As String = text.Replace("""", "")
            Dim user As String = text1
            Label5.Text = "Welcome back" + user + "! " + "Please connect to internet."
        Else
            Label5.Text = "Please connect to internet."
        End If
    End Sub
    Private Sub scroll_stop() Handles Label5.MouseHover
        If Timer2.Enabled Then
            Timer2.Stop()
        Else
            Timer3.Stop()
        End If
    End Sub
    Private Sub scroll_start() Handles Label5.MouseLeave
        If Timer2.Enabled = False Then
            If Timer3.Enabled Then
            Else
                Timer2.Start()
            End If
        End If
    End Sub
End Class
