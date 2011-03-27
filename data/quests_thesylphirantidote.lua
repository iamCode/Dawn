-- init quest namespace so different quests / zones don't conflict in names
if ( quest_thesylphirantidote == nil )
then
	quest_thesylphirantidote = {}
end

function quest_thesylphirantidote.init()
	-- this quest is initialized from zone zone1
	--quest_thesylphirantidote.effreyLongback = DawnInterface.addMobSpawnPoint( "Human", -1510, 500, 1, 0 );
	--quest_thesylphirantidote.effreyLongback = DawnInterface.addMobSpawnPoint( "Human", 510, 500, 1, 0 );
    --quest_thesylphirantidote.effreyLongback:setAttitude( Attitude.FRIENDLY );
    --quest_thesylphirantidote.effreyLongback:setWanderRadius(50);
    --quest_thesylphirantidote.effreyLongback:setName( "Effrey Longback" );
	--quest_thesylphirantidote.effreyLongbackInteraction = DawnInterface.addCharacterInteractionPoint( quest_thesylphirantidote.effreyLongback );
	--quest_thesylphirantidote.effreyLongbackInteraction:setInteractionType( InteractionType.Quest );
	--quest_thesylphirantidote.effreyLongbackInteraction:setInteractionCode( "quest_thesylphirantidote.speakWithEffrey()" );

	--quest_thesylphirantidote.jemma = DawnInterface.addMobSpawnPoint( "Human", -2162, -4580, 1, 0 );
	--quest_thesylphirantidote.jemma = DawnInterface.addMobSpawnPoint( "Spider", 462, 580, 1, 0 );
	--quest_thesylphirantidote.jemma:setAttitude( Attitude.FRIENDLY );
    --quest_thesylphirantidote.jemma:setWanderRadius(50);
	--quest_thesylphirantidote.jemma:setName( "Jemma" );
	--quest_thesylphirantidote.jemmaInteraction = DawnInterface.addCharacterInteractionPoint( quest_thesylphirantidote.jemma );
	--quest_thesylphirantidote.jemmaInteraction:setInteractionType( InteractionType.Quest );
    --quest_thesylphirantidote.jemmaInteraction:setInteractionCode( "quest_thesylphirantidote.speakWithJemma()" );

	local sylphirwoodsEnter = DawnInterface.addInteractionRegion();
	sylphirwoodsEnter:setPosition( -1215, -1000, 100, 360 );
	sylphirwoodsEnter:setOnEnterText( "quest_thesylphirantidote.enterWoods()" );
end

function quest_thesylphirantidote.enterWoods()
	local textWindow = DawnInterface.createTextWindow( true );
	textWindow:setPosition( PositionType.CENTER, 512, 382 );
	textWindow:setText( "The Sylphir woods." );
	textWindow:setAutocloseTime( 1300 );	
end

function quest_thesylphirantidote.speakWithJemma()
	if ( not quest_thesylphirantidote.completed )
	then 
		if ( quest_thesylphirantidote.added == nil )
		then 
			quest_thesylphirantidote.showJemmaText( 1 );
		elseif ( quest_thesylphirantidote.added == true and quest_thesylphirantidote.completed == false and quest_thesylphirantidote.gotInstructionFromJemma == false )
		then
			quest_thesylphirantidote.showJemmaText( 2 );
			quest_thesylphirantidote.gotInstructionFromJemma = true;
		elseif ( quest_thesylphirantidote.added == true and quest_thesylphirantidote.completed == false and quest_thesylphirantidote.gotInstrunctionFromJemma == true )
		then
			quest_thesylphirantidote.showJemmaText( 4 );
		end
	end 
end

function quest_thesylphirantidote.speakWithEffrey()
	if ( not quest_thesylphirantidote.completed )
	then
		if ( quest_thesylphirantidote.added == nil )
		then
			quest_thesylphirantidote.added = true;
			quest_thesylphirantidote.completed = false;
			quest_thesylphirantidote.gotReward = false;
			quest_thesylphirantidote.gotAntidote = false;
			quest_thesylphirantidote.gotInstructionFromJemma = false;
			DawnInterface.addQuest( "The Sylphir antidote", "Effrey Longback's daughter was bitten by a Sylphir spider. Search out Jemma the alchemist in the southern part of the Sylphir woods and obtain an antidote for Effrey." );
			quest_thesylphirantidote.showJeffreyText( 1 );
		elseif ( quest_thesylphirantidote.added == true and quest_thesylphirantidote.completed == false and quest_thesylphirantidote.gotAntidote == false )
		then
			quest_thesylphirantidote.showJeffreyText( 3 );
		elseif ( quest_thesylphirantidote.added == true and quest_thesylphirantidote.completed == false and quest_thesylphirantidote.gotAntidote == true )
		then
			quest_thesylphirantidote.showJeffreyText( 999 );
		end
	end
end

function quest_thesylphirantidote.showJeffreyText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "My daughter was bitten by a spider this morning. She is really sick and I am fearing the worst. I don't know if she went playing near the Sylphir woods... She knows it's forbidden! It's only getting worse and if I don't get an antidote to cure her I don't know what I will do. I have heard about an alchemist named Jemma in the southern part of the Sylphir woods. I would go myself but I cannot leave my little girl. You look like you could make it to Jemma's house unharmed." );
		textWindow:setAutocloseTime( 0 );
		textWindow:setOnCloseText( "quest_thesylphirantidote.showJeffreyText( 2 )" );
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Could you visit Jemma and bring me back an antidote? I'm no rich man, but I do have some pieces of equipment I could trade in return for the antidote. Please hurry!" );
		textWindow:setAutocloseTime( 0 );
	end
	if ( part == 3 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Please seek out Jemma down in the southern part of the Sylphir woods. My daugher is really sick!" );
		textWindow:setAutocloseTime( 0 );
	end
end

function quest_thesylphirantidote.showJemmaText( part )
	if ( part == 1 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "I am Jemma. Not many people dare to wander down here due to the spiders around. Don't you know these woods are dangerous? Sylphirs are growing stronger these days. Beware of the small ones. They may not look tough, but they can give you quite a bite..." );
		textWindow:setAutocloseTime( 7000 );
	end
	if ( part == 2 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "Someone got bitten? Well, you shouldn't wander out in the woods unless you are prepared to face off against those pesky spiders. Lucky for you I know just what you need... " );
		textWindow:setAutocloseTime( 0 );
		textWindow:setOnCloseText( "quest_thesylphirantidote.showJemmaText( 3 )" );
	end
	if ( part == 3 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "To make this antidote I will require five fangs from the small spiderlings. Also, three pristine spidersilks from the Webweavers. Bring me this and I have enough to make your antidote. We can discuss my fee when you return." );
		textWindow:setAutocloseTime( 0 );
	end
	if ( part == 4 )
	then
		local textWindow = DawnInterface.createTextWindow( true );
		textWindow:setPosition( PositionType.CENTER, 512, 382 );
		textWindow:setText( "How is the gathering coming along? Remember, I need spidersilks in pristine condition!" );
		textWindow:setAutocloseTime( 0 );
	end
end

-- init quest if this has not been done yet
if ( quest_thesylphirantidote.inited == nil )
then
	quest_thesylphirantidote.inited = true;
	quest_thesylphirantidote.init();
end


