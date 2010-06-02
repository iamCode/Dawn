-- init quest namespace so different quests / zones don't conflict in names
if ( quest_hexmaster == nil )
then
	quest_hexmaster = {}
end

function quest_hexmaster.init()
	-- this quest is initialized from zone zone1
	quest_hexmaster.questStartRegion = DawnInterface.addInteractionRegion();
	quest_hexmaster.questStartRegion:setPosition( 730, 2340, 400, 270 );
	quest_hexmaster.questStartRegion:setOnEnterText( "quest_hexmaster.showStartText( 1 )" );
end

function quest_hexmaster.showStartText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Hello traveller. My name is Ornad Saidor. Hear my tale, please.")
		textWindow:setOnCloseText( "quest_hexmaster.showStartText( 2 )" );
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Two weeks ago Jorni, a wizard student here in Arinox, fled town because of the accusations against him. They say he was conducting horrible experiments on living beings - as the ancient Hexmasters were doing. I don't know if what they say is true, but I heard the magistrate is looking to question him. Late last night I think I saw Jorni on the streets, entering the catacombs in the northern part of the town. I know someone who will pay a good price to find out the location of Jorni. Would you be interested in helping me?");
		DawnInterface.removeInteractionRegion( quest_hexmaster.questStartRegion );
		quest_hexmaster.questStartRegion = nil;
	end
end

-- init quest if this has not been done yet
if ( quest_hexmaster.inited == nil )
then
	quest_hexmaster.inited = true;
	quest_hexmaster.init();
end


