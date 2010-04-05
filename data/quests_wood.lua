function init()
	trader = DawnInterface.addMobSpawnPoint( "Human", 600, 150, 1, 0 );
	trader:setAttitude( Attitude.FRIENDLY );
	traderInteraction = DawnInterface.addCharacterInteractionPoint( trader );
	traderInteraction:setInteractionTexture( "data/interaction/talk.tga" );
	traderInteraction:setInteractionCode( "onActivateTrader()" );
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

	if ( quest_playHideAndSeek == nil )
	then
		quest_playHideAndSeek = {}
		quest_playHideAndSeek.fulfilled = false
		quest_playHideAndSeek.status = 0
	end

	initializeQuestStatus( quest_playHideAndSeek.status );
end

function onActivateTrader()
	traderShop:setVisible( true )
end

function initializeJohnStatus()
	print( "initializeJohnStatus with status " .. quest_playHideAndSeek.status );

	if ( quest_playHideAndSeek.status == 4 and john ~= nil )
	then
		print("if part")
		DawnInterface.removeInteractionPoint( john );
		john = nil
	elseif ( quest_playHideAndSeek.status ~= 4 )
	then
		print( "elseif part");
		if ( john == nil )
		then
			print("john was nil");
			john = DawnInterface.addInteractionPoint();
			john:setPosition( 820, 270, 25, 33 );
			john:setBackgroundTexture( "data/character/link/link1.tga" );
			john:setInteractionTexture( "data/interaction/talk.tga" );
		end
		john:setInteractionCode( "onActivateJohn()" );
	else
		print("else part")
	end
end

function initializeWolfStatus()
	if ( quest_playHideAndSeek.monsterSpawnPoint == nil and quest_playHideAndSeek.status == 1 )
	then
		quest_playHideAndSeek.monsterSpawnPoint = DawnInterface.addMobSpawnPoint( "Giant Wolf", 1750, 650, 1, 0 );
		onDieEventHandler = DawnInterface.createEventHandler();
		onDieEventHandler:setExecuteText( "onKilledQuestMonster()" );
		quest_playHideAndSeek.monsterSpawnPoint:addOnDieEventHandler( onDieEventHandler );
	elseif ( quest_playHideAndSeek.monsterSpawnPoint ~= nil and quest_playHideAndSeek.status == 2 )
	then
		DawnInterface.removeMobSpawnPoint( quest_playHideAndSeek.monsterSpawnPoint );
		quest_playHideAndSeek.monsterSpawnPoint = nil;
	end
end

function initializeJamesStatus()
	if ( quest_playHideAndSeek.status == 4 and james ~= nil )
	then
		DawnInterface.removeInteractionPoint( james );
		james = nil
	elseif ( quest_playHideAndSeek.status == 2 )
	then
		james = DawnInterface.addInteractionPoint();
		james:setPosition( 1950, 650, 20, 26 );
		james:setBackgroundTexture( "data/character/link/link1.tga" );
		james:setInteractionTexture( "data/interaction/talk.tga" );
		james:setInteractionCode( "onActivateJames()" );
	elseif ( quest_playHideAndSeek.status == 3 )
	then
		if ( james == nil )
		then
			james = DawnInterface.addInteractionPoint();
			james:setPosition( 800, 200, 20, 26 );
			james:setBackgroundTexture( "data/character/link/link1.tga" );
			james:setInteractionTexture( "data/interaction/talk.tga" );
			james:setInteractionCode( "onActivateJames()" );
		else
			james:setPosition( 800, 200, 20, 26 );
			james:setInteractionCode( "onActivateJames()" );
		end
	end
end

-- possible quest_playHideAndSeek.status:
-- 0: Initial. Quest not aquired. Character John available
-- 1: Quest aquired. John repeats request. Giant wolf available
-- 2: Giant wolf slain. Character James available
-- 3: Talked to James. Character James near character John. James will give reward. John will just say something
-- 4: Final: Quest fulfilled
function initializeQuestStatus( status )
	quest_playHideAndSeek.status = status;
	if ( quest_playHideAndSeek.status == 0 )
	then
		-- 0: Initial. Quest not aquired. Character John available
		initializeJohnStatus();
	end
	if ( quest_playHideAndSeek.status == 1 )
	then
		initializeJohnStatus();
		initializeWolfStatus();
	end
	if ( quest_playHideAndSeek.status == 2 )
	then
		initializeJohnStatus();
		initializeJamesStatus();
		initializeWolfStatus();
	end
	if ( quest_playHideAndSeek.status == 3 )
	then
		initializeJohnStatus();
		initializeJamesStatus();
	end
	if ( quest_playHideAndSeek.status == 4 )
	then
		quest_playHideAndSeek.fulfilled = true;
		initializeJohnStatus();
		initializeJamesStatus();
	end 
end

function onActivateJohn()
	if ( quest_playHideAndSeek.status == 0 )
	then
		initializeQuestStatus( 1 );
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
		textWindow:setAutocloseTime( 3000 );

		DawnInterface.addQuest("hide and seek", "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
	elseif ( quest_playHideAndSeek.status == 1 )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
		textWindow:setAutocloseTime( 3000 );
	elseif ( quest_playHideAndSeek.status == 3 )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Thank you for looking after my brother. We will leave for home now. Take this ring for your effords." );
		textWindow:setAutocloseTime( 5000 );
		DawnInterface.giveItemToPlayer( itemDatabase["ringofdefense"] );
		quest_playHideAndSeek.rewardGot = true;
		initializeQuestStatus( 4 );
		DawnInterface.removeInteractionPoint( james );
		DawnInterface.removeQuest("hide and seek");
	end
end

function onActivateJames()
	if ( quest_playHideAndSeek.status == 3 )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "This forest is so exciting." );
		textWindow:setAutocloseTime( 2000 );
	elseif ( quest_playHideAndSeek.status == 2 )
	then
		textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Thank you for helping me. I walked through this wonderful forest when suddenly I saw this huge wolf. Then I hid in the trees and hoped it would get away, but it didn't. I was so afraid. I'll better hurry to my brother John now." );
		textWindow:setAutocloseTime( 10000 );
		james:setPosition( 800, 200, 20, 26 );
		initializeQuestStatus( 3 )
		DawnInterface.changeQuestDescription("hide and seek", "Found James whose way was blocked by a huge wolf. He is on his way back to John now.");
	end
end

function onKilledQuestMonster()
	initializeQuestStatus(2);
end

if ( quest_playHideAndSeek == nil )
then
	init()
end

