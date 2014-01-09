
Public Class Extra
    Private Sub Extra_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        info()
        Timer1.Start()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs)

    End Sub
    Private Sub info()
        Try
            Dim request As System.Net.HttpWebRequest = System.Net.HttpWebRequest.Create("https://dl.dropbox.com/s/5i4lut1dj7s6qmk/extra.rtf?dl=1")
            Dim response As System.Net.HttpWebResponse = request.GetResponse()
            Dim sr As System.IO.StreamReader = New System.IO.StreamReader(response.GetResponseStream())
            Dim message As String = sr.ReadToEnd()


            RichTextBox1.Rtf = message
            RichTextBox1.SelectionProtected = True
            RichTextBox1.WordWrap = True
        Catch
        End Try
        Try
            Dim request As System.Net.HttpWebRequest = System.Net.HttpWebRequest.Create("https://dl.dropbox.com/s/4jnoxl91p1w9ypa/extra%27s%20length.dat?dl=1")

            Dim response As System.Net.HttpWebResponse = request.GetResponse()
            Dim sr As System.IO.StreamReader = New System.IO.StreamReader(response.GetResponseStream())
            Dim message As String = sr.ReadToEnd()

            RichTextBox1.Height = message
        Catch ex As Exception

        End Try
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        RichTextBox1.Top -= 2
        If RichTextBox1.Bottom < 0 Then
            RichTextBox1.Top = Me.ClientRectangle.Bottom
        End If
    End Sub
 End Class