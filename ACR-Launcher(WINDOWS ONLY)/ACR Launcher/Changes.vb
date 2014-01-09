Public Class Changes
    Private Sub Changes_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        info()
    End Sub
    Private Sub info()
        Try
            Dim request As System.Net.HttpWebRequest = System.Net.HttpWebRequest.Create("https://dl.dropbox.com/s/osqkqlqj5hxlvvj/changes.dat?dl=1")

            Dim response As System.Net.HttpWebResponse = request.GetResponse()
            Dim sr As System.IO.StreamReader = New System.IO.StreamReader(response.GetResponseStream())
            Dim message As String = sr.ReadToEnd()
            RichTextBox1.Text = message
        Catch
        End Try

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.Close()
    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs) Handles RichTextBox1.TextChanged

    End Sub
End Class