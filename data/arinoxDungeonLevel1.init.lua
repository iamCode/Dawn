if ( arinoxDungeonLevel1 == nil )
then
    arinoxDungeonLevel1 = {};
    dofile("data/arinoxDungeonLevel1.spawnpoints.lua");
    arinoxDungeonLevel1.leavePoint = DawnInterface.addInteractionPoint();
    arinoxDungeonLevel1.leavePoint:setPosition( 2007, 1913, 76, 70 );
    arinoxDungeonLevel1.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
    arinoxDungeonLevel1.leavePoint:setInteractionType( InteractionType.Zone );
    arinoxDungeonLevel1.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/zone1", 870, 2520 );\nDawnInterface.setSavingAllowed( true );' );

    arinoxDungeonLevel1.closedDoorSpot = DawnInterface.addInteractionRegion();
    arinoxDungeonLevel1.closedDoorSpot:setPosition( 990, 400, 130, 180 );
    arinoxDungeonLevel1.closedDoorSpot:setOnEnterText( 'arinoxDungeonLevel1.closedDoorInteraction()' );

    arinoxDungeonLevel1.leaveRegionSpot = DawnInterface.addInteractionPoint();
    arinoxDungeonLevel1.leaveRegionSpot:setPosition( 990, 300, 130, 100 );
    arinoxDungeonLevel1.leaveRegionSpot:setBackgroundTexture( "data/transparent2x2pixel.tga" );
    arinoxDungeonLevel1.leaveRegionSpot:setInteractionType( InteractionType.Zone );
    arinoxDungeonLevel1.leaveRegionSpot:setInteractionCode( 'arinoxDungeonLevel1.nextRegionInteraction()' );
end

function arinoxDungeonLevel1.onEnterMap(x,y)
    DawnInterface.setBackgroundMusic("data/music/ratsrats_0.ogg");
end

function arinoxDungeonLevel1.closedDoorInteraction()
	if ( quest_hexmaster )
	then
		quest_hexmaster.magicDoorInteraction()
	end
end

function arinoxDungeonLevel1.nextRegionInteraction()
	if ( quest_hexmaster )
	then
		quest_hexmaster.nextRegionInteraction()
	end
end

