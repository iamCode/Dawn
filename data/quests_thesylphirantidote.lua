-- init quest namespace so different quests / zones don't conflict in names
if ( quest_thesylphirantidote == nil )
then
	quest_thesylphirantidote = {}
end

function quest_thesylphirantidote.init()
	-- this quest is initialized from zone zone1
	--quest_thesylphirantidote.effreyLongback = DawnInterface.addMobSpawnPoint( "Human", -1510, 500, 1, 0 );
        --quest_thesylphirantidote.effreyLongback:setAttitude( Attitude.FRIENDLY );
        --quest_thesylphirantidote.effreyLongback:setWanderRadius(50);
        --quest_thesylphirantidote.effreyLongback:setName( "Effrey Longback" );

	--quest_thesylphirantidote.jemma = DawnInterface.addMobSpawnPoint( "Human", -2162, -4580, 1, 0 );
	--quest_thesylphirantidote.jemma:setAttitude( Attitude.FRIENDLY );
        --quest_thesylphirantidote.jemma:setWanderRadius(50);
	--quest_thesylphirantidote.jemma:setName( "Jemma" );
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

-- init quest if this has not been done yet
if ( quest_thesylphirantidote.inited == nil )
then
	quest_thesylphirantidote.inited = true;
	quest_thesylphirantidote.init();
end


