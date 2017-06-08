Imports System.Windows.Forms
Imports SharpDX.Direct3D11

Public Class SettingDlg
    Private ButtonImage As ShaderResourceView
    Private PanelImage As ShaderResourceView
    Private Sub OK_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OK_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Close()
    End Sub

    Private Sub Cancel_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub SettingDlg_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub
End Class
