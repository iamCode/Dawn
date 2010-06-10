-- init quest namespace so different quests / zones don't conflict in names
if ( quest_hexmaster == nil )
then
	quest_hexmaster = {}
end

function quest_hexmaster.init()
	-- this quest is initialized from zone zone1
	quest_hexmaster.questStartRegion = DawnInterface.addInteractionRegion();
	quest_hexmaster.questStartRegion:setPosition( 730, 2300, 400, 310 );
	quest_hexmaster.questStartRegion:setOnEnterText( "quest_hexmaster.onQuestGiverRegionInteraction()" );

	quest_hexmaster.ornadSaidor = DawnInterface.addMobSpawnPoint( "Human", 900, 2450, 1, 0 );
        quest_hexmaster.ornadSaidor:setAttitude( Attitude.FRIENDLY );
        quest_hexmaster.ornadSaidor:setName( "Rake Fleetwood" );
        quest_hexmaster.ornadSaidorInteraction = DawnInterface.addCharacterInteractionPoint( quest_hexmaster.ornadSaidor );
        quest_hexmaster.ornadSaidorInteraction:setInteractionType( InteractionType.Quest );
        quest_hexmaster.ornadSaidorInteraction:setInteractionCode( "quest_hexmaster.onOrnadSaidorInteraction()" );

	quest_hexmaster.noviceLeader = DawnInterface.addMobSpawnPoint( "Wizard", 0, 2100, 1, 0 );
	quest_hexmaster.noviceLeader:setAttitude( Attitude.FRIENDLY );
	quest_hexmaster.noviceLeader:setName( "Novice Leader" );
        quest_hexmaster.noviceLeaderInteraction = DawnInterface.addCharacterInteractionPoint( quest_hexmaster.noviceLeader );
        quest_hexmaster.noviceLeaderInteraction:setInteractionType( InteractionType.Quest );
        quest_hexmaster.noviceLeaderInteraction:setInteractionCode( "quest_hexmaster.onNoviceLeaderInteraction()" );
	
	quest_hexmaster.noviceLeader = DawnInterface.addMobSpawnPoint( "Wizard", -75, 2200, 1, 0 );
	quest_hexmaster.noviceLeader:setAttitude( Attitude.FRIENDLY );
	quest_hexmaster.noviceLeader:setName( "Novice" );
	quest_hexmaster.noviceLeader = DawnInterface.addMobSpawnPoint( "Wizard", 55, 2200, 1, 0 );
	quest_hexmaster.noviceLeader:setAttitude( Attitude.FRIENDLY );
	quest_hexmaster.noviceLeader:setName( "Novice" );
end

function quest_hexmaster.onQuestGiverRegionInteraction()
	if ( not quest_hexmaster.questGiven )
	then
		quest_hexmaster.showStartText( 1 )
	end
end

