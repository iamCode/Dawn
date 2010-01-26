
if ( quest_playHideAndSeek == nil or not quest_playHideAndSeek.fulfilled )
then
	john = DawnInterface.addInteractionPoint();
	john:setPosition( 820, 270, 25, 33 );
	john:setBackgroundTexture( "data/character/link/link1.tga" );
	john:setInteractionTexture( "data/interaction/talk.tga" );
	john:setInteractionCode( "onActivateJohn()" );
end

function onActivateJohn()
	if ( quest_playHideAndSeek == nil or not quest_playHideAndSeek.fulfilled )
	then
		if ( quest_playHideAndSeek == nil )
		then
			quest_playHideAndSeek = {}
			quest_playHideAndSeek.fulfilled = false;
			quest_playHideAndSeek.rewardGot = false;
			quest_playHideAndSeek.monsterSpawnPoint = DawnInterface.addMobSpawnPoint( "Giant Wolf", 1750, 650, 1, 0, zone );
			onDieEventHandler = DawnInterface.createEventHandler();
			onDieEventHandler:setExecuteText( "onKilledQuestMonster()" );
			quest_playHideAndSeek.monsterSpawnPoint:addOnDieEventHandler( onDieEventHandler );
			DawnInterface.addQuest("hide and seek", "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
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
		DawnInterface.removeQuest("hide and seek");
	end
end

function onKilledQuestMonster()
	james = DawnInterface.addInteractionPoint();
	james:setPosition( 1950, 700, 20, 26 );
	james:setBackgroundTexture( "data/character/link/link1.tga" );
	james:setInteractionTexture( "data/interaction/talk.tga" );
	james:setInteractionCode( "onActivateJames()" );
	DawnInterface.removeMobSpawnPoint( quest_playHideAndSeek.monsterSpawnPoint );
end

function onActivateJames()
	if ( quest_playHideAndSeek == nil or quest_playHideAndSeek.fulfilled )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "This forest is so exciting." );
		textWindow:setAutocloseTime( 2000 );
	elseif ( not quest_playHideAndSeek.fulfilled )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Thank you for helping me. I walked through this wonderful forest when suddenly I saw this huge wolf. Then I hid in the trees and hoped it would get away, but it didn't. I was so afraid. I'll better hurry to my brother John now." );
		textWindow:setAutocloseTime( 10000 );
		james:setPosition( 800, 200, 20, 26 );
		quest_playHideAndSeek.fulfilled = true;
		DawnInterface.changeQuestDescription("hide and seek", "Found James whose way was blocked by a huge wolf. He is on his way back to John now.");
	end
end


