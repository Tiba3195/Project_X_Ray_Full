<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class AddButtonDlg
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.TableLayoutPanel1 = New System.Windows.Forms.TableLayoutPanel()
        Me.OK_Button = New System.Windows.Forms.Button()
        Me.Cancel_Button = New System.Windows.Forms.Button()
        Me.ButtonToolTip = New System.Windows.Forms.TextBox()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.ButtonCommand = New System.Windows.Forms.TextBox()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.ButtonText = New System.Windows.Forms.TextBox()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.ButtonTextSizeY = New System.Windows.Forms.TextBox()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.ButtonTextSizeX = New System.Windows.Forms.TextBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.ButtonDimsW = New System.Windows.Forms.TextBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.ButtonDimsZ = New System.Windows.Forms.TextBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.ButtonDimsY = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.ButtonDimsX = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.ButtonName = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.ButtonTextOffsetX = New System.Windows.Forms.TextBox()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.ButtonTextOffsetY = New System.Windows.Forms.TextBox()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.CheckBox1 = New System.Windows.Forms.CheckBox()
        Me.TextureIndexBox = New System.Windows.Forms.TextBox()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.TableLayoutPanel1.SuspendLayout()
        Me.SuspendLayout()
        '
        'TableLayoutPanel1
        '
        Me.TableLayoutPanel1.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.TableLayoutPanel1.ColumnCount = 2
        Me.TableLayoutPanel1.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel1.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel1.Controls.Add(Me.OK_Button, 0, 0)
        Me.TableLayoutPanel1.Controls.Add(Me.Cancel_Button, 1, 0)
        Me.TableLayoutPanel1.Location = New System.Drawing.Point(365, 200)
        Me.TableLayoutPanel1.Margin = New System.Windows.Forms.Padding(4)
        Me.TableLayoutPanel1.Name = "TableLayoutPanel1"
        Me.TableLayoutPanel1.RowCount = 1
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel1.Size = New System.Drawing.Size(195, 36)
        Me.TableLayoutPanel1.TabIndex = 0
        '
        'OK_Button
        '
        Me.OK_Button.Anchor = System.Windows.Forms.AnchorStyles.None
        Me.OK_Button.Location = New System.Drawing.Point(4, 4)
        Me.OK_Button.Margin = New System.Windows.Forms.Padding(4)
        Me.OK_Button.Name = "OK_Button"
        Me.OK_Button.Size = New System.Drawing.Size(89, 28)
        Me.OK_Button.TabIndex = 0
        Me.OK_Button.Text = "OK"
        '
        'Cancel_Button
        '
        Me.Cancel_Button.Anchor = System.Windows.Forms.AnchorStyles.None
        Me.Cancel_Button.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Cancel_Button.Location = New System.Drawing.Point(101, 4)
        Me.Cancel_Button.Margin = New System.Windows.Forms.Padding(4)
        Me.Cancel_Button.Name = "Cancel_Button"
        Me.Cancel_Button.Size = New System.Drawing.Size(89, 28)
        Me.Cancel_Button.TabIndex = 1
        Me.Cancel_Button.Text = "Cancel"
        '
        'ButtonToolTip
        '
        Me.ButtonToolTip.Location = New System.Drawing.Point(345, 47)
        Me.ButtonToolTip.Name = "ButtonToolTip"
        Me.ButtonToolTip.Size = New System.Drawing.Size(158, 22)
        Me.ButtonToolTip.TabIndex = 48
        Me.ButtonToolTip.Text = "ToolTip"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(275, 47)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(64, 17)
        Me.Label12.TabIndex = 47
        Me.Label12.Text = "Tool Tip:"
        '
        'ButtonCommand
        '
        Me.ButtonCommand.Location = New System.Drawing.Point(96, 160)
        Me.ButtonCommand.Name = "ButtonCommand"
        Me.ButtonCommand.Size = New System.Drawing.Size(459, 22)
        Me.ButtonCommand.TabIndex = 46
        Me.ButtonCommand.Text = "Cammand goes here!"
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(15, 160)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(75, 17)
        Me.Label11.TabIndex = 45
        Me.Label11.Text = "Command:"
        '
        'ButtonText
        '
        Me.ButtonText.Location = New System.Drawing.Point(320, 17)
        Me.ButtonText.Name = "ButtonText"
        Me.ButtonText.Size = New System.Drawing.Size(189, 22)
        Me.ButtonText.TabIndex = 44
        Me.ButtonText.Text = "Add Text"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(275, 17)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(39, 17)
        Me.Label10.TabIndex = 43
        Me.Label10.Text = "Text:"
        '
        'ButtonTextSizeY
        '
        Me.ButtonTextSizeY.Location = New System.Drawing.Point(283, 122)
        Me.ButtonTextSizeY.Name = "ButtonTextSizeY"
        Me.ButtonTextSizeY.Size = New System.Drawing.Size(42, 22)
        Me.ButtonTextSizeY.TabIndex = 42
        Me.ButtonTextSizeY.Text = "0"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(183, 126)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(83, 17)
        Me.Label6.TabIndex = 41
        Me.Label6.Text = "Text Size Y:"
        '
        'ButtonTextSizeX
        '
        Me.ButtonTextSizeX.Location = New System.Drawing.Point(283, 93)
        Me.ButtonTextSizeX.Name = "ButtonTextSizeX"
        Me.ButtonTextSizeX.Size = New System.Drawing.Size(42, 22)
        Me.ButtonTextSizeX.TabIndex = 40
        Me.ButtonTextSizeX.Text = "0"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(183, 93)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(83, 17)
        Me.Label7.TabIndex = 39
        Me.Label7.Text = "Text Size X:"
        '
        'ButtonDimsW
        '
        Me.ButtonDimsW.Location = New System.Drawing.Point(200, 59)
        Me.ButtonDimsW.Name = "ButtonDimsW"
        Me.ButtonDimsW.Size = New System.Drawing.Size(42, 22)
        Me.ButtonDimsW.TabIndex = 34
        Me.ButtonDimsW.Text = "64"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(197, 39)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(52, 17)
        Me.Label5.TabIndex = 33
        Me.Label5.Text = "Size Y:"
        '
        'ButtonDimsZ
        '
        Me.ButtonDimsZ.Location = New System.Drawing.Point(138, 59)
        Me.ButtonDimsZ.Name = "ButtonDimsZ"
        Me.ButtonDimsZ.Size = New System.Drawing.Size(42, 22)
        Me.ButtonDimsZ.TabIndex = 32
        Me.ButtonDimsZ.Text = "64"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(135, 39)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(52, 17)
        Me.Label4.TabIndex = 31
        Me.Label4.Text = "Size X:"
        '
        'ButtonDimsY
        '
        Me.ButtonDimsY.Location = New System.Drawing.Point(76, 59)
        Me.ButtonDimsY.Name = "ButtonDimsY"
        Me.ButtonDimsY.Size = New System.Drawing.Size(42, 22)
        Me.ButtonDimsY.TabIndex = 30
        Me.ButtonDimsY.Text = "0"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(73, 39)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(49, 17)
        Me.Label3.TabIndex = 29
        Me.Label3.Text = "Pos Y:"
        '
        'ButtonDimsX
        '
        Me.ButtonDimsX.Location = New System.Drawing.Point(18, 59)
        Me.ButtonDimsX.Name = "ButtonDimsX"
        Me.ButtonDimsX.Size = New System.Drawing.Size(42, 22)
        Me.ButtonDimsX.TabIndex = 28
        Me.ButtonDimsX.Text = "0"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(15, 39)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(49, 17)
        Me.Label2.TabIndex = 27
        Me.Label2.Text = "Pos X:"
        '
        'ButtonName
        '
        Me.ButtonName.Location = New System.Drawing.Point(69, 12)
        Me.ButtonName.Name = "ButtonName"
        Me.ButtonName.Size = New System.Drawing.Size(173, 22)
        Me.ButtonName.TabIndex = 26
        Me.ButtonName.Text = "Button Name"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(14, 12)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(49, 17)
        Me.Label1.TabIndex = 25
        Me.Label1.Text = "Name:"
        '
        'ButtonTextOffsetX
        '
        Me.ButtonTextOffsetX.Location = New System.Drawing.Point(115, 93)
        Me.ButtonTextOffsetX.Name = "ButtonTextOffsetX"
        Me.ButtonTextOffsetX.Size = New System.Drawing.Size(42, 22)
        Me.ButtonTextOffsetX.TabIndex = 52
        Me.ButtonTextOffsetX.Text = "5"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(15, 121)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(94, 17)
        Me.Label8.TabIndex = 51
        Me.Label8.Text = "Text Offset Y:"
        '
        'ButtonTextOffsetY
        '
        Me.ButtonTextOffsetY.Location = New System.Drawing.Point(115, 121)
        Me.ButtonTextOffsetY.Name = "ButtonTextOffsetY"
        Me.ButtonTextOffsetY.Size = New System.Drawing.Size(42, 22)
        Me.ButtonTextOffsetY.TabIndex = 50
        Me.ButtonTextOffsetY.Text = "5"
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(15, 96)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(94, 17)
        Me.Label9.TabIndex = 49
        Me.Label9.Text = "Text Offset X:"
        '
        'CheckBox1
        '
        Me.CheckBox1.AutoSize = True
        Me.CheckBox1.Location = New System.Drawing.Point(358, 120)
        Me.CheckBox1.Name = "CheckBox1"
        Me.CheckBox1.Size = New System.Drawing.Size(144, 21)
        Me.CheckBox1.TabIndex = 53
        Me.CheckBox1.Text = "Use Texture Index"
        Me.CheckBox1.UseVisualStyleBackColor = True
        '
        'TextureIndexBox
        '
        Me.TextureIndexBox.Location = New System.Drawing.Point(442, 91)
        Me.TextureIndexBox.Name = "TextureIndexBox"
        Me.TextureIndexBox.Size = New System.Drawing.Size(42, 22)
        Me.TextureIndexBox.TabIndex = 55
        Me.TextureIndexBox.Text = "0"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(339, 92)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(97, 17)
        Me.Label13.TabIndex = 54
        Me.Label13.Text = "Texture Index:"
        '
        'AddButtonDlg
        '
        Me.AcceptButton = Me.OK_Button
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.CancelButton = Me.Cancel_Button
        Me.ClientSize = New System.Drawing.Size(576, 251)
        Me.Controls.Add(Me.TextureIndexBox)
        Me.Controls.Add(Me.Label13)
        Me.Controls.Add(Me.CheckBox1)
        Me.Controls.Add(Me.ButtonTextOffsetX)
        Me.Controls.Add(Me.Label8)
        Me.Controls.Add(Me.ButtonTextOffsetY)
        Me.Controls.Add(Me.Label9)
        Me.Controls.Add(Me.ButtonToolTip)
        Me.Controls.Add(Me.Label12)
        Me.Controls.Add(Me.ButtonCommand)
        Me.Controls.Add(Me.Label11)
        Me.Controls.Add(Me.ButtonText)
        Me.Controls.Add(Me.Label10)
        Me.Controls.Add(Me.ButtonTextSizeY)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.ButtonTextSizeX)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.ButtonDimsW)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.ButtonDimsZ)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.ButtonDimsY)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.ButtonDimsX)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.ButtonName)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.TableLayoutPanel1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "AddButtonDlg"
        Me.ShowInTaskbar = False
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "AddButtonDlg"
        Me.TableLayoutPanel1.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents TableLayoutPanel1 As System.Windows.Forms.TableLayoutPanel
    Friend WithEvents OK_Button As System.Windows.Forms.Button
    Friend WithEvents Cancel_Button As System.Windows.Forms.Button
    Friend WithEvents ButtonToolTip As TextBox
    Friend WithEvents Label12 As Label
    Friend WithEvents ButtonCommand As TextBox
    Friend WithEvents Label11 As Label
    Friend WithEvents ButtonText As TextBox
    Friend WithEvents Label10 As Label
    Friend WithEvents ButtonTextSizeY As TextBox
    Friend WithEvents Label6 As Label
    Friend WithEvents ButtonTextSizeX As TextBox
    Friend WithEvents Label7 As Label
    Friend WithEvents ButtonDimsW As TextBox
    Friend WithEvents Label5 As Label
    Friend WithEvents ButtonDimsZ As TextBox
    Friend WithEvents Label4 As Label
    Friend WithEvents ButtonDimsY As TextBox
    Friend WithEvents Label3 As Label
    Friend WithEvents ButtonDimsX As TextBox
    Friend WithEvents Label2 As Label
    Friend WithEvents ButtonName As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents ButtonTextOffsetX As TextBox
    Friend WithEvents Label8 As Label
    Friend WithEvents ButtonTextOffsetY As TextBox
    Friend WithEvents Label9 As Label
    Friend WithEvents CheckBox1 As CheckBox
    Friend WithEvents TextureIndexBox As TextBox
    Friend WithEvents Label13 As Label
End Class
