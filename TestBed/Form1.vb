Imports System.ComponentModel
Imports System.Drawing.Design
Imports System.IO
Imports System.Net
Imports System.Net.Cache
Imports System.Windows.Forms.Design
Imports System.Xml
Imports System.Xml.Serialization
Imports GotDotNet.XInclude
Imports Insight.Core
Imports Insight.Core.UniformPoissonDiskSampler
Imports Insight.Framework
Imports Insight.UI
Imports Newtonsoft.Json
Imports SharpDX
Imports SharpDX.Direct3D11
Imports SharpDX.DXGI

Imports SharpDX.Windows
Imports TestBed
Imports TestBed.TileEngine




Public Class Form1
    Private RenderDevice As LowLevelDevice
    Private CanDrawUI As Boolean
    Private dlg As New OpenFileDialog()
    Public SpriteBatch As Toolkit.Graphics.SpriteBatch
    Public GraphicsDevice As Toolkit.Graphics.GraphicsDevice
    Private TextureBackground As Boolean
    Private Camera As New Camera2D
    Private FontSmall As Toolkit.Graphics.SpriteFont
    '  Private SpritSheet As ShaderResourceView
    Private ContentLoadScreen As ContentLoadScreen
    Private UINodes As List(Of FPanelStruct)
    Private CurrentPanel As FPanelStruct
    Private CurrentButton As FButtonStruct
    Private StartWindow As New Dialog1
    Private SettingWindow As New SettingDlg
    Private PanelSelectedImage As ShaderResourceView
    Private ButtonSelectedImage As ShaderResourceView
    Private ButtonImage As ShaderResourceView
    Private PanelImage As ShaderResourceView
    Private HelpWindow As New AboutBox1

    Private MouseRect As New RectangleF

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Dim opndlg As New SaveFileDialog
        opndlg.Title = "Save Unreal UI Layout(.json)"
        opndlg.Filter = "Json Files (*.JSON)|*.json"
        opndlg.FileName = "UILayout.json"
        opndlg.ShowDialog()
        File.WriteAllText(opndlg.FileName, Newtonsoft.Json.JsonConvert.SerializeObject(UINodes))
    End Sub
    Private Sub Button1_Click_2(sender As Object, e As EventArgs) Handles Button1.Click
        Dim opndlg As New OpenFileDialog
        opndlg.Title = "Open Json Document"
        opndlg.Filter = "Json Files (*.JSON)|*.json"
        opndlg.FileName = "UILayout.json"
        opndlg.ShowDialog()

        Dim jsonstr As String = File.ReadAllText(opndlg.FileName).Remove(1, 1)
        Dim jsettings As New Newtonsoft.Json.JsonSerializerSettings
        UINodes = Newtonsoft.Json.JsonConvert.DeserializeObject(Of List(Of FPanelStruct))(jsonstr.Remove(jsonstr.Length - 2, 1))
    End Sub

    Private Sub SelectSreenSize()
        Select Case StartWindow.SelectedSreenSize
            Case ScreenSizes._1024x768
                Me.MaximumSize = New Size(1024, 768)
                Me.MinimumSize = New Size(1024, 768)
                Me.Size = New Size(1024, 768)
            Case ScreenSizes._1200x900
                Me.MaximumSize = New Size(1200, 900)
                Me.MinimumSize = New Size(1200, 900)
                Me.Size = New Size(1200, 900)
            Case ScreenSizes._1360x768
                Me.MaximumSize = New Size(1360, 768)
                Me.MinimumSize = New Size(1360, 768)
                Me.Size = New Size(1360, 768)
            Case ScreenSizes._1366x768
                Me.MaximumSize = New Size(1366, 768)
                Me.MinimumSize = New Size(1366, 768)
                Me.Size = New Size(1366, 768)
            Case ScreenSizes._1440x900
                Me.MaximumSize = New Size(1440, 900)
                Me.MinimumSize = New Size(1440, 900)
                Me.Size = New Size(1440, 900)
            Case ScreenSizes._1600x1200
                Me.MaximumSize = New Size(1600, 1200)
                Me.MinimumSize = New Size(1600, 1200)
                Me.Size = New Size(1600, 1200)
            Case ScreenSizes._1920x1080
                Me.MaximumSize = New Size(1920, 1080)
                Me.MinimumSize = New Size(1920, 1080)
                Me.Size = New Size(1920, 1080)
            Case ScreenSizes._1920x1200
                Me.MaximumSize = New Size(1920, 1200)
                Me.MinimumSize = New Size(1920, 1200)
                Me.Size = New Size(1920, 1200)
            Case ScreenSizes._2560x1440
                Me.MaximumSize = New Size(2560, 1440)
                Me.MinimumSize = New Size(2560, 1440)
                Me.Size = New Size(2560, 1440)
        End Select
    End Sub


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        fireTime = TimeSpan.FromMilliseconds(4.0F)
        '   StartWindow.ShowDialog()
        ' SelectSreenSize()
        Dim ContentPath As String
        '#If DEBUG Then
        '   ContentPath = "E:\Portfolio\Game\GameData\"
        '#Else
        ContentPath = "C:\Users\B201707513\Documents\Unreal Projects\ProjectXRay\Project_X_Ray\BuiltGameStuff\Content\"
        '#End If
        RenderDevice = New LowLevelDevice(Me, Panel1, ContentPath, StartWindow.CheckBox1.Checked)

        '  LowLevelDevice.LoadSptireSheet(ContentPath & "UI\UISheet.xml")
        '  LowLevelDevice.SendEvents = True
        ' LowLevelDevice.AddSprtieSheetMapping("Minimapbg.png", New RectangleF(16, 4100, 256, 256))

        AddHandler RenderDevice.Draw, AddressOf DrawFrame
        AddHandler RenderDevice.Update, AddressOf UpdateFrame

        GraphicsDevice = Toolkit.Graphics.GraphicsDevice.[New](RenderDevice)
        SpriteBatch = New Toolkit.Graphics.SpriteBatch(GraphicsDevice, 4096)
        FontSmall = Toolkit.Graphics.SpriteFont.Load(GraphicsDevice, LowLevelDevice.ContentPath & "Arial.tkb")
        '  SpritSheet = RenderDevice.CreateTexture("UI\UISheet.png")

        ButtonImage = RenderDevice.CreateTexture("Textures\UI\button_active.png")
        PanelImage = RenderDevice.CreateTexture("Textures\UI\panel.png")
        PanelSelectedImage = RenderDevice.CreateTexture("Textures\UI\panelselected.png")
        ButtonSelectedImage = RenderDevice.CreateTexture("Textures\UI\button_hover.png")

        ContentLoadScreen = New ContentLoadScreen(RenderDevice, Me.Width, Me.Height)

        RenderDevice.run()
    End Sub
    Private rand As New Random
    Private TestPerfQ As ProfileItem
    Private TotalCPUTime As ProfileItem
    Private previousFireTime As TimeSpan
    Private fireTime As TimeSpan
    Private ContentLoaded As Boolean
    Private DoOnce As Boolean = True
    Public ColorBufferView As ShaderResourceView
    Public ColorBufferRT As RenderTargetView
    Private Sub LoadContent()
        If DoOnce Then
            Me.Focus()
            DoOnce = False
            System.Threading.ThreadPool.QueueUserWorkItem(Sub()
                                                              ContentLoadScreen.SetText("Render pipeline")
                                                              Dim ColorFormat As Format = Format.R8G8B8A8_UNorm
                                                              Dim BufferDesc As New Texture2DDescription() With {
                                                           .ArraySize = 1,
                                                           .BindFlags = BindFlags.RenderTarget Or BindFlags.ShaderResource,
                                                           .CpuAccessFlags = CpuAccessFlags.None,
                                                           .Format = ColorFormat,
                                                           .Height = Height,
                                                           .Width = Width,
                                                           .MipLevels = 1,
                                                           .OptionFlags = ResourceOptionFlags.None,
                                                           .SampleDescription = New SampleDescription(1, 0),
                                                           .Usage = ResourceUsage.Default
                                                              }
                                                              Dim ColorBuffer As Texture2D
                                                              ColorBuffer = RenderDevice.CreateTexture(BufferDesc)
                                                              ColorBufferRT = RenderDevice.CreateRenderTargetView(ColorBuffer)
                                                              ColorBufferView = RenderDevice.CreateShaderResourceView(ColorBuffer)

                                                              Dim CameraParser As New CommandLineParser(Camera)
                                                              LowLevelDevice.addCommandParser("Camera", CameraParser)
                                                              ContentLoadScreen.SetText("World")

                                                              ContentLoadScreen.SetText("Performance Querys")
                                                              TestPerfQ = New ProfileItem("Main Draw Loop", RenderDevice, True)
                                                              TotalCPUTime = New ProfileItem("Total Update", RenderDevice, False)
                                                              LowLevelDevice.AddPerformanceQuery(TestPerfQ)
                                                              ContentLoadScreen.SetText("UI Engine")
                                                              ' Dim AIDebugDrawerParser As New CommandLineParser(WorldSpriteRenderer)
                                                              '  LowLevelDevice.addCommandParser("AIDebugInfo", AIDebugDrawerParser)
                                                              'Dim UIEngineService As UIEngineServiceTreeView
                                                              Dim screenWidthAtFullScale As Integer = 1920
                                                              Dim screenHeightAtFullScale As Integer = 1080
                                                              Camera.Viewport = New RectangleF(Me.Width / 2, Me.Height / 2, Width, Height)
                                                              '    UIEngineService = New UIEngineServiceTreeView(Camera)
                                                              ' UIManager = New UIEngine(SpritSheet, SpriteBatch, GraphicsDevice, Width, Height, UIEngineService)
                                                              Dim scaleX As Single = Me.Width / screenWidthAtFullScale
                                                              Dim scaleY As Single = Me.Height / screenHeightAtFullScale
                                                              '  UIManager.Scale = 1 'Min(scaleX, scaleY)
                                                              '   UIManager.Scale = Vector2.Zero - Vector2.Zero
                                                              ' UIManager.LoadUI(LowLevelDevice.ContentPath & "UI\HUD.xml")
                                                              ContentLoaded = True
                                                              '  For Each item In LowLevelDevice.ContentPaths
                                                              'If Not File.Exists("E:\BuiltGameStuff\" & item) Then
                                                              'File.Copy(LowLevelDevice.ContentPath & item, "E:\BuiltGameStuff\" & item)
                                                              'End If
                                                              'Next
                                                          End Sub)
        End If
    End Sub
    Public Sub DrawLoadingScreen(ByRef context As DeviceContext)
        RenderDevice.SetRenderTargets()
        RenderDevice.ClearRenderTargets(SharpDX.Color.Black)
        ContentLoadScreen.Draw(context, RenderDevice, FontSmall, SpriteBatch, GraphicsDevice)
    End Sub
    Private Sub DrawWorld(ByRef context As DeviceContext, gametime As GameTime)
        context.OutputMerger.SetTargets(RenderDevice.DepthStencilView, ColorBufferRT)
        context.ClearRenderTargetView(ColorBufferRT, New Color4(0, 0, 0, 0))
    End Sub
    Private DoOnceForaSeconedTime As Boolean = True
    Public Sub DrawFrame(ByRef context As DeviceContext, gametime As GameTime)
        Try
            LoadContent()
            If ContentLoaded Then
                LowLevelDevice.BeginEventInt("Frame")
                If DoOnceForaSeconedTime Then

                    DoOnceForaSeconedTime = False
                End If
                RenderDevice.startFrame()
            End If
            If Not ContentLoaded Then DrawLoadingScreen(context)
            If ContentLoaded Then
                TestPerfQ.Begin(context)
                DrawWorld(context, gametime)
                LowLevelDevice.BeginEventInt("Draw To Screen")
                RenderDevice.SetRenderTargets()
                RenderDevice.ClearRenderTargets(SharpDX.Color.White)

                If UINodes IsNot Nothing Then
                    SpriteBatch.Begin(Toolkit.Graphics.SpriteSortMode.Immediate, GraphicsDevice.BlendStates.AlphaBlend, GraphicsDevice.SamplerStates.LinearClamp, Nothing, Nothing, Nothing)
                    For i As Integer = 0 To UINodes.Count - 1
                        Dim PanleOffSet As New Vector2(UINodes(i).Dims.X, UINodes(i).Dims.Y)

                        PanleOffSet.X += UINodes(i).XMargin
                        PanleOffSet.Y += UINodes(i).YMargin

                        If CurrentPanel IsNot Nothing Then
                            If CurrentPanel.Name = UINodes(i).Name Then
                                SpriteBatch.Draw(PanelSelectedImage, New RectangleF(UINodes(i).Dims.X, UINodes(i).Dims.Y, UINodes(i).Dims.Z, UINodes(i).Dims.W), Color.White)
                            Else
                                SpriteBatch.Draw(PanelImage, New RectangleF(UINodes(i).Dims.X, UINodes(i).Dims.Y, UINodes(i).Dims.Z, UINodes(i).Dims.W), Color.White)
                            End If
                        Else
                            SpriteBatch.Draw(PanelImage, New RectangleF(UINodes(i).Dims.X, UINodes(i).Dims.Y, UINodes(i).Dims.Z, UINodes(i).Dims.W), Color.White)
                        End If
                        DoUILayoutStuffs(UINodes(i).Buttons, PanleOffSet, UINodes(i))
                    Next
                    SpriteBatch.End()
                End If
                LowLevelDevice.EndEvent()
                'Draw UI
                LowLevelDevice.BeginEventInt("Draw UI")
                '  UIManager.DrawUI()
                LowLevelDevice.EndEvent()
                LowLevelDevice.EndEvent()
                TestPerfQ.End(context)
            End If
        Catch ex As Exception
        End Try
        RenderDevice.Present()
    End Sub
    Private LastMousePos As Vector2
    Private IgnoreInput As Boolean

    Public Sub DoUILayoutStuffs(_buttons As List(Of FButtonStruct), PanleOffSet As Vector2, _panel As FPanelStruct)
        Dim rowcount As Integer = 0
        For ii As Integer = 0 To _buttons.Count - 1
            If CurrentButton IsNot Nothing Then
                If CurrentButton Is _buttons(ii) Then
                    SpriteBatch.Draw(ButtonSelectedImage, New RectangleF(PanleOffSet.X, PanleOffSet.Y, _buttons(ii).Dims.Z, _buttons(ii).Dims.W), Color.White)
                Else
                    SpriteBatch.Draw(ButtonImage, New RectangleF(PanleOffSet.X, PanleOffSet.Y, _buttons(ii).Dims.Z, _buttons(ii).Dims.W), Color.White)
                End If
            Else
                SpriteBatch.Draw(ButtonImage, New RectangleF(PanleOffSet.X, PanleOffSet.Y, _buttons(ii).Dims.Z, _buttons(ii).Dims.W), Color.White)
            End If
            Dim buttonoffset As Vector2 = New Vector2(PanleOffSet.X + _buttons(ii).Dims.Z / 4, PanleOffSet.Y + _buttons(ii).Dims.W / 4)
            SpriteBatch.DrawString(FontSmall, _buttons(ii).Text, buttonoffset, Color.White)

            Select Case _panel.LayoutType
                Case LayoutType.Vectical
                    PanleOffSet.Y += 70
                Case LayoutType.Horazontal
                    PanleOffSet.X += 70
                Case LayoutType.Grid
                    ' PanleOffSet.X += 70

            End Select
        Next
    End Sub
    Public Function DoUILayoutStuffsCheckMouseIntersection(_buttons As List(Of FButtonStruct), PanleOffSet As Vector2, _panel As FPanelStruct) As Boolean
        Dim rowcount As Integer = 0
        For ii As Integer = 0 To _buttons.Count - 1

            If (PanleOffSet.X <= RenderDevice.MouseState.X AndAlso RenderDevice.MouseState.X <= PanleOffSet.X + _buttons(ii).Dims.Z AndAlso
                            PanleOffSet.Y <= RenderDevice.MouseState.Y AndAlso RenderDevice.MouseState.Y <= PanleOffSet.Y + _buttons(ii).Dims.W) Then
                If RenderDevice.InputManager.MouseDevice.WasButtonPressed(0) Then

                    CurrentButton = _buttons(ii)
                    CurrentPanel = Nothing
                    Return True
                    Exit For
                End If
            End If

            Select Case _panel.LayoutType
                Case LayoutType.Vectical
                    PanleOffSet.Y += 70
                Case LayoutType.Horazontal
                    PanleOffSet.X += 70
                Case LayoutType.Grid
                    ' PanleOffSet.X += 70

            End Select
        Next
        Return False
    End Function
    Public Sub UpdateFrame(gametime As GameTime)
        MouseRect.X = RenderDevice.MouseState.X
        MouseRect.Y = RenderDevice.MouseState.Y
        ' TotalCPUTime.Begin(RenderDevice.ImmediateContext)

        If RenderDevice.InputManager.MouseDevice.WasButtonPressed(1) Then
            IgnoreInput = True
        End If
        If Not IgnoreInput Then


            If CurrentButton IsNot Nothing Or CurrentPanel IsNot Nothing Then
                If RenderDevice.InputManager.MouseDevice.WasButtonHeld(0) Then
                    Dim delta As New Vector2(MouseRect.X - LastMousePos.X, MouseRect.Y - LastMousePos.Y)

                    If CurrentButton IsNot Nothing Then
                        CurrentButton.Dims.X += delta.X '/ (CurrentButton.Dims.Z)
                        CurrentButton.Dims.Y += delta.Y '/ (CurrentButton.Dims.W)
                    End If
                    If CurrentPanel IsNot Nothing Then
                        CurrentPanel.Dims.X += delta.X '/ (CurrentPanel.Dims.Z)
                        CurrentPanel.Dims.Y += delta.Y '/ (CurrentPanel.Dims.W)
                    End If

                End If
            End If


            If ContentLoaded Then


                If UINodes IsNot Nothing Then
                    For i As Integer = 0 To UINodes.Count - 1

                        Dim PanleOffSet As New Vector2(UINodes(i).Dims.X, UINodes(i).Dims.Y)
                        Dim onbutton As Boolean = DoUILayoutStuffsCheckMouseIntersection(UINodes(i).Buttons, PanleOffSet, UINodes(i))

                        If (UINodes(i).Dims.X <= RenderDevice.MouseState.X AndAlso RenderDevice.MouseState.X <= UINodes(i).Dims.X + UINodes(i).Dims.Z AndAlso
                         UINodes(i).Dims.Y <= RenderDevice.MouseState.Y AndAlso RenderDevice.MouseState.Y <= UINodes(i).Dims.Y + UINodes(i).Dims.W) Then
                            If RenderDevice.InputManager.MouseDevice.WasButtonPressed(0) AndAlso Not onbutton Then
                                CurrentPanel = UINodes(i)
                                CurrentButton = Nothing
                                Exit For
                            End If
                        End If

                    Next
                End If


            End If
            '   If RenderDevice.InputManager.MouseDevice.WasButtonPressed(1) Then
            'CurrentButton = Nothing
            'CurrentPanel = Nothing
            'End If
        End If
        If CurrentButton IsNot Nothing Or CurrentPanel IsNot Nothing Then




            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.W) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.Y -= 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.Y -= 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.S) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.Y += 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.Y += 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.A) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.X -= 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.X -= 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.D) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.X += 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.X += 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.Q) Then
                If CurrentButton IsNot Nothing Then

                End If
                If CurrentPanel IsNot Nothing Then

                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.E) Then
                If CurrentButton IsNot Nothing Then

                End If
                If CurrentPanel IsNot Nothing Then

                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.D1) Then
                If CurrentButton IsNot Nothing Then

                End If
                If CurrentPanel IsNot Nothing Then

                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.D2) Then
                If CurrentButton IsNot Nothing Then

                End If
                If CurrentPanel IsNot Nothing Then

                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.R) Then

                If CurrentPanel IsNot Nothing Then

                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.Up) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.W += 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.W += 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.Down) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.W -= 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.W -= 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.Right) Then
                If CurrentButton IsNot Nothing Then
                    CurrentButton.Dims.Z += 1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.Z += 1
                End If
            End If
            If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.Left) Then
                If CurrentButton IsNot Nothing Then
                    CurrentPanel.Dims.Z += -1
                End If
                If CurrentPanel IsNot Nothing Then
                    CurrentPanel.Dims.Z += -1
                End If
            End If
        End If
        If RenderDevice.KeyBoredState.IsPressed(SharpDX.DirectInput.Key.Space) Then

        End If


        '   TotalCPUTime.End(RenderDevice.ImmediateContext)
        LastMousePos.X = MouseRect.X
        LastMousePos.Y = MouseRect.Y
    End Sub
    Private Sub Form1_Closing(sender As Object, e As CancelEventArgs) Handles Me.Closing
        RenderDevice.Close()
    End Sub
    Private Sub Button1_Click_1(sender As Object, e As EventArgs)
        For Each item In LowLevelDevice.ContentPaths
            If Not File.Exists("E:\BuiltGameStuff\" & item) Then
                File.Copy(LowLevelDevice.ContentPath & item, "E:\BuiltGameStuff\" & item)
            End If
        Next
    End Sub

    Private Sub ToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles ToolStripMenuItem1.Click
        If CurrentPanel IsNot Nothing Then
            Dim newbutton As New AddButtonDlg
            newbutton.ShowDialog()
            If newbutton.NewButton IsNot Nothing Then
                CurrentPanel.Buttons.Add(newbutton.NewButton)
            End If
        End If
        IgnoreInput = False
    End Sub
    Private Sub ToolStripMenuItem2_Click(sender As Object, e As EventArgs) Handles ToolStripMenuItem2.Click


        Dim newpanel As New AddPanelDlg
        newpanel.ShowDialog()

        If newpanel.panel IsNot Nothing Then
            UINodes.add(newpanel.panel)
        End If
        IgnoreInput = False
    End Sub
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        HelpWindow.Show()
    End Sub
    Private Sub TreeView1_MouseLeave(sender As Object, e As EventArgs)
        Panel1.Focus()
    End Sub
    Private Sub TreeView1_KeyPress(sender As Object, e As KeyPressEventArgs)
        If [Char].IsDigit(e.KeyChar) OrElse [Char].IsLetter(e.KeyChar) Then
            e.Handled = False
        End If
    End Sub

    Private Sub EditToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles EditToolStripMenuItem.Click
        IgnoreInput = False
        If CurrentPanel IsNot Nothing Then
            Dim newpanel As New AddPanelDlg
            newpanel.panel = CurrentPanel
            newpanel.ShowDialog()

        End If
        If CurrentButton IsNot Nothing Then
            Dim newbutton As New AddButtonDlg
            newbutton.NewButton = CurrentButton
            newbutton.ShowDialog()

        End If
    End Sub
End Class

Public Enum LayoutType As Integer
    Horazontal = 0
    Vectical = 1
    Grid = 2
End Enum


Public Enum ButtonEffectType As Integer
    Grow = 0
    Swap = 1
    None = 255
End Enum
Public Structure V4
    Public X As Single
    Public Y As Single
    Public Z As Single
    Public W As Single
End Structure

Public Structure V2
    Public X As Single
    Public Y As Single
End Structure
Public Class FButtonStruct
    Public Name As String
    Public type As Integer
    Public toolTip As String
    Public Dims As V4
    Public TextOffset As V2
    Public TextSize As V2
    Public Text As String
    Public Command As String
    Public UseTextureIndex As Boolean
    Public TextureIndex As Integer
    Public EffectType As ButtonEffectType = ButtonEffectType.None
End Class
Public Class FPanelStruct
    Public Name As String
    Public Dims As V4
    Public TextOffset As V2
    Public TextSize As V2
    Public Text As String
    Public XSpacing As Single
    Public YSpacing As Single
    Public XMargin As Single
    Public YMargin As Single
    Public LayoutType As LayoutType = LayoutType.Vectical
    Public Buttons As New List(Of FButtonStruct)
End Class



