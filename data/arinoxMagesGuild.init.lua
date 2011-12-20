if ( arinoxMagesGuild == nil ) then
	arinoxMagesGuild = {};
	dofile("data/arinoxMagesGuild.spawnpoints.lua");
	arinoxMagesGuild.leavePoint = DawnInterface.addInteractionPoint();
	arinoxMagesGuild.leavePoint:setPosition( -160, -94, 80, 80 );
	arinoxMagesGuild.leavePoint:setBackgroundTexture( "data/transparent2x2pixel.tga" );
	arinoxMagesGuild.leavePoint:setInteractionType( InteractionType.Zone );
	arinoxMagesGuild.leavePoint:setInteractionCode( 'DawnInterface.enterZone( "data/zone1", 430, 2020 );\nDawnInterface.setSavingAllowed( true );' );

	arinoxMagesGuild.witch = DawnInterface.addMobSpawnPoint( "Witch", -344, 180, 1, 0 );
	arinoxMagesGuild.witch:setAttitude( Attitude.FRIENDLY );
	arinoxMagesGuild.witch:setName( "Clara Wickbrew" );
	arinoxMagesGuild.witchInteraction = DawnInterface.addCharacterInteractionPoint( arinoxMagesGuild.witch );
	arinoxMagesGuild.witchInteraction:setInteractionType( InteractionType.Quest );
	arinoxMagesGuild.witchInteraction:setInteractionCode( "arinoxMagesGuild.onActivate()" );
	--arinoxMagesGuild.traderShop = DawnInterface.addShop();
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["leynorscap"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["smallhealingpotion"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["bladeofstrength"] );
	--arinoxMagesGuild.traderShop:addItem( itemDatabase["bookofleatherskinrank2"] );
end

function arinoxMagesGuild.onEnterMap(x,y)
	local textWindow = DawnInterface.createTextWindow();
	textWindow:center();
	textWindow:setText( "Mages' Guild" );
	textWindow:setAutocloseTime( 1000 );
end

function arinoxMagesGuild.onActivate()
	--arinoxMagesGuild.traderShop:toggle()
	local textWindow = DawnInterface.createTextWindow();
	textWindow:setPosition( PositionType.CENTER, 512, 382 );
	textWindow:setAutocloseTime( 0 );
	textWindow:setText( "Where are my mushrooms? I've lost my mushrooms!" );
end
