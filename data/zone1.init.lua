if ( zone1 == nil )
then
	zone1 = {};
	dofile("data/zone1.spawnpoints.lua");
	zone1.leavePoint = DawnInterface.addInteractionPoint();
	zone1.leavePoint:setPosition( 822, 2570, 128, 128 );
	zone1.leavePoint:setBackgroundTexture( "data/village/stairs.tga" );
	zone1.leavePoint:setInteractionType( InteractionType.Zone );
	zone1.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/arinoxDungeonLevel1", 2020, 1880 );\nDawnInterface.setSavingAllowed( false );' );
end

function zone1.onEnterMap(x,y)
    DawnInterface.setBackgroundMusic("data/music/Early_Dawn_Simple.ogg");
end

dofile("data/quests_hexmaster.lua");

