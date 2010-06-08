-- init quest namespace so different quests / zones don't conflict in names
if ( quest_hexmaster == nil )
then
	quest_hexmaster = {}
end

function quest_hexmaster.init()
	-- this quest is initialized from zone zone1
	quest_hexmaster.questStartRegion = DawnInterface.addInteractionRegion();
	quest_hexmaster.questStartRegion:setPosition( 730, 2340, 400, 270 );
	quest_hexmaster.questStartRegion:setOnEnterText( "quest_hexmaster.questGiverInteraction()" );
end

function quest_hexmaster.questGiverInteraction()
	if ( not quest_hexmaster.questGiven )
	then
		quest_hexmaster.showStartText( 1 )
	end
	if ( quest_hexmaster.doorTextRead and not quest_hexmaster.toldWholeStory )
	then
		quest_hexmaster.showStartText( 3 )
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

function quest_hexmaster.onDiscoveredHiddenDoor()
	if ( quest_hexmaster.questGiven and not quest_hexmaster.doorTextRead )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setAutocloseTime( 0 );
		textWindow:setText("At the end of the corridor you see a closed door. When you go close to it you notice a torn piece of novice robe is caught in the door. You try to open the door, but it is locked and won't open. Maybe the strange glowing runes drawn around the frame have something to do with it.");
		DawnInterface.changeQuestDescription("The Hexmaster", "Tell Ornad Saidor in Arinox that you have found a locked door and within the piece of a robe.");
		quest_hexmaster.doorTextRead = true;
	end
end

-- init quest if this has not been done yet
if ( quest_hexmaster.inited == nil )
then
	quest_hexmaster.inited = true;
	quest_hexmaster.init();
end


