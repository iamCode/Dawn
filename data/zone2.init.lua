if ( zone2 == nil )
then
	zone2 = {};
	dofile("data/zone2.spawnpoints.lua");
	zone2.leavePoint = DawnInterface.addInteractionPoint();
	zone2.leavePoint:setPosition( -670, 1568, 48, 70 );
	zone2.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	zone2.leavePoint:setInteractionType( InteractionType.Zone );
	zone2.leavePoint:setInteractionCode( 'zone2.normalLeavePoint()' );

	zone2.enterRegion = DawnInterface.addInteractionRegion();
	zone2.enterRegion:setPosition( -800, 1400, 300, 300 );
	zone2.enterRegion:setOnEnterText( "zone2.onEnterRegion()" );

	zone2.lockedDoor = DawnInterface.addInteractionPoint();
	zone2.lockedDoor:setPosition( -1400, 1250, 60, 100 );
	zone2.lockedDoor:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	zone2.lockedDoor:setInteractionType( InteractionType.Zone );
	zone2.lockedDoor:setInteractionCode( 'zone2.lockedDoorInteraction()' )
end

function zone2.onEnterRegion()
	if ( quest_hexmaster )
	then
		quest_hexmaster.onEnteredUndergroundRegion()
	end
end

function zone2.normalLeavePoint()
	if ( quest_hexmaster )
	then
		quest_hexmaster.onLeaveLaboratory();
	end
end

function zone2.lockedDoorInteraction()
	if ( quest_hexmaster )
	then
		quest_hexmaster.onEnterHiddenChamber();
	end
end

