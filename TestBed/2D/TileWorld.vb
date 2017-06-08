Imports SharpDX
Imports SharpDX.Direct3D11
Imports Insight.Core
Imports SharpDX.Toolkit.Graphics
Imports Insight.UI
Imports System.Xml
Imports System.IO

Public Class WorldBrain
    Private TileWorld As TileWorld
    Public Active As Boolean
    Private Towns As New List(Of TownHelper)

    Public Sub New(_TileWorld As TileWorld)
        TileWorld = _TileWorld

        Dim towncenters As List(Of Integer) = TileWorld.ReturnTownCenters
        Dim counter As Integer = 0
        For Each item In towncenters

            Dim newtown As New TownHelper("Town " & counter)
            newtown.Gold = 10000
            newtown.Wood = 10000
            newtown.Stone = 10000
            newtown.Food = 10000
            newtown.TileID = item
            newtown.ThinkTime = TimeSpan.FromSeconds(0.25F)
            newtown.BuildTime = TimeSpan.FromSeconds(0.75F)
            Towns.Add(newtown)
            counter += 1
        Next
    End Sub
    Public Sub AddBuilding()
        If TileWorld.BuildQueue IsNot Nothing Then
            Dim did As Boolean = AddBuilding(TileWorld.BuildQueue.BuildingName, TileWorld.BuildQueue.PlayerIndex)
            If did Then
                TileWorld.BuildQueue = Nothing
            End If
        End If
    End Sub
    Private Function AddBuilding(_name As String, _playerindex As Integer) As Boolean
        Dim testbuilding As Building = TileWorld.GetBuildingBluePrint(_name)
        If TileWorld.CheckCanPlace AndAlso Towns(_playerindex).CheckCost(testbuilding) Then
            Towns(_playerindex).SubtractCost(testbuilding)
            Dim newbuilding As Building = TileWorld.GetBuildingBluePrintAndClone(_name)
            newbuilding.Owner = _playerindex
            Towns(_playerindex).Buildings.Add(newbuilding)
            TileWorld.SetTile()
            TileWorld.HasBuidling = False
            Return True
        Else
            Return False
        End If
    End Function
    Public Function GetTown(_index As Integer) As TownHelper
        Return Towns(_index)
    End Function
    Public Sub update(GameTime As GameTime)

        For i As Integer = 0 To Towns.Count - 1
            Towns(i).update(GameTime, TileWorld)
        Next

    End Sub
End Class

Public Class Upgrade
    Public WoodCost As Integer = 50
    Public StoneCost As Integer = 50
    Public GoldCost As Integer = 50
    Public FoodCost As Integer = 50

End Class

Public Class Upgradeable
    Public Upgrades As New Queue(Of Upgrade)
    Public CostMultiplyer As Single = 1
    Public MaxUpgradeCount As Integer = 4
    Public CurrentUpgradeCount As Integer = 1
    Public WasJustUpgraded As Boolean
End Class

Public Class TownPlot
    Inherits Upgradeable
    Public TileID As Integer
    Public PlotType As PlotType = PlotType.none
    Public Sub New()
        MaxUpgradeCount = 3

        For i As Integer = 0 To MaxUpgradeCount - 1

            Dim blah As New Upgrade
            blah.FoodCost = 5
            blah.GoldCost = 0
            blah.WoodCost = 3
            blah.StoneCost = 0
            Upgrades.Enqueue(blah)
        Next
    End Sub
    Public ReadOnly Property CanUpgrade As Boolean
        Get
            Return CurrentUpgradeCount < MaxUpgradeCount
        End Get

    End Property

    Public Function ReturnPath() As String
        Select Case PlotType
            Case PlotType.T1
                Return "tiles/herbary/renders/work/45/001.png"
            Case PlotType.T2
                Return "tiles/herbary/renders/work/45/002.png"
            Case PlotType.T3
                Return "tiles/herbary/renders/work/45/003.png"
            Case PlotType.T4
                Return "tiles/herbary/renders/work/45/004.png"
            Case Else
                Return "tiles/world/ground/0002.gif"
        End Select
    End Function
End Class


Public Enum PlotType As Byte
    T1 = 0
    T2 = 1
    T3 = 2
    T4 = 3
    none = 255
End Enum


Public Enum TilePlaceMode As Byte
    TownPlots = 0
    Gathering = 1
    Other = 2
