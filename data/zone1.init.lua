if ( zone1 == nil )
then
	zone1 = {};
	dofile("data/zone1.spawnpoints.lua");
	zone1.leavePoint = DawnInterface.addInteractionPoint();
	zone1.leavePoint:setPosition( 822, 2570, 128, 128 );
	zone1.leavePoint:setBackgroundTexture( "data/village/stairs.tga" );
	zone1.leavePoint:setInteractionType( InteractionType.Zone );
	zone1.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/arinoxDungeonLevel1", 2020, 1880 );\nDawnInterface.setSavingAllowed( false );' );

	zone1.leavePoint = DawnInterface.addInteractionPoint();
	zone1.leavePoint:setPosition( 428, 2060, 56, 80 );
	zone1.leavePoint:setInteractionType( InteractionType.Zone );
	zone1.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	zone1.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/arinoxMagesGuild", -158, 0 );\nDawnInterface.setSavingAllowed( true );' );

	zone1.leavePoint = DawnInterface.addInteractionPoint();
	zone1.leavePoint:setPosition( 747, 1588, 56, 80 );
	zone1.leavePoint:setInteractionType( InteractionType.Zone );
	zone1.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	zone1.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/arinoxGeneralShop", -158, 0 );\nDawnInterface.setSavingAllowed( true );' );
end

function zone1.onEnterMap(x,y)
    DawnInterface.setBackgroundMusic("data/music/Early_Dawn_Simple.ogg");
end

dofile("data/quests_hexmaster.lua");

