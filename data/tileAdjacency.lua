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
tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.RIGHT, villageHouseBottomRight, 0, 1 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.RIGHT, villageHouseBottom, 0, -3 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.RIGHT, villageHouseBottomRight, 0, -2 );

tileSet:addEquivalenceAdjacency( villageHouseLeft, AdjacencyType.TOP, villageHouseLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseLeft, AdjacencyType.TOP, villageHouseTopLeft, 1, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.TOP, villageHouseLeft, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomLeft, AdjacencyType.TOP, villageHouseTopLeft, 1, 0 );

tileSet:addEquivalenceAdjacency( villageHouseCentre, AdjacencyType.TOP, villageHouseCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseCentre, AdjacencyType.TOP, villageHouseTop, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.TOP, villageHouseCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottom, AdjacencyType.TOP, villageHouseTop, 0, 0 );

tileSet:addEquivalenceAdjacency( villageHouseRight, AdjacencyType.TOP, villageHouseRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseRight, AdjacencyType.TOP, villageHouseTopRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomRight, AdjacencyType.TOP, villageHouseRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageHouseBottomRight, AdjacencyType.TOP, villageHouseTopRight, 0, 0 );

-- village fence
local villageFenceHorizontalCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageFenceHorizontalCentre, village_fence2_tga );
addTileToEquivalenceClassIfExists( villageFenceHorizontalCentre, village_fence6_tga );
addTileToEquivalenceClassIfExists( villageFenceHorizontalCentre, village_fence7_tga );

local villageFenceLeft = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageFenceLeft, village_fence1_tga, 0, 15 );
addTileToEquivalenceClassIfExists( villageFenceLeft, village_fence9_tga );

local villageFenceRight = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( villageFenceRight, village_fence3_tga );
addTileToEquivalenceClassIfExists( villageFenceRight, village_fence8_tga );
addTileToEquivalenceClassIfExists( villageFenceRight, village_fence10_tga, 0, 15 );

-- adjacency of village fence
tileSet:addEquivalenceAdjacency( villageFenceHorizontalCentre, AdjacencyType.RIGHT, villageFenceHorizontalCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageFenceHorizontalCentre, AdjacencyType.RIGHT, villageFenceRight, 0, 0 );
tileSet:addEquivalenceAdjacency( villageFenceLeft, AdjacencyType.RIGHT, villageFenceHorizontalCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( villageFenceLeft, AdjacencyType.RIGHT, villageFenceRight, 0, 0 );

addAdjacencyIfExists( village_fence4_tga, AdjacencyType.TOP, village_fence4_tga, 0, -16 )
addAdjacencyIfExists( village_fence4_tga, AdjacencyType.TOP, village_fence5_tga, 0, -16 )
addAdjacencyIfExists( village_fence4_tga, AdjacencyType.TOP, village_fence9_tga, -7, -16 )
addAdjacencyIfExists( village_fence4_tga, AdjacencyType.TOP, village_fence10_tga, -7, -40 )
addAdjacencyIfExists( village_fence5_tga, AdjacencyType.TOP, village_fence4_tga, 0, -21 )
addAdjacencyIfExists( village_fence5_tga, AdjacencyType.TOP, village_fence5_tga, 0, -21 )
addAdjacencyIfExists( village_fence5_tga, AdjacencyType.TOP, village_fence9_tga, -7, -21 )
addAdjacencyIfExists( village_fence5_tga, AdjacencyType.TOP, village_fence10_tga, -7, -45 )

addAdjacencyIfExists( village_fence4_tga, AdjacencyType.BOTTOM, village_fence1_tga, -6, 32 )
addAdjacencyIfExists( village_fence4_tga, AdjacencyType.BOTTOM, village_fence3_tga, -6, 17 )
addAdjacencyIfExists( village_fence5_tga, AdjacencyType.BOTTOM, village_fence1_tga, -6, 32 )
addAdjacencyIfExists( village_fence5_tga, AdjacencyType.BOTTOM, village_fence3_tga, -6, 17 )

addAdjacencyIfExists( village_fence9_tga, AdjacencyType.BOTTOM, village_fence1_tga, 0, 32 )
addAdjacencyIfExists( village_fence9_tga, AdjacencyType.BOTTOM, village_fence3_tga, 0, 17 )
addAdjacencyIfExists( village_fence10_tga, AdjacencyType.BOTTOM, village_fence1_tga, 0, 56 )
addAdjacencyIfExists( village_fence10_tga, AdjacencyType.BOTTOM, village_fence3_tga, 0, 41 )

-- cliffs
local cliffsTopLeftCorner = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsTopLeftCorner, cliffs_cliff9_tga );

local cliffsTopCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsTopCentre, cliffs_cliff10_tga );

local cliffsTopRightCorner = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsTopRightCorner, cliffs_cliff12_tga );

local cliffsRightBeforeTopCorner = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsRightBeforeTopCorner, cliffs_cliff6_tga );

local cliffsRightCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsRightCentre, cliffs_cliff5_tga );

local cliffsBottomRightCorner = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsBottomRightCorner, cliffs_cliff3_tga );

local cliffsBottomCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsBottomCentre, cliffs_cliff2_tga );
addTileToEquivalenceClassIfExists( cliffsBottomCentre, cliffs_cliff4_tga, 0, 1 );

local cliffsBottomLeftCorner = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsBottomLeftCorner, cliffs_cliff1_tga );

local cliffsLeftCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsLeftCentre, cliffs_cliff7_tga );
addTileToEquivalenceClassIfExists( cliffsLeftCentre, cliffs_cliff8_tga );

local cliffsCentre = tileSet:createAdjacencyEquivalenceClass();
addTileToEquivalenceClassIfExists( cliffsCentre, cliffs_cliff13_tga );
addTileToEquivalenceClassIfExists( cliffsCentre, cliffs_cliff14_tga );
addTileToEquivalenceClassIfExists( cliffsCentre, cliffs_cliff15_tga );
addTileToEquivalenceClassIfExists( cliffsCentre, cliffs_cliff16_tga );
addTileToEquivalenceClassIfExists( cliffsCentre, cliffs_cliff17_tga );

-- cliffs adjacency information
tileSet:addEquivalenceAdjacency( cliffsTopCentre, AdjacencyType.RIGHT, cliffsTopCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsTopCentre, AdjacencyType.RIGHT, cliffsTopRightCorner, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsTopLeftCorner, AdjacencyType.RIGHT, cliffsTopCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsTopLeftCorner, AdjacencyType.RIGHT, cliffsTopRightCorner, 0, 0 );

tileSet:addEquivalenceAdjacency( cliffsBottomCentre, AdjacencyType.RIGHT, cliffsBottomCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomCentre, AdjacencyType.RIGHT, cliffsBottomRightCorner, 0, -1 );
tileSet:addEquivalenceAdjacency( cliffsBottomLeftCorner, AdjacencyType.RIGHT, cliffsBottomCentre, 0, -1 );
tileSet:addEquivalenceAdjacency( cliffsBottomLeftCorner, AdjacencyType.RIGHT, cliffsBottomRightCorner, 0, 0 );

tileSet:addEquivalenceAdjacency( cliffsCentre, AdjacencyType.RIGHT, cliffsCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsCentre, AdjacencyType.RIGHT, cliffsRightCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsCentre, AdjacencyType.RIGHT, cliffsRightBeforeTopCorner, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsLeftCentre, AdjacencyType.RIGHT, cliffsCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsLeftCentre, AdjacencyType.RIGHT, cliffsRightCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsLeftCentre, AdjacencyType.RIGHT, cliffsRightBeforeTopCorner, 0, 0 );

tileSet:addEquivalenceAdjacency( cliffsRightCentre, AdjacencyType.TOP, cliffsRightCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsRightCentre, AdjacencyType.TOP, cliffsRightBeforeTopCorner, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsRightBeforeTopCorner, AdjacencyType.TOP, cliffsTopRightCorner, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomRightCorner, AdjacencyType.TOP, cliffsRightCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomRightCorner, AdjacencyType.TOP, cliffsRightBeforeTopCorner, 0, 0 );

tileSet:addEquivalenceAdjacency( cliffsLeftCentre, AdjacencyType.TOP, cliffsLeftCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsLeftCentre, AdjacencyType.TOP, cliffsTopLeftCorner, 8, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomLeftCorner, AdjacencyType.TOP, cliffsLeftCentre, 8, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomLeftCorner, AdjacencyType.TOP, cliffsTopLeftCorner, 16, 0 );

tileSet:addEquivalenceAdjacency( cliffsCentre, AdjacencyType.TOP, cliffsCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsCentre, AdjacencyType.TOP, cliffsTopCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomCentre, AdjacencyType.TOP, cliffsCentre, 0, 0 );
tileSet:addEquivalenceAdjacency( cliffsBottomCentre, AdjacencyType.TOP, cliffsTopCentre, 0, 0 );

tileSet:printTileSet();