End Enum
Public Class TownHelper
    Inherits Upgradeable
    Public Wood As Integer
    Public Stone As Integer
    Public Gold As Integer
    Public Food As Integer
    Public TileID As Integer
    Public previousThinkTime As TimeSpan
    Public ThinkTime As TimeSpan
    Public previousBuildTime As TimeSpan
    Public BuildTime As TimeSpan
    Public WorkableLand As New List(Of TownPlot)
    Public Buildings As New List(Of Building)
    Public Expand As Boolean
    Public BuildFarmPlot As Boolean
    Public Name As String
    Private rand As New Random


    Public Sub New(_Name As String)
        Name = _Name
        For i As Integer = 0 To MaxUpgradeCount - 1
            Upgrades.Enqueue(New Upgrade)
        Next
    End Sub
    Public ReadOnly Property PlotCount As Integer
        Get
            Return WorkableLand.Count
        End Get
    End Property
    Public Sub TryExpand()
        Expand = True
    End Sub
    Public Sub TryBuildFarmPlot()
        BuildFarmPlot = True
    End Sub

    Public Function CheckCost(_upgrade As Upgrade, m_CostMultiplyer As Single) As Boolean
        If Food >= (_upgrade.FoodCost * m_CostMultiplyer) AndAlso
                Gold >= (_upgrade.GoldCost * m_CostMultiplyer) AndAlso
                Stone >= (_upgrade.StoneCost * m_CostMultiplyer) AndAlso
                Wood >= (_upgrade.WoodCost * m_CostMultiplyer) Then
            Return True
        Else
            Return False
        End If
    End Function
    Public Function CheckCost(_upgrade As Building) As Boolean
        If Food >= (_upgrade.FoodCost) AndAlso
                Gold >= (_upgrade.GoldCost) AndAlso
                Stone >= (_upgrade.StoneCost) AndAlso
                Wood >= (_upgrade.WoodCost) Then
            Return True
        Else
            Return False
        End If
    End Function
    Public Sub SubtractCost(_upgrade As Building)
        Food -= (_upgrade.FoodCost)
        Gold -= (_upgrade.GoldCost)
        Stone -= (_upgrade.StoneCost)
        Wood -= (_upgrade.WoodCost)
    End Sub
    Public Sub SubtractCost(_upgrade As Upgrade, m_CostMultiplyer As Single)
        Food -= (_upgrade.FoodCost * m_CostMultiplyer)
        Gold -= (_upgrade.GoldCost * m_CostMultiplyer)
        Stone -= (_upgrade.StoneCost * m_CostMultiplyer)
        Wood -= (_upgrade.WoodCost * m_CostMultiplyer)
    End Sub

    Public Sub update(GameTime As GameTime, ByRef TileWorld As TileWorld)
        If GameTime.TotalGameTime - previousThinkTime > ThinkTime Then
            If Expand Then
                If Upgrades.Count > 0 Then
                    If CheckCost(Upgrades.Peek, CostMultiplyer) Then

                        If CurrentUpgradeCount < MaxUpgradeCount Then

                            SubtractCost(Upgrades.Peek, CostMultiplyer)
                            Upgrades.Dequeue()

                            Dim towncenterNs As List(Of Integer) = TileWorld.ReturnNneighbours(TileID, CurrentUpgradeCount)
                            For ii As Integer = 0 To towncenterNs.Count - 1
                                Dim newplot As New TownPlot
                                newplot.TileID = towncenterNs(ii)
                                If Not newplot.TileID = TileID Then
                                    If Not WorkableLand.Contains(newplot) Then
                                        TileWorld.SetTileToWorkable(towncenterNs(ii))
                                        WorkableLand.Add(newplot)
                                    End If
                                End If
                            Next
                            CurrentUpgradeCount += 1
                            CostMultiplyer *= (CurrentUpgradeCount)
                        End If
                    End If
                End If
                Expand = False
            End If
            If GameTime.TotalGameTime - previousBuildTime > BuildTime Then
                If BuildFarmPlot Then

                    Dim FarmPlot As TownPlot
                    For ii As Integer = 0 To WorkableLand.Count - 1
                        If WorkableLand(ii).WasJustUpgraded Then
                            WorkableLand(ii).WasJustUpgraded = False
                        Else
                            If WorkableLand(ii).CanUpgrade Then

                                FarmPlot = WorkableLand(ii)
                                If FarmPlot.Upgrades.Count > 0 Then
                                    If CheckCost(FarmPlot.Upgrades.Peek, FarmPlot.CostMultiplyer) Then



                                        SubtractCost(FarmPlot.Upgrades.Peek, FarmPlot.CostMultiplyer)
                                        FarmPlot.Upgrades.Dequeue()
                                        If FarmPlot.PlotType = PlotType.none Then
                                            FarmPlot.PlotType = 0
                                        Else
                                            FarmPlot.PlotType += 1
                                        End If
                                        TileWorld.SetTileTargetName(FarmPlot.ReturnPath, FarmPlot.TileID)
                                        FarmPlot.CurrentUpgradeCount += 1
                                        FarmPlot.CostMultiplyer *= (FarmPlot.CurrentUpgradeCount)
                                        FarmPlot.WasJustUpgraded = True

                                    End If
                                End If
                                Exit For
                            End If
                        End If
                    Next

                    BuildFarmPlot = False
                End If
                previousBuildTime = GameTime.TotalGameTime
            End If

            previousThinkTime = GameTime.TotalGameTime
        End If
    End Sub
End Class

Public Enum BuildingType As Byte
    Gathering = 0
    UnitBuilding = 1
    Storage = 2
    Protection = 3
End Enum

Public Class Building
    Public BuildingType As BuildingType
    Public WoodCost As Integer
    Public GoldCost As Integer
    Public StoneCost As Integer
    Public FoodCost As Integer
    Public CanUpgrade As Boolean
    Public UpgradeName As String
    Public ResourceType As ResourceType
    Public ImageName As String
    Public AnimationFrames As Integer
    Public IsAnimated As Boolean
    Public DisplayName As String
    Public Health As Integer

    Public Owner As Integer
    Public TileID As Integer

    Public Function Clone() As Building
        Dim returnobj As New Building
        returnobj.BuildingType = Me.BuildingType
        returnobj.WoodCost = Me.WoodCost
        returnobj.GoldCost = Me.GoldCost
        returnobj.StoneCost = Me.StoneCost
        returnobj.FoodCost = Me.FoodCost
        returnobj.CanUpgrade = Me.CanUpgrade
        returnobj.UpgradeName = Me.UpgradeName
        returnobj.ResourceType = Me.ResourceType
        returnobj.ImageName = Me.ImageName
        returnobj.AnimationFrames = Me.AnimationFrames
        returnobj.IsAnimated = Me.IsAnimated
        returnobj.DisplayName = Me.DisplayName
        returnobj.Health = Me.Health

        Return returnobj
    End Function
End Class

Public Class TownBuilder
    Public BuildingName As String
    Public PlayerIndex As Integer
End Class

