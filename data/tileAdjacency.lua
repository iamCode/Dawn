local tileSet = EditorInterface.getTileSet();

-- only add adjacency information if the tiles are currently defined which should mean they exist in the current tileset
function addAdjacencyIfExists( tile1, adjacencyType, tile2 )
	if ( tile1 == nil or tile2 == nil )
	then
		return;
	else
		tileSet:addAdjacency( tile1, adjacencyType, tile2 );
	end
end

addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewall2_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewall3_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewall1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewall2_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewall3_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewall14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewall2_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewall3_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged1_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewall2_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewall3_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged14_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewall2_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewall3_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewall2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewall3_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewall3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged14_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged2_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged2_tga, AdjacencyType.RIGHT, houseinterior_insidewall13_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged2_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged2_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged3_tga, AdjacencyType.RIGHT, houseinterior_insidewall4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged3_tga, AdjacencyType.RIGHT, houseinterior_insidewall14_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged3_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged4_tga );
addAdjacencyIfExists( houseinterior_insidewalldamaged3_tga, AdjacencyType.RIGHT, houseinterior_insidewalldamaged13_tga );



tileSet:printTileSet();

