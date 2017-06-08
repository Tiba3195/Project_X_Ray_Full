Imports Insight.Core
Imports SharpDX
Imports SharpDX.Direct3D11
Imports SharpDX.Toolkit.Graphics

Public Class ContentLoadScreen
    Private Logo As ShaderResourceView
    Private Shared LoadingText As String
    Private Width As Integer, Height As Integer
    Public Sub New(_device As LowLevelDevice, _width As Integer, _height As Integer)
        Logo = _device.CreateTexture("Textures\insight logo.png")
        Width = _width
        Height = _height
        Console.WriteLine(Width & " " & Height)
    End Sub
    Public Shared Sub SetText(_text As String)
        LoadingText = _text
    End Sub
    Public Sub Draw(_context As DeviceContext, _device As LowLevelDevice, _font As SpriteFont, SpriteBatch As SpriteBatch, GraphicsDevice As GraphicsDevice)
        SpriteBatch.Begin(Toolkit.Graphics.SpriteSortMode.Deferred, GraphicsDevice.BlendStates.AlphaBlend)
        SpriteBatch.Draw(Logo, New RectangleF(Width - 612, Height - 114, 612, 114), Color.White)
        Dim textsize As Vector2 = _font.MeasureString("Loading: ")
        SpriteBatch.DrawString(_font, "Loading: " & LoadingText, New Vector2((Width / 2) - textsize.X, Height / 2), Color.White)
        SpriteBatch.End()
    End Sub
End Class