Public Class TileWorld

    Public CurrentPlaceMode As TilePlaceMode = TilePlaceMode.Gathering
    Private pointlist As New List(Of Vector2)
    Private atlas As ShaderResourceView
    Private UIManager As UIEngine
    Private TileSourceRect As RectangleF
    Private tileszie As Integer
    Private bounds As RectangleF
    Private bgtilename As String

    Private BigTiles As New List(Of Tile)
    Private SmallTiles As New List(Of Tile)

    Private ActiveTiles As New List(Of Integer)

    Private GroundSpriteBatch As SpriteBatch
    Friend BuildQueue As TownBuilder
    Private PathableNodes As New List(Of Tile)
    Private MouseTargetName As String = Nothing
    Public HasBuidling As Boolean

    <CommandLineParser.UIExpose>
    Public DrawTileSelctionDebug As Boolean
    <CommandLineParser.UIExpose>
    Public DrawPathNodes As Boolean
    <CommandLineParser.UIExpose>
    Public ShowWalkableNodes As Boolean
    <CommandLineParser.UIExpose>
    Public DrawTileCollitionBounds As Boolean

    Private currenttile As Tile

    <CommandLineParser.UIExpose>
    Public Sub SetMouseTargetImage(_name As String)
        MouseTargetName = _name
    End Sub
    <CommandLineParser.UIExpose>
    Public Sub AddBuilding(_name As String, _playerindex As Integer)
        Dim blah As New TownBuilder
        blah.BuildingName = _name
        blah.PlayerIndex = _playerindex
        BuildQueue = blah
        HasBuidling = True
    End Sub
    Public Function GetBuildingBluePrintAndClone(_name As String) As Building
        Dim bb As Building = BuildingUnits(_name).Clone
        bb.TileID = currenttile.Index
        Return bb
    End Function
    Public Function GetBuildingBluePrint(_name As String) As Building
        Dim bb As Building = BuildingUnits(_name)
        Return bb
    End Function
    Public Function CheckCanPlace() As Boolean
        Dim tester As Integer = 0
        Dim resourcesclose As Boolean = False
        Dim tester2 As Integer
        If currenttile IsNot Nothing Then
            ' If currenttile.IsPassible Then
            If currenttile.Nneighbours.Count > 0 Then
                For ii As Integer = 0 To currenttile.Nneighbours.Count - 1
                    Dim tempbounds2 As RectangleF = PathableNodes(currenttile.Nneighbours(ii)).Bounds
                    If currenttile.DrawBounds.Intersects(PathableNodes(currenttile.Nneighbours(ii)).Bounds) Then
                        If currenttile.Bounds.Center.Y > PathableNodes(currenttile.Nneighbours(ii)).Bounds.Center.Y AndAlso
                            (Not PathableNodes(currenttile.Nneighbours(ii)).CanHaveStructure) Then
                            tester2 += 1
                        End If
                    End If

                    Select Case CurrentPlaceMode
                        Case TilePlaceMode.TownPlots
                            If (resourcesclose Or Not currenttile.CanHaveStructure Or currenttile.IsPassible) Then
                                tester += 1
                            End If
                        Case TilePlaceMode.Other

                            If PathableNodes(currenttile.Nneighbours(ii)).ResourceType <> ResourceType.none Then
                                resourcesclose = True
                            End If

                            If (resourcesclose Or Not currenttile.CanHaveStructure Or Not currenttile.IsPassible) Then
                                tester += 1
                            End If
                        Case TilePlaceMode.Gathering
                            For iii As Integer = 0 To PathableNodes(currenttile.Nneighbours(ii)).Nneighbours.Count - 1
                                If PathableNodes(PathableNodes(currenttile.Nneighbours(ii)).Nneighbours(iii)).ResourceType <> ResourceType.none Then
                                    resourcesclose = True
                                End If
                            Next
                            If (Not resourcesclose Or Not currenttile.CanHaveStructure Or Not currenttile.IsPassible)  Then
                                tester += 1
                            End If
                    End Select
                Next
            End If
        Else
            tester += 1
        End If

        Return If(tester = 0 AndAlso tester2 = 0, True, False)
    End Function
    Public Sub New(_atlas As ShaderResourceView, _UIManager As UIEngine, _bounds As RectangleF, _tileszie As Integer, gd As GraphicsDevice, _targettowncount As Integer)
        UIManager = _UIManager
        atlas = _atlas
        bounds = _bounds
        tileszie = _tileszie
        Dim pointsers As New UniformPoissonDiskSampler

        Dim townpoints As New Queue(Of Vector2)
        Do Until townpoints.Count = _targettowncount
            townpoints = pointsers.ReturnQueueCircle(New Vector2(0, 0), _bounds.Width - 1500, _bounds.Width - 2000, 7)
        Loop

        GroundSpriteBatch = New SpriteBatch(gd, 4096)

        BuildPointList(pointlist, New Vector2(bounds.Width, bounds.Height), tileszie * 4, New Vector2(bounds.X, bounds.Y))
        Dim rand As New Random

        For Each item In pointlist
            Dim newtile As New Tile
            newtile.depth = 0.2
            newtile.Bounds = New RectangleF(item.X, item.Y, (tileszie * 4), (tileszie * 4))
            newtile.Bounds.Location = twoDToIso(newtile.Bounds.Location)
            BigTiles.Add(newtile)
        Next
        pointlist.Clear()
        pointlist = Nothing
        pointlist = New List(Of Vector2)
        BuildPointList(pointlist, New Vector2(bounds.Width, bounds.Height), tileszie * 2, New Vector2(bounds.X, bounds.Y))
        For Each item In pointlist
            Dim newtile As New Tile
            newtile.Bounds = New RectangleF(item.X, item.Y, (tileszie * 2), (tileszie * 2))
            newtile.Bounds.Location = twoDToIso(newtile.Bounds.Location)
            For Each item2 In BigTiles
                If item2.Bounds.Contains(newtile.Bounds) Or item2.Bounds.Intersects(newtile.Bounds) Then
                    item2.Childern.Add(newtile)
                End If
            Next
        Next
        Dim resourcetiles As New List(Of Tile)
        pointlist.Clear()
        pointlist = Nothing
        pointlist = New List(Of Vector2)
        Dim counter As Integer = 0
        BuildPointList(pointlist, New Vector2(bounds.Width, bounds.Height), tileszie, New Vector2(bounds.X, bounds.Y))
        For Each item In pointlist
            Dim newtile As New Tile
            newtile.depth = 1
            newtile.BaseTargetName = "tiles/world/ground/0001.gif"
            Dim roll As Integer = rand.Next(0, 55)

            If roll = 13 Then
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/0080.png"
                newtile.HasStuff = True
            End If
            If roll = 9 Then
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/longgrass.png"
                newtile.HasStuff = True
            End If
            If roll = 32 Then
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/floawers.png"
                newtile.HasStuff = True
            End If
            If roll = 48 Then
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/longgrass.png"
                newtile.HasStuff = True
            End If
            If roll = 22 Then
                newtile.TargetName = "tiles/world/decor/0082.png"
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.HasStuff = True
                newtile.IsPassible = False
                newtile.HasResource = True
                newtile.CanHaveStructure = False
                newtile.ResourceType = ResourceType.Wood
                resourcetiles.Add(newtile)
            End If
            If roll = 8 Then
                newtile.HasStuff = True
                newtile.CanHaveStructure = False
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/0001.png"
                newtile.HasResource = True
                newtile.ResourceType = ResourceType.Wood
                newtile.IsPassible = False
                resourcetiles.Add(newtile)
            End If
            If rand.Next(0, 200) = 8 Then
                newtile.HasStuff = True
                newtile.CanHaveStructure = False
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/rocksandtree.png"
                newtile.HasResource = True
                newtile.ResourceType = ResourceType.Wood
                newtile.IsPassible = False
                resourcetiles.Add(newtile)
            End If
            If rand.Next(0, 400) = 8 Then
                newtile.HasStuff = True
                newtile.CanHaveStructure = False
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.TargetName = "tiles/world/decor/pagoda.png"
                newtile.IsPassible = False
                newtile.HasResource = True
                newtile.ResourceType = ResourceType.Stone
                resourcetiles.Add(newtile)
            End If

            If rand.Next(0, 1000) = 8 Then
                newtile.HasStuff = True
                newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                newtile.HasResource = True
                newtile.ResourceType = ResourceType.Gold
                newtile.TargetName = "tiles/world/as_mountain5x5/idle/45/0.png"
                newtile.ScaleFactor = 4
                newtile.CanHaveStructure = False
                newtile.IsPassible = False
                resourcetiles.Add(newtile)
            End If



            newtile.Bounds = New RectangleF(item.X, item.Y, tileszie * 2, tileszie * 2)
            newtile.Bounds.Location = twoDToIso(newtile.Bounds.Location)
            For i As Integer = 0 To townpoints.Count - 1
                If newtile.Bounds.Contains(twoDToIso(townpoints.Peek())) Then
                    townpoints.Dequeue()
                    newtile.HasStuff = True
                    newtile.BaseTargetName = "tiles/world/ground/0002.gif"
                    newtile.TargetName = "tiles/church/renders/idle/45/000.png"
                    newtile.CanHaveStructure = False
                    newtile.IsPassible = False
                    newtile.IsTownCenter = True
                    newtile.HasBuilding = True

                    '   TownCenters.Add(newtile.Index)
                    Exit For
                End If
            Next


            For Each item2 In BigTiles
                If item2.Bounds.Contains(newtile.Bounds) Or item2.Bounds.Intersects(newtile.Bounds) Then
                    For Each item3 In item2.Childern
                        If item3.Bounds.Contains(newtile.Bounds.Location) Then
                            newtile.Parent = item3.Index
                            newtile.ShouldDraw = True
                            newtile.Index = counter
                            item3.Childern.Add(newtile)
                            PathableNodes.Add(newtile)

                            If newtile.IsTownCenter Then
                                TownCenters.Add(newtile.Index)
                            End If
                            counter += 1
                            Exit For

                        End If
                    Next
                End If
            Next
        Next
        Parallel.For(0, PathableNodes.Count, Sub(item As Integer)
                                                 For Each item2 In PathableNodes
                                                     If PathableNodes(item).Bounds <> item2.Bounds Then

                                                         If PathableNodes(item).DrawTestBounds.Intersects(item2.Bounds) Then

                                                             Dim d As Single = Vector2.Distance(item2.TestingBounds.Center, PathableNodes(item).TestingBounds.Center
                                                                                                )
                                                             If PathableNodes(item).ResourceType = ResourceType.Gold AndAlso d <= tileszie * 3.5 Then
                                                                 item2.BaseTargetName = "tiles/world/ground/0001.gif"
                                                                 item2.TargetName = Nothing
                                                                 item2.CanHaveStructure = False
                                                                 item2.TargetName = Nothing
                                                                 item2.ResourceType = ResourceType.none
                                                                 item2.IsPassible = True
                                                                 If d <= tileszie * 2 Then
                                                                     item2.BaseTargetName = "tiles/world/ground/0002.gif"
                                                                     item2.IsPassible = False
                                                                 End If


                                                             End If
                                                         End If
                                                         If PathableNodes(item).TestingBounds.Intersects(item2.TestingBounds) Then
                                                             If PathableNodes(item).IsTownCenter Then
                                                                 item2.BaseTargetName = "tiles/world/ground/0002.gif"
                                                                 item2.TargetName = Nothing
                                                                 item2.IsWorkableLand = True
                                                                 item2.CanHaveStructure = False
                                                                 item2.TargetName = Nothing
                                                             End If
                                                             PathableNodes(item).Nneighbours.Add(item2.Index)
                                                         End If



                                                     End If
                                                 Next
                                             End Sub)


        For i As Integer = 0 To resourcetiles.Count - 1

            Dim testbounds As RectangleF

            If resourcetiles(i).ResourceType = ResourceType.Gold Then
                testbounds = resourcetiles(i).DrawTestBounds
            Else
                testbounds = resourcetiles(i).DrawBounds
            End If

            For ii As Integer = 0 To resourcetiles(i).Nneighbours.Count - 1

                If testbounds.Intersects(PathableNodes(resourcetiles(i).Nneighbours(ii)).Bounds) Then

                    If resourcetiles(i).ResourceType <> ResourceType.none AndAlso PathableNodes(resourcetiles(i).Nneighbours(ii)).ResourceType = ResourceType.none Then
                        If resourcetiles(i).Bounds.Center.Y > PathableNodes(resourcetiles(i).Nneighbours(ii)).Bounds.Center.Y Then

                            PathableNodes(resourcetiles(i).Nneighbours(ii)).BaseTargetName = "tiles/world/ground/0002.gif"
                            PathableNodes(resourcetiles(i).Nneighbours(ii)).CanHaveStructure = False
                            PathableNodes(resourcetiles(i).Nneighbours(ii)).IsPassible = False

                        End If

                    End If
                End If

            Next

        Next

        resourcetiles.Clear()

        pointlist.Clear()
        pointlist = Nothing
        bgtilename = "quad_box.tga"
        LoadBuildings()
    End Sub

    Private TownCenters As New List(Of Integer)
    Private Buildings As New List(Of Integer)

    Public ActiveTileCount As Integer
    Private TilesWithStuffList As New List(Of Tile)
    Private timer As Integer


    Private Sub LoadBuildings()
        Dim files As FileInfo() = New DirectoryInfo(LowLevelDevice.ContentPath & "Isometeric\Buildings\").GetFiles
        For i As Integer = 0 To files.Count - 1
            ParseBuildingXML(files(i).FullName)
        Next

    End Sub
    Private Sub ParseBuildingXML(_filepath As String)


        Try
            Dim xDoc As New XmlDocument()
            xDoc.Load(_filepath)
            ParseBuilding(xDoc.DocumentElement)
        Catch xExc As XmlException

        Catch ex As Exception
        Finally
        End Try

    End Sub

    Private BuildingUnits As New Dictionary(Of String, Building)
    Private Sub ParseBuilding(xmlNode As XmlNode)
        Dim attstr As New System.Text.StringBuilder()

        If xmlNode.Attributes.Count > 0 Then
            For i As Integer = 0 To xmlNode.Attributes.Count - 1
                attstr.Append(xmlNode.Attributes(i).Name & "=" & xmlNode.Attributes(i).Value & ",")
            Next
        End If

        Dim strarray As String() = attstr.ToString.Split(","c)
        Dim newbuilding As Building = SetupBuildingInfo(strarray)
        BuildingUnits.Add(newbuilding.DisplayName, newbuilding)
        attstr = Nothing
    End Sub
    Private Function SetupBuildingInfo(ByRef arry As String()) As Building
        Dim newsettings As New Building
        For Each item In arry
            Dim tempstr As String() = item.Split("="c)
            If tempstr(0) = ("BuildingType") Then
                Select Case tempstr(1)
                    Case "Gathering"
                        newsettings.BuildingType = BuildingType.Gathering
                    Case "UnitBuilding"
                        newsettings.BuildingType = BuildingType.UnitBuilding
                    Case "Storage"
                        newsettings.BuildingType = BuildingType.Storage
                    Case "Protection"
                        newsettings.BuildingType = BuildingType.Protection
                End Select
            End If
            If tempstr(0) = ("WoodCost") Then
                newsettings.WoodCost = tempstr(1)
            End If
            If tempstr(0) = ("GoldCost") Then
                newsettings.GoldCost = tempstr(1)
            End If
            If tempstr(0) = ("StoneCost") Then
                newsettings.StoneCost = tempstr(1)
            End If
            If tempstr(0) = ("FoodCost") Then

                newsettings.FoodCost = tempstr(1)
            End If
            If tempstr(0) = ("CanUpgrade") Then
                newsettings.CanUpgrade = tempstr(1)
            End If
            If tempstr(0) = ("UpgradeName") Then
                newsettings.UpgradeName = tempstr(1)
            End If
            If tempstr(0) = ("ResourceType") Then
                Select Case tempstr(1)
                    Case "Gold"
                        newsettings.ResourceType = ResourceType.Gold
                    Case "Stone"
                        newsettings.ResourceType = ResourceType.Stone
                    Case "Wood"
                        newsettings.ResourceType = ResourceType.Wood
                    Case "Food"
                        newsettings.ResourceType = ResourceType.Food
                    Case "None"
                        newsettings.ResourceType = ResourceType.none
                End Select
            End If
            If tempstr(0) = ("ImageName") Then
                newsettings.ImageName = tempstr(1)
            End If
            If tempstr(0) = ("IsAnimated") Then
                newsettings.IsAnimated = tempstr(1)
            End If
            If tempstr(0) = ("AnimationFrames") Then
                newsettings.AnimationFrames = tempstr(1)
            End If
            If tempstr(0) = ("DisplayName") Then
                newsettings.DisplayName = tempstr(1)
            End If
            If tempstr(0) = ("Health") Then
                newsettings.Health = tempstr(1)
            End If
            tempstr = Nothing
        Next
        arry = Nothing
        Return newsettings
    End Function

    Private Sub getNneighbours(ByRef temlist As List(Of Integer), _tile As Tile, depth As Integer, maxdepth As Integer)

        temlist.Add(_tile.Index)
        depth += 1
        If depth < maxdepth Then
            For i As Integer = 0 To _tile.Nneighbours.Count - 1
                getNneighbours(temlist, PathableNodes(_tile.Nneighbours(i)), depth, maxdepth)
            Next
        End If

    End Sub
    Public Function ReturnNneighbours(_index As Integer, maxdepth As Integer) As List(Of Integer)
        Dim temlist As New List(Of Integer)
        Dim _tile As Tile = PathableNodes(_index)
        If _tile.Nneighbours.Count > 0 Then
            For i As Integer = 0 To _tile.Nneighbours.Count - 1
                getNneighbours(temlist, PathableNodes(_tile.Nneighbours(i)), 0, maxdepth)
            Next

            Return temlist
        End If
        Return temlist
    End Function

    Public Sub SetTileToWorkable(_index As Integer)

        If Not PathableNodes(_index).IsTownCenter Then
            PathableNodes(_index).BaseTargetName = "tiles/world/ground/0002.gif"
            PathableNodes(_index).TargetName = Nothing
            PathableNodes(_index).IsWorkableLand = True
            PathableNodes(_index).IsPassible = True
        End If
    End Sub
    Public Sub SetTileImage(_index As Integer)

        If Not PathableNodes(_index).IsTownCenter Then
            PathableNodes(_index).TargetName = "tiles/world/ground/0002.gif"

        End If
    End Sub


    Public Function ReturnTownCenters() As List(Of Integer)
        Return TownCenters
    End Function
    Public Function ReturnBuildings() As List(Of Integer)
        Return Buildings
    End Function

    Public Sub SetTileTargetName(_TargetName As String, _TileId As Integer)
        PathableNodes(_TileId).HasStuff = True
        PathableNodes(_TileId).CanHaveStructure = False
        PathableNodes(_TileId).TargetName = _TargetName
    End Sub
    Public Sub SetTile()
        If Not PathableNodes(currenttile.Index).HasStuff Then
            PathableNodes(currenttile.Index).HasStuff = True
            PathableNodes(currenttile.Index).CanHaveStructure = False
            PathableNodes(currenttile.Index).IsPassible = False
            PathableNodes(currenttile.Index).TargetName = MouseTargetName
            PathableNodes(currenttile.Index).HasBuilding = True
            MouseTargetName = Nothing
            HasBuidling = False
            For ii As Integer = 0 To PathableNodes(currenttile.Index).Nneighbours.Count - 1

                Dim testbounds As RectangleF

                '  If PathableNodes(currenttile.Index).ResourceType = ResourceType.Gold Then
                'testbounds = PathableNodes(currenttile.Index).DrawTestBounds
                ' Else
                'testbounds = PathableNodes(currenttile.Index).DrawBounds
                'End If


                If testbounds.Intersects(PathableNodes(PathableNodes(currenttile.Index).Nneighbours(ii)).Bounds) Then
                    If PathableNodes(currenttile.Index).Bounds.Center.Y > PathableNodes(PathableNodes(currenttile.Index).Nneighbours(ii)).Bounds.Center.Y Then
                        PathableNodes(PathableNodes(currenttile.Index).Nneighbours(ii)).BaseTargetName = "tiles/world/ground/0002.gif"
                        PathableNodes(PathableNodes(currenttile.Index).Nneighbours(ii)).CanHaveStructure = False
                        PathableNodes(PathableNodes(currenttile.Index).Nneighbours(ii)).IsPassible = False

                    End If
                End If
            Next
        End If
    End Sub
    Private Sub gettiles(Camera As Insight.UI.Camera2D)
        timer += 1

        If timer >= 2 Then
            ActiveTiles.Clear()
            TilesWithStuffList.Clear()

            For i As Integer = 0 To BigTiles.Count - 1
                Dim tempbounds As RectangleF = BigTiles(i).Bounds

                Dim tempvp As RectangleF = Camera.Viewport

                tempbounds.Location = Vector2.Transform(tempbounds.Location, Camera.ViewTransformationMatrix)

                tempvp.Location = Vector2.Transform(tempvp.Location, Camera.ViewTransformationMatrixNoZoomorRotation)
                tempvp.Location = twoDToIso(tempvp.Location)
                tempbounds.Width *= 2 * Camera.Zoom
                tempbounds.Height *= 2 * Camera.Zoom
                If ((tempvp.Contains(tempbounds) Or tempvp.Intersects(tempbounds))) Then
                    FindTiles(BigTiles(i), Camera)
                End If
            Next
            timer = 0
        End If

    End Sub
    Private Sub FindTiles(_tile As Tile, Camera As Insight.UI.Camera2D)


        Dim tempbounds As RectangleF = _tile.Bounds
        Dim tempvp As RectangleF = Camera.Viewport

        tempbounds.Location = Vector2.Transform(tempbounds.Location, Camera.ViewTransformationMatrix)

        tempvp.Location = Vector2.Transform(tempvp.Location, Camera.ViewTransformationMatrixNoZoomorRotation)
        tempvp.Location = twoDToIso(tempvp.Location)
        tempbounds.Width *= 2 * Camera.Zoom
        tempbounds.Height *= 2 * Camera.Zoom
        If (tempvp.Contains(tempbounds) Or tempvp.Intersects(tempbounds)) Then
            Dim br As Vector2 = New Vector2(4096 * 2, 4096 * 4)
            _tile.dist = Vector2.Distance(_tile.DrawBounds.Location, br) 'MathHelper.manhattanDistance(_tile.DrawBounds.Location, br)
            If _tile.ShouldDraw Then
                If _tile.HasStuff Then
                    TilesWithStuffList.Add(_tile)
                End If
                ActiveTiles.Add(_tile.Index)
            End If
            If _tile.Childern.Count > 0 Then
                For i As Integer = 0 To _tile.Childern.Count - 1
                    FindTiles(_tile.Childern(i), Camera)
                Next
            End If
        End If




    End Sub


    Public Sub draw(SpriteBatch As SpriteBatch, GraphicsDevice As GraphicsDevice, camera As Insight.UI.Camera2D)
        '  GroundSpriteBatch.Begin(Toolkit.Graphics.SpriteSortMode.BackToFront, GraphicsDevice.BlendStates.AlphaBlend, Nothing, Nothing, Nothing, Nothing, camera.ViewTransformationMatrix)
        SpriteBatch.Begin(Toolkit.Graphics.SpriteSortMode.Deferred, GraphicsDevice.BlendStates.AlphaBlend, Nothing, Nothing, Nothing, Nothing, camera.ViewTransformationMatrix)
        ActiveTileCount = ActiveTiles.Count
        currenttile = Nothing
        For i As Integer = 0 To ActiveTiles.Count - 1
            Dim tempbounds As RectangleF = PathableNodes(ActiveTiles(i)).Bounds

            tempbounds.Width /= 2
            tempbounds.Height /= 2

            Dim tempmouserect As RectangleF = camera.MouseRect
            tempmouserect.Y -= 175
            tempmouserect.X -= 75

            tempmouserect.Width = 0.1
            tempmouserect.Height = 0.1


            If tempbounds.Intersects(tempmouserect) Then
                currenttile = PathableNodes(ActiveTiles(i))
            End If

            If ShowWalkableNodes Then
                If PathableNodes(ActiveTiles(i)).IsPassible Then
                    SpriteBatch.Draw(atlas, PathableNodes(ActiveTiles(i)).Bounds, LowLevelDevice.GetSourceRectangle(PathableNodes(ActiveTiles(i)).BaseTargetName), Color.Green, 0, Nothing, Nothing, PathableNodes(ActiveTiles(i)).depth)
                Else
                    SpriteBatch.Draw(atlas, PathableNodes(ActiveTiles(i)).Bounds, LowLevelDevice.GetSourceRectangle(PathableNodes(ActiveTiles(i)).BaseTargetName), Color.Red, 0, Nothing, Nothing, PathableNodes(ActiveTiles(i)).depth)
                End If
            Else
                SpriteBatch.Draw(atlas, PathableNodes(ActiveTiles(i)).Bounds, LowLevelDevice.GetSourceRectangle(PathableNodes(ActiveTiles(i)).BaseTargetName), Color.White, 0, Nothing, Nothing, PathableNodes(ActiveTiles(i)).depth)
            End If


        Next

        If currenttile IsNot Nothing Then

            If DrawTileSelctionDebug Then
                If currenttile.Nneighbours.Count > 0 Then
                    For ii As Integer = 0 To currenttile.Nneighbours.Count - 1
                        Dim tempbounds2 As RectangleF = PathableNodes(currenttile.Nneighbours(ii)).Bounds

                        If Not PathableNodes(currenttile.Nneighbours(ii)).IsPassible Then
                            SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.9)
                        Else
                            Dim resourcesclose As Boolean = False
                            For iii As Integer = 0 To PathableNodes(currenttile.Nneighbours(ii)).Nneighbours.Count - 1
                                If PathableNodes(PathableNodes(currenttile.Nneighbours(ii)).Nneighbours(iii)).ResourceType <> ResourceType.none Then
                                    resourcesclose = True
                                End If
                            Next

                            Select Case CurrentPlaceMode
                                Case TilePlaceMode.TownPlots
                                    If Not resourcesclose Then
                                        SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Green, 0, Nothing, Nothing, 0.9)
                                    Else
                                        SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.9)
                                    End If
                                Case TilePlaceMode.Other
                                    If Not resourcesclose AndAlso PathableNodes(currenttile.Nneighbours(ii)).CanHaveStructure Then
                                        SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Green, 0, Nothing, Nothing, 0.9)
                                    Else
                                        SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.9)
                                    End If
                                Case TilePlaceMode.Gathering

                                    If Not resourcesclose Then
                                        SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.9)
                                    Else
                                        SpriteBatch.Draw(atlas, tempbounds2, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Green, 0, Nothing, Nothing, 0.9)
                                    End If
                            End Select
                        End If
                    Next
                End If
            End If

            If DrawTileCollitionBounds Then
                SpriteBatch.Draw(atlas, currenttile.DrawBounds, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Gray, 0, Nothing, Nothing, 0.85)
                If MouseTargetName IsNot Nothing Then
                    SpriteBatch.Draw(atlas, currenttile.Bounds, LowLevelDevice.GetSourceRectangle(MouseTargetName), Color.White, 0, Nothing, Nothing, 0.75)
                End If
            Else
                SpriteBatch.Draw(atlas, currenttile.Bounds, LowLevelDevice.GetSourceRectangle(currenttile.BaseTargetName), Color.Gray, 0, Nothing, Nothing, 0.85)
                If MouseTargetName IsNot Nothing Then
                    SpriteBatch.Draw(atlas, currenttile.Bounds, LowLevelDevice.GetSourceRectangle(MouseTargetName), Color.White, 0, Nothing, Nothing, 0.75)
                End If
            End If
        End If
        If DrawPathNodes Then
            If FoundPath IsNot Nothing Then
                For i As Integer = 0 To FoundPath.Count - 1
                    SpriteBatch.Draw(atlas, PathableNodes(FoundPath(i)).Bounds, LowLevelDevice.GetSourceRectangle(PathableNodes(FoundPath(i)).BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.8)
                Next
            End If
            If HasStartNode Then
                SpriteBatch.Draw(atlas, PathableNodes(StartNodeIndex).Bounds, LowLevelDevice.GetSourceRectangle(PathableNodes(StartNodeIndex).BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.8)
            End If
            If HasEndNode Then
                SpriteBatch.Draw(atlas, PathableNodes(EndNodeIndex).Bounds, LowLevelDevice.GetSourceRectangle(PathableNodes(EndNodeIndex).BaseTargetName), Color.Red, 0, Nothing, Nothing, 0.8)
            End If
        End If
        SpriteBatch.End()

        TilesWithStuffList.Sort()
        Dim counter As Integer = TilesWithStuffList.Count - 1
        SpriteBatch.Begin(Toolkit.Graphics.SpriteSortMode.BackToFront, GraphicsDevice.BlendStates.AlphaBlend, Nothing, Nothing, Nothing, Nothing, camera.ViewTransformationMatrix)
        For i As Integer = 0 To TilesWithStuffList.Count - 1
            Dim tempbounds As RectangleF = TilesWithStuffList(counter).Bounds
            SpriteBatch.Draw(atlas, If(TilesWithStuffList(counter).HasResource Or TilesWithStuffList(counter).HasBuilding, TilesWithStuffList(counter).DrawBounds, tempbounds), LowLevelDevice.GetSourceRectangle(TilesWithStuffList(counter).TargetName), Color.White,
                             0, Nothing, Nothing, TilesWithStuffList(counter).dist / TilesWithStuffList(TilesWithStuffList.Count - 1).dist)
            counter -= 1
        Next
        SpriteBatch.End()


    End Sub





    Private StartNodeIndex As Integer
    Private EndNodeIndex As Integer
    Private HasStartNode As Boolean
    Private HasEndNode As Boolean


    Public Sub SetStartNode()

        If currenttile IsNot Nothing Then
            If Not currenttile.IsPassible Or Not currenttile.CanHaveStructure Then Exit Sub
            HasStartNode = True
            StartNodeIndex = currenttile.Index
        End If
    End Sub
    Public Sub SetEndNode()
        If currenttile IsNot Nothing Then
            If Not currenttile.IsPassible Or Not currenttile.CanHaveStructure Then Exit Sub
            HasEndNode = True
            EndNodeIndex = currenttile.Index
        End If
    End Sub
    Private FoundPath As List(Of Integer)
    Public Sub FindPath()


        If HasEndNode AndAlso HasStartNode Then
            FoundPath = FindPath(StartNodeIndex, EndNodeIndex)
            CurrentPathNodeCount = FoundPath.Count
        End If


    End Sub

    Public Sub update(camera As Insight.UI.Camera2D, Device As LowLevelDevice)

        gettiles(camera)
    End Sub
    Public CurrentPathIterations As Integer
    Public CurrentPathNodeCount As Integer
    Public MaxPathIterations As Integer = 2000
    ''' <summary>
    ''' Calculate the shortest path between two points
    ''' </summary>
    ''' <param name="start"> Starting point </param>
    ''' <param name="end"> Ending point </param>
    ''' <returns> List of points included in the path (in order) </returns>
    Public Function FindPath(start As Integer, [end] As Integer) As List(Of Integer)
        '   Reset()
        CurrentPathIterations = 0
        Dim openHeap As Object = New BinaryHeap(Of PathNode)()

        ' find the node at the starting point, close it, and add it
        ' to the heap

        Dim base As Tile = PathableNodes(start)
        Dim startNode As New PathNode
        startNode.Index = base.Index
        startNode.IsPassible = base.IsPassible
        startNode.Closed = True

        openHeap.Add(startNode)
        Dim path As List(Of Integer) = New List(Of Integer)()
        ' iterate until there are no more items in the heap
        While openHeap.Count > 0
            Dim currentNode As PathNode = openHeap.Pop()

            ' reached our destination
            If currentNode.Index = [end] Or CurrentPathIterations = MaxPathIterations Then
                Dim current As PathNode = currentNode



                path.Add(start)

                While current.Parent IsNot Nothing
                    If Not path.Contains(current.Index) Then path.Add(current.Index)

                    current = current.Parent
                End While

                path.Reverse()

                Return path
            End If

            currentNode.Closed = True

            If CurrentPathIterations = MaxPathIterations Then
                Exit While
            End If

            Dim neighbors As List(Of PathNode) = getNneighbours(currentNode.Index)

            For Each neighbor As PathNode In neighbors
                ' don't need to check it
                If neighbor.Closed OrElse Not neighbor.IsPassible Then
                    Continue For
                End If

                ' the g score is the shortest distance from start 
                ' to the current node. We need to check if the current
                ' neighbor to this node is the lowest cost so far
                Dim g As Integer = currentNode.G + neighbor.Cost

                Dim hasVisited As Boolean = neighbor.Visited

                If Not hasVisited OrElse g < neighbor.G Then

                    ' found the best node so far, so estimate it's cost
                    ' and deal with it in the heap accordingly
                    neighbor.Visited = True
                    neighbor.Parent = currentNode
                    neighbor.H = manhattanDistance(neighbor.Index, [end])
                    neighbor.G = g
                    neighbor.F = neighbor.G + neighbor.H

                    ' add the neighbor to the heap if we haven't visited
                    ' it yet, otherwise re score it in the heap
                    If Not hasVisited Then
                        openHeap.Add(neighbor)
                    Else
                        openHeap.RescoreItem(neighbor)
                    End If
                End If
            Next
            CurrentPathIterations += 1
        End While

        Return path
    End Function


    Private Function getNneighbours(_index As Integer) As List(Of PathNode)
        Dim _list As New List(Of PathNode)
        If PathableNodes(_index).Nneighbours.Count > 0 Then
            For i As Integer = 0 To PathableNodes(_index).Nneighbours.Count - 1
                Dim d As Single = Vector2.Distance(PathableNodes(_index).Bounds.Center, PathableNodes(PathableNodes(_index).Nneighbours(i)).Bounds.Center)
                'If d <= tileszie Then
                Dim startNode As New PathNode
                startNode.Index = PathableNodes(PathableNodes(_index).Nneighbours(i)).Index
                startNode.IsPassible = PathableNodes(PathableNodes(_index).Nneighbours(i)).IsPassible
                _list.Add(startNode)
                ' End If
            Next
        End If
        Return _list
    End Function
    ''' <summary>
    ''' Manhattan distance between two points. Used for estimating the 
    ''' score of a path node
    ''' </summary>
    Function manhattanDistance(p1 As Integer, p2 As Integer) As Integer

        Dim point As Vector2 = PathableNodes(p1).Bounds.Location
        Dim point2 As Vector2 = PathableNodes(p2).Bounds.Location

        Return Math.Max(Math.Abs(point.X - point2.X), Math.Abs(point.Y - point2.Y))
    End Function
End Class
Public Class PathNode
    Implements IComparable(Of PathNode)
    Private _f As Integer, _g As Integer, _h As Integer, _cost As Integer

    ''' <summary>
    ''' Total cost of this node from estimations
    ''' </summary>
    Public Property F() As Integer
        Get
            Return _f
        End Get
        Set
            _f = Value
        End Set
    End Property

    ''' <summary>
    ''' Total cost of this node from the starting point
    ''' </summary>
    Public Property G() As Integer
        Get
            Return _g
        End Get
        Set
            _g = Value
        End Set
    End Property

    ''' <summary>
    ''' Estimated Heuristic cost of this node from the destination
    ''' </summary>
    Public Property H() As Integer
        Get
            Return _h
        End Get
        Set
            _h = Value
        End Set
    End Property

    ''' <summary>
    ''' Initial cost of this node
    ''' </summary>
    Public Property Cost() As Integer
        Get
            Return _cost
        End Get
        Set
            _cost = Value
        End Set
    End Property

    Private _visited As Boolean

    ''' <summary>
    ''' Whether or not we've searched this node
    ''' </summary>
    Public Property Visited() As Boolean
        Get
            Return _visited
        End Get
        Set
            _visited = Value
        End Set
    End Property

    Private _closed As Boolean

    ''' <summary>
    ''' Whether or not this node is able to be searched again
    ''' </summary>
    Public Property Closed() As Boolean
        Get
            Return _closed
        End Get
        Set
            _closed = Value
        End Set
    End Property

    Private _isPassible As Boolean = True

    ''' <summary>
    ''' Whether or not this node can be used as a path
    ''' </summary>
    Public Property IsPassible() As Boolean
        Get
            Return _isPassible
        End Get
        Set
            _isPassible = Value
        End Set
    End Property

    ''' <summary>
    ''' Grid location
    ''' </summary>
    Public Index As Integer


    Public Parent As PathNode

    ''' <summary>
    ''' Compares the f cost variable
    ''' </summary>
    Function CompareTo(other As PathNode) As Integer Implements IComparable(Of PathNode).CompareTo
        Return F - other.F
    End Function



End Class

Public Enum ResourceType As Byte
    Wood = 0
    Stone = 1
    Gold = 3
    Food = 4
    none = 255
End Enum
Public Class Tile
    Implements IComparable(Of Tile)
    Implements IEquatable(Of Tile)
    Public Bounds As New RectangleF
    Public Nneighbours As New List(Of Integer)
    Public Childern As New List(Of Tile)
    Public Parent As Integer
    Public ShouldDraw As Boolean
    Public Color As Color = Color.White
    Public TargetName As String
    Public BaseTargetName As String
    Public depth As Single
    Public HasStuff As Boolean
    Public IsPassible As Boolean = True
    Private _index As Integer

    Public IsTownCenter As Boolean
    Public IsWorkableLand As Boolean
    Public HasResource As Boolean
    Public ResourceType As ResourceType = ResourceType.none
    Public CanHaveStructure As Boolean = True
    Public HasBuilding As Boolean
    Public ScaleFactor As Single = 2
    ''' <summary>
    ''' Grid location
    ''' </summary>
    Public Property Index() As Integer

        Get
            Return _index
        End Get
        Set(value As Integer)
            _index = value
        End Set


    End Property
    Public ReadOnly Property TestingBounds As RectangleF
        Get
            Dim tempvect As Vector2 = IsoTo2D(Bounds.Location)
            Dim temprect As RectangleF = New RectangleF(tempvect.X, tempvect.Y, Bounds.Width / 2, Bounds.Height / 2)
            temprect.Inflate(2, 2)
            Return temprect
        End Get

    End Property
    Public ReadOnly Property TestingBounds2x As RectangleF
        Get
            Dim tempvect As Vector2 = Bounds.Location
            Dim temprect As RectangleF = New RectangleF(tempvect.X, tempvect.Y - (Bounds.Width / 4), Bounds.Width, Bounds.Height)

            Return temprect
        End Get

    End Property
    Public ReadOnly Property DrawBounds As RectangleF
        Get
            Dim tempvect As Vector2 = Bounds.Location
            Dim temprect As RectangleF = New RectangleF(If(ScaleFactor = 4, tempvect.X - Bounds.Width * 1.5, tempvect.X - Bounds.Width / 2), If(ScaleFactor = 4, tempvect.Y - Bounds.Width * 1.8, tempvect.Y - Bounds.Width), Bounds.Width * ScaleFactor, Bounds.Height * ScaleFactor)

            Return temprect
        End Get

    End Property
    Public ReadOnly Property DrawTestBounds As RectangleF
        Get
            Dim tempvect As Vector2 = Bounds.Location
            Dim temprect As RectangleF = New RectangleF(If(ScaleFactor = 4, tempvect.X - (Bounds.Width / 3), tempvect.X - Bounds.Width / 2), If(ScaleFactor = 4, tempvect.Y - Bounds.Width, tempvect.Y - Bounds.Width), Bounds.Width * (ScaleFactor / 2.7), Bounds.Height * (ScaleFactor * 0.7))

            Return temprect
        End Get

    End Property
    Public dist As Single
    Public Function CompareTo(other As Tile) As Integer Implements IComparable(Of Tile).CompareTo
        Return dist.CompareTo(other.dist)
    End Function

    Public Function EqualsEX(other As Tile) As Boolean Implements IEquatable(Of Tile).Equals
        Return Me.Bounds.Center = other.Bounds.Center
    End Function
End Class