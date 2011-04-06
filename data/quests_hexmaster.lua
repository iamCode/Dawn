-- init quest namespace so different quests / zones don't conflict in names
if ( quest_hexmaster == nil )
then
	quest_hexmaster = {}
end

function quest_hexmaster.init()
	-- this quest is initialized from zone zone1
	quest_hexmaster.questStartRegion = DawnInterface.addInteractionRegion();
	quest_hexmaster.questStartRegion:setPosition( 730, 2250, 400, 310 );
	quest_hexmaster.questStartRegion:setOnEnterText( "quest_hexmaster.onQuestGiverRegionInteraction()" );

	quest_hexmaster.ornadSaidor = DawnInterface.addMobSpawnPoint( "Human", 900, 2350, 1, 0 );
        quest_hexmaster.ornadSaidor:setAttitude( Attitude.FRIENDLY );
        quest_hexmaster.ornadSaidor:setWanderRadius(50);
        quest_hexmaster.ornadSaidor:setName( "Ornad Saidor" );
        quest_hexmaster.ornadSaidorInteraction = DawnInterface.addCharacterInteractionPoint( quest_hexmaster.ornadSaidor );
        quest_hexmaster.ornadSaidorInteraction:setInteractionType( InteractionType.Quest );
        quest_hexmaster.ornadSaidorInteraction:setInteractionCode( "quest_hexmaster.onOrnadSaidorInteraction()" );

	quest_hexmaster.noviceLeader = DawnInterface.addMobSpawnPoint( "Wizard", 0, 2100, 1, 0 );
	quest_hexmaster.noviceLeader:setAttitude( Attitude.FRIENDLY );
	quest_hexmaster.noviceLeader:setName( "Novice Leader" );
        quest_hexmaster.noviceLeaderInteraction = DawnInterface.addCharacterInteractionPoint( quest_hexmaster.noviceLeader );
        quest_hexmaster.noviceLeaderInteraction:setInteractionType( InteractionType.Quest );
        quest_hexmaster.noviceLeaderInteraction:setInteractionCode( "quest_hexmaster.onNoviceLeaderInteraction()" );
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
	elseif ( quest_hexmaster.metJorni )
	then
		quest_hexmaster.showStartText( 7 )
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

		quest_hexmaster.quest = DawnInterface.addQuest(	"The Hexmaster", "Explore the catacombs underneath the town of Arinox and report back any trace of Jorni to Ornad Saidor." );
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
		DawnInterface.changeQuestDescription( quest_hexmaster.quest, "Ornad Saidor thinks you need magical help from the mages guild to open the dungeon door and continue to search for Jorni");
	end
	if ( part == 7 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("So is was Xaralax, not Jorni? I thought something was strange. Give me time to think about this.");
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
		DawnInterface.changeQuestDescription( quest_hexmaster.quest, "Lead the novice mages to the locked dungeon door so they can try to spell it open")
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
		DawnInterface.changeQuestDescription( quest_hexmaster.quest, "Tell Ornad Saidor in Arinox that you have found a locked door and within the piece of a robe.");
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

		DawnInterface.changeQuestDescription( quest_hexmaster.quest, "Explore the depth of the Arinox dungeon and find Jorni.");
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

function quest_hexmaster.onEnteredUndergroundRegion()
	if ( not quest_hexmaster.showedUndergroundText )
	then
		quest_hexmaster.showedUndergroundText = true;
		quest_hexmaster.showEnterRoomText( 1 );
	end
end

function quest_hexmaster.onLeaveLaboratory()
	if ( not quest_hexmaster.killedSkeleton )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 2000 );
		textWindow:setText("The door has been magically sealed again. Perhaps the door will open if you destroy the magic animating the skeleton.")
	else
		DawnInterface.enterZone( "data/arinoxDungeonLevel1", 1020, 420 );
	end
end

