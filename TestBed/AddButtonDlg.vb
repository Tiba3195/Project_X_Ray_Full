Imports System.Windows.Forms

Public Class AddButtonDlg
    Public NewButton As FButtonStruct

    Private Sub OK_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OK_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK
        If NewButton Is Nothing Then
            NewButton = New FButtonStruct
        End If

        NewButton.Command = ButtonCommand.Text
        NewButton.Name = ButtonName.Text
        NewButton.toolTip = ButtonToolTip.Text
        NewButton.Text = ButtonText.Text
        NewButton.type = -1
        NewButton.Dims = New V4
        NewButton.Dims.X = ButtonDimsX.Text
        NewButton.Dims.Y = ButtonDimsY.Text
        NewButton.Dims.Z = ButtonDimsZ.Text
        NewButton.Dims.W = ButtonDimsW.Text

        NewButton.TextOffset = New V2
        NewButton.TextOffset.X = ButtonTextOffsetX.Text
        NewButton.TextOffset.Y = ButtonTextOffsetY.Text
        NewButton.TextureIndex = TextureIndexBox.Text
        NewButton.TextSize = New V2
        NewButton.TextSize.X = ButtonTextSizeX.Text
        NewButton.TextSize.Y = ButtonTextSizeY.Text
        NewButton.UseTextureIndex = CheckBox1.Checked
        Me.Close()
    End Sub

    Private Sub Cancel_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel

        Me.Close()
    End Sub

    Private Sub AddButtonDlg_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        If NewButton IsNot Nothing Then
            ButtonCommand.Text = NewButton.Command
            ButtonName.Text = NewButton.Name
            ButtonToolTip.Text = NewButton.toolTip
            ButtonText.Text = NewButton.Text
            NewButton.type = -1
            ButtonDimsX.Text = NewButton.Dims.X
            ButtonDimsY.Text = NewButton.Dims.Y
            ButtonDimsZ.Text = NewButton.Dims.Z
            ButtonDimsW.Text = NewButton.Dims.W
            ButtonTextOffsetX.Text = NewButton.TextOffset.X
            ButtonTextOffsetY.Text = NewButton.TextOffset.Y
            ButtonTextSizeX.Text = NewButton.TextSize.X
            ButtonTextSizeY.Text = NewButton.TextSize.Y
            TextureIndexBox.Text = NewButton.TextureIndex
            CheckBox1.Checked = NewButton.UseTextureIndex

            Me.Text = "Edit Button"
        Else
            Me.Text = "Add New Button"
        End If
    End Sub
End Class
