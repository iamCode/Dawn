-- init quest namespace so different quests / zones don't conflict in names
if( quest_playHideAndSeek == nil )
then
	quest_playHideAndSeek = {}
end

function quest_playHideAndSeek.enterTown()
	if ( not DawnInterface.isSavingAllowed() )
	then
		DawnInterface.setSavingAllowed( true );

		local textWindow = DawnInterface.createTextWindow();
		textWindow:center();
		textWindow:setText( "The town of Arinox." );
		textWindow:setAutocloseTime( 1000 );
	end
end

function quest_playHideAndSeek.leaveTown()
	if ( DawnInterface.isSavingAllowed() )
	then
		DawnInterface.setSavingAllowed( false );
	end
end

function quest_playHideAndSeek.testInteractionRegionLeave()
	local textWindow = DawnInterface.createTextWindow();
	textWindow:setPosition( PositionType.CENTER, 512, 382 );
	textWindow:setText( "Left test region." );
	textWindow:setAutocloseTime( 1000 );
end

function quest_playHideAndSeek.init()
	local townEnterRegion = DawnInterface.addInteractionRegion();
	townEnterRegion:setPosition( 550, 1300, 300, 100 );
	townEnterRegion:setOnEnterText( "quest_playHideAndSeek.enterTown()" );
	local townLeaveRegion = DawnInterface.addInteractionRegion();
	townLeaveRegion:setPosition( 550, 1200, 300, 100 );
	townLeaveRegion:setOnEnterText( "quest_playHideAndSeek.leaveTown()" );

	john = DawnInterface.addInteractionPoint();
	john:setPosition( 820, 270, 64, 64 );
	john:setBackgroundTexture( "data/character/John.tga" );
	john:setInteractionType( InteractionType.Quest );
	john:setInteractionCode( "quest_playHideAndSeek.onActivateJohn()" );
end

function quest_playHideAndSeek.onActivateJohn()
	if( not quest_playHideAndSeek.fulfilled ) then
		if( quest_playHideAndSeek.added == nil ) then
			quest_playHideAndSeek.added = true;
			quest_playHideAndSeek.fulfilled = false;
			quest_playHideAndSeek.rewardGot = false;
			quest_playHideAndSeek.monsterSpawnPoint = DawnInterface.addMobSpawnPoint( "Giant Wolf", 3462, 557, 1, 0 );
			quest_playHideAndSeek.monsterSpawnPoint:setAttitude ( Attitude.HOSTILE );
			onDieEventHandler = DawnInterface.createEventHandler();
			onDieEventHandler:setExecuteText( "quest_playHideAndSeek.onKilledQuestMonster()" );
			quest_playHideAndSeek.monsterSpawnPoint:addOnDieEventHandler( onDieEventHandler );
			quest_playHideAndSeek.quest = DawnInterface.addQuest("Hide and Seek", "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
			quest_playHideAndSeek.quest:setExperienceReward( 150 );
			quest_playHideAndSeek.quest:setCoinReward( 821 );
			quest_playHideAndSeek.quest:setItemReward( itemDatabase["ringofdefense"] );
		end
		local textWindow = DawnInterface.createTextWindow();
		textWindow:center();
		textWindow:setText( "My little brother James is somewhere in this forest. I fear he got lost. Please find him and tell him to come to me." );
		textWindow:setAutocloseTime( 4000 );
	elseif( quest_playHideAndSeek.fulfilled and not quest_playHideAndSeek.rewardGot ) then
		local textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Thank you for looking after my brother. We will leave for home now. Take this ring for your effords." );
		textWindow:setAutocloseTime( 5000 );
		quest_playHideAndSeek.rewardGot = true;
		DawnInterface.removeInteractionPoint( john );
		DawnInterface.removeInteractionPoint( james );
		john = nil;
		james = nil;
		quest_playHideAndSeek.quest:finishQuest();
		quest_playHideAndSeek.quest = nil
	end
end

function quest_playHideAndSeek.onKilledQuestMonster()
	james = DawnInterface.addInteractionPoint();
	james:setPosition( 3783,640, 64, 64 );
	james:setBackgroundTexture( "data/character/James.tga" );
	james:setInteractionType( InteractionType.Quest );
	james:setInteractionCode( "quest_playHideAndSeek.onActivateJames()" );
	DawnInterface.removeMobSpawnPoint( quest_playHideAndSeek.monsterSpawnPoint );
	quest_playHideAndSeek.monsterSpawnPoint = nil;
end

function quest_playHideAndSeek.onActivateJames()
	if( quest_playHideAndSeek == nil or quest_playHideAndSeek.fulfilled ) then
		local textWindow = DawnInterface.createTextWindow();
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "This forest is so exciting." );
		textWindow:setAutocloseTime( 2000 );
	elseif( not quest_playHideAndSeek.fulfilled ) then
		local textWindow = DawnInterface.createTextWindow();
		textWindow:center();
		textWindow:setText( "Thank you for helping me. I walked through this wonderful forest when suddenly I saw this huge wolf. Then I hid in the trees and hoped it would get away, but it didn't. I was so afraid. I'll better hurry to my brother John now." );
		textWindow:setAutocloseTime( 10000 );
		james:setPosition( 800, 200, 64, 64 );
		quest_playHideAndSeek.fulfilled = true;
		quest_playHideAndSeek.quest:setDescription("Found James whose way was blocked by a huge wolf. He is on his way back to John now.");
	end
end

-- init quest if this has not been done yet
if( quest_playHideAndSeek.inited == nil ) then
	quest_playHideAndSeek.inited = true
	quest_playHideAndSeek.init()
end
