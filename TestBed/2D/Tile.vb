Imports System
Imports System.Collections.Generic
Imports System.Linq
Imports System.Text
Imports Microsoft.Xna.Framework
Imports Microsoft.Xna.Framework.Graphics
Imports SharpDX
Imports SharpDX.Direct3D11

Namespace TileEngine
    Public Class Tile
        Public Shared TileSetTexture As ShaderResourceView
        Public Shared TileWidth As Integer = 64
        Public Shared TileHeight As Integer = 64
        Public Shared TileStepX As Integer = 64
        Public Shared TileStepY As Integer = 16
        Public Shared OddRowXOffset As Integer = 32
        Public Shared HeightTileOffset As Integer = 32

        Public Shared originPoint As New Vector2(500, 500)

        Public Shared Width As Integer = 640


        Public Shared Function GetSourceRectangle(tileIndex As Integer) As Rectangle
            Dim tileY As Integer = tileIndex / (Width / TileWidth)
            Dim tileX As Integer = tileIndex Mod (Width / TileWidth)

            Return New Rectangle(tileX * TileWidth, tileY * TileHeight, TileWidth, TileHeight)
        End Function
    End Class
End Namespace