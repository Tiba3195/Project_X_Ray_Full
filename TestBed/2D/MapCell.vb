Imports System
Imports System.Collections.Generic
Imports System.Linq
Imports System.Text

Namespace TileEngine
    Public Class MapCell
        Public BaseTiles As New List(Of Integer)()
        Public HeightTiles As New List(Of Integer)()
        Public TopperTiles As New List(Of Integer)()

        Public Property TileID() As Integer
            Get
                Return If(BaseTiles.Count > 0, BaseTiles(0), 0)
            End Get
            Set
                If BaseTiles.Count > 0 Then
                    BaseTiles(0) = Value
                Else
                    AddBaseTile(Value)
                End If
            End Set
        End Property

        Public Sub AddBaseTile(tileID As Integer)
            BaseTiles.Add(tileID)
        End Sub

        Public Sub AddHeightTile(tileID As Integer)
            HeightTiles.Add(tileID)
        End Sub

        Public Sub AddTopperTile(tileID As Integer)
            TopperTiles.Add(tileID)
        End Sub

        Public Sub New(tileID As Integer)
            tileID = tileID
        End Sub
    End Class
End Namespace