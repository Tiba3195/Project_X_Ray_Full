Imports System.Windows.Forms

Public Class AddPanelDlg

    Public panel As FPanelStruct
    Private Sub OK_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OK_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK
        If panel Is Nothing Then
            panel = New FPanelStruct
        End If

        panel.Name = PanelNameTextBox.Text

        panel.Text = PanelName.Text

        panel.Dims = New V4
        panel.Dims.X = PanelDimsX.Text
        panel.Dims.Y = PanelDimsY.Text
        panel.Dims.Z = PanelDimsZ.Text
        panel.Dims.W = PanelDimsW.Text

        panel.TextOffset = New V2
        panel.TextOffset.X = TextOffsetX.Text
        panel.TextOffset.Y = TextOffsetY.Text

        panel.TextSize = New V2
        panel.TextSize.X = TextBox1.Text
        panel.TextSize.Y = TextBox2.Text
        panel.LayoutType = ComboBox1.SelectedItem

        panel.XSpacing = TextBox3.Text
        panel.YSpacing = TextBox4.Text
        panel.XMargin = TextBox6.Text
        panel.YMargin = TextBox5.Text

        Me.Close()
    End Sub

    Private Sub Cancel_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel_Button.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub AddPanelDlg_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        ComboBox1.DataSource = [Enum].GetValues(GetType(LayoutType))
        If panel IsNot Nothing Then
            PanelNameTextBox.Text = panel.Name
            PanelName.Text = panel.Text
            PanelDimsX.Text = panel.Dims.X
            PanelDimsY.Text = panel.Dims.Y
            PanelDimsZ.Text = panel.Dims.Z
            PanelDimsW.Text = panel.Dims.W
            TextOffsetX.Text = panel.TextOffset.X
            TextOffsetY.Text = panel.TextOffset.Y
            TextBox1.Text = panel.TextSize.X
            TextBox2.Text = panel.TextSize.Y

            TextBox3.Text = panel.XSpacing
            TextBox4.Text = panel.YSpacing

            TextBox6.Text = panel.XMargin
            TextBox5.Text = panel.YMargin

            ComboBox1.SelectedItem = panel.LayoutType

            Me.Text = "Edit Panel"
        Else
            Me.Text = "Add New Panel"
        End If
    End Sub
End Class
