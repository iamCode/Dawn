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

function addTileToEquivalenceClassIfExists( equivalenceClass, tile )
	if ( tile == nil )
	then
		return;
	else
		equivalenceClass:addEquivalentTile( tile );
	end
end

-- create adjacence equivalence classes
-- This are groups of tiles where each can be exchanged by another with respect to the tiles that fit next to them

-- all dungeon walls of houseinterior tile group

-- left top tiles <--> centre top tiles <--> right top tiles
--
-- top left tiles                                  top right tiles
--         /\                                              /\
--         ||                                              ||
--         \/                                              \/
-- centre left tiles                               centre right tiles
--         /\                                              /\
--         ||                                              ||
--         \/                                              \/
-- bottom left tiles                               bottom right tiles
--
-- left bottom tiles <--> centre bottom tiles <--> right bottom tiles

-- left top tiles 
local houseInteriorLeftTop = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorLeftTop, houseinterior_insidewall1_tga );
addTileToEquivalenceClassIfExists( houseInteriorLeftTop, houseinterior_insidewall14_tga );
addTileToEquivalenceClassIfExists( houseInteriorLeftTop, houseinterior_insidewalldamaged1_tga );
addTileToEquivalenceClassIfExists( houseInteriorLeftTop, houseinterior_insidewalldamaged14_tga );

-- centre top tiles
local houseInteriorCentreTop = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorCentreTop, houseinterior_insidewall2_tga );
addTileToEquivalenceClassIfExists( houseInteriorCentreTop, houseinterior_insidewall3_tga );
addTileToEquivalenceClassIfExists( houseInteriorCentreTop, houseinterior_insidewalldamaged2_tga );
addTileToEquivalenceClassIfExists( houseInteriorCentreTop, houseinterior_insidewalldamaged3_tga );
addTileToEquivalenceClassIfExists( houseInteriorCentreTop, houseinterior_insidewall_door_tga );

-- right top tiles
local houseInteriorRightTop = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorRightTop, houseinterior_insidewall4_tga );
addTileToEquivalenceClassIfExists( houseInteriorRightTop, houseinterior_insidewall13_tga );
addTileToEquivalenceClassIfExists( houseInteriorRightTop, houseinterior_insidewalldamaged4_tga );
addTileToEquivalenceClassIfExists( houseInteriorRightTop, houseinterior_insidewalldamaged13_tga );

-- add equivalence rules for X top tiles
tileSet:addEquivalenceAdjacency( houseInteriorCentreTop, AdjacencyType.RIGHT, houseInteriorCentreTop );
tileSet:addEquivalenceAdjacency( houseInteriorCentreTop, AdjacencyType.RIGHT, houseInteriorRightTop );
tileSet:addEquivalenceAdjacency( houseInteriorLeftTop, AdjacencyType.RIGHT, houseInteriorCentreTop );
tileSet:addEquivalenceAdjacency( houseInteriorLeftTop, AdjacencyType.RIGHT, houseInteriorRightTop );

tileSet:printTileSet();

