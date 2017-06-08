Imports System
Imports System.Collections.Generic
Imports System.Linq
Imports Insight.Core
Imports Insight.UI
Imports Microsoft.Xna.Framework
Imports Microsoft.Xna.Framework.Audio
Imports Microsoft.Xna.Framework.Content
Imports Microsoft.Xna.Framework.GamerServices
Imports Microsoft.Xna.Framework.Graphics
Imports Microsoft.Xna.Framework.Input
Imports Microsoft.Xna.Framework.Media
Imports SharpDX
Imports SharpDX.Toolkit.Graphics

Namespace TileEngine
    ''' <summary>
    ''' This is the main type for your game
    ''' </summary>
    Public Class TileGame

        Private spriteBatch As SpriteBatch

        Private pericles6 As SpriteFont

        Private myMap As New TileMap()
        Private squaresAcross As Integer = 17
        Private squaresDown As Integer = 37
        Private baseOffsetX As Integer = -32
        Private baseOffsetY As Integer = -64
        Private heightRowDepthMod As Single = 0.00001F





        ''' <summary>
        ''' LoadContent will be called once per game and is the place to load
        ''' all of your content.
        ''' </summary>
        Public Sub LoadContent(_TileSetTexture As Direct3D11.ShaderResourceView, _SpriteBatch As SpriteBatch, _SpriteFont As SpriteFont)
            ' Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = _SpriteBatch

            Tile.TileSetTexture = _TileSetTexture 'Content.Load(Of Texture2D)("Textures\TileSets\part4_tileset")

            pericles6 = _SpriteFont

            ' TODO: use this.Content to load your game content here
        End Sub



        ''' <summary>
        ''' Allows the game to run logic such as updating the world,
        ''' checking for collisions, gathering input, and playing audio.
        ''' </summary>
        ''' <param name="gameTime">Provides a snapshot of timing values.</param>
        Public Sub Update(gameTime As GameTime, _device As LowLevelDevice, Camera2D As Camera2D)
            ' Allows the game to exit






        End Sub
        Public Offset As Vector2
        ''' <summary>
        ''' This is called when the game should draw itself.
        ''' </summary>
        ''' <param name="gameTime">Provides a snapshot of timing values.</param>
        Public Sub Draw(gameTime As GameTime, gd As GraphicsDevice, Camera2D As Camera2D)


            spriteBatch.Begin(SpriteSortMode.BackToFront, gd.BlendStates.AlphaBlend)

            Dim firstSquare As New Vector2(Camera2D.Position.X / Tile.TileStepX, Camera2D.Position.Y / Tile.TileStepY)
            Dim firstX As Integer = CType(firstSquare.X, Integer)
            Dim firstY As Integer = CType(firstSquare.Y, Integer)

            Dim squareOffset As New Vector2(Camera2D.Position.X Mod Tile.TileStepX, Camera2D.Position.Y Mod Tile.TileStepY)
            Dim offsetX As Integer = CType(squareOffset.X, Integer)
            Dim offsetY As Integer = CType(squareOffset.Y, Integer)

            Dim maxdepth As Single = ((myMap.MapWidth + 1) * ((myMap.MapHeight + 1) * Tile.TileWidth)) / 10
            Dim depthOffset As Single

            Dim y As Integer = 0
            While y < squaresDown
                Dim rowOffset As Integer = 0
                If (firstY + y) Mod 2 = 1 Then
                    rowOffset = Tile.OddRowXOffset
                End If

                Dim x As Integer = 0
                While x < squaresAcross
                    Dim mapx As Integer = (firstX + x)
                    Dim mapy As Integer = (firstY + y)
                    depthOffset = 0.7F - ((mapx + (mapy * Tile.TileWidth)) / maxdepth)

                    For Each tileID As Integer In myMap.Rows(mapy).Columns(mapx).BaseTiles

                        spriteBatch.Draw(Tile.TileSetTexture, New RectangleF((x * Tile.TileStepX) - offsetX + rowOffset + baseOffsetX, (y * Tile.TileStepY) - offsetY + baseOffsetY, Tile.TileWidth, Tile.TileHeight), Tile.GetSourceRectangle(tileID), Color.White, 0F, Vector2.Zero,
                            SpriteEffects.None, 1.0F)
                    Next

                    Dim heightRow As Integer = 0

                    For Each tileID As Integer In myMap.Rows(mapy).Columns(mapx).HeightTiles
                        spriteBatch.Draw(Tile.TileSetTexture, New RectangleF((x * Tile.TileStepX) - offsetX + rowOffset + baseOffsetX, (y * Tile.TileStepY) - offsetY + baseOffsetY - (heightRow * Tile.HeightTileOffset), Tile.TileWidth, Tile.TileHeight), Tile.GetSourceRectangle(tileID), Color.White, 0F, Vector2.Zero,
                            SpriteEffects.None, depthOffset - (CType(heightRow, Single) * heightRowDepthMod))
                        System.Math.Max(System.Threading.Interlocked.Increment(heightRow), heightRow - 1)
                    Next

                    For Each tileID As Integer In myMap.Rows(y + firstY).Columns(x + firstX).TopperTiles
                        spriteBatch.Draw(Tile.TileSetTexture, New RectangleF((x * Tile.TileStepX) - offsetX + rowOffset + baseOffsetX, (y * Tile.TileStepY) - offsetY + baseOffsetY - (heightRow * Tile.HeightTileOffset), Tile.TileWidth, Tile.TileHeight), Tile.GetSourceRectangle(tileID), Color.White, 0F, Vector2.Zero,
                            SpriteEffects.None, depthOffset - (CType(heightRow, Single) * heightRowDepthMod))

                        'spriteBatch.DrawString(pericles6, (x + firstX).ToString() + ", " + (y + firstY).ToString(),
                        '    new Vector2((x * Tile.TileStepX) - offsetX + rowOffset + baseOffsetX + 24,
                        '        (y * Tile.TileStepY) - offsetY + baseOffsetY + 48), Color.White, 0f, Vector2.Zero,
                        '        1.0f, SpriteEffects.None, 0.0f);
                    Next
                    System.Math.Max(System.Threading.Interlocked.Increment(x), x - 1)
                End While
                System.Math.Max(System.Threading.Interlocked.Increment(y), y - 1)
            End While

            spriteBatch.[End]()
            ' TODO: Add your drawing code here


        End Sub
    End Class
End Namespace