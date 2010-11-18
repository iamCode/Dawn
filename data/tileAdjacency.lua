local tileSet = EditorInterface.getTileSet();

-- only add adjacency information if the tiles are currently defined which should mean they exist in the current tileset
function addAdjacencyIfExists( tile1, adjacencyType, tile2, offsetX, offsetY )
	if ( tile1 == nil or tile2 == nil )
	then
		return;
	else
		if ( offsetX == nil )
		then
			offsetX = 0;
		end
		if ( offsetY == nil )
		then
			offsetY = 0;
		end
		tileSet:addAdjacency( tile1, adjacencyType, tile2, offsetX, offsetY );
	end
end

function addTileToEquivalenceClassIfExists( equivalenceClass, tile, offsetX, offsetY )
	if ( tile == nil )
	then
		return;
	else
		if ( offsetX == nil )
		then
			offsetX = 0;
		end
		if ( offsetY == nil )
		then
			offsetY = 0;
		end
		equivalenceClass:addEquivalentTile( tile, offsetX, offsetY );
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
tileSet:addEquivalenceAdjacency( houseInteriorCentreTop, AdjacencyType.RIGHT, houseInteriorCentreTop, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorCentreTop, AdjacencyType.RIGHT, houseInteriorRightTop, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorLeftTop, AdjacencyType.RIGHT, houseInteriorCentreTop, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorLeftTop, AdjacencyType.RIGHT, houseInteriorRightTop, 0, 0 );

-- left tiles are with shadow to the right
-- top left tiles
local houseInteriorTopLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorTopLeft, houseinterior_insidewall1_tga, 0, -40 );
addTileToEquivalenceClassIfExists( houseInteriorTopLeft, houseinterior_insidewalldamaged1_tga, 0, -40 );
addTileToEquivalenceClassIfExists( houseInteriorTopLeft, houseinterior_insidewall15_tga, -11, 0 );
addTileToEquivalenceClassIfExists( houseInteriorTopLeft, houseinterior_insidewalldamaged15_tga, -11, 0 );

-- centre left tiles
local houseInteriorCentreLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorCentreLeft, houseinterior_insidewall7_tga, 5, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreLeft, houseinterior_insidewalldamaged7_tga, 5, 0 );

-- bottom left tiles
local houseInteriorBottomLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorBottomLeft, houseinterior_insidewall9_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorBottomLeft, houseinterior_insidewalldamaged9_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorBottomLeft, houseinterior_insidewall13_tga, -11, 0 );
addTileToEquivalenceClassIfExists( houseInteriorBottomLeft, houseinterior_insidewalldamaged13_tga, -11, 0 );

tileSet:addEquivalenceAdjacency( houseInteriorCentreLeft, AdjacencyType.TOP, houseInteriorCentreLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorCentreLeft, AdjacencyType.TOP, houseInteriorTopLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorBottomLeft, AdjacencyType.TOP, houseInteriorCentreLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorBottomLeft, AdjacencyType.TOP, houseInteriorTopLeft, 0, 0 );

-- right tiles are without shadow to the right

-- top right tiles
local houseInteriorTopRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorTopRight, houseinterior_insidewall4_tga, 0, -40 );
addTileToEquivalenceClassIfExists( houseInteriorTopRight, houseinterior_insidewalldamaged4_tga, 0, -40 );
addTileToEquivalenceClassIfExists( houseInteriorTopRight, houseinterior_insidewall16_tga, 37, 0 );
addTileToEquivalenceClassIfExists( houseInteriorTopRight, houseinterior_insidewalldamaged16_tga, 37, 0 );

-- centre right tiles
local houseInteriorCentreRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorCentreRight, houseinterior_insidewall5_tga, 42, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreRight, houseinterior_insidewalldamaged5_tga, 42, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreRight, houseinterior_insidewall6_tga, 42, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreRight, houseinterior_insidewalldamaged6_tga, 41, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreRight, houseinterior_insidewall8_tga, 42, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreRight, houseinterior_insidewalldamaged8_tga, 41, 0 );

-- bottom right tiles
local houseInteriorBottomRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorBottomRight, houseinterior_insidewall12_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorBottomRight, houseinterior_insidewalldamaged12_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorBottomRight, houseinterior_insidewall14_tga, 33, 0 );
addTileToEquivalenceClassIfExists( houseInteriorBottomRight, houseinterior_insidewalldamaged14_tga, 33, 0 );

tileSet:addEquivalenceAdjacency( houseInteriorCentreRight, AdjacencyType.TOP, houseInteriorCentreRight, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorCentreRight, AdjacencyType.TOP, houseInteriorTopRight, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorBottomRight, AdjacencyType.TOP, houseInteriorCentreRight, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorBottomRight, AdjacencyType.TOP, houseInteriorTopRight, 0, 0 );