function quest_hexmaster.showEnterRoomText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("You enter what looks like a mixture of torture chamber and temple. There are blood and bones everywhere and bracelets invest the walls. On the far end of the room a large altar surrounded by candles stands in contrast to the rest of the room. A contrast only on first look since you quickly notice blood and even a dried human head on it. Some sketches of a somewhat human body but with much too much muscle mass and an additional pair of arms is sketched on a strange kind of leather. You seem to have found the laboratory of the hexmaster. Luckily, the master doesn't seem to be at home. While your gaze wanders around the room you notice a small door on the western side of the room. Further your gaze is caught by something glittering below the bones to the right. You take a step closer...");
		textWindow:setOnCloseText( "quest_hexmaster.showEnterRoomText( 2 )" );
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Suddenly a cold breeze touches your shoulder. You hear a shallow laughter and it takes a blink to notice it is not in your ears, but in the back of your head. The ground seems to be moving before your eyes and it is when you lean against the wall for hold that you see it was no imagination at all. The bones are moving and form into a body again. You turn to flee, but it is too late. The door snaps shut behind you and you know instantly that it will not open to your touch. Slowly your nightmare continues as a full grown human skeleton rises before you with a battered but powerful blade in its bony fingers. The laughter in your head rises to a crescendo then suddendly moves away to come back from the mouth of the bony reaver as it moves towards you with obviously malicious intend.");
		textWindow:setOnCloseText( "quest_hexmaster.showEnterRoomText( 3 )" );
	end
	if ( part == 3 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("In a moment of utter horror it occurs to you that your existence might not end if you die here. Next time it could be your body rising to meet an unwelcome intruder. Trapped and lost with your back against the wall you take control of your actions again. You concentrate on the enemy willing to set as high a price as possible on your soul...");
		textWindow:setOnCloseText( "quest_hexmaster.showEnterRoomText( 4 )" );
	end
	if ( part == 4 )
	then
		quest_hexmaster.skeleton = DawnInterface.addMobSpawnPoint( "Skeleton", -1145, 1321, 180, 0 )
        	quest_hexmaster.skeleton:setAttitude( Attitude.HOSTILE )
		local onDieEventHandler = DawnInterface.createEventHandler();
		onDieEventHandler:setExecuteText( "quest_hexmaster.showEnterRoomText( 5 )" );
		quest_hexmaster.skeleton:addOnDieEventHandler( onDieEventHandler );
	end
	if ( part == 5 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("When you crush its head the skeleton falls appart, now again a liveless heap of bones. With a shrill sound the black unlife behind the eye sockets vanishes and the head turns to dust. In the dust you see again the glittering from before. Clearly now before your eyes lies a perfectly circular silver plate and your gaze falls to the door on the western wall again. It might be worth a try...")
		DawnInterface.removeMobSpawnPoint( quest_hexmaster.skeleton );
		quest_hexmaster.skeleton = nil
		quest_hexmaster.killedSkeleton = true
	end
end

function quest_hexmaster.onEnterHiddenChamber()
	if ( not quest_hexmaster.killedSkeleton )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 2000 );
		textWindow:setText("The door has no handle, but only a perfectly circular depression is in the middle. Better turn to the fight than waste your time here.");
	end
	if ( quest_hexmaster.killedSkeleton and not quest_hexmaster.metJorni )
	then
		quest_hexmaster.showJorniText( 1 )
	end
	if ( quest_hexmaster.metJorni )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 2000 );
		textWindow:setText("This door is closed forever now. May Jorni find peace in the afterworld.");
	end
end

function quest_hexmaster.showJorniText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("You take the silver plate and put it into the depression. First nothing happens, but then the massive stone door opens...")
		textWindow:setOnCloseText( "quest_hexmaster.showJorniText( 2 )" );
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("On the ground of the room you see a figure in torn and bloody novice robes. His breath goes irregular and sounds strange and it is obvious to you that he is beyond any help. Then you see his eyes focussing on you and his lips start moving. You step closer to hear his wisper.")
		textWindow:setOnCloseText( "quest_hexmaster.showJorniText( 3 )" );
	end
	if ( part == 3 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("Stranger... please listen, I don't have much time left... ugh... I am Jorni, accused of performing... ugh... dark magic. I know I will not live long. I came here to... ugh... to gather proof of my innocence... ugh... The master of novices... ugh... Xaralax... ugh... is the hexmaster. I fear he will have left town by now... ugh... fearing discovery. I was trapped here by the door outside... ugh... when I found the Xaralax diary in a hidden cache on the... ugh... altar.")
		textWindow:setOnCloseText( "quest_hexmaster.showJorniText( 4 )" );
	end
	if ( part == 4 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("It will prove my innocence... ugh... little good it will do me... ugh... please take it to the High Mage so the evil Xaralax... ugh... can be brought to justice... I came here... ugh... deadly wounded by the guardian... ugh... This is some kind of prison... ugh... Go now... quickly... The door is... ugh... closing again and... ugh... with the guardian finished... ugh... the door will soon close forever...")
		textWindow:setOnCloseText( "quest_hexmaster.showJorniText( 5 )" );
	end
	if ( part == 5 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("And... ugh... Thank... ugh... you for.. ugh... saving my... ugh... soul...")
		textWindow:setOnCloseText( "quest_hexmaster.showJorniText( 6 )" );
	end
	if ( part == 6 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("With this the light leaves Jornis eyes. You quickly take the diary and leave the prison which soon closes again to finally become a young mans tomb. Rest well, Jorni. You turn to leave the dungeon again, your initial suspicions about conveniently quickly found suspects having turned out right. You silently promise to wash Jornis name clear and bring down the evil hexmaster. Then you turn to go.");
		quest_hexmaster.metJorni=true
	end
end


-- init quest if this has not been done yet
if ( quest_hexmaster.inited == nil )
then
	quest_hexmaster.inited = true;
	quest_hexmaster.init();
end


