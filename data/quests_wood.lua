
if ( quest_playHideAndSeek == nil or not quest_playHideAndSeek.fulfilled )
then
	john = DawnInterface.addInteractionPoint();
	john:setPosition( 820, 270, 25, 33 );
	john:setBackgroundTexture( "data/character/link/link1.tga" );
	john:setInteractionTexture( "data/interaction/talk.tga" );
	john:setInteractionCode( "onActivateJohn()" );

	james = DawnInterface.addInteractionPoint();
	james:setPosition( 1950, 700, 20, 26 );
	james:setBackgroundTexture( "data/character/link/link1.tga" );
	james:setInteractionTexture( "data/interaction/talk.tga" );
	james:setInteractionCode( "onActivateJames()" );
end

function onActivateJohn()
	if ( quest_playHideAndSeek == nil or not quest_playHideAndSeek.fulfilled )
	then
		if ( quest_playHideAndSeek == nil )
		then
			quest_playHideAndSeek = {}
			quest_playHideAndSeek.fulfilled = false;
			quest_playHideAndSeek.rewardGot = false;
		end
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
		textWindow:setAutocloseTime( 3000 );
	elseif ( quest_playHideAndSeek.fulfilled and not quest_playHideAndSeek.rewardGot )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Thank you for looking after my brother. We will leave for home now. Take this ring for your effords." );
		textWindow:setAutocloseTime( 5000 );
		DawnInterface.giveItemToPlayer( itemDatabase["ringofdefense"] );
		quest_playHideAndSeek.rewardGot = true;
		DawnInterface.removeInteractionPoint( john );
		DawnInterface.removeInteractionPoint( james );
	end
end

function onActivateJames()
	if ( quest_playHideAndSeek == nil or quest_playHideAndSeek.fulfilled )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "This forest is so exciting." );
		textWindow:setAutocloseTime( 3000 );
	elseif ( not quest_playHideAndSeek.fulfilled )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "My brother James is always so worried about me. But I will better leave before he gets angry." );
		textWindow:setAutocloseTime( 3000 );
		james:setPosition( 800, 200, 20, 26 );
		quest_playHideAndSeek.fulfilled = true;
	end
end