-- bottom tiles

-- left bottom tiles
local houseInteriorLeftBottom = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorLeftBottom, houseinterior_insidewall9_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorLeftBottom, houseinterior_insidewalldamaged9_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorLeftBottom, houseinterior_insidewall16_tga, 0, -6 );
addTileToEquivalenceClassIfExists( houseInteriorLeftBottom, houseinterior_insidewalldamaged16_tga, 0, -6 );

-- centre bottom tiles
local houseInteriorCentreBottom = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorCentreBottom, houseinterior_insidewall10_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreBottom, houseinterior_insidewalldamaged10_tga, 0, 0 );
addTileToEquivalenceClassIfExists( houseInteriorCentreBottom, houseinterior_insidewall11_tga, 0, -2 );
addTileToEquivalenceClassIfExists( houseInteriorCentreBottom, houseinterior_insidewalldamaged11_tga, 0, -2 );

-- right bottom tiles
local houseInteriorRightBottom = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( houseInteriorRightBottom, houseinterior_insidewall12_tga, 0, -3 );
addTileToEquivalenceClassIfExists( houseInteriorRightBottom, houseinterior_insidewalldamaged12_tga, 0, -3 );
addTileToEquivalenceClassIfExists( houseInteriorRightBottom, houseinterior_insidewall15_tga, 0, -5 );
addTileToEquivalenceClassIfExists( houseInteriorRightBottom, houseinterior_insidewalldamaged15_tga, 0, -5 );

tileSet:addEquivalenceAdjacency( houseInteriorCentreBottom, AdjacencyType.RIGHT, houseInteriorCentreBottom, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorCentreBottom, AdjacencyType.RIGHT, houseInteriorRightBottom, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorLeftBottom, AdjacencyType.RIGHT, houseInteriorCentreBottom, 0, 0 );
tileSet:addEquivalenceAdjacency( houseInteriorLeftBottom, AdjacencyType.RIGHT, houseInteriorRightBottom, 0, 0 );


-- village houses

local villageHouseTopLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseTopLeft, village_village1_tga );

local villageHouseLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseLeft, village_village2_tga );

local villageHouseBottomLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseBottomLeft, village_village3_tga );

local villageHouseTop = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseTop, village_village4_tga );

local villageHouseCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseCentre, village_village5_tga );

local villageHouseBottom = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseBottom, village_village6_tga );
addTileToEquivalenceClassIfExists( villageHouseBottom, village_village10_tga, 0, 11 );
addTileToEquivalenceClassIfExists( villageHouseBottom, village_village11_tga );
addTileToEquivalenceClassIfExists( villageHouseBottom, village_village12_tga );

local villageHouseTopRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseTopRight, village_village7_tga );

local villageHouseRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseRight, village_village8_tga );

local villageHouseBottomRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageHouseBottomRight, village_village9_tga );

-- adjacency of village house tiles
tileSet:addEquivalenceAdjacency( villageHouseTop, AdjacencyType.RIGHT, villageHouseTop, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseTop, AdjacencyType.RIGHT, villageHouseTopRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseTopLeft, AdjacencyType.RIGHT, villageHouseTop, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseTopLeft, AdjacencyType.RIGHT, villageHouseTopRight, 0, 0 );

tileSet:addEquivalenceAdjacency( villageHouseCentre, AdjacencyType.RIGHT, villageHouseCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseCentre, AdjacencyType.RIGHT, villageHouseRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseLeft, AdjacencyType.RIGHT, villageHouseCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseLeft, AdjacencyType.RIGHT, villageHouseRight, 0, 0 );

tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.RIGHT, villageHouseBottom, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.RIGHT, villageHouseBottomRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.RIGHT, villageHouseBottom, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.RIGHT, villageHouseBottomRight, 0, 0 );

tileSet:addEquivalenceAdjacency( villageHouseLeft, AdjacencyType.TOP, villageHouseLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseLeft, AdjacencyType.TOP, villageHouseTopLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.TOP, villageHouseLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.TOP, villageHouseTopLeft, 0, 0 );

tileSet:addEquivalenceAdjacency( villageHouseCentre, AdjacencyType.TOP, villageHouseCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseCentre, AdjacencyType.TOP, villageHouseTop, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.TOP, villageHouseCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.TOP, villageHouseTop, 0, 0 );

tileSet:addEquivalenceAdjacency( villageHouseRight, AdjacencyType.TOP, villageHouseRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseRight, AdjacencyType.TOP, villageHouseTopRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomRight, AdjacencyType.TOP, villageHouseRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomRight, AdjacencyType.TOP, villageHouseTopRight, 0, 0 );


tileSet:printTileSet();

