Imports System
Imports System.Collections.Generic
Imports System.Linq
Imports System.Text
Imports SharpDX.Direct3D11

Namespace TileEngine
    Public Class MapRow
        Public Columns As New List(Of MapCell)()
    End Class

    Public Class TileMap
        Public Rows As New List(Of MapRow)()
        Public MapWidth As Integer = 50
        Public MapHeight As Integer = 50

        Public Sub New()
            Dim y As Integer = 0
            While y < MapHeight
                Dim thisRow As New MapRow()
                Dim x As Integer = 0
                While x < MapWidth
                    thisRow.Columns.Add(New MapCell(0))
                    System.Math.Max(System.Threading.Interlocked.Increment(x), x - 1)
                End While
                Rows.Add(thisRow)
                System.Math.Max(System.Threading.Interlocked.Increment(y), y - 1)
            End While

            ' Create Sample Map Data
            Rows(0).Columns(3).TileID = 3
            Rows(0).Columns(4).TileID = 3
            Rows(0).Columns(5).TileID = 1
            Rows(0).Columns(6).TileID = 1
            Rows(0).Columns(7).TileID = 1

            Rows(1).Columns(3).TileID = 3
            Rows(1).Columns(4).TileID = 1
            Rows(1).Columns(5).TileID = 1
            Rows(1).Columns(6).TileID = 1
            Rows(1).Columns(7).TileID = 1

            Rows(2).Columns(2).TileID = 3
            Rows(2).Columns(3).TileID = 1
            Rows(2).Columns(4).TileID = 1
            Rows(2).Columns(5).TileID = 1
            Rows(2).Columns(6).TileID = 1
            Rows(2).Columns(7).TileID = 1

            Rows(3).Columns(2).TileID = 3
            Rows(3).Columns(3).TileID = 1
            Rows(3).Columns(4).TileID = 1
            Rows(3).Columns(5).TileID = 2
            Rows(3).Columns(6).TileID = 2
            Rows(3).Columns(7).TileID = 2

            Rows(4).Columns(2).TileID = 3
            Rows(4).Columns(3).TileID = 1
            Rows(4).Columns(4).TileID = 1
            Rows(4).Columns(5).TileID = 2
            Rows(4).Columns(6).TileID = 2
            Rows(4).Columns(7).TileID = 2

            Rows(5).Columns(2).TileID = 3
            Rows(5).Columns(3).TileID = 1
            Rows(5).Columns(4).TileID = 1
            Rows(5).Columns(5).TileID = 2
            Rows(5).Columns(6).TileID = 2
            Rows(5).Columns(7).TileID = 2

            Rows(16).Columns(4).AddHeightTile(54)

            Rows(17).Columns(3).AddHeightTile(54)

            Rows(15).Columns(3).AddHeightTile(54)
            Rows(16).Columns(3).AddHeightTile(53)

            Rows(15).Columns(4).AddHeightTile(54)
            Rows(15).Columns(4).AddHeightTile(54)
            Rows(15).Columns(4).AddHeightTile(51)

            Rows(18).Columns(3).AddHeightTile(51)
            Rows(19).Columns(3).AddHeightTile(50)
            Rows(18).Columns(4).AddHeightTile(55)

            Rows(14).Columns(4).AddHeightTile(54)

            Rows(14).Columns(5).AddHeightTile(62)
            Rows(14).Columns(5).AddHeightTile(61)
            Rows(14).Columns(5).AddHeightTile(63)

            Rows(17).Columns(4).AddTopperTile(114)
            Rows(16).Columns(5).AddTopperTile(115)
            Rows(14).Columns(4).AddTopperTile(125)
            Rows(15).Columns(5).AddTopperTile(91)

            'Rows[3].Columns[5].AddBaseTile(30);
            'Rows[4].Columns[5].AddBaseTile(27);
            'Rows[5].Columns[5].AddBaseTile(28);

            'Rows[3].Columns[6].AddBaseTile(25);
            'Rows[5].Columns[6].AddBaseTile(24);

            'Rows[3].Columns[7].AddBaseTile(31);
            'Rows[4].Columns[7].AddBaseTile(26);
            'Rows[5].Columns[7].AddBaseTile(29);

            'Rows[4].Columns[6].AddBaseTile(104);
            ' End Create Sample Map Data
            Rows(16).Columns(6).AddTopperTile(94)
        End Sub
    End Class
End Namespace