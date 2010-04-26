-- init quest namespace so different quests / zones don't conflict in names
if ( quest_playHideAndSeek == nil )
then
	quest_playHideAndSeek = {}
end


function quest_playHideAndSeek.init()
	trader = DawnInterface.addMobSpawnPoint( "Human", 600, 1400, 1, 0 );
	trader:setAttitude( Attitude.FRIENDLY );
	trader:setName( "Rake Fleetwood" );
	traderInteraction = DawnInterface.addCharacterInteractionPoint( trader );
	traderInteraction:setInteractionType( InteractionType.Shop );
	traderInteraction:setInteractionCode( "quest_playHideAndSeek.onActivateTrader()" );
	traderShop = DawnInterface.addShop();
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["smallhealingpotion"] );
	traderShop:addItem( itemDatabase["bladeofstrength"] );

	john = DawnInterface.addInteractionPoint();
	john:setPosition( 820, 270, 25, 33 );
	john:setBackgroundTexture( "data/character/link/link1.tga" );
	john:setInteractionType( InteractionType.Quest );
	john:setInteractionCode( "quest_playHideAndSeek.onActivateJohn()" );
end

function quest_playHideAndSeek.onActivateTrader()
	traderShop:toggle()
end

function quest_playHideAndSeek.onActivateJohn()
	if ( not quest_playHideAndSeek.fulfilled )
	then
		if ( quest_playHideAndSeek.added == nil )
		then
			quest_playHideAndSeek.added = true;
			quest_playHideAndSeek.fulfilled = false;
			quest_playHideAndSeek.rewardGot = false;
			quest_playHideAndSeek.monsterSpawnPoint = DawnInterface.addMobSpawnPoint( "Giant Wolf", 3462, 557, 1, 0 );
			quest_playHideAndSeek.monsterSpawnPoint:setAttitude ( Attitude.HOSTILE );
			onDieEventHandler = DawnInterface.createEventHandler();
			onDieEventHandler:setExecuteText( "quest_playHideAndSeek.onKilledQuestMonster()" );
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
		john = nil;
		james = nil;
		DawnInterface.removeQuest("hide and seek");
	end
end

function quest_playHideAndSeek.onKilledQuestMonster()
	james = DawnInterface.addInteractionPoint();
	james:setPosition( 3783,640, 20, 26 );
	james:setBackgroundTexture( "data/character/link/link1.tga" );
	james:setInteractionType( InteractionType.Quest );
	james:setInteractionCode( "quest_playHideAndSeek.onActivateJames()" );
	DawnInterface.removeMobSpawnPoint( quest_playHideAndSeek.monsterSpawnPoint );
	quest_playHideAndSeek.monsterSpawnPoint = nil;
end

function quest_playHideAndSeek.onActivateJames()
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

-- init quest if this has not been done yet
if ( quest_playHideAndSeek.inited == nil )
then
	quest_playHideAndSeek.inited = true;
	quest_playHideAndSeek.init();
end


