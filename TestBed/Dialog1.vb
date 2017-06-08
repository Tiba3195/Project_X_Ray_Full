Imports System.Windows.Forms

Public Class Dialog1

    Public SelectedSreenSize As ScreenSizes

    Private Sub OK_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OK_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Close()
    End Sub

    Private Sub Cancel_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub meGotFocus(sender As Object, e As EventArgs) Handles Me.GotFocus
        Me.ComboBox1.DataSource = System.Enum.GetValues(GetType(ScreenSizes))
    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedValueChanged
        SelectedSreenSize = Me.ComboBox1.SelectedValue
    End Sub
End Class