function quest_hexmaster.onOrnadSaidorInteraction()
	if ( quest_hexmaster.doorTextRead and not quest_hexmaster.toldWholeStory )
	then
		quest_hexmaster.showStartText( 3 )
	else
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("What are you waiting for. There is work to do. Go on.")
	end
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
		-- DawnInterface.removeInteractionRegion( quest_hexmaster.questStartRegion );
		-- quest_hexmaster.questStartRegion = nil;

		DawnInterface.addQuest(	"The Hexmaster", "Explore the catacombs underneath the town of Arinox and report back any trace of Jorni to Ornad Saidor." );
		quest_hexmaster.questGiven = true;
	end
	if ( part == 3 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("You found a sign of Jorni? So you are willing to work for me?");
		textWindow:setOnCloseText( "quest_hexmaster.showStartText( 4 )" );
	end
	if ( part == 4 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("I am. But I need help if I am to succeed.");
		textWindow:setOnCloseText( "quest_hexmaster.showStartText( 5 )" );
	end
	if ( part == 5 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("I will tell you all I know about what has happened. About a year ago some townspeople started diappearing. One every few month so people were worried, a murderer was in town, but all investigations lead to dead ends. Then last week another one disappeared - the daughter of a wealthy trader in town. He hired me to find the murderer and bring him to justice. The night before yesterday her body ran around town - horribly twisted and without a head, but still walking. The townspeople were enraged and some openly talked of tearing down the mages guild when the guildmaster stopped them and said internal inspections had found the responsible. The novice Jorni who came to the guild a few weeks before the first murder. All evidence was against him since some personal items of the daughter were found in his rooms and he even came from a town in the far north that is very close to a former stronghold of the hexmasters of old before they where extinguished by the holy church in the cleaning crusade.")
		textWindow:setOnCloseText( "quest_hexmaster.showStartText( 6 )" );
	end
	if ( part == 6 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("The townspeople wanted to execute him right away, but this is a lawful town and he was imprisoned to be judged in the morning. During night some townspeople wanted to kill him in prison but somehow he escaped in the tumult and ran to the dungeons beneath the city. Even though that seems to confirm his guilt he must have his labratories there so no one dared to enter the dungeons, yet. The mages guild is probably willing to help, but they say they need to wait for a high protector from the church to shield them during the operation. My master doesn't want to wait that long and I for myself find the quick investigations of the guild somewhat suspicious. However, to continue into the dungeons you will probably need the help of some mages since what you describe sounds very much like a magical lock. Since Jorni seems to have been an outsider in the guild it shouldn't be hard to find someone among them who will help you break the lock.");
		quest_hexmaster.toldWholeStory = true
		DawnInterface.changeQuestDescription("The Hexmaster", "Ornad Saidor thinks you need magical help from the mages guild to open the dungeon door and continue to search for Jorni");
	end
end

function quest_hexmaster.onNoviceLeaderInteraction()
	if ( quest_hexmaster.toldWholeStory and not quest_hexmaster.novicesOfferedHelp )
	then
		quest_hexmaster.showNoviceText( 1 )
	else
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("We are novices of the mages guild, always seeking for knowledge. Don't disturb our learning, please.")
	end
end

function quest_hexmaster.showNoviceText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		-- TODO: center on player
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("I have been commisioned to find the novice Jorni who seems to have hidden in the catacombs behind a magically locked door. Will you help me break the lock so I can further investigate his actions?");
		textWindow:setOnCloseText( "quest_hexmaster.showNoviceText( 2 )" );
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Whatever you might have heard, I can't believe he is a hexmaster. The daughter and Jorni were in love with each other. That's why he had personal items of her. I understand that the guild leaders were pressed to name someone given the hatred of the townspeople, but it was wrong. Jorni was distant the last weeks and even told us - his only friends - just that he had a very bad suspicion and was looking for proof. I can't believe he is a hexmaster, but that he is a victim. We will help you to open the lock, but can't do more since we have orders from the guild leaders to stay away from the catacombs so even that little help might have dire consequences for us. Show us the door and we will break it.")
		quest_hexmaster.novicesOfferedHelp = true
		DawnInterface.changeQuestDescription("The Hexmaster", "Lead the novice mages to the locked dungeon door so they can try to spell it open")
	end
end

function quest_hexmaster.magicDoorInteraction()
	if ( quest_hexmaster.questGiven and not quest_hexmaster.doorTextRead )
	then
		quest_hexmaster.showMagicDoorText( 1 )
	end
	if ( quest_hexmaster.novicesOfferedHelp and not quest_hexmaster.magicDoorOpened )
	then
		quest_hexmaster.showMagicDoorText( 2 )	
	end
end

function quest_hexmaster.showMagicDoorText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("At the end of the corridor you see a closed door. When you go close to it you notice a torn piece of novice robe is caught in the door. You try to open the door, but it is locked and won't open. Maybe the strange glowing runes drawn around the frame have something to do with it.");
		DawnInterface.changeQuestDescription("The Hexmaster", "Tell Ornad Saidor in Arinox that you have found a locked door and within the piece of a robe.");
		quest_hexmaster.doorTextRead = true;
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Please take a step back and don't disturb our concentration or this might easily become dangerous")
		textWindow:setOnCloseText( "quest_hexmaster.showMagicDoorText( 3 )" );
	end
	if ( part == 3 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("The three mages step in front of the door. They form a pointed triangle which looks as if it is aimed at the door. Then they start gesticulating and murmuring words in a foreign and probably very old language. A few moments later sweat starts running from their heads and they look rather exhausted. You believe something is wrong, but dare not interfere with their magics. Some moments later you almost expect the three of them to drop to the ground dead")
		textWindow:setOnCloseText( "quest_hexmaster.showMagicDoorText( 4 )" );
	end
	if ( part == 4 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Then you hear a sound like a sigh out of a grave that sends a shiver through your body. Then the runes around the door fade and a feeling of immense evil passes you on its way out of the dungeon. You know instantly this was no normal magic lock. The mages look dead tired, but gather the strength to leave. On their way out their leader turns and says.")
		textWindow:setOnCloseText( "quest_hexmaster.showMagicDoorText( 5 )" );
	end
	if ( part == 5 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("This door is open now. But be careful when you enter this room. We underestimated that lock. The magic that was worked there was unknown to us, but very powerful. It felt dead and evil and nearly killed us. Now I really believe some hexmaster has come to terrorize our town. Good luck to you")
		quest_hexmaster.magicDoorOpened = true

		DawnInterface.changeQuestDescription("The Hexmaster", "Explore the depth of the Arinox dungeon and find Jorni.");
	end
end

function quest_hexmaster.nextRegionInteraction()
	if ( quest_hexmaster.magicDoorOpened )
	then
		DawnInterface.enterZone( "data/zone2", -670, 1529 );
	else
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("This door is surrounded by several magic runes. You can not get it open.")
	end
end

-- init quest if this has not been done yet
if ( quest_hexmaster.inited == nil )
then
	quest_hexmaster.inited = true;
	quest_hexmaster.init();
end


